.segment "DATA"

; program/process variables
build:              .byte BUILD                 ; Build number
running:			.byte 0                     ; 1 - IRQ Player is inserted, 0 - IRQ Player is not inserted
tempo:				.byte 0                     ; tempo in 60th per second cycles
voices:				.byte 0                     ; number of voices 0 - MAX        TO BE CHANGED to start from 1
repeat:				.byte 0                     ; 1 - repeat music after the end, 0 - exit after the finish
length:             .word 0                     ; length of music 
tempo_count:        .byte 0                     ; counter until next note starts
music_start: 		.word 0                     ; memory location where music data starts
music_pointer       = MUSIC_POINTER             ; pointer to current note in the music data is stored in the Zero Page
music_end:          .word 0                     ; music_start address + length precaluclated for speed


; voice static settings
wavepulse_setting:	.res MAX_VOICES,0
AD_setting:			.res MAX_VOICES,0
SR_setting:			.res MAX_VOICES,0
volume_setting:		.res MAX_VOICES,0
sustain_setting:	.res MAX_VOICES,0
continuous_setting: .res MAX_VOICES,0
LR_setting:         .res MAX_VOICES,0

; voice calculated settings
attack_duration:    .res MAX_VOICES,0			; counter for Attack duration
decay_duration:     .res MAX_VOICES,0			; counter for Decay duration
sustain_duration:   .res MAX_VOICES,0			; counter for Sustain duration - unless overriden by the note duration
release_duration:   .res MAX_VOICES,0			; counter for Release duration

max_vol_changeLo:	.res MAX_VOICES, 0			; volume change at each cycle to reach attack volume
max_vol_changeHi:	.res MAX_VOICES, 0
dec_vol_changeLo:	.res MAX_VOICES, 0			; volume change at each cycle to reach sustain volume
dec_vol_changeHi:	.res MAX_VOICES, 0
rel_vol_changeLo:	.res MAX_VOICES, 0			; volume change at each cycle from sustain to 0
rel_vol_changeHi:	.res MAX_VOICES, 0

; current note variables
phase:				.res MAX_VOICES,0			; 0 - not playing, 255 - Start, 1 - Attack, 2 - Decay, 3 - Sustain, 4 - Release
current_note:		.res MAX_VOICES,0			; Current note, if 0 there is no action, if 255 stop the sound
frequencyLo:		.res MAX_VOICES,0           ; current Frequency Low byte
frequencyHi:		.res MAX_VOICES,0           ; current Frequency Hi byte
volumeLo:			.res MAX_VOICES,0			; current Volume value Low byte
volumeHi:			.res MAX_VOICES,0			; current Volume value Hi byte

attack_count:       .res MAX_VOICES,0			; counter for Attack duration
decay_count:        .res MAX_VOICES,0			; counter for Decay duration
sustain_count:      .res MAX_VOICES,0			; counter for Sustain duration - unless overriden by the continuous voice setting
release_count:      .res MAX_VOICES,0			; counter for Release duration

; temp data buffer
data_store:         .res 4,0
