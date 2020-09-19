; Music Player for BASIC Programs
; Author:		Dusan Strakl
; More Info:	8BITCODING.COM
;
; System:		Commander X16
; Version:		Emulator R.37+
; Compiler:		CC65
; Build using:	cl65 -t cx16 Play.asm -C cx16-asm.cfg -o PLAY.PRG


.org $9000
.segment "CODE"

BUILD			= 1
MAX_VOICES		= 6
IRQ_VECTOR 		= $0314
OLD_IRQ_HANDLER = $30
MUSIC_POINTER 	= $32

;*******************************************************************************
; ENTRY SECTION
; ******************************************************************************
jmp Start								; configures and starts the music. Address to music structure is expected in r0
jmp Stop								; stops the music and removes the IRQ player
jmp GetInfo								; returns the address of the variables memory location in r0 and Instruments in r1


.include "x16.inc"
.include "Variables.inc"
.include "Tables.inc"
.include "IRQPlayer.asm"

; zero page temporary variable
divisor = $20     ;$59 used for hi-byte
dividend = $22	  ;$fc used for hi-byte
remainder = $24	  ;$fe used for hi-byte
result = dividend ;save memory by reusing divident to store the result

; ******************************************************************************
; START SECTION
; takes address to Music data structure and fills the variables for IRQ Play
; routine
; Structure:
; Header:
; Voices:
; Music:
; ******************************************************************************
Start:

; Process Header
	ldy #0								; Number of voices
	lda (r0),y
	sta voices

	iny									; music tempo
	lda (r0),y
	sta tempo

	iny									; length of music
	lda (r0),y
	sta length
	iny
	lda (r0),y
	sta length+1

	iny									; auto repeat - continuous play
	lda (r0),y
	sta repeat


	; add y to pointer
	iny
	sty data_store
	lda r0L
	clc 
	adc data_store
	sta r0L
	lda r0H
	adc #0
	sta r0H 
	ldy #0

; Process voices
	ldx #0

:	lda (r0)	
	asl
	asl
	asl
	tay
	lda Instruments,y
	sta wavepulse_setting,x
	iny
	lda Instruments,y
	sta AD_setting,x
	iny
	lda Instruments,y
	sta SR_setting,x 
	iny
	lda Instruments,y
	sta continuous_setting,x 
	iny
	lda Instruments,y
	sta volume_setting,x 
	iny
	lda Instruments,y
	sta sustain_setting,x 
	iny
	lda Instruments,y
	asl
	asl
	asl
	asl
	asl
	asl
	sta LR_setting,x 

	jsr Setup

	inc r0L
	bne :+
	inc r0H

:	inx
	cpx voices
	bcc :--

	; Prepare music pointers
	lda r0L
	sta music_start
	sta music_pointer
	lda r0H
	sta music_start+1
	sta music_pointer+1
	clc
	lda music_start
	adc length
	sta music_end
	lda music_start+1
	adc length+1
	sta music_end+1


	; Initialize counters before music starts
	lda #0
	sta tempo_count

	;sta DataIndex						; TEMPORARY HACK


; insert custom IRQ player
	lda running							; is IRQ player already running
	bne return

	sei									; if not inject the Player address
	lda IRQ_VECTOR
	sta OLD_IRQ_HANDLER
    lda #<Play
    sta IRQ_VECTOR
    lda IRQ_VECTOR+1
    sta OLD_IRQ_HANDLER+1
    lda #>Play
    sta IRQ_VECTOR+1
    cli
	lda #1
	sta running

return:

	rts


; ******************************************************************************
; SETUP VOICE SECTION
; X - Voice 0 - MAX_VOICES
; ******************************************************************************
Setup:
; Attack Phase
	lda AD_setting,x
	and #$F0 
	lsr
	lsr
	lsr
	lsr
	tay
	lda DelayLoops,y
	sta attack_duration,x

; Decay Phase
	lda AD_setting,x
	and #$0F 
	tay
	lda DelayLoops,y
	sta decay_duration,x

; Sustain Phase
	lda SR_setting,x
	and #$F0 
	lsr
	lsr
	lsr
	lsr
	tay
	lda DelayLoops,y
	sta sustain_duration,x

; Release phase
	lda SR_setting,x
	and #$0F 
	tay
	lda DelayLoops,y
	sta release_duration,x


; Calculate volume increases per cycle from 0 to Max Volume
; divide Volume change / number of loops to get volume step per loop
	stz dividend
	lda volume_setting,x
	sta dividend+1

	lda attack_duration,x
	sta divisor
	stz divisor+1

	jsr divide 

	lda result
	sta max_vol_changeLo,x
	lda result+1
	sta max_vol_changeHi,x


; Calculate volume decreases per cycle from Max Volume to Sustain volume
; divide Volume change / number of loops to get volume step per loop
	stz dividend
	sec
	lda volume_setting,x
	sbc sustain_setting,x
	sta dividend+1

	lda decay_duration,x
	sta divisor
	stz divisor+1

	jsr divide

	lda result
	sta dec_vol_changeLo,x
	lda result+1
	sta dec_vol_changeHi,x

; Calculate volume decreases per cycle from Sustain volume to 0
; divide Volume change / number of loops to get volume step per loop
	stz dividend
	lda sustain_setting,x
	sta dividend+1

	lda release_duration,x
	sta divisor
	stz divisor+1

	jsr divide

	lda result
	sta rel_vol_changeLo,x
	lda result+1
	sta rel_vol_changeHi,x

	rts


; ******************************************************************************
; STOP FUNCTION
; stops all the sounds and removes the IRQ player
; ******************************************************************************
Stop:
; Remove IRQ Player
	sei									; if not inject the Player address
	lda OLD_IRQ_HANDLER
    sta IRQ_VECTOR
    lda OLD_IRQ_HANDLER+1
    sta IRQ_VECTOR+1
    cli
	lda #0
	sta running

; Set volume to 0 for all voices
	ldx #0								; number of voices counter in x
:	VERA_SET_4X VOICE10VOL,1
	stz VERA_DATA0						; set volume to 0
	inx	
	cpx voices
	bcc :-

	rts

; ******************************************************************************
; GETINFO FUNCTION
; returns the address to Variables memory location in r0
; ******************************************************************************
GetInfo:
	lda #<build
	sta r0L
	lda #>build
	sta r0H

	lda #<Instruments
	sta r1L
	lda #>Instruments
	sta r1H

	rts
	

; ******************************************************************************
; UTILITY FUNCTIONS SECTION
; ******************************************************************************

; DIVIDE 16 bit NUMBERS
; For dividing volume change by number of loops we will do
; ******************************************************************************
divide:
	phx									; save X

	stz remainder						; preset reminder to 0
	stz remainder+1
	ldx #16								; repeat for each bit: ...

divloop:
	asl dividend						; dividend lb & hb*2, msb -> Carry
	rol dividend+1	
	rol remainder						; remainder lb & hb * 2 + msb from carry
	rol remainder+1
	lda remainder
	sec
	sbc divisor							; substract divisor to see if it fits in
	tay									; lb result -> Y, for we may need it later
	lda remainder+1
	sbc divisor+1
	bcc :+								; if carry=0 then divisor didn't fit in yet

	sta remainder+1						; else save substraction result as new remainder,
	sty remainder	
	inc result							; and INCrement result cause divisor fit in 1 times

:	dex
	bne divloop	

	plx
	rts
