F800:          org $f800
F800:          fcb  $a6, $cd
F802:          fcc "E34058702054019"

;F800: A6 CD    lda  (x+$CD)
;F802: 45       illegal
;F803: 33       pulb 
;F804: 34       des  
;F805: 30       tsx  
;F806: 35       txs  
;F807: 38       illegal
;F808: 37       pshb 
;F809: 30       tsx  
;F80A: 32       pula 
;F80B: 30       tsx  
;F80C: 35       txs  
;F80D: 34       des  
;F80E: 30       tsx  
;F80F: 31       ins  
;F810: 39       rts  

; subroutine to setup soft interrupt vectors / jump table
F811: CE F8 4A ldx  #$F84A
F814: FF 01 81 stx  $0181
F817: FF 01 84 stx  $0184
F81A: FF 01 87 stx  $0187
F81D: FF 01 8A stx  $018A
F820: FF 01 8D stx  $018D
F823: FF 01 90 stx  $0190
F826: FF 01 93 stx  $0193
F829: FF 01 9C stx  $019C
F82C: FF FF E8 stx  $FFE8
F82F: 86 7E    lda  #$7E
F831: C6 0A    ldb  #$0A
F833: CE 01 80 ldx  #$0180
F836: A7 00    sta  (x+$00)
F838: 08       inx  
F839: 08       inx  
F83A: 08       inx  
F83B: 5A       decb 
F83C: 26 F8    bne  $F836
F83E: 4F       clra 
F83F: B7 F7 C4 sta  $F7C4
F842: B6 F9 1E lda  $F91E
F845: B7 F7 D2 sta  $F7D2
F848: 0E       cli  
F849: 39       rts  
; dummy interrupt routine
F84A: 3B       rti

inits:
; MIC PIA init
F84B: 86 04    lda  #$04   
F84D: B7 F7 C5 sta  $F7C5 ; DDRA
F850: 86 02    lda  #$02
F852: B7 F7 C4 sta  $F7C4
F855: 7F F7 C5 clr  $F7C5 ; DDRA
F858: 86 7A    lda  #$7A
F85A: B7 F7 C4 sta  $F7C4 ; Port A = 0x7A
F85D: 86 3C    lda  #$3C
F85F: B7 F7 C5 sta  $F7C5 ; DDRA CA2=1
F862: 86 04    lda  #$04 
F864: B7 F7 C7 sta  $F7C7 ; DDRB
F867: 86 41    lda  #$41
F869: B7 F7 C6 sta  $F7C6
F86C: 7F F7 C7 clr  $F7C7 ; no DDRB
F86F: 86 7F    lda  #$7F
F871: B7 F7 C6 sta  $F7C6 ; Port B = 0x7F
F874: 86 04    lda  #$04
F876: B7 F7 C7 sta  $F7C7 ; DDRB
F879: 86 09    lda  #$09
F87B: B7 F7 C6 sta  $F7C6
F87E: F7 01 B1 stb  $01B1 ; b -- (CB1) --> 0x01b1

; TIA - ADLC init
F881: 86 C1    lda  #$C1
F883: B7 F7 20 sta  $F720
F886: 86 80    lda  #$80
F888: B7 F7 21 sta  $F721
F88B: 86 1F    lda  #$1F
F88D: B7 F7 23 sta  $F723
F890: 86 C0    lda  #$C0
F892: B7 F7 20 sta  $F720
F895: 4F       clra 
F896: B7 F7 21 sta  $F721
F899: 86 05    lda  #$05

; TIA - DMAC init
F89B: B7 F7 10 sta  $F710
F89E: 86 04    lda  #$04
F8A0: B7 F7 11 sta  $F711
F8A3: 4F       clra 
F8A4: B7 F7 14 sta  $F714
F8A7: B7 F7 15 sta  $F715
F8AA: B7 F7 16 sta  $F716

F8AD: 86 01    lda  #$01
F8AF: B7 F7 58 sta  $F758 ; ACA I PIA
F8B2: B7 F7 A9 sta  $F7A9 ; ACA II PIA
F8B5: B7 F7 59 sta  $F759 ; ACA I TIMER
F8B8: B7 F7 A9 sta  $F7A9 ; ACA II PIA
F8BB: 86 5B    lda  #$5B  
F8BD: B7 F7 60 sta  $F760 ; ACA I ACIA
F8C0: B7 F7 B0 sta  $F7B0 ; ACA II ACIA

F8C3: 86 5B    lda  #$5B  
F8C5: B7 F7 C0 sta  $F7C0 ; MIC KBD ACIA Master reset, 8E1S

F8C8: 5F       clrb 
F8C9: CE F9 0B ldx  #$F90B ; crtcinitvalues: start of table of CRTC init values

crtcinit:                             
F8CC: F7 F7 D8 stb  $F7D8  ; CRTC 
F8CF: A6 00    lda  (x+$00)
F8D1: B7 F7 D9 sta  $F7D9
F8D4: 08       inx  
F8D5: 5C       incb 
F8D6: C1 0F    cmpb #$0F
F8D8: 2F F2    ble  $F8CC ; crtcinit

 ; * 00 <=  99 [63] R0 - Horizontal Total
 ; * 01 <=  80 [50] R1 - Horizontal Displayed
 ; * 02 <=  88 [58] R2 - Horizontal Sync Position
 ; * 03 <=   6 [06] R3 - Sync Width
 ; * 04 <=  25 [19] R4 - Vertical Total
 ; * 05 <=  10 [0a] R5 - Vertical Total Adjust
 ; * 06 <=  25 [19] R6 - Vertical Displayed
 ; * 07 <=  25 [19] R7 - Vertical Sync Position
 ; * 08 <=   0 [00] R8 - Interlace & Skew
 ; * 09 <=  15 [0f] R9 - Maximum Raster Address
 ; * 0a <=  66 [42] R10 - Cursor Start Address
 ; * 0b <=  10 [0a] R11 - Cursor End Address
 ; * 0c <= 120 [78] R12 - Start Address (H)
 ; * 0d <=   0 [00] R13 - Start Address (L)
 ; * 0e <= 120 [78] R14 - Cursor (H)
 ; * 0f <=   0 [00] R15 - Cursor (L)

; DIA PIA init - PIA to control video circuitry
F8DA: 86 04    lda  #$04
F8DC: B7 F7 D1 sta  $F7D1 ; DDRA
F8DF: B6 F9 1D lda  $F91D ; use prommed config at 0xf91d
F8E2: B7 F7 D0 sta  $F7D0 
F8E5: 7F F7 D1 clr  $F7D1 ; no DDRA
F8E8: C6 FF    ldb  #$FF  ; 
F8EA: F7 F7 D0 stb  $F7D0 ; Port A = 0xFF
F8ED: 86 04    lda  #$04  
F8EF: B7 F7 D1 sta  $F7D1 ; DDRA
F8F2: B7 F7 D3 sta  $F7D3 ; DDRB
F8F5: B6 F9 1E lda  $F91E ; use prommed config at 0xf91d
F8F8: 84 EF    anda #$EF  ; make sure MSB is masked out
F8FA: B7 F7 D2 sta  $F7D2 ; DDRA = 0x00 & 0xEF == 0x00
F8FD: 7F F7 D3 clr  $F7D3 ; no DDRB
F900: F7 F7 D2 stb  $F7D2 ; DDRA = 0xFF
F903: 86 04    lda  #$04
F905: B7 F7 D3 sta  $F7D3 ; DDRB
F908: 7E FB 04 jmp  $FB04 ; in case of faulty RAM, *jump* back!

crtcinitvalues:
;F90B: 63 50 58 06 19 0A 19 19 00 0F 42 0A 78 00 78 00
              FCB  $63,$50,$58,$06,$19,$0A,$19,$19,$00,$0F,$42,$0A,$78,$00,$78,$00 

F91B: 7F 7F
F91D: 00 ; DDRA value for DIA PIA
F91E: 11 ; DDRB value for DIA PIA

F91F: CE FA B2 ldx  #$FAB2 ; address of interrupt routine
F922: FF 01 84 stx  $0184  ; soft interupt vector $0183
F925: 86 3F    lda  #$3F
F927: B7 F7 C5 sta  $F7C5  
F92A: CE 01 00 ldx  #$0100
F92D: DF 00    stx  $00
F92F: BD FA A7 jsr  $FAA7
F932: 86 FF    lda  #$FF
F934: B7 7F 80 sta  $7F80  ; Adress in display memory 
F937: CE 4C 4F ldx  #$4C4F ; Text LO
F93A: FF 7F 81 stx  $7F81  ; 
F93D: CE 41 44 ldx  #$4144 ; Text AD
F940: FF 7F 83 stx  $7F83  ; to put on the status line on the display (LOAD)
F943: BD FA 4C jsr  $FA4C
F946: F6 01 41 ldb  $0141
F949: 01       nop  
F94A: 01       nop  
F94B: 26 F6    bne  $F943
F94D: B6 01 43 lda  $0143
F950: 2C F1    bge  $F943
F952: F6 01 40 ldb  $0140
F955: F7 01 02 stb  $0102
F958: F6 01 42 ldb  $0142
F95B: F7 01 A1 stb  $01A1
F95E: BD FA 2F jsr  $FA2F
F961: BD FA 4C jsr  $FA4C
F964: DE 06    ldx  $06
F966: 8C 1A 00 cmpx #$1A00
F969: 2E 4A    bgt  $F9B5
F96B: DE 04    ldx  $04
F96D: E6 00    ldb  (x+$00)
F96F: F1 01 02 cmpb $0102
F972: 26 ED    bne  $F961
F974: A6 03    lda  (x+$03)
F976: 2C 09    bge  $F981
F978: BD FA A7 jsr  $FAA7
F97B: BD FA 2F jsr  $FA2F
F97E: 7E FA 1F jmp  $FA1F
F981: 84 BF    anda #$BF
F983: 81 05    cmpa #$05
F985: 26 2A    bne  $F9B1
F987: 86 49    lda  #$49
F989: B7 7F 86 sta  $7F86
F98C: B6 01 45 lda  $0145
F98F: B7 01 A0 sta  $01A0
F992: 7F 01 01 clr  $0101
F995: FE 01 4B ldx  $014B
F998: DF 04    stx  $04
F99A: FE 01 52 ldx  $0152
F99D: DF 06    stx  $06
F99F: CE 00 04 ldx  #$0004
F9A2: DF 02    stx  $02
F9A4: B6 01 42 lda  $0142
F9A7: B7 01 00 sta  $0100
F9AA: 86 07    lda  #$07
F9AC: BD FA 7D jsr  $FA7D
F9AF: 20 6E    bra  $FA1F
F9B1: 81 12    cmpa #$12
F9B3: 26 57    bne  $FA0C
F9B5: FE F7 06 ldx  $F706
F9B8: 27 10    beq  $F9CA
F9BA: 08       inx  
F9BB: 08       inx  
F9BC: 08       inx  
F9BD: 08       inx  
F9BE: 9C 06    cmpx $06
F9C0: 26 A9    bne  $F96B
F9C2: B6 01 03 lda  $0103
F9C5: BD FA 7D jsr  $FA7D
F9C8: 20 55    bra  $FA1F
F9CA: B6 01 A0 lda  $01A0
F9CD: 81 40    cmpa #$40
F9CF: 26 07    bne  $F9D8
F9D1: 86 0F    lda  #$0F
F9D3: BD FA 7D jsr  $FA7D
F9D6: 20 05    bra  $F9DD
F9D8: 86 10    lda  #$10
F9DA: BD FA 7D jsr  $FA7D
F9DD: C6 04    ldb  #$04
F9DF: CE 01 4E ldx  #$014E
F9E2: FF 01 A7 stx  $01A7
F9E5: FE 01 4B ldx  $014B
F9E8: FF 01 A9 stx  $01A9
F9EB: FE 01 A7 ldx  $01A7
F9EE: A6 00    lda  (x+$00)
F9F0: 08       inx  
F9F1: FF 01 A7 stx  $01A7
F9F4: FE 01 A9 ldx  $01A9
F9F7: A7 00    sta  (x+$00)
F9F9: 08       inx  
F9FA: FF 01 A9 stx  $01A9
F9FD: 5A       decb 
F9FE: 26 EB    bne  $F9EB
FA00: B6 01 A0 lda  $01A0
FA03: 81 40    cmpa #$40
FA05: 27 1B    beq  $FA22
FA07: BD FA A7 jsr  $FAA7
FA0A: 20 13    bra  $FA1F
FA0C: 81 01    cmpa #$01
FA0E: 26 0F    bne  $FA1F
FA10: CE 00 04 ldx  #$0004
FA13: DF 02    stx  $02
FA15: B6 01 42 lda  $0142
FA18: B7 01 00 sta  $0100
FA1B: 4F       clra 
FA1C: BD FA 7D jsr  $FA7D
FA1F: 7E F9 61 jmp  $F961
FA22: FE 01 49 ldx  $0149
FA25: FF 01 A5 stx  $01A5
FA28: F6 01 4D ldb  $014D
FA2B: F7 01 B0 stb  $01B0
FA2E: 39       rts  

; subroutine
FA2F: 86 50    lda  #$50
FA31: B7 7F 86 sta  $7F86
FA34: CE 00 05 ldx  #$0005
FA37: DF 02    stx  $02
FA39: B6 01 A1 lda  $01A1
FA3C: B7 01 00 sta  $0100
FA3F: 86 FF    lda  #$FF
FA41: B7 01 01 sta  $0101
FA44: B7 01 04 sta  $0104
FA47: 86 A0    lda  #$A0
FA49: 7E FA 7D jmp  $FA7D
; subroutine 
FA4C: CE 05 DC ldx  #$05DC
FA4F: FF 01 9E stx  $019E
FA52: DE 04    ldx  $04
FA54: FF F7 04 stx  $F704
FA57: DE 06    ldx  $06
FA59: FF F7 06 stx  $F706
FA5C: 7F 00 08 clr  $0008
FA5F: 86 02    lda  #$02
FA61: B7 F7 14 sta  $F714
FA64: CE FA DE ldx  #$FADE ; set new interrupt routine
FA67: FF 01 96 stx  $0196  ; in soft vector for TIA / ADLC
FA6A: 86 8A    lda  #$8A
FA6C: B7 F7 20 sta  $F720
FA6F: 96 08    lda  $08
FA71: 27 FC    beq  $FA6F
FA73: 85 02    bita #$02
FA75: 26 03    bne  $FA7A
FA77: 7E FF 9F jmp  $FF9F
FA7A: 7E FF 99 jmp  $FF99
; continue from FA49
FA7D: B7 01 03 sta  $0103
FA80: 7F 00 09 clr  $0009
FA83: DE 00    ldx  $00
FA85: FF F7 00 stx  $F700
FA88: DE 02    ldx  $02
FA8A: FF F7 02 stx  $F702
FA8D: 86 01    lda  #$01
FA8F: B7 F7 14 sta  $F714
FA92: CE FA C6 ldx  #$FAC6
FA95: FF 01 96 stx  $0196
FA98: 86 54    lda  #$54
FA9A: B7 F7 20 sta  $F720
FA9D: 86 80    lda  #$80
FA9F: B7 F7 21 sta  $F721
FAA2: 96 09    lda  $09
FAA4: 27 FC    beq  $FAA2
FAA6: 39       rts  
; subroutine 
FAA7: CE 01 40 ldx  #$0140
FAAA: DF 04    stx  $04
FAAC: CE 00 3F ldx  #$003F
FAAF: DF 06    stx  $06
FAB1: 39       rts  
; interrupt handler routine PIA
FAB2: B6 F7 C4 lda  $F7C4
FAB5: FE 01 9E ldx  $019E
FAB8: 27 0B    beq  $FAC5
FABA: 09       dex  
FABB: FF 01 9E stx  $019E
FABE: 26 05    bne  $FAC5
FAC0: 86 20    lda  #$20
FAC2: B7 7F 86 sta  $7F86
FAC5: 3B       rti  
; interrupt routine #1 ADLC / TIA
FAC6: F6 F7 20 ldb  $F720
FAC9: 86 40    lda  #$40
FACB: B7 F7 21 sta  $F721
FACE: B6 F7 20 lda  $F720
FAD1: 85 10    bita #$10
FAD3: 26 01    bne  $FAD6
FAD5: 3B       rti  
FAD6: D7 09    stb  $09
FAD8: 86 C0    lda  #$C0
FADA: B7 F7 20 sta  $F720
FADD: 3B       rti  
; interrupt routine #2 ADLC/TIA
FADE: B6 F7 21 lda  $F721
FAE1: 85 7A    bita #$7A
FAE3: 26 06    bne  $FAEB
FAE5: 86 20    lda  #$20
FAE7: B7 F7 21 sta  $F721
FAEA: 3B       rti  
FAEB: 84 7F    anda #$7F
FAED: 97 08    sta  $08
FAEF: 86 C0    lda  #$C0
FAF1: B7 F7 20 sta  $F720
FAF4: 3B       rti  
;


               fcb  $60, $10
               fdb  $01d8     ;value for the initial stack pointer
               fdb  $7800
FAF5: 60 10    neg  (x+$10)
FAF7: 01       nop  
FAF8: D8 78    eorb $78
FAFA: 00       illegal

; Exceution starts here
reset:
FAFB: F6 F7 C7 ldb  $F7C7 ; b <-- CB1
FAFE: BE FA F7 lds  $FAF7 ; Set stack
FB01: BD F8 4B jsr  $F84B ; inits()
FB04: B6 F7 C4 lda  $F7C4 ; Read MIC PIA port A
FB07: 84 04    anda #$04  ; Check if bit 2 is cleared
FB09: 26 18    bne  $FB23 ; or jump ahead

FB0B: B6 F7 FC lda  $F7FC ; Read panel
FB0E: 2A 13    bpl  $FB23 ; jump ahead if set
FB10: B6 01 B1 lda  $01B1 ; Check flag at 0x1B1
FB13: 2B 03    bmi  $FB18 ; Skip jump if set
FB15: 7E 80 00 jmp  $8000 ; Jump to code in RAM 8000
FB18: F6 01 B6 ldb  $01B6 ; Load flag from 0x1B6
FB1B: BD FB 72 jsr  $FB72 ; ---Do stuff
FB1E: 2C F5    bge  $FB15 ; Jump 8000 if true else 8003 in RAM
FB20: 7E 80 03 jmp  $8003 , Jump to code in RAM 8003

ahead:
FB23: B6 01 B1 lda  $01B1
FB26: 2B 2F    bmi  $FB57
FB28: CE FF FF ldx  #$FFFF
FB2B: 86 AA    lda  #$AA
FB2D: C6 55    ldb  #$55

; Fill RAM with test pattern
fillram:
FB2F: 08       inx  
FB30: A7 00    sta  (x+$00)
FB32: 08       inx  
FB33: E7 00    stb  (x+$00)
FB35: 8C 7F FF cmpx #$7FFF
FB38: 26 F5    bne  $FB2F fillram:

FB3A: CE 00 00 ldx  #$0000

; Check the test pattern
remtest:
FB3D: E6 00    ldb  (x+$00)
FB3F: C1 AA    cmpb #$AA
FB41: 26 07    bne  $FB4A
FB43: 08       inx  
FB44: E6 00    ldb  (x+$00)
FB46: C1 55    cmpb #$55
FB48: 27 03    beq  $FB4D
FB4A: 7E FB A7 jmp  $FBA7 ramerror:
FB4D: 08       inx  
FB4E: 8C 80 00 cmpx #$8000
FB51: 26 EA    bne  $FB3D ramtest:

FB53: C6 01    ldb  #$01
FB55: 20 07    bra  $FB5E

FB57: BD FB BF jsr  $FBBF
FB5A: B6 F7 C6 lda  $F7C6
FB5D: 5F       clrb 

FB5E: 7E FB EC jmp  $FBEC
FB61: F7 01 B1 stb  $01B1
FB64: BD FC 03 jsr  $FC03
FB67: BD F8 11 jsr  $F811 ; init soft interrupt vectors
FB6A: BD F9 1F jsr  $F91F ; type LOAD on screen and do stuff with TIA / ADLC
FB6D: FE 01 A5 ldx  $01A5
FB70: 6E 00    jmp  (x+$00)
FB72: 39       rts  
FB73: F6 F7 C4 ldb  $F7C4
FB76: F7 01 B6 stb  $01B6
FB79: BD FB 72 jsr  $FB72
FB7C: 2C 03    bge  $FB81
FB7E: 7E FA FE jmp  $FAFE
FB81: B6 01 A4 lda  $01A4
FB84: 81 80    cmpa #$80
FB86: 26 05    bne  $FB8D
FB88: FE 01 A2 ldx  $01A2
FB8B: 6E 00    jmp  (x+$00)
FB8D: B6 F7 C6 lda  $F7C6
FB90: BD FB 9B jsr  $FB9B
FB93: 27 03    beq  $FB98
FB95: 7E FF A5 jmp  $FFA5
FB98: 0E       cli  
FB99: 01       nop  
FB9A: 3B       rti  
FB9B: 84 01    anda #$01
FB9D: 26 06    bne  $FBA5
FB9F: B6 F7 C4 lda  $F7C4
FBA2: 84 01    anda #$01
FBA4: 39       rts  
FBA5: 4F       clra 
FBA6: 39       rts  

ramerror:
FBA7: 86 52    lda  #$52
FBA9: C6 45    ldb  #$45
FBAB: CE 7F 80 ldx  #$7F80
FBAE: A7 01    sta  (x+$01)
FBB0: E7 02    stb  (x+$02)
FBB2: 86 FF    lda  #$FF
FBB4: A7 00    sta  (x+$00)
FBB6: B6 F9 1E lda  $F91E
FBB9: B7 F7 D2 sta  $F7D2
FBBC: 20 FE    bra  $FBBC
FBBE: 39       rts
; 
FBBF: 7C 01 B4 inc  $01B4
FBC2: FE FA F5 ldx  $FAF5
FBC5: FF 01 A9 stx  $01A9
FBC8: FE FB E8 ldx  $FBE8
FBCB: FF 01 A7 stx  $01A7
FBCE: FE 01 A7 ldx  $01A7
FBD1: BC FB EA cmpx $FBEA
FBD4: 27 11    beq  $FBE7
FBD6: A6 00    lda  (x+$00)
FBD8: 08       inx  
FBD9: FF 01 A7 stx  $01A7
FBDC: FE 01 A9 ldx  $01A9
FBDF: A7 00    sta  (x+$00)
FBE1: 08       inx  
FBE2: FF 01 A9 stx  $01A9
FBE5: 20 E7    bra  $FBCE
FBE7: 39       rts  

      FDB      $0000
FBE8: 00       illegal
FBE9: 00       illegal
      FDB      $0800
FBEA: 08       inx  
FBEB: 00       illegal

; jumps here..
FBEC: 4F       clra 
FBED: CE 00 00 ldx  #$0000

FBF0: A7 00    sta  (x+$00)
FBF2: 08       inx  
FBF3: BC FA F5 cmpx $FAF5
FBF6: 26 03    bne  $FBFB
FBF8: CE 78 00 ldx  #$7800
FBFB: 8C 80 00 cmpx #$8000
FBFE: 26 F0    bne  $FBF0
FC00: 7E FB 61 jmp  $FB61

; subroutine 
FC03: CE F8 02 ldx  #$F802
FC06: FF 01 A9 stx  $01A9
FC09: CE 00 00 ldx  #$0000
FC0C: FF 01 AB stx  $01AB
FC0F: CE F8 00 ldx  #$F800
FC12: FF 01 A7 stx  $01A7
FC15: BD FC 23 jsr  $FC23
FC18: B6 01 B7 lda  $01B7
FC1B: 27 05    beq  $FC22
FC1D: 86 50    lda  #$50
FC1F: 7E FB A9 jmp  $FBA9
FC22: 39       rts  

; subroutine 
FC23: 7F 01 B8 clr  $01B8
FC26: 7F 01 B9 clr  $01B9
FC29: FE 01 A9 ldx  $01A9
FC2C: 86 F8    lda  #$F8
FC2E: B7 01 BA sta  $01BA
FC31: A6 00    lda  (x+$00)
FC33: 08       inx  
FC34: B7 01 BB sta  $01BB
FC37: 74 01 B9 lsr  $01B9
FC3A: 76 01 B8 ror  $01B8
FC3D: C6 00    ldb  #$00
FC3F: 59       rolb 
FC40: F8 01 BB eorb $01BB
FC43: C4 01    andb #$01
FC45: 27 0E    beq  $FC55
FC47: F8 01 B8 eorb $01B8
FC4A: F7 01 B8 stb  $01B8
FC4D: F6 01 B9 ldb  $01B9
FC50: C8 A0    eorb #$A0
FC52: F7 01 B9 stb  $01B9
FC55: 7C 01 BA inc  $01BA
FC58: 27 03    beq  $FC5D
FC5A: 44       lsra 
FC5B: 20 D7    bra  $FC34
FC5D: BC 01 AB cmpx $01AB
FC60: 26 CA    bne  $FC2C
FC62: FE 01 A7 ldx  $01A7
FC65: EE 00    ldx  (x+$00)
FC67: BC 01 B8 cmpx $01B8
FC6A: 27 03    beq  $FC6F
FC6C: 7C 01 B7 inc  $01B7
FC6F: 39       rts  


FC70: 16       tab  
FC71: A6 00    lda  (x+$00)
FC73: D7 1A    stb  $1A
FC75: C6 08    ldb  #$08
FC77: D7 1B    stb  $1B
FC79: 5F       clrb 
FC7A: 58       aslb 
FC7B: 49       rola 
FC7C: 24 04    bcc  $FC82
FC7E: DB 1A    addb $1A
FC80: 89 00    adca #$00
FC82: 7A 00 1B dec  $001B
FC85: 26 F3    bne  $FC7A
FC87: 20 45    bra  $FCCE
FC89: 97 19    sta  $19
FC8B: D7 1A    stb  $1A
FC8D: A6 00    lda  (x+$00)
FC8F: 97 1C    sta  $1C
FC91: 5F       clrb 
FC92: 20 26    bra  $FCBA
FC94: 16       tab  
FC95: EE 00    ldx  (x+$00)
FC97: 17       tba  
FC98: DF 19    stx  $19
FC9A: 97 1C    sta  $1C
FC9C: 5F       clrb 
FC9D: 20 1B    bra  $FCBA
FC9F: EE 00    ldx  (x+$00)
FCA1: 97 19    sta  $19
FCA3: D7 1A    stb  $1A
FCA5: DF 1B    stx  $1B
FCA7: 5F       clrb 
FCA8: 7D 00 1B tst  $001B
FCAB: 27 0D    beq  $FCBA
FCAD: 86 08    lda  #$08
FCAF: 58       aslb 
FCB0: 78 00 1B asl  $001B
FCB3: 24 02    bcc  $FCB7
FCB5: DB 1A    addb $1A
FCB7: 4A       deca 
FCB8: 26 F5    bne  $FCAF
FCBA: 86 08    lda  #$08
FCBC: 97 1B    sta  $1B
FCBE: 58       aslb 
FCBF: 49       rola 
FCC0: 78 00 1C asl  $001C
FCC3: 24 04    bcc  $FCC9
FCC5: DB 1A    addb $1A
FCC7: 99 19    adca $19
FCC9: 7A 00 1B dec  $001B
FCCC: 26 F0    bne  $FCBE
FCCE: 97 19    sta  $19
FCD0: D7 1A    stb  $1A
FCD2: DE 19    ldx  $19
FCD4: 39       rts  

; 
FCD5: 36       psha 
FCD6: 17       tba  
FCD7: 33       pulb 
FCD8: 20 08    bra  $FCE2
FCDA: 16       tab  
FCDB: A6 00    lda  (x+$00)
FCDD: 20 03    bra  $FCE2
FCDF: 17       tba  
FCE0: E6 00    ldb  (x+$00)
FCE2: 97 1C    sta  $1C
FCE4: 4F       clra 
FCE5: 97 1A    sta  $1A
FCE7: 5D       tstb 
FCE8: 26 01    bne  $FCEB
FCEA: 39       rts  
FCEB: 2B 04    bmi  $FCF1
FCED: 4C       inca 
FCEE: 58       aslb 
FCEF: 2A FC    bpl  $FCED
FCF1: 97 1F    sta  $1F
FCF3: 96 1C    lda  $1C
FCF5: 10       sba  
FCF6: 24 04    bcc  $FCFC
FCF8: 1B       aba  
FCF9: 0C       clc  
FCFA: 20 01    bra  $FCFD
FCFC: 0D       sec  
FCFD: 79 00 1A rol  $001A
FD00: 54       lsrb 
FD01: 7A 00 1F dec  $001F
FD04: 2A EF    bpl  $FCF5
FD06: D6 1A    ldb  $1A
FD08: 39       rts  

; 
FD09: EE 00    ldx  (x+$00)
FD0B: 97 1B    sta  $1B
FD0D: D7 1C    stb  $1C
FD0F: DF 1D    stx  $1D
FD11: 96 1D    lda  $1D
FD13: D6 1E    ldb  $1E
FD15: CE 00 1B ldx  #$001B
FD18: EE 00    ldx  (x+$00)
FD1A: 97 20    sta  $20
FD1C: 26 02    bne  $FD20
FD1E: 20 1B    bra  $FD3B
FD20: 2A 05    bpl  $FD27
FD22: 50       negb 
FD23: 25 01    bcs  $FD26
FD25: 4A       deca 
FD26: 43       coma 
FD27: 97 1D    sta  $1D
FD29: D7 1E    stb  $1E
FD2B: 5F       clrb 
FD2C: 20 1A    bra  $FD48
FD2E: 97 1B    sta  $1B
FD30: D7 1C    stb  $1C
FD32: A6 00    lda  (x+$00)
FD34: DE 1B    ldx  $1B
FD36: 20 04    bra  $FD3C
FD38: 16       tab  
FD39: EE 00    ldx  (x+$00)
FD3B: 17       tba  
FD3C: 97 1D    sta  $1D
FD3E: 26 01    bne  $FD41
FD40: 39       rts  
FD41: 5F       clrb 
FD42: D7 1E    stb  $1E
FD44: D7 20    stb  $20
FD46: C6 08    ldb  #$08
FD48: DF 1B    stx  $1B
FD4A: 4F       clra 
FD4B: 97 19    sta  $19
FD4D: 97 1A    sta  $1A
FD4F: 96 1D    lda  $1D
FD51: 2B 09    bmi  $FD5C
FD53: 5C       incb 
FD54: 78 00 1E asl  $001E
FD57: 49       rola 
FD58: 2A F9    bpl  $FD53
FD5A: 97 1D    sta  $1D
FD5C: D7 1F    stb  $1F
FD5E: 96 1B    lda  $1B
FD60: 16       tab  
FD61: D8 20    eorb $20
FD63: D7 20    stb  $20
FD65: D6 1C    ldb  $1C
FD67: 4D       tsta 
FD68: 2A 05    bpl  $FD6F
FD6A: 50       negb 
FD6B: 25 01    bcs  $FD6E
FD6D: 4A       deca 
FD6E: 43       coma 
FD6F: D0 1E    subb $1E
FD71: 92 1D    sbca $1D
FD73: 24 07    bcc  $FD7C
FD75: DB 1E    addb $1E
FD77: 99 1D    adca $1D
FD79: 0C       clc  
FD7A: 20 01    bra  $FD7D
FD7C: 0D       sec  
FD7D: 79 00 1A rol  $001A
FD80: 79 00 19 rol  $0019
FD83: 74 00 1D lsr  $001D
FD86: 76 00 1E ror  $001E
FD89: 7A 00 1F dec  $001F
FD8C: 2A E1    bpl  $FD6F
FD8E: 7D 00 20 tst  $0020
FD91: 2A 10    bpl  $FDA3
FD93: 50       negb 
FD94: 25 01    bcs  $FD97
FD96: 4A       deca 
FD97: 43       coma 
FD98: 70 00 1A neg  $001A
FD9B: 25 03    bcs  $FDA0
FD9D: 7A 00 19 dec  $0019
FDA0: 73 00 19 com  $0019
FDA3: DE 19    ldx  $19
FDA5: 39       rts  
FDA6: 16       tab  
FDA7: 4F       clra 
FDA8: 36       psha 
FDA9: 07       tpa  
FDAA: 0F       sei  
FDAB: 97 23    sta  $23
FDAD: 32       pula 
FDAE: DF 21    stx  $21
FDB0: DB 22    addb $22
FDB2: 99 21    adca $21
FDB4: D7 22    stb  $22
FDB6: 97 21    sta  $21
FDB8: DE 21    ldx  $21
FDBA: 36       psha 
FDBB: 96 23    lda  $23
FDBD: 06       tap  
FDBE: 32       pula 
FDBF: 39       rts  
FDC0: 37       pshb 
FDC1: 36       psha 
FDC2: 30       tsx  
FDC3: EE 00    ldx  (x+$00)
FDC5: 31       ins  
FDC6: 31       ins  
FDC7: 39       rts  
FDC8: 07       tpa  
FDC9: 0F       sei  
FDCA: DF 21    stx  $21
FDCC: D6 21    ldb  $21
FDCE: 37       pshb 
FDCF: D6 22    ldb  $22
FDD1: 06       tap  
FDD2: 32       pula 
FDD3: 39       rts  
FDD4: DF 19    stx  $19
FDD6: D7 1C    stb  $1C
FDD8: 97 1B    sta  $1B
FDDA: 36       psha 
FDDB: 96 19    lda  $19
FDDD: D6 1A    ldb  $1A
FDDF: 37       pshb 
FDE0: 36       psha 
FDE1: BD FE 9B jsr  $FE9B
FDE4: 30       tsx  
FDE5: A6 02    lda  (x+$02)
FDE7: 97 1B    sta  $1B
FDE9: EE 00    ldx  (x+$00)
FDEB: DF 19    stx  $19
FDED: DE 1F    ldx  $1F
FDEF: 09       dex  
FDF0: DF 1F    stx  $1F
FDF2: 26 ED    bne  $FDE1
FDF4: 31       ins  
FDF5: 31       ins  
FDF6: 31       ins  
FDF7: 39       rts  
FDF8: 7D 00 20 tst  $0020
FDFB: 27 0B    beq  $FE08
FDFD: E7 01    stb  (x+$01)
FDFF: A7 00    sta  (x+$00)
FE01: 08       inx  
FE02: 08       inx  
FE03: 7A 00 20 dec  $0020
FE06: 26 F5    bne  $FDFD
FE08: 7A 00 1F dec  $001F
FE0B: 2A F0    bpl  $FDFD
FE0D: 39       rts  

; 
FE0E: 97 1A    sta  $1A
FE10: 4F       clra 
FE11: D7 20    stb  $20
FE13: 97 1F    sta  $1F
FE15: D7 1C    stb  $1C
FE17: 97 1B    sta  $1B
FE19: DF 1D    stx  $1D
FE1B: 8D 49    bsr  $FE66
FE1D: DE 1D    ldx  $1D
FE1F: 8D 23    bsr  $FE44
FE21: DF 1D    stx  $1D
FE23: 20 15    bra  $FE3A
FE25: 4F       clra 
FE26: 20 0C    bra  $FE34
FE28: 97 20    sta  $20
FE2A: 4F       clra 
FE2B: 97 1F    sta  $1F
FE2D: 20 05    bra  $FE34
FE2F: 4F       clra 
FE30: D7 20    stb  $20
FE32: 97 1F    sta  $1F
FE34: 8D 20    bsr  $FE56
FE36: 8D 2E    bsr  $FE66
FE38: 8D 61    bsr  $FE9B
FE3A: DE 1F    ldx  $1F
FE3C: DF 1B    stx  $1B
FE3E: DE 1D    ldx  $1D
FE40: 86 20    lda  #$20
FE42: 97 1A    sta  $1A
FE44: 96 1A    lda  $1A
FE46: D6 1C    ldb  $1C
FE48: 27 06    beq  $FE50
FE4A: A7 00    sta  (x+$00)
FE4C: 08       inx  
FE4D: 5A       decb 
FE4E: 26 FA    bne  $FE4A
FE50: 7A 00 1B dec  $001B
FE53: 2A F5    bpl  $FE4A
FE55: 39       rts  
; subroutine 
FE56: 4D       tsta 
FE57: 2A 06    bpl  $FE5F
FE59: A6 00    lda  (x+$00)
FE5B: E6 01    ldb  (x+$01)
FE5D: 08       inx  
FE5E: 08       inx  
FE5F: DF 19    stx  $19
FE61: D7 1C    stb  $1C
FE63: 97 1B    sta  $1B
FE65: 39       rts 
; subroutine 
FE66: D6 20    ldb  $20
FE68: 96 1F    lda  $1F
FE6A: 2A 1E    bpl  $FE8A
FE6C: 84 7F    anda #$7F
FE6E: 97 1F    sta  $1F
FE70: D0 1C    subb $1C
FE72: 92 1B    sbca $1B
FE74: 24 04    bcc  $FE7A
FE76: DE 1F    ldx  $1F
FE78: DF 1B    stx  $1B
FE7A: DE 1D    ldx  $1D
FE7C: 96 1B    lda  $1B
FE7E: D6 1C    ldb  $1C
FE80: E7 01    stb  (x+$01)
FE82: A7 00    sta  (x+$00)
FE84: 08       inx  
FE85: 08       inx  
FE86: DF 1D    stx  $1D
FE88: 20 0A    bra  $FE94
FE8A: D0 1C    subb $1C
FE8C: 92 1B    sbca $1B
FE8E: 24 06    bcc  $FE96
FE90: DE 1F    ldx  $1F
FE92: DF 1B    stx  $1B
FE94: 4F       clra 
FE95: 5F       clrb 
FE96: D7 20    stb  $20
FE98: 97 1F    sta  $1F
FE9A: 39       rts

; subroutine 
FE9B: DE 1D    ldx  $1D
FE9D: D6 1C    ldb  $1C
FE9F: 7D 01 BC tst  $01BC
FEA2: 27 1A    beq  $FEBE
FEA4: 5D       tstb 
FEA5: 27 11    beq  $FEB8
FEA7: DE 19    ldx  $19
FEA9: A6 00    lda  (x+$00)
FEAB: 08       inx  
FEAC: DF 19    stx  $19
FEAE: DE 1D    ldx  $1D
FEB0: A7 00    sta  (x+$00)
FEB2: 08       inx  
FEB3: DF 1D    stx  $1D
FEB5: 5A       decb 
FEB6: 26 EF    bne  $FEA7
FEB8: 7A 00 1B dec  $001B
FEBB: 2A EA    bpl  $FEA7
FEBD: 39       rts  
FEBE: 5D       tstb 
FEBF: 27 16    beq  $FED7
FEC1: 07       tpa  
FEC2: 36       psha 
FEC3: 9F 1D    sts  $1D
FEC5: 0F       sei  
FEC6: 9E 19    lds  $19
FEC8: 34       des  
FEC9: 32       pula 
FECA: A7 00    sta  (x+$00)
FECC: 08       inx  
FECD: 5A       decb 
FECE: 26 F9    bne  $FEC9
FED0: 31       ins  
FED1: 9F 19    sts  $19
FED3: 9E 1D    lds  $1D
FED5: 32       pula 
FED6: 06       tap  
FED7: 7A 00 1B dec  $001B
FEDA: 2A E5    bpl  $FEC1
FEDC: DF 1D    stx  $1D
FEDE: 39       rts  
; 
FEDF: 97 1A    sta  $1A
FEE1: 4F       clra 
FEE2: D7 20    stb  $20
FEE4: 97 1F    sta  $1F
FEE6: D7 1C    stb  $1C
FEE8: 97 1B    sta  $1B
FEEA: DF 1D    stx  $1D
FEEC: BD FF 85 jsr  $FF85
FEEF: BD FF 72 jsr  $FF72
FEF2: DE 1D    ldx  $1D
FEF4: 96 1A    lda  $1A
FEF6: 8D 67    bsr  $FF5F
FEF8: 26 08    bne  $FF02
FEFA: D6 1B    ldb  $1B
FEFC: 2B 02    bmi  $FF00
FEFE: 20 50    bra  $FF50
FF00: 81 20    cmpa #$20
FF02: 39       rts 
; 
FF03: 4F       clra 
FF04: 20 0C    bra  $FF12
FF06: 97 20    sta  $20
FF08: 4F       clra 
FF09: 97 1F    sta  $1F
FF0B: 20 05    bra  $FF12
FF0D: 4F       clra 
FF0E: D7 20    stb  $20
FF10: 97 1F    sta  $1F
FF12: BD FE 56 jsr  $FE56
FF15: 8D 6E    bsr  $FF85
FF17: 8D 59    bsr  $FF72
FF19: D6 20    ldb  $20
FF1B: 27 13    beq  $FF30
FF1D: DE 1D    ldx  $1D
FF1F: A6 00    lda  (x+$00)
FF21: 08       inx  
FF22: DF 1D    stx  $1D
FF24: DE 19    ldx  $19
FF26: A1 00    cmpa (x+$00)
FF28: 26 25    bne  $FF4F
FF2A: 08       inx  
FF2B: DF 19    stx  $19
FF2D: 5A       decb 
FF2E: 26 ED    bne  $FF1D
FF30: 7A 00 1F dec  $001F
FF33: 2A E8    bpl  $FF1D
FF35: 96 1B    lda  $1B
FF37: 2B 17    bmi  $FF50
FF39: DE 1D    ldx  $1D
FF3B: D6 1C    ldb  $1C
FF3D: 27 0A    beq  $FF49
FF3F: A6 00    lda  (x+$00)
FF41: 81 20    cmpa #$20
FF43: 26 0A    bne  $FF4F
FF45: 08       inx  
FF46: 5A       decb 
FF47: 26 F6    bne  $FF3F
FF49: 7A 00 1B dec  $001B
FF4C: 2A F1    bpl  $FF3F
FF4E: 4F       clra 
FF4F: 39       rts  
FF50: 96 1B    lda  $1B
FF52: D6 1C    ldb  $1C
FF54: 50       negb 
FF55: 25 01    bcs  $FF58
FF57: 4A       deca 
FF58: 43       coma 
FF59: D7 20    stb  $20
FF5B: 97 1F    sta  $1F
FF5D: 86 20    lda  #$20
FF5F: D6 20    ldb  $20
FF61: 27 08    beq  $FF6B
FF63: A1 00    cmpa (x+$00)
FF65: 26 0A    bne  $FF71
FF67: 08       inx  
FF68: 5A       decb 
FF69: 26 F8    bne  $FF63
FF6B: 7A 00 1F dec  $001F
FF6E: 2A F3    bpl  $FF63
FF70: 5F       clrb 
FF71: 39       rts  
; 
FF72: 96 1F    lda  $1F
FF74: D6 20    ldb  $20
FF76: D0 1C    subb $1C
FF78: 92 1B    sbca $1B
FF7A: 25 04    bcs  $FF80
FF7C: DE 1B    ldx  $1B
FF7E: DF 1F    stx  $1F
FF80: D7 1C    stb  $1C
FF82: 97 1B    sta  $1B
FF84: 39       rts  
; 
FF85: 7D 00 1F tst  $001F
FF88: 2A 0E    bpl  $FF98
FF8A: DE 1D    ldx  $1D
FF8C: A6 00    lda  (x+$00)
FF8E: E6 01    ldb  (x+$01)
FF90: 08       inx  
FF91: 08       inx  
FF92: DF 1D    stx  $1D
FF94: D7 20    stb  $20
FF96: 97 1F    sta  $1F
FF98: 39       rts  
; subroutine 
FF99: 86 40    lda  #$40
FF9B: 4A       deca 
FF9C: 26 FD    bne  $FF9B
FF9E: 39       rts  
; subroutine 
FF9F: BD FA A7 jsr  $FAA7
FFA2: 7E FA 4C jmp  $FA4C
FFA5: FE 01 B2 ldx  $01B2
FFA8: 6E 00    jmp  (x+$00)
FFAA: 3B       rti  


FFAB: FF FF FF stx  $FFFF
FFAE: FF FF FF stx  $FFFF
FFB1: FF FF FF stx  $FFFF
FFB4: FF FF FF stx  $FFFF
FFB7: FF FF FF stx  $FFFF
FFBA: FF FF FF stx  $FFFF
FFBD: FF FF FF stx  $FFFF
FFC0: FF FF FF stx  $FFFF
FFC3: FF FF FF stx  $FFFF
FFC6: FF FF FF stx  $FFFF
FFC9: FF FF FF stx  $FFFF
FFCC: FF FF FF stx  $FFFF
FFCF: FF FF FF stx  $FFFF
FFD2: FF FF FF stx  $FFFF
FFD5: FF FF FF stx  $FFFF
FFD8: FF FF FF stx  $FFFF
FFDB: FF FF FF stx  $FFFF
FFDE: FF FF FF stx  $FFFF
FFE1: FF FF FF stx  $FFFF
FFE4: FF FF FF stx  $FFFF
;FFE7: 01       nop  
;FFE8: 01       nop  
;FFE9: 80 01    suba #$01
;FFEB: 83       illegal
;FFEC: 01       nop  
;FFED: 86 01    lda  #$01
;FFEF: 89 01    adca #$01
;FFF1: 8C 01 8F cmpx #$018F
;FFF4: 01       nop  
;FFF5: 92 01    sbca $01
;FFF7: 95 F8    bita $F8
;FFF9: 4A       deca 
;FFFA: 01       nop  
;FFFB: 9B FB    adda $FB
;FFFD: 73 FA FB com  $FAFB
               ORG  $FFE7
               FCB  $01
; soft interrupt vectors
               FDB  $0180
               FDB  $0183
               FDB  $0186
               FDB  $0189
               FDB  $018C
               FDB  $018F
               FDB  $0192
               FDB  $0195
; hard interrupt vectors               
               FDB  $F84A
               FDB  $019B
               FDB  $FB73
               FDB  $FAFB
