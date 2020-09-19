; Lookup Tables

.segment "DATA"

NoteToFreqHi:
.byte   0           ; 0 - No sound
.byte   0           ; 1 - C0
.byte   0           ; 2 - C#0
.byte   0           ; 3 - D0
.byte   0           ; 4 - D#0
.byte   0           ; 5 - E0
.byte   0           ; 6 - F0
.byte   0           ; 7 - F#0
.byte   0           ; 8 - G0
.byte   0           ; 9 - G#0
.byte   0           ; 10 - A0
.byte   0           ; 11 - A#0
.byte   0           ; 12 - B0
.byte   0           ; 13 - C1
.byte   0           ; 14 - C#1
.byte   0           ; 15 - D1
.byte   0           ; 16 - D#1
.byte   0           ; 17 - E1
.byte   0           ; 18 - F1
.byte   0           ; 19 - F#1
.byte   0           ; 20 - G1
.byte   0           ; 21 - G#1
.byte   0           ; 22 - A1
.byte   0           ; 23 - A#1
.byte   0           ; 24 - B1
.byte   0           ; 25 - C2
.byte   0           ; 26 - C#2
.byte   0           ; 27 - D2
.byte   0           ; 28 - D#2
.byte   0           ; 29 - E2
.byte   0           ; 30 - F2
.byte   0           ; 31 - F#2
.byte   1           ; 32 - G2
.byte   1           ; 33 - G#2
.byte   1           ; 34 - A2
.byte   1           ; 35 - A#2
.byte   1           ; 36 - B2
.byte   1           ; 37 - C3
.byte   1           ; 38 - C#3
.byte   1           ; 39 - D3
.byte   1           ; 40 - D#3
.byte   1           ; 41 - E3
.byte   1           ; 42 - F3
.byte   1           ; 43 - F#3
.byte   2           ; 44 - G3
.byte   2           ; 45 - G#3
.byte   2           ; 46 - A3
.byte   2           ; 47 - A#3
.byte   2           ; 48 - B3
.byte   2           ; 49 - C4
.byte   2           ; 50 - C#4
.byte   3           ; 51 - D4
.byte   3           ; 52 - D#4
.byte   3           ; 53 - E4
.byte   3           ; 54 - F4
.byte   3           ; 55 - F#4
.byte   4           ; 56 - G4
.byte   4           ; 57 - G#4
.byte   4           ; 58 - A4
.byte   4           ; 59 - A#4
.byte   5           ; 60 - B4
.byte   5           ; 61 - C5
.byte   5           ; 62 - C#5
.byte   6           ; 63 - D5
.byte   6           ; 64 - D#5
.byte   6           ; 65 - E5
.byte   7           ; 66 - F5
.byte   7           ; 67 - F#5
.byte   8           ; 68 - G5
.byte   8           ; 69 - G#5
.byte   9           ; 70 - A5
.byte   9           ; 71 - A#5
.byte   10          ; 72 - B5
.byte   10          ; 73 - C6
.byte   11          ; 74 - C#6
.byte   12          ; 75 - D6
.byte   13          ; 76 - D#6
.byte   13          ; 77 - E6
.byte   14          ; 78 - F6
.byte   15          ; 79 - F#6
.byte   16          ; 80 - G6
.byte   17          ; 81 - G#6
.byte   18          ; 82 - A6
.byte   19          ; 83 - A#6
.byte   20          ; 84 - B6
.byte   21          ; 85 - C7
.byte   23          ; 86 - C#7
.byte   24          ; 87 - D7
.byte   26          ; 88 - D#7
.byte   27          ; 89 - E7
.byte   29          ; 90 - F7
.byte   31          ; 91 - F#7
.byte   32          ; 92 - G7
.byte   34          ; 93 - G#7
.byte   36          ; 94 - A7
.byte   39          ; 95 - A#7
.byte   41          ; 96 - B7
.byte   43          ; 97 - C8
.byte   46          ; 98 - C#8
.byte   49          ; 99 - D8
.byte   52          ; 100 - D#8
.byte   55          ; 101 - E8
.byte   58          ; 102 - F8
.byte   62          ; 103 - F#8
.byte   65          ; 104 - G8
.byte   69          ; 105 - G#8
.byte   73          ; 106 - A8
.byte   78          ; 107 - A#8
.byte   82          ; 108 - B8

NoteToFreqLo:
.byte   0           ; 0 - No sound
.byte   44          ; 1 - C0
.byte   46          ; 2 - C#0
.byte   49          ; 3 - D0
.byte   52          ; 4 - D#0
.byte   55          ; 5 - E0
.byte   59          ; 6 - F0
.byte   62          ; 7 - F#0
.byte   66          ; 8 - G0
.byte   70          ; 9 - G#0
.byte   74          ; 10 - A0
.byte   78          ; 11 - A#0
.byte   83          ; 12 - B0
.byte   88          ; 13 - C1
.byte   93          ; 14 - C#1
.byte   99          ; 15 - D1
.byte   104         ; 16 - D#1
.byte   111         ; 17 - E1
.byte   117         ; 18 - F1
.byte   124         ; 19 - F#1
.byte   132         ; 20 - G1
.byte   139         ; 21 - G#1
.byte   148         ; 22 - A1
.byte   156         ; 23 - A#1
.byte   166         ; 24 - B1
.byte   176         ; 25 - C2
.byte   186         ; 26 - C#2
.byte   197         ; 27 - D2
.byte   209         ; 28 - D#2
.byte   221         ; 29 - E2
.byte   234         ; 30 - F2
.byte   248         ; 31 - F#2
.byte   7           ; 32 - G2
.byte   23          ; 33 - G#2
.byte   39          ; 34 - A2
.byte   57          ; 35 - A#2
.byte   75          ; 36 - B2
.byte   95          ; 37 - C3
.byte   116         ; 38 - C#3
.byte   138         ; 39 - D3
.byte   162         ; 40 - D#3
.byte   186         ; 41 - E3
.byte   213         ; 42 - F3
.byte   241         ; 43 - F#3
.byte   14          ; 44 - G3
.byte   45          ; 45 - G#3
.byte   79          ; 46 - A3
.byte   114         ; 47 - A#3
.byte   151         ; 48 - B3
.byte   190         ; 49 - C4
.byte   232         ; 40 - C#4
.byte   20          ; 51 - D4
.byte   67          ; 52 - D#4
.byte   117         ; 53 - E4
.byte   169         ; 54 - F4
.byte   225         ; 55 - F#4
.byte   28          ; 56 - G4
.byte   91          ; 57 - G#4
.byte   157         ; 58 - A4
.byte   227         ; 59 - A#4
.byte   46          ; 60 - B4
.byte   125         ; 61 - C5
.byte   208         ; 62 - C#5
.byte   41          ; 63 - D5
.byte   134         ; 64 - D#5
.byte   234         ; 65 - E5
.byte   83          ; 66 - F5
.byte   194         ; 67 - F#5
.byte   57          ; 68 - G5
.byte   182         ; 69 - G#5
.byte   58          ; 70 - A5
.byte   199         ; 71 - A#5
.byte   92          ; 72 - B5
.byte   249         ; 73 - C6
.byte   160         ; 74 - C#6
.byte   81          ; 75 - D6
.byte   13          ; 76 - D#6
.byte   211         ; 77 - E6
.byte   166         ; 78 - F6
.byte   133         ; 79 - F#6
.byte   113         ; 80 - G6
.byte   107         ; 81 - G#6
.byte   116         ; 82 - A6
.byte   141         ; 83 - A#6
.byte   183         ; 84 - B6
.byte   242         ; 85 - C7
.byte   64          ; 86 - C#7
.byte   162         ; 87 - D7
.byte   25          ; 88 - D#7
.byte   167         ; 89 - E7
.byte   76          ; 90 - F7
.byte   10          ; 91 - F#7
.byte   226         ; 92 - G7
.byte   215         ; 93 - G#7
.byte   233         ; 94 - A7
.byte   27          ; 95 - A#7
.byte   110         ; 96 - B7
.byte   229         ; 97 - C8
.byte   129         ; 98 - C#8
.byte   69          ; 99 - D8
.byte   51          ; 100 - D#8
.byte   77          ; 101 - E8
.byte   151         ; 102 - F8
.byte   19          ; 103 - F#8
.byte   196         ; 104 - G8
.byte   173         ; 105 - G#8
.byte   210         ; 106 - A8
.byte   54          ; 107 - A#8
.byte   220         ; 108 - B8

DelayLoops:
.byte   0           ; 0 - 0 ms
.byte   1           ; 1 - 16.67 ms
.byte   2           ; 2 - 33.33 ms
.byte   3           ; 3 - 50 ms
.byte   4           ; 4 - 66.67 ms
.byte   5           ; 5 - 83.33 ms
.byte   7           ; 6 - 116.67 ms
.byte   10          ; 7 - 166.67 ms
.byte   12          ; 8 - 200 ms
.byte   15          ; 9 - 250 ms
.byte   20          ; 10 - 333.33 ms
.byte   30          ; 11 - 500 ms
.byte   40          ; 12 - 0.67 s
.byte   60          ; 13 - 1 s
.byte   90			; 14 - 1.5 s
.byte   120         ; 15 - 2 s


Instruments:
; Instrument 0 - Piano
.byte   %10000000   ; wave + pulse
.byte   $22         ; AD
.byte   $0E         ; SR
.byte   0           ; not continuous
.byte   63          ; max volume
.byte   63          ; sustain volume
.byte   3           ; LR
.byte   0           ; empty

; Instrument 1 - Organ
.byte   %10000000   ; wave + pulse
.byte   $10         ; AD
.byte   $F3         ; SR
.byte   1           ; continuous
.byte   63          ; max volume
.byte   63          ; sustain volume
.byte   3           ; LR
.byte   0           ; empty

; Instrument 2 - Violin
.byte   %01000000   ; wave + pulse
.byte   $10         ; AD
.byte   $F5         ; SR
.byte   1           ; continuous
.byte   63          ; max volume
.byte   60          ; sustain volume
.byte   3           ; LR
.byte   0           ; empty

; Instrument 3 - Trumpet
.byte   %00111111   ; wave + pulse
.byte   $10         ; AD
.byte   $F5         ; SR
.byte   1           ; continuous
.byte   63          ; max volume
.byte   60          ; sustain volume
.byte   3           ; LR
.byte   0           ; empty

; Instrument 4 - Percussion
.byte   %11000000   ; wave + pulse
.byte   $03         ; AD
.byte   $1A         ; SR
.byte   0           ; not continuous
.byte   63          ; max volume
.byte   50          ; sustain volume
.byte   3           ; LR
.byte   0           ; empty


; Instrument 5 - Guitar
.byte   %00011111   ; wave + pulse
.byte   $01         ; AD
.byte   $5E         ; SR
.byte   0           ; not continuous
.byte   63          ; max volume
.byte   50          ; sustain volume
.byte   3           ; LR
.byte   0           ; empty


; Instrument 6 - Custom
.res 8,0

; Instrument 7 - Custom
.res 8,0
