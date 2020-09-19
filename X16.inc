; I/O Registers
VERA_LOW	= $9F20
VERA_MID	= $9F21
VERA_HIGH	= $9F22
VERA_DATA0	= $9F23
VERA_CTRL	= $9F25

; Programmable Sound Generator (PSG)
VOICE0		= $1F9C0
VOICE10		= $1F9E8
VOICE10VOL	= VOICE10+2


; IRQs
IRQVec		= $0314

; 
r0			= $02
r0L			= r0
r0H			= r0+1
r1			= $04
r1L			= r1
r1H			= r1+1


;   Macros

.macro VERA_SET_ADDR addr, increment
	.ifnblank increment
      .if increment < 0
         lda #((^addr) | $08 | ((0-increment) << 4))
      .else
         lda #((^addr) | (increment << 4))
      .endif
	.else
		lda #(^addr) | $10
	.endif

	sta VERA_HIGH
	lda #(>addr)
	sta VERA_MID
	lda #(<addr)
	sta VERA_LOW
.endmacro

.macro VERA_SET_4X addr, increment
	stz VERA_CTRL
    lda #((^addr) | (increment << 4))
	sta VERA_HIGH
	clc
	txa									; add X
	rol									; multiply by 4
	rol
	adc #(<addr)
	sta VERA_LOW
	lda #0
	adc #(>addr)
	sta VERA_MID
.endmacro
