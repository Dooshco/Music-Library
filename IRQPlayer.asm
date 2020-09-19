; ******************************************************************************
; PLAY SECTION
; ******************************************************************************
Play:

	lda $9F27
    and #$01
    beq irq_exit

	; sava VERA registers
	lda $9F20
	sta data_store
	lda $9F21
	sta data_store+1
	lda $9F22
	sta data_store+2
	lda $9F25
	sta data_store+3

Play_song:
; ******************************************************************************

	lda tempo_count
	bne play_existing


	lda tempo							; reset tempo counter
	sta tempo_count

	; read music and store
	ldx #0								; start new note
:	txa
	tay
	lda (music_pointer),y
	sta current_note,x
	cmp #0
	beq skip_note

	jsr Start_note

skip_note:
	inx	
	cpx voices
	bcc :-

	; update music_pointer
	clc
	lda music_pointer
	adc voices
	sta music_pointer
	lda music_pointer+1
	adc #0
	sta music_pointer+1

	; check if we are at the end > music_pointer >= music_end
	lda music_pointer+1
	cmp music_end+1
	bcc play_existing					; not at the end yet
	lda music_pointer
	cmp music_end
	bcc play_existing					; still not there

	lda repeat							; we are at the end
	bne start_over						; autorepeat is ON

	jsr Stop 							; autorepeat is OFF
	jmp (IRQ_VECTOR)

start_over:
	lda music_start						; reset the music pointers
	sta music_pointer
	lda music_start+1
	sta music_pointer+1


play_existing:
 	dec tempo_count
	ldx #0
: 	jsr Play_note
	inx
	cpx voices
	bcc :-

irq_exit:

	; restore VERA registers
	lda data_store
	sta $9F20
	lda data_store+1
	sta $9F21
	lda data_store+2
	sta $9F22
	lda data_store+3
	sta $9F25


	jmp (OLD_IRQ_HANDLER)


Play_note:
; ******************************************************************************

	lda phase,x
	cmp #0								; if phase = 0 - Exit
	bne :+
	jmp exit

:	cmp #1								; if phase = 1 - Attack
	bne :+
	jmp attack

:	cmp #2								; if phase = 2 - Decay
	bne :+
	jmp decay

:	cmp #3								; if phase = 3 - Sustain
	bne :+
	jmp sustain

:	cmp #4								; if phase = 4 - Release
	bne :+
	jmp release

:	lda #1								; else phase = 255 - Start
	sta phase,x


	VERA_SET_4X VOICE10,1

	lda frequencyLo,x 					; read and set frequency
	sta VERA_DATA0
	lda frequencyHi,x
	sta VERA_DATA0

	stz VERA_DATA0						; starting Volume  = 0
	lda wavepulse_setting,x
	sta VERA_DATA0


; ATTACK PHASE
; ******************************************************************************
attack:

	lda attack_count,x
	bne attack_loop						; not finished yet

    VERA_SET_4X VOICE10VOL,1

	stz volumeLo
    lda volume_setting,x
	sta volumeHi
	ora LR_setting,x
    sta VERA_DATA0						; max volume at the end of Attack phase

	lda #2								; attack finished, move to decay
	sta phase,x
    jmp decay

attack_loop:

    clc									; increase 16 bit Volume
	lda volumeLo,x
	adc max_vol_changeLo,x
	sta volumeLo,x
	lda volumeHi,x
	adc max_vol_changeHi,x
	sta volumeHi,x

	VERA_SET_4X VOICE10VOL,1

    lda volumeHi,x
	ora LR_setting,x
    sta VERA_DATA0						; play at current volume

	dec attack_count,x
	jmp exit

; DECAY PHASE
; ******************************************************************************
decay:

	lda decay_count,x
	bne decay_loop						; not finished yet

    VERA_SET_4X VOICE10VOL,1

	stz volumeLo,x
    lda sustain_setting,x
	sta volumeHi,x
	ora LR_setting,x
    sta VERA_DATA0						; sustain volume at the end of Decay phase

	lda #3								; decay finished, move to sustain
	sta phase,x
    jmp sustain

decay_loop:

    sec									; decrease 16 bit Volume
	lda volumeLo,x
	sbc dec_vol_changeLo,x
	sta volumeLo,x
	lda volumeHi,x
	sbc dec_vol_changeHi,x
	sta volumeHi,x

    VERA_SET_4X VOICE10VOL,1

	lda volumeHi,x
	ora LR_setting,x
    sta VERA_DATA0						; play at current volume

	dec decay_count,x
	jmp exit

; SUSTAIN PHASE
; ******************************************************************************
sustain:

	lda sustain_count,x
	bne sustain_loop					; not finished yet

    VERA_SET_4X VOICE10VOL,1

	stz volumeLo,x
    lda sustain_setting,x
	sta volumeHi,x
	ora LR_setting,x
    sta VERA_DATA0						; sustain volume at the end of Sustain phase (redundant)

	lda #4								; sustain finished, move to release
	sta phase,x
    jmp release

sustain_loop:

	dec sustain_count,x
	jmp exit


; RELEASE PHASE
; ******************************************************************************
release:

	lda release_count,x
	bne release_loop					; not finished yet

	VERA_SET_4X VOICE10VOL,1

	stz volumeLo,x
	stz volumeHi,x
	stz VERA_DATA0						; set volume to 0 at the end of Release phase

	stz phase,x							; release finished, exit
    jmp exit

release_loop:

    sec									; decrease 16 bit volume
	lda volumeLo,x
	sbc rel_vol_changeLo,x
	sta volumeLo,x
	lda volumeHi,x
	sbc rel_vol_changeHi,x
	sta volumeHi,x

    VERA_SET_4X VOICE10VOL,1

    lda volumeHi,x
	ora LR_setting,x
    sta VERA_DATA0						; plat at current Volume

	dec release_count,x

exit:
rts


Start_note:
	stz volumeLo,x
	stz volumeHi,x

	lda attack_duration,x
	sta attack_count,x
	lda decay_duration,x
	sta decay_count,x
	lda sustain_duration,x
	sta sustain_count,x
	lda release_duration,x
	sta release_count,x

	; calculate and set frequencey
	ldy current_note,x
	lda NoteToFreqLo,y            ; Frequency Lo
	sta frequencyLo,x
	lda NoteToFreqHi,y            ; Frequency Hi
	sta frequencyHi,x

	lda #255
	sta phase,x

	rts
