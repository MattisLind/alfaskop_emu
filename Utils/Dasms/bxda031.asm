0600: 7E 35 00 jmp  $3500
               org  $0603
               fcb  $05
               fdb  $0000

0606: 33       pulb 
0607: 3B       rti  
0608: 2A 37    bpl  $0641
               org  $060A
               fdb  $0000

060C: 00       illegal
060D: 00       illegal
060E: 00       illegal
060F: 00       illegal
0610: 00       illegal
0611: 00       illegal
0612: 00       illegal
0613: 00       illegal
               org  $614
               fcb  $00, $ff
               fcc "*EM*                                                                           "
               org  $0665
               fcb  $ff

               org  $0667
               fdb  $0918
               
0666: 00 09 stx  $0009
0668: 18       illegal
0669: 00       illegal
066A: 7E 06 6A jmp  $066A
066D: 01       nop  
066E: 00       illegal
066F: 06       tap  
0670: 87 00    sta  #$00
0672: 00       illegal
0673: 00       illegal
0674: 00       illegal
0675: 00       illegal
0676: 00       illegal
0677: 00       illegal
0678: 00       illegal
0679: 00       illegal
067A: 00       illegal
067B: 00       illegal
067C: 00       illegal
067D: 00       illegal
067E: 00       illegal
067F: 00       illegal
0680: 00       illegal
0681: 00       illegal
0682: 00       illegal
0683: 00       illegal
0684: 00       illegal
0685: 00       illegal
0686: 00       illegal
0687: 00       illegal
0688: 00       illegal
0689: 00       illegal
068A: 00       illegal
068B: 00       illegal
068C: 00       illegal
068D: 06       tap  
068E: 6A 00    dec  (x+$00)

               org  $068F
               fdb  $0000

0690: 00       illegal
0691: 00       illegal
0692: 00       illegal
0693: 01       nop  
0694: E0 06    subb (x+$06)
0696: D7 06    stb  $06
0698: 69 00    rol  (x+$00)
069A: 00       illegal
069B: 00       illegal
069C: 00       illegal
069D: 00       illegal
069E: 00       illegal
069F: 00       illegal
06A0: 00       illegal
06A1: 00       illegal
06A2: 00       illegal
06A3: 00       illegal
06A4: 00       illegal
06A5: 00       illegal
06A6: 00       illegal
06A7: 00       illegal
06A8: 00       illegal
06A9: 00       illegal
06AA: 00       illegal
06AB: 00       illegal
06AC: 00       illegal
06AD: 00       illegal
06AE: 00       illegal
06AF: 00       illegal
06B0: 00       illegal
06B1: 00       illegal
06B2: 00       illegal
06B3: 00       illegal
06B4: 00       illegal
06B5: 00       illegal
06B6: 00       illegal
06B7: 00       illegal
06B8: 00       illegal
06B9: 00       illegal
06BA: 00       illegal
06BB: 00       illegal
06BC: 00       illegal
06BD: 00       illegal
06BE: 00       illegal
06BF: 00       illegal
06C0: 00       illegal
06C1: 00       illegal
06C2: 00       illegal
06C3: 00       illegal
06C4: 00       illegal
06C5: 00       illegal
06C6: 00       illegal
06C7: 00       illegal
06C8: 00       illegal
06C9: 00       illegal
06CA: 00       illegal
06CB: 00       illegal
06CC: 00       illegal
06CD: 00       illegal
06CE: 00       illegal
06CF: 00       illegal
06D0: 00       illegal
06D1: 00       illegal
06D2: 00       illegal
06D3: C0 FE    subb #$FE
06D5: 20 32    bra  $0709
06D7: EA C0    orb  (x+$C0)
06D9: 00       illegal
06DA: 0E       cli  
06DB: 23 88    bls  $0665
06DD: 36       psha 
06DE: 4D       tsta

               org  $6df
               fcb  $00, $ff
               fcc  "*OS*"
               fcb  $80
               
06DF: 00       illegal
06E0: FF 2A 4F stx  $2A4F
06E3: 53       comb 
06E4: 2A 80    bpl  $0666
06E6: 20 20    bra  $0708
06E8: 20 20    bra  $070A
06EA: 20 20    bra  $070C
06EC: 20 20    bra  $070E
06EE: 20 20    bra  $0710
06F0: 20 20    bra  $0712
06F2: 20 20    bra  $0714
06F4: 20 20    bra  $0716
06F6: 20 20    bra  $0718
06F8: 20 20    bra  $071A
06FA: 20 20    bra  $071C
06FC: 20 20    bra  $071E
06FE: 20 20    bra  $0720
0700: 20 20    bra  $0722
0702: 20 20    bra  $0724
0704: 20 20    bra  $0726
0706: 20 20    bra  $0728
0708: 20 20    bra  $072A
070A: 20 20    bra  $072C
070C: 20 20    bra  $072E
070E: 20 20    bra  $0730
0710: 20 20    bra  $0732
0712: 20 20    bra  $0734
0714: 20 20    bra  $0736
0716: 20 20    bra  $0738
0718: 20 20    bra  $073A
071A: 20 20    bra  $073C
071C: 20 20    bra  $073E
071E: 20 20    bra  $0740
0720: 80 20    suba #$20
0722: 20 20    bra  $0744
0724: 20 20    bra  $0746
0726: 20 20    bra  $0748
0728: 20 20    bra  $074A
072A: 20 20    bra  $074C
072C: 20 20    bra  $074E
072E: 20 A0    bra  $06D0

               org  $730
               fcc  "DISK FAILURE. ERROR NUMBER = XX. W A I T ."
               
               org  $75A
               fdb  $0000
075A: 00       illegal
075B: 00       illegal
075C: 00       illegal
075D: 00       illegal
075E: 00       illegal
075F: 00       illegal
0760: 00       illegal
0761: 00       illegal
0762: 00       illegal
0763: 00       illegal
0764: 00       illegal
0765: 00       illegal
0766: 10       sba  
0767: 00       illegal
0768: 00       illegal
0769: 00       illegal
076A: 00       illegal
076B: 00       illegal
076C: 00       illegal
076D: 00       illegal
076E: 07       tpa  
076F: 5C       incb 
0770: 20 00    bra  $0772
0772: 00       illegal
0773: 00       illegal
0774: 00       illegal
0775: 00       illegal
0776: 00       illegal
0777: 00       illegal
0778: 07       tpa  
0779: 66 30    ror  (x+$30)
077B: 00       illegal
077C: 00       illegal
077D: 00       illegal
077E: 00       illegal
077F: 00       illegal
0780: 00       illegal
0781: 00       illegal
0782: 07       tpa  
0783: 70 40 00 neg  $4000
0786: 00       illegal
0787: 00       illegal
0788: 00       illegal
0789: 00       illegal
078A: 00       illegal
078B: 00       illegal
078C: 07       tpa  
078D: 7A 50 00 dec  $5000
0790: 00       illegal
0791: 00       illegal
0792: 00       illegal
0793: 00       illegal
0794: 00       illegal
0795: 00       illegal
0796: 07       tpa  
0797: 84 60    anda #$60
0799: 00       illegal
079A: 00       illegal
079B: 00       illegal
079C: 00       illegal
079D: 00       illegal
079E: 00       illegal
079F: 00       illegal
07A0: 07       tpa  
07A1: 8E 70 00 lds  #$7000
07A4: 00       illegal
07A5: 00       illegal
07A6: 00       illegal
07A7: 00       illegal
07A8: 00       illegal
07A9: 00       illegal
07AA: 07       tpa  
07AB: 98 80    eora $80
07AD: 00       illegal
07AE: 00       illegal
07AF: 00       illegal
07B0: 00       illegal
07B1: 00       illegal
07B2: 00       illegal
07B3: 00       illegal
07B4: 07       tpa  
07B5: A2 90    sbca (x+$90)
07B7: 00       illegal
07B8: 00       illegal
07B9: 00       illegal
07BA: 00       illegal
07BB: 00       illegal
07BC: 00       illegal
07BD: 00       illegal
07BE: 07       tpa  
07BF: AC A0    cmpx (x+$A0)
07C1: 00       illegal
07C2: 00       illegal
07C3: 00       illegal
07C4: 00       illegal
07C5: 00       illegal
07C6: 00       illegal
07C7: 00       illegal
07C8: 07       tpa  
07C9: B6 B0 00 lda  $B000
07CC: 00       illegal
07CD: 00       illegal
07CE: 00       illegal
07CF: 00       illegal
07D0: 00       illegal
07D1: 00       illegal
07D2: 07       tpa  
07D3: C0 C0    subb #$C0
07D5: 00       illegal
07D6: 00       illegal
07D7: 00       illegal
07D8: 00       illegal
07D9: 00       illegal
07DA: 00       illegal
07DB: 00       illegal
07DC: 07       tpa  
07DD: CA D0    orb  #$D0
07DF: 00       illegal
07E0: 00       illegal
07E1: 00       illegal
07E2: 00       illegal
07E3: 00       illegal
07E4: 00       illegal
07E5: 00       illegal
07E6: 07       tpa  
07E7: D4 E0    andb $E0
07E9: 00       illegal
07EA: 00       illegal
07EB: 00       illegal
07EC: 00       illegal
07ED: 00       illegal
07EE: 00       illegal
07EF: 00       illegal
07F0: 00       illegal
07F1: 00       illegal
07F2: 07       tpa  
07F3: DE 00    ldx  $00
07F5: 00       illegal
07F6: 00       illegal
07F7: 00       illegal
07F8: 00       illegal
07F9: 00       illegal
07FA: 00       illegal
07FB: 00       illegal
07FC: 00       illegal
07FD: 00       illegal
07FE: 00       illegal
07FF: 00       illegal
0800: 7E 0F F6 jmp  $0FF6
0803: 7E 1B 4A jmp  $1B4A
0806: 7E 0F 3A jmp  $0F3A
0809: 7E 1B C7 jmp  $1BC7
080C: 7E 22 71 jmp  $2271
080F: 7E 22 AC jmp  $22AC
0812: 7E 22 BA jmp  $22BA
0815: 7E 22 C5 jmp  $22C5
0818: 7E 22 E3 jmp  $22E3
081B: 7E 22 F1 jmp  $22F1
081E: 7E 22 FF jmp  $22FF
0821: 7E 23 2A jmp  $232A
0824: 7E 23 82 jmp  $2382
0827: 7E 24 1B jmp  $241B
082A: 7E 24 67 jmp  $2467
082D: 7E 0A A0 jmp  $0AA0
0830: 7E 25 5A jmp  $255A
0833: 7E 32 90 jmp  $3290
0836: 7E 32 A7 jmp  $32A7
0839: 7E 32 ED jmp  $32ED
083C: 7E 33 18 jmp  $3318
083F: 7E 32 F5 jmp  $32F5
0842: 7E 33 B6 jmp  $33B6
0845: 7E 34 64 jmp  $3464
0848: 7E 34 6F jmp  $346F
084B: 7E 34 6E jmp  $346E
084E: 7E 34 67 jmp  $3467
0851: 7E 24 36 jmp  $2436
0854: 7E 08 54 jmp  $0854
0857: 7E 08 57 jmp  $0857

; indirection table for SWI
               fdb  $30E1  ; $00 - Used
               fdb  $3152  ; $02 
               fdb  $315D  ; $04
               fdb  $3178  ; $06 - Used
               fdb  $31FF  ; $08
               fdb  $320D  ; $0A
               fdb  $3212  ; $0C
               fdb  $2C72  ; $0E - Used
               fdb  $2BEE  ; $10 - Used
               fdb  $2DDC  ; $12 - Used
               fdb  $37E3  ; $14
               fdb  $3796  ; $16
               fdb  $2E55  ; $18 - Used
               fdb  $2D2E  ; $1A - Used
               fdb  $3800  ; $1C  probably not a SWI routine . Doesn't jump back to $2F3A.
               fdb  $2F27  ; $1E
               fdb  $2F13  ; $20 - Used
               fdb  $2EFF  ; $22
               fdb  $381B  ; $24  probably no SWI routine here. Doesn't jump back to $2F3A.
               fdb  $2F9E  ; $26 - Used
               fdb  $382E  ; $28  probably no SWI routine here. Doesn't jump back to $2F3A.
               fdb  $38AE  ; $2A  probably no SWI routine here. Doesn't jump back to $2F3A.
               fdb  $37B4  ; $2C  probably no SWI routine here. Doesn't jump back to $2F3A.
               fdb  $379F  ; $2E  probably no SWI routine here. Doesn't jump back to $2F3A.
               fdb  $37DA  ; $30  probably no SWI routine here. Doesn't jump back to $2F3A.
               fdb  $37D1  ; $32  probably no SWI routine here. Doesn't jump back to $2F3A.
               fdb  $3788  ; $34  probably no SWI routine here. Doesn't jump back to $2F3A.
               fdb  $3777  ; $36  probably no SWI routine here. Doesn't jump back to $2F3A.
               fdb  $0000
               fdb  $30B2
               
               org  $0896
               
               fdb  $0000
               fdb  $0000
0896: 00 00    sbca $0000
0898: 00       illegal
0899: 00       illegal
089A: 00       illegal
089B: 00       illegal
089C: 00       illegal
089D: 00       illegal
089E: 00       illegal
089F: 00       illegal
08A0: 00       illegal
08A1: 00       illegal
08A2: 00       illegal
08A3: 00       illegal
08A4: 00       illegal
08A5: 00       illegal
08A6: 00       illegal
08A7: 00       illegal
08A8: 00       illegal
08A9: 00       illegal
08AA: 00       illegal
08AB: 00       illegal
08AC: 00       illegal
08AD: 00       illegal
08AE: 00       illegal
08AF: 00       illegal
08B0: 00       illegal
08B1: 00       illegal
08B2: 00       illegal
08B3: 00       illegal
08B4: 00       illegal
08B5: 00       illegal
08B6: 00       illegal
08B7: 00       illegal
08B8: 00       illegal
08B9: 00       illegal
08BA: 00       illegal
08BB: 00       illegal
08BC: 00       illegal
08BD: 00       illegal
08BE: 00       illegal
08BF: 00       illegal
08C0: 00       illegal
08C1: 00       illegal
08C2: 00       illegal
08C3: 00       illegal
08C4: 00       illegal
08C5: 00       illegal
08C6: 00       illegal
08C7: 00       illegal
08C8: 00       illegal
08C9: 00       illegal
08CA: 00       illegal
08CB: 00       illegal
08CC: 00       illegal
08CD: 00       illegal
08CE: 00       illegal
08CF: 00       illegal
08D0: 00       illegal
08D1: 00       illegal
08D2: 00       illegal
08D3: 00       illegal
08D4: 00       illegal
08D5: 00       illegal
08D6: 00       illegal
08D7: 00       illegal
08D8: 00       illegal
08D9: 00       illegal
08DA: 00       illegal
08DB: 00       illegal
08DC: 00       illegal
08DD: 00       illegal
08DE: 00       illegal
08DF: 00       illegal
08E0: 00       illegal
08E1: 00       illegal
08E2: 00       illegal
08E3: 00       illegal
08E4: 00       illegal
08E5: 00       illegal
08E6: 00       illegal
08E7: 00       illegal
08E8: 00       illegal
08E9: 00       illegal
08EA: 00       illegal
08EB: 00       illegal
08EC: 00       illegal
08ED: 00       illegal
08EE: 00       illegal
08EF: 00       illegal
08F0: 00       illegal
08F1: 00       illegal
08F2: 00       illegal
08F3: 00       illegal
08F4: 00       illegal
08F5: 00       illegal
08F6: 00       illegal
08F7: 00       illegal
08F8: 00       illegal
08F9: 00       illegal
08FA: 00       illegal
08FB: 00       illegal
08FC: 00       illegal
08FD: 00       illegal
08FE: 00       illegal
08FF: 00       illegal
0900: 00       illegal
0901: 00       illegal
0902: 00       illegal
0903: 00       illegal
0904: 00       illegal
0905: 00       illegal
0906: 00       illegal
0907: 00       illegal
0908: 00       illegal
0909: 00       illegal
090A: 00       illegal
090B: 00       illegal
090C: 00       illegal
090D: 00       illegal
090E: 00       illegal
090F: 00       illegal
0910: 00       illegal
0911: 00       illegal
0912: 00       illegal
0913: 00       illegal
0914: 00       illegal
0915: 00       illegal
0916: 00       illegal
0917: 00       illegal
0918: 00       illegal
0919: 00       illegal
091A: 00       illegal
091B: 00       illegal
091C: 00       illegal
091D: 00       illegal
091E: 00       illegal
091F: 00       illegal
0920: 00       illegal
0921: 00       illegal
0922: 00       illegal
0923: 00       illegal
0924: 00       illegal
0925: 00       illegal
0926: 00       illegal
0927: 00       illegal
0928: 00       illegal
0929: 00       illegal
092A: 00       illegal
092B: 00       illegal
092C: 00       illegal
092D: 00       illegal
092E: 00       illegal
092F: 00       illegal
0930: 00       illegal
0931: 00       illegal
0932: 00       illegal
0933: 00       illegal
0934: 00       illegal
0935: 00       illegal
0936: 00       illegal
0937: 00       illegal
0938: 00       illegal
0939: 00       illegal
093A: 00       illegal
093B: 00       illegal
093C: 00       illegal
093D: 00       illegal
093E: 00       illegal
093F: 00       illegal
0940: 00       illegal
0941: 00       illegal
0942: 00       illegal
0943: 00       illegal
0944: 00       illegal
0945: 00       illegal
0946: 00       illegal
0947: 00       illegal
0948: 00       illegal
0949: 00       illegal
094A: 00       illegal
094B: 00       illegal
094C: 00       illegal
094D: 00       illegal
094E: 00       illegal
094F: 00       illegal
0950: 00       illegal
0951: 00       illegal
0952: 00       illegal
0953: 00       illegal
0954: 00       illegal
0955: 00       illegal
0956: 00       illegal
0957: 00       illegal
0958: 00       illegal
0959: 00       illegal
095A: 00       illegal
095B: 00       illegal
095C: 00       illegal
095D: 00       illegal
095E: 00       illegal
095F: 00       illegal
0960: 00       illegal
0961: 00       illegal
0962: 00       illegal
0963: 00       illegal
0964: 00       illegal
0965: 00       illegal
0966: 00       illegal
0967: 00       illegal
0968: 00       illegal
0969: 00       illegal
096A: 00       illegal
096B: 00       illegal
096C: 00       illegal
096D: 00       illegal
096E: 00       illegal
096F: 00       illegal
0970: 00       illegal
0971: 00       illegal

; jumps here from many places.
0972: 86 05    lda  #$05
0974: B7 06 03 sta  $0603
0977: CE 0A 90 ldx  #$0A90
097A: 86 0E    lda  #$0E
097C: 3F       swi  
097D: CE 0A 79 ldx  #$0A79
0980: FF 04 95 stx  $0495
0983: 86 FF    lda  #$FF
0985: B7 04 97 sta  $0497
0988: FE 04 95 ldx  $0495
098B: BD 0F F6 jsr  $0FF6
098E: FE 04 95 ldx  $0495
0991: A6 11    lda  (x+$11)
0993: 26 5E    bne  $09F3
0995: CE 02 EB ldx  #$02EB
0998: FF 04 95 stx  $0495
099B: B6 04 97 lda  $0497
099E: 26 38    bne  $09D8
09A0: 7F 02 B0 clr  $02B0
09A3: BD 08 27 jsr  $0827
09A6: CE 78 30 ldx  #$7830
09A9: 7F 00 1A clr  $001A
09AC: 86 07    lda  #$07
09AE: C6 D0    ldb  #$D0
09B0: BD FE 11 jsr  $FE11
09B3: CE 78 30 ldx  #$7830
09B6: FF 03 C2 stx  $03C2
09B9: CE 7F AF ldx  #$7FAF
09BC: FF 03 C6 stx  $03C6
09BF: FE 0A 9E ldx  $0A9E
09C2: BD 08 24 jsr  $0824
09C5: FE 03 C2 ldx  $03C2
09C8: FF 02 A2 stx  $02A2
09CB: 86 02    lda  #$02
09CD: BD 08 21 jsr  $0821
09D0: 8D 72    bsr  $0A44
09D2: B6 F9 1E lda  $F91E
09D5: B7 F7 D2 sta  $F7D2
09D8: FE 02 05 ldx  $0205
09DB: AD 00    jsr  (x+$00)
09DD: CE 02 CE ldx  #$02CE
09E0: 4F       clra 
09E1: C6 0C    ldb  #$0C
09E3: BD FE 0E jsr  $FE0E
09E6: B6 04 97 lda  $0497
09E9: 27 87    beq  $0972
09EB: 7F 09 17 clr  $0917
09EE: 7F 04 97 clr  $0497
09F1: 20 95    bra  $0988
09F3: B6 01 DE lda  $01DE
09F6: B7 02 FD sta  $02FD
09F9: 8D 52    bsr  $0A4D
09FB: FF 07 4D stx  $074D
09FE: CE 06 E6 ldx  #$06E6
0A01: DF 1D    stx  $1D
0A03: CE 07 30 ldx  #$0730
0A06: 86 4A    lda  #$4A
0A08: C6 1F    ldb  #$1F
0A0A: BD FE 28 jsr  $FE28
0A0D: B6 02 FD lda  $02FD
0A10: 81 BF    cmpa #$BF
0A12: 23 13    bls  $0A27
0A14: 81 C6    cmpa #$C6
0A16: 24 0F    bcc  $0A27
0A18: CE 07 05 ldx  #$0705
0A1B: DF 1D    stx  $1D
0A1D: CE 07 4F ldx  #$074F
0A20: 86 2B    lda  #$2B
0A22: C6 0B    ldb  #$0B
0A24: BD FE 28 jsr  $FE28
0A27: B6 04 97 lda  $0497
0A2A: 26 08    bne  $0A34
0A2C: B6 02 FD lda  $02FD
0A2F: 8B 01    adda #$01
0A31: B7 04 38 sta  $0438
0A34: CE 4F 53 ldx  #$4F53
0A37: FF 09 18 stx  $0918
0A3A: 86 40    lda  #$40
0A3C: B7 09 1F sta  $091F
0A3F: 8D 03    bsr  $0A44
0A41: 7E 09 72 jmp  $0972
0A44: CE 09 18 ldx  #$0918
0A47: FF 06 67 stx  $0667
0A4A: 7E 08 2D jmp  $082D
0A4D: B7 04 98 sta  $0498
0A50: 44       lsra 
0A51: 44       lsra 
0A52: 44       lsra 
0A53: 44       lsra 
0A54: 8B 30    adda #$30
0A56: B7 04 99 sta  $0499
0A59: 81 39    cmpa #$39
0A5B: 23 05    bls  $0A62
0A5D: 8B 07    adda #$07
0A5F: B7 04 99 sta  $0499
0A62: B6 04 98 lda  $0498
0A65: 84 0F    anda #$0F
0A67: 8B 30    adda #$30
0A69: B7 04 9A sta  $049A
0A6C: 81 39    cmpa #$39
0A6E: 23 05    bls  $0A75
0A70: 8B 07    adda #$07
0A72: B7 04 9A sta  $049A
0A75: FE 04 99 ldx  $0499
0A78: 39       rts  

               org  $0A79
               fcc  "SYSLIB  LOGONPRG"

0A89: 00       illegal
0A8A: 00       illegal
0A8B: 00       illegal
0A8C: 46       rora 
0A8D: 44       lsra 
0A8E: 53       comb 
0A8F: 20 01    bra  $0A92
0A91: BD 0A 8C jsr  $0A8C
0A94: 00       illegal
0A95: 00       illegal
0A96: 00       illegal
0A97: 00       illegal
0A98: 00       illegal
0A99: 00       illegal
0A9A: 00       illegal
0A9B: 00       illegal
0A9C: 00       illegal
0A9D: 00       illegal

               org  $0A9E
               fdb  $03B6
;0A9E: 03       illegal
;0A9F: B6     

; subroutine from jumptable $082D - seems to update the status line.
0AA0: FF 04 9B stx  $049B
0AA3: FF 04 1D stx  $041D
0AA6: B6 02 A8 lda  $02A8
0AA9: F6 02 A9 ldb  $02A9
0AAC: CB 01    addb #$01
0AAE: 89 00    adca #$00
0AB0: F7 04 20 stb  $0420
0AB3: B7 04 1F sta  $041F
0AB6: 86 FF    lda  #$FF
0AB8: FE 04 9B ldx  $049B
0ABB: A7 08    sta  (x+$08)
0ABD: B6 02 C9 lda  $02C9
0AC0: 27 1E    beq  $0AE0
0AC2: FE 03 AE ldx  $03AE
0AC5: A6 00    lda  (x+$00)
0AC7: 84 04    anda #$04
0AC9: 81 04    cmpa #$04
0ACB: 26 08    bne  $0AD5
0ACD: 86 01    lda  #$01
0ACF: FE 04 9B ldx  $049B
0AD2: A7 08    sta  (x+$08)
0AD4: 39       rts  
0AD5: 7F 02 C9 clr  $02C9
0AD8: 7F 03 86 clr  $0386
0ADB: 86 01    lda  #$01
0ADD: BD 08 21 jsr  $0821
0AE0: BD 0B 86 jsr  $0B86
0AE3: FE 04 9B ldx  $049B
0AE6: A6 07    lda  (x+$07)
0AE8: 81 01    cmpa #$01
0AEA: 27 64    beq  $0B50
0AEC: EE 00    ldx  (x+$00)
0AEE: 8C 4F 53 cmpx #$4F53 
0AF1: 26 05    bne  $0AF8
0AF3: 7F 04 22 clr  $0422
0AF6: 20 05    bra  $0AFD
0AF8: 86 01    lda  #$01
0AFA: B7 04 22 sta  $0422
0AFD: BD 0E 94 jsr  $0E94  ; update the status line. Non-zero in $0422 mean *EM* 0 mean *OS*
0B00: FE 04 9B ldx  $049B
0B03: A6 07    lda  (x+$07)
0B05: FE 03 AE ldx  $03AE
0B08: A7 00    sta  (x+$00)
0B0A: FE 04 9B ldx  $049B
0B0D: A6 07    lda  (x+$07)
0B0F: 84 08    anda #$08
0B11: 27 23    beq  $0B36
0B13: C6 20    ldb  #$20
0B15: F7 04 9E stb  $049E
0B18: FE 03 AE ldx  $03AE
0B1B: 08       inx  
0B1C: 08       inx  
0B1D: 08       inx  
0B1E: 08       inx  
0B1F: 08       inx  
0B20: 08       inx  
0B21: DF 1D    stx  $1D
0B23: CE 04 9E ldx  #$049E
0B26: 86 4B    lda  #$4B
0B28: C6 01    ldb  #$01
0B2A: BD FE 28 jsr  $FE28
0B2D: 86 A0    lda  #$A0
0B2F: FE 03 AE ldx  $03AE
0B32: A7 50    sta  (x+$50)
0B34: 20 1A    bra  $0B50
0B36: B6 04 22 lda  $0422
0B39: 26 15    bne  $0B50
0B3B: FE 03 AE ldx  $03AE
0B3E: 08       inx  
0B3F: 08       inx  
0B40: 08       inx  
0B41: 08       inx  
0B42: 08       inx  
0B43: 08       inx  
0B44: DF 1D    stx  $1D
0B46: FE 04 9B ldx  $049B
0B49: EE 02    ldx  (x+$02)
0B4B: C6 4B    ldb  #$4B
0B4D: BD FE 2F jsr  $FE2F   ; seems to be some kind of mem copy routine
0B50: FE 04 1F ldx  $041F
0B53: DF 1D    stx  $1D
0B55: FE 03 AE ldx  $03AE
0B58: 08       inx  
0B59: C6 50    ldb  #$50    ; copy 80 characters?
0B5B: BD FE 2F jsr  $FE2F
0B5E: 8D 1F    bsr  $0B7F
0B60: FE 04 9B ldx  $049B
0B63: A6 07    lda  (x+$07)
0B65: 84 90    anda #$90
0B67: 81 90    cmpa #$90
0B69: 26 13    bne  $0B7E
0B6B: 7F 02 62 clr  $0262
0B6E: 86 80    lda  #$80
0B70: B7 02 63 sta  $0263
0B73: 86 02    lda  #$02
0B75: B7 02 64 sta  $0264
0B78: CE 03 87 ldx  #$0387
0B7B: 86 04    lda  #$04
0B7D: 3F       swi  
0B7E: 39       rts  

0B7F: B6 04 9D lda  $049D
0B82: B7 F7 C6 sta  $F7C6
0B85: 39       rts  


0B86: B6 F7 C6 lda  $F7C6
0B89: B7 04 9D sta  $049D
0B8C: B6 F7 C6 lda  $F7C6
0B8F: 84 DF    anda #$DF
0B91: B7 F7 C6 sta  $F7C6
0B94: B6 04 9D lda  $049D
0B97: 84 02    anda #$02
0B99: 27 25    beq  $0BC0
0B9B: B6 04 9D lda  $049D
0B9E: 84 01    anda #$01
0BA0: 26 0F    bne  $0BB1
0BA2: B6 04 1F lda  $041F
0BA5: F6 04 20 ldb  $0420
0BA8: 80 40    suba #$40
0BAA: F7 03 B5 stb  $03B5
0BAD: B7 03 B4 sta  $03B4
0BB0: 39       rts  


0BB1: B6 04 1F lda  $041F
0BB4: F6 04 20 ldb  $0420
0BB7: 80 30    suba #$30
0BB9: F7 03 B5 stb  $03B5
0BBC: B7 03 B4 sta  $03B4
0BBF: 39       rts  


0BC0: 7F 03 B5 clr  $03B5
0BC3: 7F 03 B4 clr  $03B4
0BC6: 39       rts  


0BC7: B6 02 A8 lda  $02A8
0BCA: F6 02 A9 ldb  $02A9
0BCD: CB 01    addb #$01
0BCF: 89 00    adca #$00
0BD1: F7 04 20 stb  $0420
0BD4: B7 04 1F sta  $041F
0BD7: BD 0B 86 jsr  $0B86
0BDA: 86 43    lda  #$43
0BDC: B7 03 91 sta  $0391
0BDF: 86 0B    lda  #$0B
0BE1: B7 03 92 sta  $0392
0BE4: B6 02 AA lda  $02AA
0BE7: 80 05    suba #$05
0BE9: B7 04 A1 sta  $04A1
0BEC: CE 03 87 ldx  #$0387
0BEF: 6F 00    clr  (x+$00)
0BF1: 6F 01    clr  (x+$01)
0BF3: 6F 04    clr  (x+$04)
0BF5: 86 82    lda  #$82
0BF7: BD 08 0C jsr  $080C
0BFA: BD 0B 7F jsr  $0B7F
0BFD: CE 03 87 ldx  #$0387
0C00: FF 04 A7 stx  $04A7
0C03: 86 01    lda  #$01
0C05: B7 04 A6 sta  $04A6
0C08: CE 04 A6 ldx  #$04A6
0C0B: 86 06    lda  #$06
0C0D: 3F       swi  
0C0E: BD 0B 86 jsr  $0B86
0C11: B6 03 91 lda  $0391
0C14: 84 60    anda #$60
0C16: F6 02 A4 ldb  $02A4
0C19: C4 1F    andb #$1F
0C1B: F7 04 A5 stb  $04A5
0C1E: BA 04 A5 ora  $04A5
0C21: B7 03 91 sta  $0391
0C24: 7C 03 91 inc  $0391
0C27: B6 02 A5 lda  $02A5
0C2A: 8B 01    adda #$01
0C2C: B7 03 92 sta  $0392
0C2F: B6 02 C9 lda  $02C9
0C32: 26 07    bne  $0C3B
0C34: B6 03 91 lda  $0391
0C37: 84 60    anda #$60
0C39: 27 07    beq  $0C42
0C3B: B6 02 63 lda  $0263
0C3E: 84 80    anda #$80
0C40: 27 1B    beq  $0C5D
0C42: B6 02 64 lda  $0264
0C45: 81 01    cmpa #$01
0C47: 26 03    bne  $0C4C
0C49: 7E 0D CF jmp  $0DCF
0C4C: 81 02    cmpa #$02
0C4E: 26 03    bne  $0C53
0C50: 7E 0E 4A jmp  $0E4A
0C53: 81 03    cmpa #$03
0C55: 27 03    beq  $0C5A
0C57: 7E 0E 70 jmp  $0E70
0C5A: 7E 0D C7 jmp  $0DC7
0C5D: B6 02 62 lda  $0262
0C60: 84 80    anda #$80
0C62: 27 0D    beq  $0C71
0C64: B6 03 91 lda  $0391
0C67: 84 1F    anda #$1F
0C69: B7 03 91 sta  $0391
0C6C: 86 00    lda  #$00
0C6E: BD 08 21 jsr  $0821
0C71: B6 02 62 lda  $0262
0C74: 84 10    anda #$10
0C76: 27 10    beq  $0C88
0C78: B6 03 91 lda  $0391
0C7B: 8A 40    ora  #$40
0C7D: B7 03 91 sta  $0391
0C80: 86 00    lda  #$00
0C82: BD 08 21 jsr  $0821
0C85: 7E 0E 75 jmp  $0E75
0C88: FE 03 AE ldx  $03AE
0C8B: A6 00    lda  (x+$00)
0C8D: 84 02    anda #$02
0C8F: 27 0B    beq  $0C9C
0C91: 86 02    lda  #$02
0C93: FE 04 1D ldx  $041D
0C96: A7 09    sta  (x+$09)
0C98: 86 1F    lda  #$1F
0C9A: A7 0A    sta  (x+$0A)
0C9C: B6 02 63 lda  $0263
0C9F: FE 04 1D ldx  $041D
0CA2: A4 09    anda (x+$09)
0CA4: 26 03    bne  $0CA9
0CA6: 7E 0D 42 jmp  $0D42
0CA9: B6 02 64 lda  $0264
0CAC: A1 0A    cmpa (x+$0A)
0CAE: 27 03    beq  $0CB3
0CB0: 7E 0D 42 jmp  $0D42
0CB3: FE 03 AE ldx  $03AE
0CB6: 6F 00    clr  (x+$00)
0CB8: 7F 02 C9 clr  $02C9
0CBB: 7F 03 86 clr  $0386
0CBE: 86 01    lda  #$01
0CC0: BD 08 21 jsr  $0821
0CC3: B6 04 22 lda  $0422
0CC6: 26 1D    bne  $0CE5
0CC8: FE 04 1D ldx  $041D
0CCB: EE 04    ldx  (x+$04)
0CCD: DF 1D    stx  $1D
0CCF: FE 04 1F ldx  $041F
0CD2: 08       inx  
0CD3: 08       inx  
0CD4: 08       inx  
0CD5: 08       inx  
0CD6: 08       inx  
0CD7: C6 4B    ldb  #$4B
0CD9: BD FE 2F jsr  $FE2F
0CDC: CE 02 B1 ldx  #$02B1
0CDF: 86 04    lda  #$04
0CE1: 3F       swi  
0CE2: 7E 0E 75 jmp  $0E75
0CE5: CE 06 E5 ldx  #$06E5
0CE8: DF 1D    stx  $1D
0CEA: FE 04 1F ldx  $041F
0CED: 08       inx  
0CEE: 08       inx  
0CEF: 08       inx  
0CF0: 08       inx  
0CF1: 08       inx  
0CF2: C6 4B    ldb  #$4B
0CF4: BD FE 2F jsr  $FE2F
0CF7: CE 02 1D ldx  #$021D
0CFA: 86 04    lda  #$04
0CFC: 3F       swi  
0CFD: C6 20    ldb  #$20
0CFF: F7 04 A5 stb  $04A5
0D02: FE 04 1F ldx  $041F
0D05: 08       inx  
0D06: 08       inx  
0D07: 08       inx  
0D08: 08       inx  
0D09: 08       inx  
0D0A: DF 1D    stx  $1D
0D0C: CE 04 A5 ldx  #$04A5
0D0F: 86 4B    lda  #$4B
0D11: C6 01    ldb  #$01
0D13: BD FE 28 jsr  $FE28
0D16: 86 80    lda  #$80
0D18: FE 04 1F ldx  $041F
0D1B: A7 05    sta  (x+$05)
0D1D: 86 A0    lda  #$A0
0D1F: A7 4F    sta  (x+$4F)
0D21: 86 A2    lda  #$A2
0D23: FE 03 AE ldx  $03AE
0D26: A7 00    sta  (x+$00)
0D28: 86 FF    lda  #$FF
0D2A: B7 0F 39 sta  $0F39
0D2D: CE 04 A2 ldx  #$04A2
0D30: DF 1D    stx  $1D
0D32: CE 06 E6 ldx  #$06E6
0D35: C6 03    ldb  #$03
0D37: BD FE 2F jsr  $FE2F
0D3A: 86 01    lda  #$01
0D3C: B7 04 9F sta  $049F
0D3F: 7E 0E 75 jmp  $0E75
0D42: B6 02 63 lda  $0263
0D45: 84 02    anda #$02
0D47: 27 6A    beq  $0DB3
0D49: B6 02 64 lda  $0264
0D4C: 81 02    cmpa #$02
0D4E: 26 05    bne  $0D55
0D50: BD 0E BF jsr  $0EBF
0D53: 20 5E    bra  $0DB3
0D55: 81 01    cmpa #$01
0D57: 26 48    bne  $0DA1
0D59: BD 0E AD jsr  $0EAD
0D5C: FE 04 1F ldx  $041F
0D5F: FF 04 A9 stx  $04A9
0D62: 4F       clra 
0D63: F6 04 9F ldb  $049F
0D66: FB 04 AA addb $04AA
0D69: B9 04 A9 adca $04A9
0D6C: F7 04 AA stb  $04AA
0D6F: B7 04 A9 sta  $04A9
0D72: FE 04 A9 ldx  $04A9
0D75: A6 04    lda  (x+$04)
0D77: 81 80    cmpa #$80
0D79: 26 38    bne  $0DB3
0D7B: 20 03    bra  $0D80
0D7D: BD 0E AD jsr  $0EAD
0D80: FE 04 1F ldx  $041F
0D83: FF 04 A9 stx  $04A9
0D86: 4F       clra 
0D87: F6 04 9F ldb  $049F
0D8A: FB 04 AA addb $04AA
0D8D: B9 04 A9 adca $04A9
0D90: F7 04 AA stb  $04AA
0D93: B7 04 A9 sta  $04A9
0D96: FE 04 A9 ldx  $04A9
0D99: A6 04    lda  (x+$04)
0D9B: 81 A0    cmpa #$A0
0D9D: 26 DE    bne  $0D7D
0D9F: 20 B8    bra  $0D59
0DA1: 81 08    cmpa #$08
0DA3: 26 0E    bne  $0DB3
0DA5: B6 04 A0 lda  $04A0
0DA8: 8B 02    adda #$02
0DAA: B7 04 A0 sta  $04A0
0DAD: BD 0E BF jsr  $0EBF
0DB0: 7F 04 A0 clr  $04A0
0DB3: B6 02 63 lda  $0263
0DB6: 84 83    anda #$83
0DB8: 26 5C    bne  $0E16
0DBA: B6 02 64 lda  $0264
0DBD: FE 03 8F ldx  $038F
0DC0: A7 00    sta  (x+$00)
0DC2: BD 0E BF jsr  $0EBF
0DC5: 20 4F    bra  $0E16
0DC7: 86 02    lda  #$02
0DC9: BD 08 51 jsr  $0851
0DCC: 7E 0E 75 jmp  $0E75
0DCF: FE 03 AE ldx  $03AE
0DD2: A6 00    lda  (x+$00)
0DD4: 84 04    anda #$04
0DD6: 27 03    beq  $0DDB
0DD8: 7E 0E 70 jmp  $0E70
0DDB: BD 0E 94 jsr  $0E94
0DDE: FE 04 1F ldx  $041F
0DE1: DF 1D    stx  $1D
0DE3: FE 03 AE ldx  $03AE
0DE6: 08       inx  
0DE7: C6 50    ldb  #$50
0DE9: BD FE 2F jsr  $FE2F
0DEC: B6 02 C9 lda  $02C9
0DEF: 26 03    bne  $0DF4
0DF1: 7E 0E 87 jmp  $0E87
0DF4: FE 03 AE ldx  $03AE
0DF7: A6 00    lda  (x+$00)
0DF9: 84 80    anda #$80
0DFB: 26 09    bne  $0E06
0DFD: FE 02 A2 ldx  $02A2
0E00: FF 03 8F stx  $038F
0E03: 7E 0E 87 jmp  $0E87
0E06: 86 01    lda  #$01
0E08: B7 04 9F sta  $049F
0E0B: 86 02    lda  #$02
0E0D: B7 04 A0 sta  $04A0
0E10: BD 0E BF jsr  $0EBF
0E13: 7F 04 A0 clr  $04A0
0E16: B6 04 1F lda  $041F
0E19: F6 04 20 ldb  $0420
0E1C: FB 04 9F addb $049F
0E1F: 89 00    adca #$00
0E21: CB 04    addb #$04
0E23: 89 00    adca #$00
0E25: FB 03 B5 addb $03B5
0E28: B9 03 B4 adca $03B4
0E2B: F7 03 90 stb  $0390
0E2E: B7 03 8F sta  $038F
0E31: B6 03 91 lda  $0391
0E34: 8A 40    ora  #$40
0E36: B7 03 91 sta  $0391
0E39: 86 FF    lda  #$FF
0E3B: B7 03 86 sta  $0386
0E3E: 86 00    lda  #$00
0E40: BD 08 21 jsr  $0821
0E43: 86 01    lda  #$01
0E45: B7 02 C9 sta  $02C9
0E48: 20 2B    bra  $0E75
0E4A: B6 02 C9 lda  $02C9
0E4D: 26 16    bne  $0E65
0E4F: FE 03 AE ldx  $03AE
0E52: A6 00    lda  (x+$00)
0E54: 84 80    anda #$80
0E56: 81 80    cmpa #$80
0E58: 26 16    bne  $0E70
0E5A: B6 03 91 lda  $0391
0E5D: 84 40    anda #$40
0E5F: 81 40    cmpa #$40
0E61: 27 A3    beq  $0E06
0E63: 20 0B    bra  $0E70
0E65: FE 03 AE ldx  $03AE
0E68: A6 00    lda  (x+$00)
0E6A: 84 04    anda #$04
0E6C: 81 04    cmpa #$04
0E6E: 26 17    bne  $0E87
0E70: 86 32    lda  #$32
0E72: BD 08 1E jsr  $081E
0E75: CE 03 87 ldx  #$0387
0E78: 6F 00    clr  (x+$00)
0E7A: 6F 01    clr  (x+$01)
0E7C: 6F 04    clr  (x+$04)
0E7E: CE 02 92 ldx  #$0292
0E81: 86 04    lda  #$04
0E83: 3F       swi  
0E84: 7E 0B FA jmp  $0BFA
0E87: 7F 02 C9 clr  $02C9
0E8A: 7F 03 86 clr  $0386
0E8D: 86 01    lda  #$01
0E8F: BD 08 21 jsr  $0821
0E92: 20 E1    bra  $0E75

; subroutine. Sets a pointer to the text to update the status line with.
0E94: B6 04 22 lda  $0422
0E97: 26 0A    bne  $0EA3
0E99: 7C 04 22 inc  $0422
0E9C: CE 06 DF ldx  #$06DF  ; *OS* status line
0E9F: FF 03 AE stx  $03AE
0EA2: 39       rts  
0EA3: 7F 04 22 clr  $0422
0EA6: CE 06 14 ldx  #$0614  ; *EM* status line
0EA9: FF 03 AE stx  $03AE
0EAC: 39       rts  


0EAD: B6 04 9F lda  $049F
0EB0: 81 01    cmpa #$01
0EB2: 26 07    bne  $0EBB
0EB4: B6 04 A1 lda  $04A1
0EB7: B7 04 9F sta  $049F
0EBA: 39       rts  
0EBB: 7A 04 9F dec  $049F
0EBE: 39       rts  


0EBF: B6 04 A0 lda  $04A0
0EC2: 81 01    cmpa #$01
0EC4: 27 06    beq  $0ECC
0EC6: 81 02    cmpa #$02
0EC8: 27 25    beq  $0EEF
0ECA: 8D 45    bsr  $0F11
0ECC: FE 04 1F ldx  $041F
0ECF: FF 04 AB stx  $04AB
0ED2: 4F       clra 
0ED3: F6 04 9F ldb  $049F
0ED6: FB 04 AC addb $04AC
0ED9: B9 04 AB adca $04AB
0EDC: F7 04 AC stb  $04AC
0EDF: B7 04 AB sta  $04AB
0EE2: FE 04 AB ldx  $04AB
0EE5: A6 04    lda  (x+$04)
0EE7: 81 A0    cmpa #$A0
0EE9: 26 25    bne  $0F10
0EEB: 20 02    bra  $0EEF
0EED: 8D 22    bsr  $0F11
0EEF: FE 04 1F ldx  $041F
0EF2: FF 04 AB stx  $04AB
0EF5: 4F       clra 
0EF6: F6 04 9F ldb  $049F
0EF9: FB 04 AC addb $04AC
0EFC: B9 04 AB adca $04AB
0EFF: F7 04 AC stb  $04AC
0F02: B7 04 AB sta  $04AB
0F05: FE 04 AB ldx  $04AB
0F08: A6 04    lda  (x+$04)
0F0A: 81 80    cmpa #$80
0F0C: 26 DF    bne  $0EED
0F0E: 20 BA    bra  $0ECA
0F10: 39       rts  


0F11: B6 04 9F lda  $049F
0F14: B1 04 A1 cmpa $04A1
0F17: 25 06    bcs  $0F1F
0F19: 86 01    lda  #$01
0F1B: B7 04 9F sta  $049F
0F1E: 39       rts  
0F1F: 7C 04 9F inc  $049F
0F22: 39       rts 


0F23: 00       illegal
0F24: 00       illegal
0F25: 00       illegal
0F26: 00       illegal
0F27: 00       illegal
0F28: 00       illegal
0F29: 00       illegal
0F2A: 00       illegal
0F2B: 00       illegal
0F2C: 00       illegal
0F2D: 00       illegal
0F2E: 00       illegal
0F2F: 00       illegal
0F30: 00       illegal
0F31: 00       illegal
0F32: 00       illegal
0F33: 00       illegal
0F34: 00       illegal
0F35: 00       illegal
0F36: 00       illegal
0F37: 00       illegal
0F38: 00       illegal
0F39: 00       illegal

; subroutine from jumptable $0800
0F3A: BD 32 ED jsr  $32ED
0F3D: 7F 02 4B clr  $024B
0F40: B6 02 3B lda  $023B
0F43: 26 06    bne  $0F4B
0F45: 86 01    lda  #$01
0F47: 97 25    sta  $25
0F49: 20 27    bra  $0F72
0F4B: 81 01    cmpa #$01
0F4D: 26 10    bne  $0F5F
0F4F: 86 05    lda  #$05
0F51: 97 25    sta  $25
0F53: FE 02 41 ldx  $0241
0F56: DF 27    stx  $27
0F58: FE 02 43 ldx  $0243
0F5B: DF 29    stx  $29
0F5D: 20 13    bra  $0F72
0F5F: 81 02    cmpa #$02
0F61: 27 04    beq  $0F67
0F63: 81 10    cmpa #$10
0F65: 26 23    bne  $0F8A
0F67: FE 02 45 ldx  $0245
0F6A: DF 2C    stx  $2C
0F6C: 81 02    cmpa #$02
0F6E: 27 17    beq  $0F87
0F70: 20 18    bra  $0F8A
0F72: 86 01    lda  #$01
0F74: 97 2B    sta  $2B
0F76: CE 01 04 ldx  #$0104
0F79: DF 1D    stx  $1D
0F7B: CE 02 3B ldx  #$023B
0F7E: C6 06    ldb  #$06
0F80: BD FE 2F jsr  $FE2F
0F83: 86 06    lda  #$06
0F85: 97 26    sta  $26
0F87: BD 12 F8 jsr  $12F8
0F8A: CE 04 8A ldx  #$048A
0F8D: FF 04 AE stx  $04AE
0F90: 86 01    lda  #$01
0F92: B7 04 AD sta  $04AD
0F95: CE 04 AD ldx  #$04AD
0F98: 86 06    lda  #$06
0F9A: 3F       swi  
0F9B: BD 32 ED jsr  $32ED
0F9E: CE 04 8A ldx  #$048A
0FA1: 6F 00    clr  (x+$00)
0FA3: 6F 01    clr  (x+$01)
0FA5: 6F 04    clr  (x+$04)
0FA7: 96 24    lda  $24
0FA9: 81 01    cmpa #$01
0FAB: 27 04    beq  $0FB1
0FAD: 81 05    cmpa #$05
0FAF: 26 31    bne  $0FE2
0FB1: CE 02 3B ldx  #$023B
0FB4: DF 1D    stx  $1D
0FB6: CE 01 44 ldx  #$0144
0FB9: C6 06    ldb  #$06
0FBB: BD FE 2F jsr  $FE2F
0FBE: FE 01 4A ldx  $014A
0FC1: FF 02 49 stx  $0249
0FC4: 96 24    lda  $24
0FC6: 81 05    cmpa #$05
0FC8: 26 15    bne  $0FDF
0FCA: 86 02    lda  #$02
0FCC: 97 25    sta  $25
0FCE: 97 2B    sta  $2B
0FD0: FE 02 45 ldx  $0245
0FD3: DF 2C    stx  $2C
0FD5: B6 02 4D lda  $024D
0FD8: 27 AD    beq  $0F87
0FDA: 86 03    lda  #$03
0FDC: B7 02 3B sta  $023B
0FDF: 7E 32 F5 jmp  $32F5
0FE2: 81 09    cmpa #$09
0FE4: 26 0D    bne  $0FF3
0FE6: 86 10    lda  #$10
0FE8: B7 02 3B sta  $023B
0FEB: 86 80    lda  #$80
0FED: B7 02 4B sta  $024B
0FF0: 7E 32 F5 jmp  $32F5
0FF3: 7E 32 F5 jmp  $32F5

; subroutine from jumptabel $0800
0FF6: FF 04 B0 stx  $04B0
0FF9: FF 11 56 stx  $1156
0FFC: 08       inx  
0FFD: 08       inx  
0FFE: 08       inx  
0FFF: 08       inx  
1000: 08       inx  
1001: 08       inx  
1002: 08       inx  
1003: 08       inx  
1004: FF 11 52 stx  $1152
1007: CE 11 5E ldx  #$115E
100A: FF 11 54 stx  $1154
100D: B6 06 03 lda  $0603
1010: B7 04 B2 sta  $04B2
1013: 86 05    lda  #$05
1015: B7 06 03 sta  $0603
1018: CE 11 50 ldx  #$1150
101B: 86 10    lda  #$10
101D: 3F       swi  
101E: FE 04 B0 ldx  $04B0
1021: A6 10    lda  (x+$10)
1023: 84 81    anda #$81
1025: 81 81    cmpa #$81
1027: 26 1B    bne  $1044
1029: A6 0F    lda  (x+$0F)
102B: B1 02 E7 cmpa $02E7
102E: 26 04    bne  $1034
1030: 6F 10    clr  (x+$10)
1032: 20 4A    bra  $107E
1034: CE 01 DD ldx  #$01DD
1037: FF 07 5A stx  $075A
103A: FE 04 B0 ldx  $04B0
103D: 6F 10    clr  (x+$10)
103F: 86 FF    lda  #$FF
1041: B7 04 B5 sta  $04B5
1044: CE 01 DD ldx  #$01DD
1047: 86 12    lda  #$12
1049: 3F       swi  
104A: CE 11 4D ldx  #$114D
104D: 86 06    lda  #$06
104F: 3F       swi  
1050: 5D       tstb 
1051: 26 2B    bne  $107E
1053: B6 04 B5 lda  $04B5
1056: 81 FF    cmpa #$FF
1058: 26 0B    bne  $1065
105A: FE 04 B0 ldx  $04B0
105D: A6 0F    lda  (x+$0F)
105F: B7 02 E7 sta  $02E7
1062: 7F 04 B5 clr  $04B5
1065: FE 04 B0 ldx  $04B0
1068: A6 10    lda  (x+$10)
106A: B7 09 16 sta  $0916
106D: 4D       tsta 
106E: 27 0E    beq  $107E
1070: CE 11 5F ldx  #$115F
1073: FF 11 54 stx  $1154
1076: CE 11 50 ldx  #$1150
1079: 86 10    lda  #$10
107B: 3F       swi  
107C: 8D 17    bsr  $1095
107E: FE 04 B0 ldx  $04B0
1081: B6 01 DD lda  $01DD
1084: F6 01 DE ldb  $01DE
1087: E7 12    stb  (x+$12)
1089: A7 11    sta  (x+$11)
108B: 7F 04 B5 clr  $04B5
108E: B6 04 B2 lda  $04B2
1091: B7 06 03 sta  $0603
1094: 39       rts  


1095: FE 02 05 ldx  $0205
1098: FF 04 B3 stx  $04B3
109B: CE 01 DD ldx  #$01DD
109E: C6 10    ldb  #$10
10A0: 86 18    lda  #$18
10A2: 3F       swi  
10A3: 7F 09 15 clr  $0915
10A6: CE 11 4D ldx  #$114D
10A9: 86 06    lda  #$06
10AB: 3F       swi  
10AC: 5D       tstb 
10AD: 27 03    beq  $10B2
10AF: 7E 11 46 jmp  $1146
10B2: CE 11 60 ldx  #$1160
10B5: 86 1E    lda  #$1E
10B7: 3F       swi  
10B8: CE 11 4D ldx  #$114D
10BB: 86 06    lda  #$06
10BD: 3F       swi  
10BE: 5D       tstb 
10BF: 27 03    beq  $10C4
10C1: 7E 11 46 jmp  $1146
10C4: CE 01 DD ldx  #$01DD
10C7: 86 1A    lda  #$1A
10C9: 3F       swi  
10CA: CE 11 4D ldx  #$114D
10CD: 86 06    lda  #$06
10CF: 3F       swi  
10D0: CE 08 98 ldx  #$0898
10D3: FF 11 52 stx  $1152
10D6: CE 11 5E ldx  #$115E
10D9: FF 11 54 stx  $1154
10DC: 86 01    lda  #$01
10DE: 20 36    bra  $1116
10E0: FE 11 52 ldx  $1152
10E3: 08       inx  
10E4: 08       inx  
10E5: 08       inx  
10E6: 08       inx  
10E7: 08       inx  
10E8: 08       inx  
10E9: 08       inx  
10EA: 08       inx  
10EB: FF 11 56 stx  $1156
10EE: CE 11 50 ldx  #$1150
10F1: 86 10    lda  #$10
10F3: 3F       swi  
10F4: CE 01 DD ldx  #$01DD
10F7: 86 12    lda  #$12
10F9: 3F       swi  
10FA: CE 11 4D ldx  #$114D
10FD: 86 06    lda  #$06
10FF: 3F       swi  
1100: 5D       tstb 
1101: 26 43    bne  $1146
1103: FE 11 56 ldx  $1156
1106: 08       inx  
1107: 08       inx  
1108: 08       inx  
1109: 08       inx  
110A: 08       inx  
110B: 08       inx  
110C: 08       inx  
110D: 08       inx  
110E: FF 11 52 stx  $1152
1111: B6 04 B5 lda  $04B5
1114: 8B 01    adda #$01
1116: B7 04 B5 sta  $04B5
1119: B1 08 96 cmpa $0896
111C: 23 C2    bls  $10E0
111E: B6 09 17 lda  $0917
1121: 27 23    beq  $1146
1123: B6 08 97 lda  $0897
1126: 27 1B    beq  $1143
1128: 7F 08 96 clr  $0896
112B: CE 08 96 ldx  #$0896
112E: DF 1D    stx  $1D
1130: CE 00 48 ldx  #$0048
1133: DF 1F    stx  $1F
1135: FE 11 52 ldx  $1152
1138: B6 08 96 lda  $0896
113B: F6 08 97 ldb  $0897
113E: BD FE 34 jsr  $FE34
1141: 20 03    bra  $1146
1143: 7F 08 96 clr  $0896
1146: FE 04 B3 ldx  $04B3
1149: FF 02 05 stx  $0205
114C: 39       rts  


114D: 01       nop  
114E: 01       nop  
114F: DD       illegal
1150: 01       nop  
1151: DD       illegal
1152: 00       illegal
1153: 00       illegal
1154: 00       illegal
1155: 00       illegal
1156: 00       illegal
1157: 00       illegal
1158: 01       nop  
1159: BD FF FE jsr  $FFFE
115C: FF FE 41 stx  $FE41
115F: 46       rora 
1160: 01       nop  
1161: DD       illegal
1162: 09       dex  
1163: 15       illegal
1164: 08       inx  
1165: 96 CE    lda  $CE
1167: 01       nop  
1168: 00       illegal
1169: FF 04 88 stx  $0488
116C: 96 45    lda  $45
116E: B8 02 54 eora $0254
1171: 84 02    anda #$02
1173: 27 06    beq  $117B
1175: 96 45    lda  $45
1177: 84 FE    anda #$FE
1179: 97 45    sta  $45
117B: 96 44    lda  $44
117D: B1 02 39 cmpa $0239
1180: 27 1C    beq  $119E
1182: 96 45    lda  $45
1184: 84 0F    anda #$0F
1186: B1 03 B2 cmpa $03B2
1189: 27 2D    beq  $11B8
118B: 96 45    lda  $45
118D: 84 0F    anda #$0F
118F: B7 02 53 sta  $0253
1192: B7 03 B2 sta  $03B2
1195: FE 02 C5 ldx  $02C5
1198: 27 1E    beq  $11B8
119A: AD 00    jsr  (x+$00)
119C: 20 1A    bra  $11B8
119E: 96 45    lda  $45
11A0: 84 0F    anda #$0F
11A2: B1 03 B3 cmpa $03B3
11A5: 27 11    beq  $11B8
11A7: 96 45    lda  $45
11A9: 84 0F    anda #$0F
11AB: B7 02 53 sta  $0253
11AE: B7 03 B3 sta  $03B3
11B1: FE 02 C3 ldx  $02C3
11B4: 27 02    beq  $11B8
11B6: AD 00    jsr  (x+$00)
11B8: 96 45    lda  $45
11BA: 84 20    anda #$20
11BC: 27 60    beq  $121E
11BE: 96 44    lda  $44
11C0: B1 02 39 cmpa $0239
11C3: 27 1B    beq  $11E0
11C5: CE 02 59 ldx  #$0259
11C8: FF 04 B8 stx  $04B8
11CB: CE 02 56 ldx  #$0256
11CE: FF 04 B6 stx  $04B6
11D1: FE 07 FA ldx  $07FA
11D4: FF 04 BA stx  $04BA
11D7: CE 02 55 ldx  #$0255
11DA: FF 04 BC stx  $04BC
11DD: 7E 12 7D jmp  $127D
11E0: 96 45    lda  $45
11E2: B4 02 54 anda $0254
11E5: 84 01    anda #$01
11E7: 26 12    bne  $11FB
11E9: B6 02 2D lda  $022D
11EC: 43       coma 
11ED: F6 03 FE ldb  $03FE
11F0: B7 04 BE sta  $04BE
11F3: F4 04 BE andb $04BE
11F6: F7 03 FE stb  $03FE
11F9: 20 09    bra  $1204
11FB: B6 03 FE lda  $03FE
11FE: BA 02 2D ora  $022D
1201: B7 03 FE sta  $03FE
1204: CE 02 2E ldx  #$022E
1207: FF 04 B8 stx  $04B8
120A: CE 02 36 ldx  #$0236
120D: FF 04 B6 stx  $04B6
1210: FE 07 F4 ldx  $07F4
1213: FF 04 BA stx  $04BA
1216: CE 02 54 ldx  #$0254
1219: FF 04 BC stx  $04BC
121C: 20 5F    bra  $127D
121E: FE 04 B6 ldx  $04B6
1221: A6 00    lda  (x+$00)
1223: 81 C0    cmpa #$C0
1225: 26 0D    bne  $1234
1227: FE 04 B8 ldx  $04B8
122A: 86 04    lda  #$04
122C: 3F       swi  
122D: FE 04 B6 ldx  $04B6
1230: 6F 00    clr  (x+$00)
1232: 20 49    bra  $127D
1234: FE 04 BA ldx  $04BA
1237: DF 4E    stx  $4E
1239: DE 4E    ldx  $4E
123B: EE 08    ldx  (x+$08)
123D: FF 04 BA stx  $04BA
1240: 86 F0    lda  #$F0
1242: DE 4E    ldx  $4E
1244: A7 01    sta  (x+$01)
1246: 96 44    lda  $44
1248: B1 02 39 cmpa $0239
124B: 27 19    beq  $1266
124D: FE 04 BA ldx  $04BA
1250: FF 07 FA stx  $07FA
1253: DE 4E    ldx  $4E
1255: B6 07 FE lda  $07FE
1258: F6 07 FF ldb  $07FF
125B: E7 09    stb  (x+$09)
125D: A7 08    sta  (x+$08)
125F: DE 4E    ldx  $4E
1261: FF 07 FE stx  $07FE
1264: 20 17    bra  $127D
1266: FE 04 BA ldx  $04BA
1269: FF 07 F4 stx  $07F4
126C: DE 4E    ldx  $4E
126E: B6 07 F8 lda  $07F8
1271: F6 07 F9 ldb  $07F9
1274: E7 09    stb  (x+$09)
1276: A7 08    sta  (x+$08)
1278: DE 4E    ldx  $4E
127A: FF 07 F8 stx  $07F8
127D: FE 04 B6 ldx  $04B6
1280: A6 00    lda  (x+$00)
1282: 27 21    beq  $12A5
1284: 86 C0    lda  #$C0
1286: A7 00    sta  (x+$00)
1288: 86 ED    lda  #$ED
128A: B7 01 04 sta  $0104
128D: CE 01 05 ldx  #$0105
1290: DF 1D    stx  $1D
1292: FE 04 B6 ldx  $04B6
1295: EE 01    ldx  (x+$01)
1297: C6 15    ldb  #$15
1299: BD FE 2F jsr  $FE2F
129C: B6 01 05 lda  $0105
129F: 8B 02    adda #$02
12A1: 97 26    sta  $26
12A3: 20 3D    bra  $12E2
12A5: FE 04 BA ldx  $04BA
12A8: 27 2F    beq  $12D9
12AA: DF 4E    stx  $4E
12AC: DE 4E    ldx  $4E
12AE: A6 01    lda  (x+$01)
12B0: B7 01 04 sta  $0104
12B3: A6 02    lda  (x+$02)
12B5: B7 01 05 sta  $0105
12B8: A6 03    lda  (x+$03)
12BA: B7 01 06 sta  $0106
12BD: A6 04    lda  (x+$04)
12BF: B7 01 07 sta  $0107
12C2: A6 05    lda  (x+$05)
12C4: B7 01 08 sta  $0108
12C7: A6 01    lda  (x+$01)
12C9: 81 C0    cmpa #$C0
12CB: 26 06    bne  $12D3
12CD: 86 03    lda  #$03
12CF: 97 26    sta  $26
12D1: 20 0F    bra  $12E2
12D3: 86 05    lda  #$05
12D5: 97 26    sta  $26
12D7: 20 09    bra  $12E2
12D9: 86 FF    lda  #$FF
12DB: B7 01 04 sta  $0104
12DE: 86 01    lda  #$01
12E0: 97 26    sta  $26
12E2: FE 04 BC ldx  $04BC
12E5: A6 00    lda  (x+$00)
12E7: 84 0F    anda #$0F
12E9: D6 45    ldb  $45
12EB: C4 90    andb #$90
12ED: F7 04 BF stb  $04BF
12F0: BA 04 BF ora  $04BF
12F3: 97 25    sta  $25
12F5: 7E 12 F8 jmp  $12F8
12F8: DE 40    ldx  $40
12FA: DF 4E    stx  $4E
12FC: B6 04 21 lda  $0421
12FF: 27 0C    beq  $130D
1301: 86 FF    lda  #$FF
1303: DE 4E    ldx  $4E
1305: A7 01    sta  (x+$01)
1307: CE 16 01 ldx  #$1601
130A: 7E 33 18 jmp  $3318
130D: CE 1D 23 ldx  #$1D23
1310: FF 01 96 stx  $0196
1313: 96 25    lda  $25
1315: 81 09    cmpa #$09
1317: 26 03    bne  $131C
1319: 7E 15 BC jmp  $15BC
131C: 84 40    anda #$40
131E: 27 0D    beq  $132D
1320: B6 01 03 lda  $0103
1323: 8A 40    ora  #$40
1325: B7 01 03 sta  $0103
1328: 97 45    sta  $45
132A: 7E 15 BC jmp  $15BC
132D: CE 01 00 ldx  #$0100
1330: DF 46    stx  $46
1332: 96 26    lda  $26
1334: 97 49    sta  $49
1336: 7F 00 48 clr  $0048
1339: CE 01 40 ldx  #$0140
133C: DF 4A    stx  $4A
133E: CE 00 40 ldx  #$0040
1341: DF 4C    stx  $4C
1343: 96 25    lda  $25
1345: 81 80    cmpa #$80
1347: 25 0B    bcs  $1354
1349: 86 FF    lda  #$FF
134B: 97 43    sta  $43
134D: 96 25    lda  $25
134F: 97 45    sta  $45
1351: 7E 15 0B jmp  $150B
1354: DE 4E    ldx  $4E
1356: 27 18    beq  $1370
1358: 96 2B    lda  $2B
135A: 26 08    bne  $1364
135C: A6 01    lda  (x+$01)
135E: 27 04    beq  $1364
1360: 86 C0    lda  #$C0
1362: A7 01    sta  (x+$01)
1364: A6 05    lda  (x+$05)
1366: 97 43    sta  $43
1368: 96 31    lda  $31
136A: D6 32    ldb  $32
136C: E7 07    stb  (x+$07)
136E: A7 06    sta  (x+$06)
1370: 96 25    lda  $25
1372: 26 42    bne  $13B6
1374: 86 FE    lda  #$FE
1376: 97 42    sta  $42
1378: 86 FF    lda  #$FF
137A: 97 43    sta  $43
137C: 7F 00 49 clr  $0049
137F: 7F 00 48 clr  $0048
1382: 7F 00 3F clr  $003F
1385: 7F 00 33 clr  $0033
1388: 96 2B    lda  $2B
138A: 26 07    bne  $1393
138C: 86 0E    lda  #$0E
138E: 97 45    sta  $45
1390: 7E 14 F7 jmp  $14F7
1393: 81 01    cmpa #$01
1395: 26 0B    bne  $13A2
1397: 86 FD    lda  #$FD
1399: A7 01    sta  (x+$01)
139B: 86 0B    lda  #$0B
139D: 97 45    sta  $45
139F: 7E 14 F7 jmp  $14F7
13A2: 96 36    lda  $36
13A4: 81 80    cmpa #$80
13A6: 25 07    bcs  $13AF
13A8: 86 0A    lda  #$0A
13AA: 97 45    sta  $45
13AC: 7E 14 F7 jmp  $14F7
13AF: 86 0F    lda  #$0F
13B1: 97 45    sta  $45
13B3: 7E 14 F7 jmp  $14F7
13B6: 81 01    cmpa #$01
13B8: 26 07    bne  $13C1
13BA: 86 01    lda  #$01
13BC: 97 45    sta  $45
13BE: 7E 14 F7 jmp  $14F7
13C1: 81 02    cmpa #$02
13C3: 26 6A    bne  $142F
13C5: 7F 00 49 clr  $0049
13C8: 7F 00 48 clr  $0048
13CB: 96 2B    lda  $2B
13CD: 81 02    cmpa #$02
13CF: 26 3E    bne  $140F
13D1: 96 24    lda  $24
13D3: 84 04    anda #$04
13D5: 27 38    beq  $140F
13D7: 86 09    lda  #$09
13D9: 97 25    sta  $25
13DB: 96 2C    lda  $2C
13DD: D6 2D    ldb  $2D
13DF: F0 02 C8 subb $02C8
13E2: B2 02 C7 sbca $02C7
13E5: 25 0A    bcs  $13F1
13E7: 26 03    bne  $13EC
13E9: 5D       tstb 
13EA: 27 05    beq  $13F1
13EC: FE 02 C7 ldx  $02C7
13EF: DF 2C    stx  $2C
13F1: DE 2C    ldx  $2C
13F3: DF 4A    stx  $4A
13F5: DE 2E    ldx  $2E
13F7: DF 4C    stx  $4C
13F9: 96 4C    lda  $4C
13FB: D6 4D    ldb  $4D
13FD: C0 04    subb #$04
13FF: 82 00    sbca #$00
1401: 2C 05    bge  $1408
1403: CE 00 04 ldx  #$0004
1406: DF 4C    stx  $4C
1408: 86 07    lda  #$07
140A: 97 45    sta  $45
140C: 7E 14 F7 jmp  $14F7
140F: 96 2B    lda  $2B
1411: 26 0B    bne  $141E
1413: 86 C0    lda  #$C0
1415: A7 01    sta  (x+$01)
1417: 86 0B    lda  #$0B
1419: 97 45    sta  $45
141B: 7E 14 F7 jmp  $14F7
141E: 81 03    cmpa #$03
1420: 26 07    bne  $1429
1422: 86 0F    lda  #$0F
1424: 97 45    sta  $45
1426: 7E 14 F7 jmp  $14F7
1429: 7F 00 45 clr  $0045
142C: 7E 14 F7 jmp  $14F7
142F: 81 03    cmpa #$03
1431: 26 0D    bne  $1440
1433: 7F 00 49 clr  $0049
1436: 7F 00 48 clr  $0048
1439: 86 0D    lda  #$0D
143B: 97 45    sta  $45
143D: 7E 14 F7 jmp  $14F7
1440: 81 04    cmpa #$04
1442: 26 1D    bne  $1461
1444: DE 29    ldx  $29
1446: FF 01 08 stx  $0108
1449: CE 01 04 ldx  #$0104
144C: DF 1D    stx  $1D
144E: DE 27    ldx  $27
1450: C6 04    ldb  #$04
1452: BD FE 2F jsr  $FE2F
1455: CE 00 06 ldx  #$0006
1458: DF 48    stx  $48
145A: 86 04    lda  #$04
145C: 97 45    sta  $45
145E: 7E 14 F7 jmp  $14F7
1461: 81 05    cmpa #$05
1463: 26 3B    bne  $14A0
1465: 96 26    lda  $26
1467: 8B 04    adda #$04
1469: 97 C5    sta  $C5
146B: B6 15 FE lda  $15FE
146E: F6 15 FF ldb  $15FF
1471: DB C5    addb $C5
1473: 89 00    adca #$00
1475: D7 C4    stb  $C4
1477: 97 C3    sta  $C3
1479: DE C3    ldx  $C3
147B: DF 1D    stx  $1D
147D: DE 27    ldx  $27
147F: C6 04    ldb  #$04
1481: BD FE 2F jsr  $FE2F
1484: DE C3    ldx  $C3
1486: 96 29    lda  $29
1488: D6 2A    ldb  $2A
148A: E7 05    stb  (x+$05)
148C: A7 04    sta  (x+$04)
148E: 96 48    lda  $48
1490: D6 49    ldb  $49
1492: CB 06    addb #$06
1494: 89 00    adca #$00
1496: D7 49    stb  $49
1498: 97 48    sta  $48
149A: 86 05    lda  #$05
149C: 97 45    sta  $45
149E: 20 57    bra  $14F7
14A0: 81 07    cmpa #$07
14A2: 26 3B    bne  $14DF
14A4: 96 29    lda  $29
14A6: D6 2A    ldb  $2A
14A8: C0 04    subb #$04
14AA: 82 00    sbca #$00
14AC: D7 49    stb  $49
14AE: 97 48    sta  $48
14B0: C0 00    subb #$00
14B2: 82 00    sbca #$00
14B4: 2C 06    bge  $14BC
14B6: 7F 00 49 clr  $0049
14B9: 7F 00 48 clr  $0048
14BC: DE 27    ldx  $27
14BE: DF 46    stx  $46
14C0: CE 00 37 ldx  #$0037
14C3: DF 1D    stx  $1D
14C5: DE 27    ldx  $27
14C7: C6 04    ldb  #$04
14C9: BD FE 2F jsr  $FE2F
14CC: B6 01 03 lda  $0103
14CF: 84 4F    anda #$4F
14D1: 81 49    cmpa #$49
14D3: 26 04    bne  $14D9
14D5: 86 0A    lda  #$0A
14D7: 97 25    sta  $25
14D9: 86 02    lda  #$02
14DB: 97 45    sta  $45
14DD: 20 18    bra  $14F7
14DF: 81 08    cmpa #$08
14E1: 26 0A    bne  $14ED
14E3: 86 FF    lda  #$FF
14E5: 97 43    sta  $43
14E7: 86 08    lda  #$08
14E9: 97 45    sta  $45
14EB: 20 0A    bra  $14F7
14ED: 7F 00 49 clr  $0049
14F0: 7F 00 48 clr  $0048
14F3: 86 49    lda  #$49
14F5: 97 45    sta  $45
14F7: 96 2B    lda  $2B
14F9: 81 03    cmpa #$03
14FB: 26 08    bne  $1505
14FD: DE 4E    ldx  $4E
14FF: 27 04    beq  $1505
1501: 86 FF    lda  #$FF
1503: A7 01    sta  (x+$01)
1505: 96 45    lda  $45
1507: 9A 3F    ora  $3F
1509: 97 45    sta  $45
150B: 96 3F    lda  $3F
150D: 88 10    eora #$10
150F: 97 3F    sta  $3F
1511: 96 48    lda  $48
1513: D6 49    ldb  $49
1515: CB 04    addb #$04
1517: 89 00    adca #$00
1519: D7 49    stb  $49
151B: 97 48    sta  $48
151D: DE 46    ldx  $46
151F: DF 1D    stx  $1D
1521: CE 00 42 ldx  #$0042
1524: C6 04    ldb  #$04
1526: BD FE 2F jsr  $FE2F
1529: 96 42    lda  $42
152B: B1 02 39 cmpa $0239
152E: 27 08    beq  $1538
1530: B1 02 3A cmpa $023A
1533: 27 03    beq  $1538
1535: 7E 15 BC jmp  $15BC
1538: 96 33    lda  $33
153A: 26 20    bne  $155C
153C: CE 04 39 ldx  #$0439
153F: DF 1D    stx  $1D
1541: CE 00 24 ldx  #$0024
1544: C6 0C    ldb  #$0C
1546: BD FE 2F jsr  $FE2F
1549: CE 00 24 ldx  #$0024
154C: DF 1D    stx  $1D
154E: CE 04 C0 ldx  #$04C0
1551: C6 0C    ldb  #$0C
1553: BD FE 2F jsr  $FE2F
1556: 86 80    lda  #$80
1558: 97 33    sta  $33
155A: 20 1D    bra  $1579
155C: CE 04 C0 ldx  #$04C0
155F: DF 1D    stx  $1D
1561: CE 00 24 ldx  #$0024
1564: C6 0C    ldb  #$0C
1566: BD FE 2F jsr  $FE2F
1569: CE 00 24 ldx  #$0024
156C: DF 1D    stx  $1D
156E: CE 04 39 ldx  #$0439
1571: C6 0C    ldb  #$0C
1573: BD FE 2F jsr  $FE2F
1576: 7F 00 33 clr  $0033
1579: 96 2B    lda  $2B
157B: 81 02    cmpa #$02
157D: 26 17    bne  $1596
157F: DE 2C    ldx  $2C
1581: 9C 46    cmpx $46
1583: 27 31    beq  $15B6
1585: DF 1D    stx  $1D
1587: DE 48    ldx  $48
1589: DF 1F    stx  $1F
158B: DE 46    ldx  $46
158D: 96 48    lda  $48
158F: D6 49    ldb  $49
1591: BD FE 34 jsr  $FE34
1594: 20 20    bra  $15B6
1596: 4F       clra 
1597: C6 40    ldb  #$40
1599: D0 49    subb $49
159B: 92 48    sbca $48
159D: F7 F7 07 stb  $F707
15A0: B7 F7 06 sta  $F706
15A3: CE 01 40 ldx  #$0140
15A6: DF 1D    stx  $1D
15A8: DE 48    ldx  $48
15AA: DF 1F    stx  $1F
15AC: CE 01 00 ldx  #$0100
15AF: 96 48    lda  $48
15B1: D6 49    ldb  $49
15B3: BD FE 34 jsr  $FE34
15B6: CE 16 01 ldx  #$1601
15B9: 7E 33 18 jmp  $3318
15BC: 96 33    lda  $33
15BE: 26 06    bne  $15C6
15C0: 86 FF    lda  #$FF
15C2: 97 34    sta  $34
15C4: 20 14    bra  $15DA
15C6: 96 34    lda  $34
15C8: 26 10    bne  $15DA
15CA: 96 25    lda  $25
15CC: 81 09    cmpa #$09
15CE: 26 06    bne  $15D6
15D0: 86 07    lda  #$07
15D2: 97 34    sta  $34
15D4: 20 04    bra  $15DA
15D6: 86 02    lda  #$02
15D8: 97 34    sta  $34
15DA: 7F 00 36 clr  $0036
15DD: FE 02 B9 ldx  $02B9
15E0: 27 02    beq  $15E4
15E2: AD 00    jsr  (x+$00)
15E4: DE 46    ldx  $46
15E6: FF F7 00 stx  $F700
15E9: DE 48    ldx  $48
15EB: FF F7 02 stx  $F702
15EE: 86 54    lda  #$54
15F0: B7 F7 20 sta  $F720
15F3: 86 80    lda  #$80
15F5: B7 F7 21 sta  $F721
15F8: 86 01    lda  #$01
15FA: B7 F7 14 sta  $F714
15FD: 39       rts 


15FE: 01       nop  
15FF: 00       illegal
1600: DE 40    ldx  $40
1602: DF 4E    stx  $4E
1604: 96 36    lda  $36
1606: 81 80    cmpa #$80
1608: 25 38    bcs  $1642
160A: 96 33    lda  $33
160C: 26 07    bne  $1615
160E: 86 FF    lda  #$FF
1610: 97 35    sta  $35
1612: 7E 1A DE jmp  $1ADE
1615: 96 25    lda  $25
1617: 81 40    cmpa #$40
1619: 25 03    bcs  $161E
161B: 7E 1A 67 jmp  $1A67
161E: 81 0A    cmpa #$0A
1620: 26 0F    bne  $1631
1622: DE 27    ldx  $27
1624: DF 1D    stx  $1D
1626: CE 00 37 ldx  #$0037
1629: C6 04    ldb  #$04
162B: BD FE 2F jsr  $FE2F
162E: 7E 1A 67 jmp  $1A67
1631: 81 07    cmpa #$07
1633: 26 06    bne  $163B
1635: 86 0A    lda  #$0A
1637: 97 25    sta  $25
1639: 20 04    bra  $163F
163B: 8A 40    ora  #$40
163D: 97 25    sta  $25
163F: 7E 12 F8 jmp  $12F8
1642: 7F 00 36 clr  $0036
1645: B6 04 21 lda  $0421
1648: 27 03    beq  $164D
164A: 7E 18 15 jmp  $1815
164D: 96 25    lda  $25
164F: 84 BF    anda #$BF
1651: 97 25    sta  $25
1653: BD 1A C4 jsr  $1AC4
1656: 96 25    lda  $25
1658: 81 07    cmpa #$07
165A: 27 04    beq  $1660
165C: 81 0A    cmpa #$0A
165E: 26 0C    bne  $166C
1660: DE 27    ldx  $27
1662: DF 1D    stx  $1D
1664: CE 00 37 ldx  #$0037
1667: C6 04    ldb  #$04
1669: BD FE 2F jsr  $FE2F
166C: 96 25    lda  $25
166E: 81 09    cmpa #$09
1670: 26 14    bne  $1686
1672: DE 2C    ldx  $2C
1674: A6 00    lda  (x+$00)
1676: 97 44    sta  $44
1678: A6 01    lda  (x+$01)
167A: 97 30    sta  $30
167C: A6 02    lda  (x+$02)
167E: 97 42    sta  $42
1680: A6 03    lda  (x+$03)
1682: 97 45    sta  $45
1684: 20 14    bra  $169A
1686: B6 01 40 lda  $0140
1689: 97 44    sta  $44
168B: B6 01 41 lda  $0141
168E: 97 30    sta  $30
1690: B6 01 42 lda  $0142
1693: 97 42    sta  $42
1695: B6 01 43 lda  $0143
1698: 97 45    sta  $45
169A: BD 1A B6 jsr  $1AB6
169D: 96 45    lda  $45
169F: 84 8F    anda #$8F
16A1: 97 C9    sta  $C9
16A3: 96 45    lda  $45
16A5: 84 20    anda #$20
16A7: 27 31    beq  $16DA
16A9: B6 06 65 lda  $0665
16AC: 81 FF    cmpa #$FF
16AE: 27 18    beq  $16C8
16B0: FE 02 E4 ldx  $02E4
16B3: 27 13    beq  $16C8
16B5: 96 45    lda  $45
16B7: 81 80    cmpa #$80
16B9: 24 08    bcc  $16C3
16BB: B6 06 65 lda  $0665
16BE: B1 01 40 cmpa $0140
16C1: 27 05    beq  $16C8
16C3: FE 02 E4 ldx  $02E4
16C6: AD 00    jsr  (x+$00)
16C8: 96 45    lda  $45
16CA: 81 80    cmpa #$80
16CC: 25 04    bcs  $16D2
16CE: 84 08    anda #$08
16D0: 26 05    bne  $16D7
16D2: 86 FF    lda  #$FF
16D4: B7 06 65 sta  $0665
16D7: 7F 00 3F clr  $003F
16DA: 96 45    lda  $45
16DC: 81 80    cmpa #$80
16DE: 25 03    bcs  $16E3
16E0: 7E 17 F8 jmp  $17F8
16E3: 96 30    lda  $30
16E5: 81 F0    cmpa #$F0
16E7: 24 03    bcc  $16EC
16E9: 7E 17 A7 jmp  $17A7
16EC: BD 1B 05 jsr  $1B05
16EF: 96 30    lda  $30
16F1: 84 0F    anda #$0F
16F3: B7 04 87 sta  $0487
16F6: 81 0E    cmpa #$0E
16F8: 27 2F    beq  $1729
16FA: CE 06 04 ldx  #$0604
16FD: FF 04 D0 stx  $04D0
1700: 4F       clra 
1701: F6 04 87 ldb  $0487
1704: 58       aslb 
1705: 49       rola 
1706: FB 04 D1 addb $04D1
1709: B9 04 D0 adca $04D0
170C: F7 04 D1 stb  $04D1
170F: B7 04 D0 sta  $04D0
1712: FE 04 D0 ldx  $04D0
1715: EE 00    ldx  (x+$00)
1717: 27 07    beq  $1720
1719: B6 04 87 lda  $0487
171C: 81 07    cmpa #$07
171E: 23 09    bls  $1729
1720: 7F 00 41 clr  $0041
1723: 7F 00 40 clr  $0040
1726: 7E 17 EF jmp  $17EF
1729: 96 30    lda  $30
172B: 81 FE    cmpa #$FE
172D: 26 28    bne  $1757
172F: B6 01 40 lda  $0140
1732: B7 06 65 sta  $0665
1735: CE 07 E8 ldx  #$07E8
1738: DF 4E    stx  $4E
173A: 7F 00 3F clr  $003F
173D: 86 FE    lda  #$FE
173F: DE 4E    ldx  $4E
1741: A7 05    sta  (x+$05)
1743: 86 FD    lda  #$FD
1745: A7 01    sta  (x+$01)
1747: 96 44    lda  $44
1749: 84 03    anda #$03
174B: 26 04    bne  $1751
174D: 6F 03    clr  (x+$03)
174F: 20 3E    bra  $178F
1751: 86 0C    lda  #$0C
1753: A7 03    sta  (x+$03)
1755: 20 38    bra  $178F
1757: FE 07 F2 ldx  $07F2
175A: DF 4E    stx  $4E
175C: EE 08    ldx  (x+$08)
175E: FF 07 F2 stx  $07F2
1761: 86 FE    lda  #$FE
1763: DE 4E    ldx  $4E
1765: A7 01    sta  (x+$01)
1767: 96 44    lda  $44
1769: 84 03    anda #$03
176B: 26 11    bne  $177E
176D: B6 07 F8 lda  $07F8
1770: F6 07 F9 ldb  $07F9
1773: E7 09    stb  (x+$09)
1775: A7 08    sta  (x+$08)
1777: 6F 03    clr  (x+$03)
1779: FF 07 F8 stx  $07F8
177C: 20 11    bra  $178F
177E: B6 07 FE lda  $07FE
1781: F6 07 FF ldb  $07FF
1784: E7 09    stb  (x+$09)
1786: A7 08    sta  (x+$08)
1788: 86 0C    lda  #$0C
178A: A7 03    sta  (x+$03)
178C: FF 07 FE stx  $07FE
178F: 96 30    lda  $30
1791: 84 0F    anda #$0F
1793: DE 4E    ldx  $4E
1795: AA 00    ora  (x+$00)
1797: 97 30    sta  $30
1799: A7 04    sta  (x+$04)
179B: 6F 07    clr  (x+$07)
179D: 6F 06    clr  (x+$06)
179F: 7F 00 32 clr  $0032
17A2: 7F 00 31 clr  $0031
17A5: 20 44    bra  $17EB
17A7: DE 4E    ldx  $4E
17A9: 27 25    beq  $17D0
17AB: A6 04    lda  (x+$04)
17AD: 91 30    cmpa $30
17AF: 27 0D    beq  $17BE
17B1: 96 42    lda  $42
17B3: 98 44    eora $44
17B5: 81 01    cmpa #$01
17B7: 23 17    bls  $17D0
17B9: BD 1B 05 jsr  $1B05
17BC: 20 12    bra  $17D0
17BE: 96 C9    lda  $C9
17C0: 81 0C    cmpa #$0C
17C2: 26 2B    bne  $17EF
17C4: A6 01    lda  (x+$01)
17C6: 81 F0    cmpa #$F0
17C8: 27 25    beq  $17EF
17CA: 86 10    lda  #$10
17CC: 97 3F    sta  $3F
17CE: 20 28    bra  $17F8
17D0: 96 30    lda  $30
17D2: 44       lsra 
17D3: 44       lsra 
17D4: 44       lsra 
17D5: 44       lsra 
17D6: 16       tab  
17D7: 48       asla 
17D8: 48       asla 
17D9: 1B       aba  
17DA: 48       asla 
17DB: 97 C8    sta  $C8
17DD: B6 1B 48 lda  $1B48
17E0: F6 1B 49 ldb  $1B49
17E3: DB C8    addb $C8
17E5: 89 00    adca #$00
17E7: D7 4F    stb  $4F
17E9: 97 4E    sta  $4E
17EB: DE 4E    ldx  $4E
17ED: DF 40    stx  $40
17EF: 96 25    lda  $25
17F1: 81 08    cmpa #$08
17F3: 26 03    bne  $17F8
17F5: 7F 00 3F clr  $003F
17F8: 96 45    lda  $45
17FA: 84 40    anda #$40
17FC: 27 17    beq  $1815
17FE: 96 45    lda  $45
1800: 84 10    anda #$10
1802: 91 3F    cmpa $3F
1804: 26 06    bne  $180C
1806: 96 C9    lda  $C9
1808: 81 09    cmpa #$09
180A: 26 09    bne  $1815
180C: 96 3F    lda  $3F
180E: 88 10    eora #$10
1810: 97 3F    sta  $3F
1812: 7E 12 F8 jmp  $12F8
1815: 96 45    lda  $45
1817: 81 80    cmpa #$80
1819: 24 03    bcc  $181E
181B: 7E 18 C4 jmp  $18C4
181E: 7F 00 33 clr  $0033
1821: 84 08    anda #$08
1823: 27 7E    beq  $18A3
1825: 96 44    lda  $44
1827: 84 03    anda #$03
1829: 97 CC    sta  $CC
182B: 4D       tsta 
182C: 26 07    bne  $1835
182E: FE 07 F8 ldx  $07F8
1831: DF 4E    stx  $4E
1833: 20 2E    bra  $1863
1835: FE 07 FE ldx  $07FE
1838: DF 4E    stx  $4E
183A: 20 27    bra  $1863
183C: DE 4E    ldx  $4E
183E: A6 01    lda  (x+$01)
1840: 81 F0    cmpa #$F0
1842: 25 17    bcs  $185B
1844: A6 01    lda  (x+$01)
1846: 81 FF    cmpa #$FF
1848: 27 11    beq  $185B
184A: 86 08    lda  #$08
184C: B7 04 21 sta  $0421
184F: A6 01    lda  (x+$01)
1851: 81 F0    cmpa #$F0
1853: 26 03    bne  $1858
1855: 7E 1A 61 jmp  $1A61
1858: 7E 1A 67 jmp  $1A67
185B: 86 FF    lda  #$FF
185D: A7 02    sta  (x+$02)
185F: EE 08    ldx  (x+$08)
1861: DF 4E    stx  $4E
1863: DE 4E    ldx  $4E
1865: 26 D5    bne  $183C
1867: 96 CC    lda  $CC
1869: 26 07    bne  $1872
186B: FE 07 F4 ldx  $07F4
186E: DF 4E    stx  $4E
1870: 20 19    bra  $188B
1872: FE 07 FA ldx  $07FA
1875: DF 4E    stx  $4E
1877: 20 12    bra  $188B
1879: DE 4E    ldx  $4E
187B: A6 01    lda  (x+$01)
187D: 81 C0    cmpa #$C0
187F: 26 06    bne  $1887
1881: 86 FF    lda  #$FF
1883: A7 02    sta  (x+$02)
1885: 6F 01    clr  (x+$01)
1887: EE 08    ldx  (x+$08)
1889: DF 4E    stx  $4E
188B: DE 4E    ldx  $4E
188D: 26 EA    bne  $1879
188F: B6 06 65 lda  $0665
1892: 91 44    cmpa $44
1894: 26 0D    bne  $18A3
1896: CE 07 E8 ldx  #$07E8
1899: DF 4E    stx  $4E
189B: 86 FF    lda  #$FF
189D: B7 06 65 sta  $0665
18A0: 7E 1A 67 jmp  $1A67
18A3: 7F 00 41 clr  $0041
18A6: 7F 00 40 clr  $0040
18A9: BD 1B 05 jsr  $1B05
18AC: B6 04 21 lda  $0421
18AF: 27 10    beq  $18C1
18B1: 7F 04 21 clr  $0421
18B4: CE 01 40 ldx  #$0140
18B7: DF 4A    stx  $4A
18B9: CE 00 40 ldx  #$0040
18BC: DF 4C    stx  $4C
18BE: 7E 1A DE jmp  $1ADE
18C1: 7E 11 66 jmp  $1166
18C4: 96 C9    lda  $C9
18C6: 27 08    beq  $18D0
18C8: 81 0B    cmpa #$0B
18CA: 27 04    beq  $18D0
18CC: 81 0F    cmpa #$0F
18CE: 26 17    bne  $18E7
18D0: 96 25    lda  $25
18D2: 81 05    cmpa #$05
18D4: 27 04    beq  $18DA
18D6: 81 04    cmpa #$04
18D8: 26 07    bne  $18E1
18DA: 86 0A    lda  #$0A
18DC: 97 24    sta  $24
18DE: 7E 1A 77 jmp  $1A77
18E1: 7F 00 24 clr  $0024
18E4: 7E 1A 77 jmp  $1A77
18E7: 81 01    cmpa #$01
18E9: 26 18    bne  $1903
18EB: 96 25    lda  $25
18ED: 81 05    cmpa #$05
18EF: 27 04    beq  $18F5
18F1: 81 04    cmpa #$04
18F3: 26 07    bne  $18FC
18F5: 86 03    lda  #$03
18F7: 97 24    sta  $24
18F9: 7E 1A 77 jmp  $1A77
18FC: 86 01    lda  #$01
18FE: 97 24    sta  $24
1900: 7E 1A 77 jmp  $1A77
1903: 81 02    cmpa #$02
1905: 26 19    bne  $1920
1907: BD 1A C4 jsr  $1AC4
190A: DE 2C    ldx  $2C
190C: DF 1D    stx  $1D
190E: CE 00 3B ldx  #$003B
1911: C6 04    ldb  #$04
1913: BD FE 2F jsr  $FE2F
1916: BD 1A B6 jsr  $1AB6
1919: 86 02    lda  #$02
191B: 97 24    sta  $24
191D: 7E 1A 77 jmp  $1A77
1920: 81 04    cmpa #$04
1922: 26 37    bne  $195B
1924: CE 00 3B ldx  #$003B
1927: DF 1D    stx  $1D
1929: CE 01 44 ldx  #$0144
192C: C6 04    ldb  #$04
192E: BD FE 2F jsr  $FE2F
1931: FE 01 48 ldx  $0148
1934: DF 2E    stx  $2E
1936: 96 25    lda  $25
1938: 81 05    cmpa #$05
193A: 27 04    beq  $1940
193C: 81 04    cmpa #$04
193E: 26 07    bne  $1947
1940: 86 0B    lda  #$0B
1942: 97 24    sta  $24
1944: 7E 1A 77 jmp  $1A77
1947: 86 04    lda  #$04
1949: 97 24    sta  $24
194B: 96 2B    lda  $2B
194D: 81 02    cmpa #$02
194F: 27 03    beq  $1954
1951: 7E 1A 77 jmp  $1A77
1954: 86 02    lda  #$02
1956: 97 25    sta  $25
1958: 7E 12 F8 jmp  $12F8
195B: 81 05    cmpa #$05
195D: 26 3E    bne  $199D
195F: 96 25    lda  $25
1961: 81 05    cmpa #$05
1963: 27 04    beq  $1969
1965: 81 04    cmpa #$04
1967: 26 06    bne  $196F
1969: 86 07    lda  #$07
196B: 97 24    sta  $24
196D: 20 04    bra  $1973
196F: 86 05    lda  #$05
1971: 97 24    sta  $24
1973: 86 3A    lda  #$3A
1975: B0 F7 07 suba $F707
1978: 97 C8    sta  $C8
197A: B6 1B 45 lda  $1B45
197D: F6 1B 46 ldb  $1B46
1980: DB C8    addb $C8
1982: 89 00    adca #$00
1984: D7 C7    stb  $C7
1986: 97 C6    sta  $C6
1988: CE 00 3B ldx  #$003B
198B: DF 1D    stx  $1D
198D: DE C6    ldx  $C6
198F: C6 04    ldb  #$04
1991: BD FE 2F jsr  $FE2F
1994: DE C6    ldx  $C6
1996: EE 04    ldx  (x+$04)
1998: DF 2E    stx  $2E
199A: 7E 1A 77 jmp  $1A77
199D: 81 07    cmpa #$07
199F: 26 0D    bne  $19AE
19A1: 86 07    lda  #$07
19A3: 97 25    sta  $25
19A5: DE 4E    ldx  $4E
19A7: EE 06    ldx  (x+$06)
19A9: DF 31    stx  $31
19AB: 7E 12 F8 jmp  $12F8
19AE: 81 0C    cmpa #$0C
19B0: 26 24    bne  $19D6
19B2: B6 01 44 lda  $0144
19B5: DE 4E    ldx  $4E
19B7: A7 02    sta  (x+$02)
19B9: B6 01 45 lda  $0145
19BC: A7 05    sta  (x+$05)
19BE: 86 C0    lda  #$C0
19C0: A7 01    sta  (x+$01)
19C2: 86 80    lda  #$80
19C4: 97 33    sta  $33
19C6: 96 42    lda  $42
19C8: 81 FF    cmpa #$FF
19CA: 26 03    bne  $19CF
19CC: 7E 1A 61 jmp  $1A61
19CF: 86 06    lda  #$06
19D1: 97 24    sta  $24
19D3: 7E 1A 77 jmp  $1A77
19D6: 81 08    cmpa #$08
19D8: 26 57    bne  $1A31
19DA: DE 40    ldx  $40
19DC: 26 07    bne  $19E5
19DE: 86 FF    lda  #$FF
19E0: B7 01 05 sta  $0105
19E3: 20 15    bra  $19FA
19E5: 96 30    lda  $30
19E7: B7 01 05 sta  $0105
19EA: B6 01 44 lda  $0144
19ED: DE 4E    ldx  $4E
19EF: A7 02    sta  (x+$02)
19F1: B6 01 45 lda  $0145
19F4: A7 05    sta  (x+$05)
19F6: EE 06    ldx  (x+$06)
19F8: DF 31    stx  $31
19FA: B6 01 44 lda  $0144
19FD: B7 01 04 sta  $0104
1A00: 96 44    lda  $44
1A02: B1 02 39 cmpa $0239
1A05: 26 08    bne  $1A0F
1A07: B6 02 54 lda  $0254
1A0A: B7 01 06 sta  $0106
1A0D: 20 06    bra  $1A15
1A0F: B6 02 55 lda  $0255
1A12: B7 01 06 sta  $0106
1A15: 86 03    lda  #$03
1A17: 97 26    sta  $26
1A19: 86 08    lda  #$08
1A1B: 97 25    sta  $25
1A1D: 86 01    lda  #$01
1A1F: 97 2B    sta  $2B
1A21: CE 04 39 ldx  #$0439
1A24: DF 1D    stx  $1D
1A26: CE 00 24 ldx  #$0024
1A29: C6 0C    ldb  #$0C
1A2B: BD FE 2F jsr  $FE2F
1A2E: 7E 12 F8 jmp  $12F8
1A31: 81 0A    cmpa #$0A
1A33: 26 15    bne  $1A4A
1A35: 86 FF    lda  #$FF
1A37: DE 4E    ldx  $4E
1A39: A7 05    sta  (x+$05)
1A3B: A6 01    lda  (x+$01)
1A3D: 81 FD    cmpa #$FD
1A3F: 24 26    bcc  $1A67
1A41: 86 FF    lda  #$FF
1A43: A7 02    sta  (x+$02)
1A45: 6F 01    clr  (x+$01)
1A47: 7E 1A FC jmp  $1AFC
1A4A: BD 1A FC jsr  $1AFC
1A4D: CE 00 30 ldx  #$0030
1A50: FF 04 CC stx  $04CC
1A53: DE 4E    ldx  $4E
1A55: 08       inx  
1A56: 08       inx  
1A57: 08       inx  
1A58: FF 04 CE stx  $04CE
1A5B: CE 04 CC ldx  #$04CC
1A5E: 7E 1B C7 jmp  $1BC7
1A61: 86 08    lda  #$08
1A63: 97 24    sta  $24
1A65: 20 04    bra  $1A6B
1A67: 86 09    lda  #$09
1A69: 97 24    sta  $24
1A6B: DE 4E    ldx  $4E
1A6D: A6 01    lda  (x+$01)
1A6F: 81 FE    cmpa #$FE
1A71: 26 04    bne  $1A77
1A73: 86 FF    lda  #$FF
1A75: A7 01    sta  (x+$01)
1A77: DE 4E    ldx  $4E
1A79: DF 40    stx  $40
1A7B: DE 4E    ldx  $4E
1A7D: A6 01    lda  (x+$01)
1A7F: 81 FF    cmpa #$FF
1A81: 26 0A    bne  $1A8D
1A83: 7F 00 25 clr  $0025
1A86: 86 03    lda  #$03
1A88: 97 2B    sta  $2B
1A8A: 7E 12 F8 jmp  $12F8
1A8D: A6 01    lda  (x+$01)
1A8F: 81 FE    cmpa #$FE
1A91: 26 04    bne  $1A97
1A93: 86 FD    lda  #$FD
1A95: A7 01    sta  (x+$01)
1A97: A6 04    lda  (x+$04)
1A99: 97 30    sta  $30
1A9B: EE 06    ldx  (x+$06)
1A9D: DF 31    stx  $31
1A9F: 7F 00 34 clr  $0034
1AA2: 84 0F    anda #$0F
1AA4: 81 07    cmpa #$07
1AA6: 23 07    bls  $1AAF
1AA8: CE 04 8A ldx  #$048A
1AAB: 86 04    lda  #$04
1AAD: 3F       swi  
1AAE: 39       rts  
1AAF: CE 02 BB ldx  #$02BB
1AB2: 86 04    lda  #$04
1AB4: 3F       swi  
1AB5: 39       rts  
1AB6: 36       psha 
1AB7: B6 F7 C6 lda  $F7C6
1ABA: 84 EF    anda #$EF
1ABC: BA 1B 47 ora  $1B47
1ABF: B7 F7 C6 sta  $F7C6
1AC2: 32       pula 
1AC3: 39       rts  
1AC4: 36       psha 
1AC5: B6 F7 C6 lda  $F7C6
1AC8: 84 10    anda #$10
1ACA: B7 1B 47 sta  $1B47
1ACD: B6 03 B0 lda  $03B0
1AD0: 84 80    anda #$80
1AD2: 27 08    beq  $1ADC
1AD4: B6 F7 C6 lda  $F7C6
1AD7: 8A 10    ora  #$10
1AD9: B7 F7 C6 sta  $F7C6
1ADC: 32       pula 
1ADD: 39       rts  
1ADE: CE 1C DE ldx  #$1CDE
1AE1: FF 01 96 stx  $0196
1AE4: DE 4A    ldx  $4A
1AE6: FF F7 04 stx  $F704
1AE9: DE 4C    ldx  $4C
1AEB: FF F7 06 stx  $F706
1AEE: 86 8A    lda  #$8A
1AF0: B7 F7 20 sta  $F720
1AF3: 86 02    lda  #$02
1AF5: B7 F7 14 sta  $F714
1AF8: 7F 00 36 clr  $0036
1AFB: 39       rts  
1AFC: 7F 00 25 clr  $0025
1AFF: 7F 00 2B clr  $002B
1B02: 7E 12 F8 jmp  $12F8
1B05: CE 07 F0 ldx  #$07F0
1B08: DF CA    stx  $CA
1B0A: 8D 05    bsr  $1B11
1B0C: CE 07 F6 ldx  #$07F6
1B0F: DF CA    stx  $CA
1B11: 20 2B    bra  $1B3E
1B13: DE CA    ldx  $CA
1B15: EE 08    ldx  (x+$08)
1B17: DF 4E    stx  $4E
1B19: A6 01    lda  (x+$01)
1B1B: 81 FF    cmpa #$FF
1B1D: 26 1D    bne  $1B3C
1B1F: 6F 01    clr  (x+$01)
1B21: A6 08    lda  (x+$08)
1B23: E6 09    ldb  (x+$09)
1B25: DE CA    ldx  $CA
1B27: E7 09    stb  (x+$09)
1B29: A7 08    sta  (x+$08)
1B2B: DE 4E    ldx  $4E
1B2D: B6 07 F2 lda  $07F2
1B30: F6 07 F3 ldb  $07F3
1B33: E7 09    stb  (x+$09)
1B35: A7 08    sta  (x+$08)
1B37: FF 07 F2 stx  $07F2
1B3A: 20 02    bra  $1B3E
1B3C: DF CA    stx  $CA
1B3E: DE CA    ldx  $CA
1B40: EE 08    ldx  (x+$08)
1B42: 26 CF    bne  $1B13
1B44: 39       rts  
1B45: 01       nop  
1B46: 40       nega 
1B47: 00       illegal
1B48: 07       tpa  
1B49: 5C       incb 

; subroutine from jumpatble $083
1B4A: BD 32 ED jsr  $32ED
1B4D: FF 04 D2 stx  $04D2
1B50: FE 07 F2 ldx  $07F2
1B53: DF 4E    stx  $4E
1B55: 27 64    beq  $1BBB
1B57: 08       inx  
1B58: DF 1D    stx  $1D
1B5A: FE 04 D2 ldx  $04D2
1B5D: C6 07    ldb  #$07
1B5F: BD FE 2F jsr  $FE2F
1B62: DE 4E    ldx  $4E
1B64: A6 04    lda  (x+$04)
1B66: AA 00    ora  (x+$00)
1B68: A7 04    sta  (x+$04)
1B6A: A6 05    lda  (x+$05)
1B6C: 8A F0    ora  #$F0
1B6E: A7 05    sta  (x+$05)
1B70: EE 08    ldx  (x+$08)
1B72: FF 07 F2 stx  $07F2
1B75: DE 4E    ldx  $4E
1B77: 6F 09    clr  (x+$09)
1B79: 6F 08    clr  (x+$08)
1B7B: FE 04 D2 ldx  $04D2
1B7E: A6 02    lda  (x+$02)
1B80: 81 0C    cmpa #$0C
1B82: 27 07    beq  $1B8B
1B84: B6 FF E7 lda  $FFE7
1B87: 81 07    cmpa #$07
1B89: 26 07    bne  $1B92
1B8B: CE 07 FA ldx  #$07FA
1B8E: DF CF    stx  $CF
1B90: 20 05    bra  $1B97
1B92: CE 07 F4 ldx  #$07F4
1B95: DF CF    stx  $CF
1B97: DE CF    ldx  $CF
1B99: EE 00    ldx  (x+$00)
1B9B: 26 0C    bne  $1BA9
1B9D: DE CF    ldx  $CF
1B9F: 96 4E    lda  $4E
1BA1: D6 4F    ldb  $4F
1BA3: E7 01    stb  (x+$01)
1BA5: A7 00    sta  (x+$00)
1BA7: 20 0C    bra  $1BB5
1BA9: DE CF    ldx  $CF
1BAB: EE 02    ldx  (x+$02)
1BAD: 96 4E    lda  $4E
1BAF: D6 4F    ldb  $4F
1BB1: E7 09    stb  (x+$09)
1BB3: A7 08    sta  (x+$08)
1BB5: DE CF    ldx  $CF
1BB7: E7 03    stb  (x+$03)
1BB9: A7 02    sta  (x+$02)
1BBB: 96 65    lda  $65
1BBD: 27 03    beq  $1BC2
1BBF: DE 4E    ldx  $4E
1BC1: 39       rts  
1BC2: DE 4E    ldx  $4E
1BC4: 7E 32 F5 jmp  $32F5

; subroutine from jumptable $0809
1BC7: BD 32 ED jsr  $32ED
1BCA: FF 04 D7 stx  $04D7
1BCD: EE 00    ldx  (x+$00)
1BCF: A6 00    lda  (x+$00)
1BD1: B7 04 D5 sta  $04D5
1BD4: FE 04 D7 ldx  $04D7
1BD7: EE 02    ldx  (x+$02)
1BD9: A6 00    lda  (x+$00)
1BDB: B7 04 D6 sta  $04D6
1BDE: B6 04 D5 lda  $04D5
1BE1: 44       lsra 
1BE2: 44       lsra 
1BE3: 44       lsra 
1BE4: 44       lsra 
1BE5: 16       tab  
1BE6: 48       asla 
1BE7: 48       asla 
1BE8: 1B       aba  
1BE9: 48       asla 
1BEA: B7 04 D4 sta  $04D4
1BED: B6 1C 8C lda  $1C8C
1BF0: F6 1C 8D ldb  $1C8D
1BF3: FB 04 D4 addb $04D4
1BF6: 89 00    adca #$00
1BF8: D7 4F    stb  $4F
1BFA: 97 4E    sta  $4E
1BFC: DE 4E    ldx  $4E
1BFE: A6 02    lda  (x+$02)
1C00: 81 FF    cmpa #$FF
1C02: 26 04    bne  $1C08
1C04: 6F 01    clr  (x+$01)
1C06: 20 04    bra  $1C0C
1C08: 86 C0    lda  #$C0
1C0A: A7 01    sta  (x+$01)
1C0C: B6 04 D6 lda  $04D6
1C0F: A7 03    sta  (x+$03)
1C11: 81 0C    cmpa #$0C
1C13: 27 07    beq  $1C1C
1C15: B6 FF E7 lda  $FFE7
1C18: 81 07    cmpa #$07
1C1A: 26 0C    bne  $1C28
1C1C: CE 07 FA ldx  #$07FA
1C1F: DF CF    stx  $CF
1C21: CE 07 F6 ldx  #$07F6
1C24: DF CD    stx  $CD
1C26: 20 12    bra  $1C3A
1C28: CE 07 F4 ldx  #$07F4
1C2B: DF CF    stx  $CF
1C2D: CE 07 F0 ldx  #$07F0
1C30: DF CD    stx  $CD
1C32: 20 06    bra  $1C3A
1C34: DE CD    ldx  $CD
1C36: EE 08    ldx  (x+$08)
1C38: DF CD    stx  $CD
1C3A: DE CD    ldx  $CD
1C3C: EE 08    ldx  (x+$08)
1C3E: 9C 4E    cmpx $4E
1C40: 26 F2    bne  $1C34
1C42: DE 4E    ldx  $4E
1C44: A6 08    lda  (x+$08)
1C46: E6 09    ldb  (x+$09)
1C48: DE CD    ldx  $CD
1C4A: E7 09    stb  (x+$09)
1C4C: A7 08    sta  (x+$08)
1C4E: DE CF    ldx  $CF
1C50: EE 00    ldx  (x+$00)
1C52: 26 16    bne  $1C6A
1C54: DE 4E    ldx  $4E
1C56: 6F 09    clr  (x+$09)
1C58: 6F 08    clr  (x+$08)
1C5A: DE CF    ldx  $CF
1C5C: 96 4E    lda  $4E
1C5E: D6 4F    ldb  $4F
1C60: E7 03    stb  (x+$03)
1C62: A7 02    sta  (x+$02)
1C64: E7 01    stb  (x+$01)
1C66: A7 00    sta  (x+$00)
1C68: 20 1A    bra  $1C84
1C6A: DE CF    ldx  $CF
1C6C: EE 00    ldx  (x+$00)
1C6E: A6 08    lda  (x+$08)
1C70: E6 09    ldb  (x+$09)
1C72: DE 4E    ldx  $4E
1C74: E7 09    stb  (x+$09)
1C76: A7 08    sta  (x+$08)
1C78: DE CF    ldx  $CF
1C7A: EE 00    ldx  (x+$00)
1C7C: 96 4E    lda  $4E
1C7E: D6 4F    ldb  $4F
1C80: E7 09    stb  (x+$09)
1C82: A7 08    sta  (x+$08)
1C84: 96 65    lda  $65
1C86: 27 01    beq  $1C89
1C88: 39       rts  
1C89: 7E 32 F5 jmp  $32F5
1C8C: 07       tpa  
1C8D: 5C       incb 
1C8E: CE 02 BB ldx  #$02BB
1C91: FF 04 DD stx  $04DD
1C94: 86 01    lda  #$01
1C96: B7 04 DC sta  $04DC
1C99: CE 04 DC ldx  #$04DC
1C9C: 86 06    lda  #$06
1C9E: 3F       swi  
1C9F: 96 30    lda  $30
1CA1: 84 0F    anda #$0F
1CA3: B7 04 D9 sta  $04D9
1CA6: CE 06 04 ldx  #$0604
1CA9: FF 04 DF stx  $04DF
1CAC: 4F       clra 
1CAD: F6 04 D9 ldb  $04D9
1CB0: 58       aslb 
1CB1: 49       rola 
1CB2: FB 04 E0 addb $04E0
1CB5: B9 04 DF adca $04DF
1CB8: F7 04 E0 stb  $04E0
1CBB: B7 04 DF sta  $04DF
1CBE: FE 04 DF ldx  $04DF
1CC1: EE 00    ldx  (x+$00)
1CC3: FF 04 DA stx  $04DA
1CC6: AD 00    jsr  (x+$00)
1CC8: CE 02 BB ldx  #$02BB
1CCB: 6F 00    clr  (x+$00)
1CCD: 6F 01    clr  (x+$01)
1CCF: 6F 04    clr  (x+$04)
1CD1: BD 32 ED jsr  $32ED
1CD4: FE 1C DC ldx  $1CDC
1CD7: BD 12 F8 jsr  $12F8
1CDA: 20 B2    bra  $1C8E
1CDC: 00       illegal
1CDD: 24 B6    bcc  $1C95
1CDF: F7 21 84 stb  $2184
1CE2: 7A 26 06 dec  $2606
1CE5: 86 20    lda  #$20
1CE7: B7 F7 21 sta  $F721
1CEA: 3B       rti  
1CEB: C6 C0    ldb  #$C0
1CED: F7 F7 20 stb  $F720
1CF0: 85 02    bita #$02
1CF2: 27 28    beq  $1D1C
1CF4: BD 1A C4 jsr  $1AC4
1CF7: DE 4A    ldx  $4A
1CF9: E6 00    ldb  (x+$00)
1CFB: F1 02 39 cmpb $0239
1CFE: 27 0D    beq  $1D0D
1D00: F1 02 3A cmpb $023A
1D03: 26 17    bne  $1D1C
1D05: F6 02 55 ldb  $0255
1D08: CA 80    orb  #$80
1D0A: F7 02 55 stb  $0255
1D0D: 7F 00 35 clr  $0035
1D10: 97 36    sta  $36
1D12: BD 1A B6 jsr  $1AB6
1D15: CE 16 01 ldx  #$1601
1D18: BD 33 18 jsr  $3318
1D1B: 3B       rti  
1D1C: BD 1A B6 jsr  $1AB6
1D1F: BD 1A DE jsr  $1ADE
1D22: 3B       rti  
1D23: F6 F7 20 ldb  $F720
1D26: 86 40    lda  #$40
1D28: B7 F7 21 sta  $F721
1D2B: B6 F7 20 lda  $F720
1D2E: 85 10    bita #$10
1D30: 26 01    bne  $1D33
1D32: 3B       rti  
1D33: 96 34    lda  $34
1D35: 97 35    sta  $35
1D37: BD 1A DE jsr  $1ADE
1D3A: B6 03 B0 lda  $03B0
1D3D: 2A 30    bpl  $1D6F
1D3F: B6 F7 C6 lda  $F7C6
1D42: 8A 10    ora  #$10
1D44: B7 F7 C6 sta  $F7C6
1D47: D6 34    ldb  $34
1D49: F7 04 E1 stb  $04E1
1D4C: 7F 04 E2 clr  $04E2
1D4F: C6 04    ldb  #$04
1D51: FE 04 E1 ldx  $04E1
1D54: B6 F7 21 lda  $F721
1D57: 84 02    anda #$02
1D59: 26 0C    bne  $1D67
1D5B: 09       dex  
1D5C: 27 02    beq  $1D60
1D5E: 20 F4    bra  $1D54
1D60: 5A       decb 
1D61: 26 EE    bne  $1D51
1D63: 86 01    lda  #$01
1D65: 97 35    sta  $35
1D67: B6 F7 C6 lda  $F7C6
1D6A: 84 EF    anda #$EF
1D6C: B7 F7 C6 sta  $F7C6
1D6F: 3B       rti  
1D70: B6 F7 C0 lda  $F7C0
1D73: 2B 1F    bmi  $1D94
1D75: B6 F7 D0 lda  $F7D0
1D78: 86 10    lda  #$10
1D7A: B7 F7 D8 sta  $F7D8
1D7D: F6 F7 D9 ldb  $F7D9
1D80: F7 04 1B stb  $041B
1D83: 4C       inca 
1D84: B7 F7 D8 sta  $F7D8
1D87: F6 F7 D9 ldb  $F7D9
1D8A: F7 04 1C stb  $041C
1D8D: CE 1E DD ldx  #$1EDD
1D90: BD 33 18 jsr  $3318
1D93: 3B       rti  
1D94: F6 F7 C1 ldb  $F7C1
1D97: FE 04 04 ldx  $0404
1D9A: 6E 00    jmp  (x+$00)
1D9C: FE 03 AC ldx  $03AC
1D9F: E6 00    ldb  (x+$00)
1DA1: C1 AA    cmpb #$AA
1DA3: 27 15    beq  $1DBA
1DA5: F7 F7 C1 stb  $F7C1
1DA8: 08       inx  
1DA9: FF 03 AC stx  $03AC
1DAC: 3B       rti  
1DAD: F6 03 FE ldb  $03FE
1DB0: F7 F7 C1 stb  $F7C1
1DB3: CE 1D BA ldx  #$1DBA
1DB6: FF 04 04 stx  $0404
1DB9: 3B       rti  
1DBA: B6 04 19 lda  $0419
1DBD: 84 FE    anda #$FE
1DBF: 81 88    cmpa #$88
1DC1: 27 1B    beq  $1DDE
1DC3: CE 1D CA ldx  #$1DCA
1DC6: FF 04 04 stx  $0404
1DC9: 3B       rti  
1DCA: 84 70    anda #$70
1DCC: 26 24    bne  $1DF2
1DCE: F7 03 F2 stb  $03F2
1DD1: 2A 1F    bpl  $1DF2
1DD3: C4 20    andb #$20
1DD5: 26 07    bne  $1DDE
1DD7: CE 1D EB ldx  #$1DEB
1DDA: FF 04 04 stx  $0404
1DDD: 3B       rti  
1DDE: CE 02 66 ldx  #$0266
1DE1: FF 03 AC stx  $03AC
1DE4: CE 1E 01 ldx  #$1E01
1DE7: FF 04 04 stx  $0404
1DEA: 3B       rti  
1DEB: 84 70    anda #$70
1DED: 26 03    bne  $1DF2
1DEF: F7 03 F3 stb  $03F3
1DF2: B7 03 F4 sta  $03F4
1DF5: 86 1A    lda  #$1A
1DF7: B7 F7 C0 sta  $F7C0
1DFA: CE 1E 2B ldx  #$1E2B
1DFD: BD 33 18 jsr  $3318
1E00: 3B       rti  
1E01: 84 70    anda #$70
1E03: 26 ED    bne  $1DF2
1E05: C1 AA    cmpb #$AA
1E07: 27 E9    beq  $1DF2
1E09: FE 03 AC ldx  $03AC
1E0C: B6 04 19 lda  $0419
1E0F: 84 FE    anda #$FE
1E11: 81 88    cmpa #$88
1E13: 26 07    bne  $1E1C
1E15: 8C 02 83 cmpx #$0283
1E18: 27 DB    beq  $1DF5
1E1A: 20 07    bra  $1E23
1E1C: 86 08    lda  #$08
1E1E: 8C 02 7A cmpx #$027A
1E21: 27 CF    beq  $1DF2
1E23: E7 00    stb  (x+$00)
1E25: 08       inx  
1E26: FF 03 AC stx  $03AC
1E29: 3B       rti  
1E2A: B6 03 F4 lda  $03F4
1E2D: 27 1A    beq  $1E49
1E2F: B6 04 E3 lda  $04E3
1E32: 81 02    cmpa #$02
1E34: 25 0E    bcs  $1E44
1E36: B6 03 F5 lda  $03F5
1E39: BA 03 F4 ora  $03F4
1E3C: B7 03 F5 sta  $03F5
1E3F: 7F 04 E3 clr  $04E3
1E42: 20 6B    bra  $1EAF
1E44: 7C 04 E3 inc  $04E3
1E47: 20 73    bra  $1EBC
1E49: 7F 04 E3 clr  $04E3
1E4C: B6 03 F2 lda  $03F2
1E4F: 84 E0    anda #$E0
1E51: 27 5C    beq  $1EAF
1E53: B6 03 F2 lda  $03F2
1E56: 84 40    anda #$40
1E58: 27 0F    beq  $1E69
1E5A: B6 03 F3 lda  $03F3
1E5D: 84 30    anda #$30
1E5F: 27 08    beq  $1E69
1E61: B6 04 02 lda  $0402
1E64: 8A 40    ora  #$40
1E66: B7 04 02 sta  $0402
1E69: B6 03 CD lda  $03CD
1E6C: 81 10    cmpa #$10
1E6E: 25 0E    bcs  $1E7E
1E70: B6 03 F2 lda  $03F2
1E73: 84 40    anda #$40
1E75: 27 2B    beq  $1EA2
1E77: B6 03 F3 lda  $03F3
1E7A: 84 20    anda #$20
1E7C: 27 24    beq  $1EA2
1E7E: FE 03 CE ldx  $03CE
1E81: B6 03 F2 lda  $03F2
1E84: F6 03 F3 ldb  $03F3
1E87: E7 01    stb  (x+$01)
1E89: A7 00    sta  (x+$00)
1E8B: 7C 03 CD inc  $03CD
1E8E: 8C 03 EE cmpx #$03EE
1E91: 26 08    bne  $1E9B
1E93: CE 03 D0 ldx  #$03D0
1E96: FF 03 CE stx  $03CE
1E99: 20 14    bra  $1EAF
1E9B: 08       inx  
1E9C: 08       inx  
1E9D: FF 03 CE stx  $03CE
1EA0: 20 0D    bra  $1EAF
1EA2: B6 04 03 lda  $0403
1EA5: 8A 80    ora  #$80
1EA7: B7 04 03 sta  $0403
1EAA: 86 01    lda  #$01
1EAC: B7 04 E3 sta  $04E3
1EAF: B6 03 CD lda  $03CD
1EB2: 81 01    cmpa #$01
1EB4: 22 06    bhi  $1EBC
1EB6: CE 04 11 ldx  #$0411
1EB9: 86 04    lda  #$04
1EBB: 3F       swi  
1EBC: B6 04 E3 lda  $04E3
1EBF: 26 10    bne  $1ED1
1EC1: B6 04 02 lda  $0402
1EC4: B7 04 19 sta  $0419
1EC7: B6 04 02 lda  $0402
1ECA: 84 10    anda #$10
1ECC: B7 04 02 sta  $0402
1ECF: 20 08    bra  $1ED9
1ED1: B6 04 19 lda  $0419
1ED4: 8A 01    ora  #$01
1ED6: B7 04 19 sta  $0419
1ED9: 7E 22 43 jmp  $2243
1EDC: B6 03 CD lda  $03CD
1EDF: 81 10    cmpa #$10
1EE1: 24 42    bcc  $1F25
1EE3: B6 04 1B lda  $041B
1EE6: F6 04 1C ldb  $041C
1EE9: C0 09    subb #$09
1EEB: 82 00    sbca #$00
1EED: 24 0E    bcc  $1EFD
1EEF: B6 04 1B lda  $041B
1EF2: F6 04 1C ldb  $041C
1EF5: 8B 40    adda #$40
1EF7: F7 04 1C stb  $041C
1EFA: B7 04 1B sta  $041B
1EFD: B6 04 1B lda  $041B
1F00: F6 04 1C ldb  $041C
1F03: CB F7    addb #$F7
1F05: 89 3F    adca #$3F
1F07: FE 03 CE ldx  $03CE
1F0A: E7 01    stb  (x+$01)
1F0C: A7 00    sta  (x+$00)
1F0E: 7C 03 CD inc  $03CD
1F11: 8C 03 EE cmpx #$03EE
1F14: 26 08    bne  $1F1E
1F16: CE 03 D0 ldx  #$03D0
1F19: FF 03 CE stx  $03CE
1F1C: 20 0F    bra  $1F2D
1F1E: 08       inx  
1F1F: 08       inx  
1F20: FF 03 CE stx  $03CE
1F23: 20 08    bra  $1F2D
1F25: B6 04 03 lda  $0403
1F28: 8A 40    ora  #$40
1F2A: B7 04 03 sta  $0403
1F2D: B6 03 CD lda  $03CD
1F30: 81 01    cmpa #$01
1F32: 22 06    bhi  $1F3A
1F34: CE 04 11 ldx  #$0411
1F37: 86 04    lda  #$04
1F39: 3F       swi  
1F3A: 39       rts  
1F3B: CE 04 11 ldx  #$0411
1F3E: FF 04 EA stx  $04EA
1F41: CE 04 06 ldx  #$0406
1F44: FF 04 EC stx  $04EC
1F47: CE 03 F6 ldx  #$03F6
1F4A: FF 04 EE stx  $04EE
1F4D: 86 FD    lda  #$FD
1F4F: B7 04 E9 sta  $04E9
1F52: CE 04 E9 ldx  #$04E9
1F55: 86 06    lda  #$06
1F57: 3F       swi  
1F58: B7 04 E6 sta  $04E6
1F5B: B6 03 FA lda  $03FA
1F5E: 84 80    anda #$80
1F60: 27 20    beq  $1F82
1F62: CE 03 F6 ldx  #$03F6
1F65: 6F 00    clr  (x+$00)
1F67: 6F 01    clr  (x+$01)
1F69: 6F 04    clr  (x+$04)
1F6B: B6 03 FF lda  $03FF
1F6E: 27 0A    beq  $1F7A
1F70: FE 04 00 ldx  $0400
1F73: A7 00    sta  (x+$00)
1F75: 7F 03 FF clr  $03FF
1F78: 20 08    bra  $1F82
1F7A: B6 04 02 lda  $0402
1F7D: 84 EF    anda #$EF
1F7F: B7 04 02 sta  $0402
1F82: B6 04 0A lda  $040A
1F85: 84 80    anda #$80
1F87: 27 62    beq  $1FEB
1F89: CE 04 06 ldx  #$0406
1F8C: 6F 00    clr  (x+$00)
1F8E: 6F 01    clr  (x+$01)
1F90: 6F 04    clr  (x+$04)
1F92: BD 32 ED jsr  $32ED
1F95: B6 F7 C4 lda  $F7C4
1F98: 8A 02    ora  #$02
1F9A: B7 F7 C4 sta  $F7C4
1F9D: BD 32 F5 jsr  $32F5
1FA0: CE 0C 35 ldx  #$0C35
1FA3: 09       dex  
1FA4: 26 FD    bne  $1FA3
1FA6: BD 32 ED jsr  $32ED
1FA9: B6 F7 C4 lda  $F7C4
1FAC: 84 FD    anda #$FD
1FAE: B7 F7 C4 sta  $F7C4
1FB1: 86 50    lda  #$50
1FB3: FE 04 0E ldx  $040E
1FB6: A7 00    sta  (x+$00)
1FB8: CE 04 06 ldx  #$0406
1FBB: FF 04 EA stx  $04EA
1FBE: 86 01    lda  #$01
1FC0: B7 04 E9 sta  $04E9
1FC3: CE 04 E9 ldx  #$04E9
1FC6: 86 06    lda  #$06
1FC8: 3F       swi  
1FC9: CE 04 06 ldx  #$0406
1FCC: 6F 00    clr  (x+$00)
1FCE: 6F 01    clr  (x+$01)
1FD0: 6F 04    clr  (x+$04)
1FD2: FE 02 90 ldx  $0290
1FD5: 26 07    bne  $1FDE
1FD7: 86 12    lda  #$12
1FD9: B7 04 19 sta  $0419
1FDC: 20 05    bra  $1FE3
1FDE: 86 16    lda  #$16
1FE0: B7 04 19 sta  $0419
1FE3: 86 32    lda  #$32
1FE5: BD 08 1E jsr  $081E
1FE8: BD 22 43 jsr  $2243
1FEB: B6 03 F5 lda  $03F5
1FEE: 27 03    beq  $1FF3
1FF0: BD 22 3C jsr  $223C
1FF3: BD 32 ED jsr  $32ED
1FF6: B6 03 CD lda  $03CD
1FF9: 26 0C    bne  $2007
1FFB: CE 04 11 ldx  #$0411
1FFE: 6F 00    clr  (x+$00)
2000: 6F 01    clr  (x+$01)
2002: 6F 04    clr  (x+$04)
2004: 7E 1F 3B jmp  $1F3B
2007: BD 32 F5 jsr  $32F5
200A: B6 04 03 lda  $0403
200D: 27 06    beq  $2015
200F: BD 22 3C jsr  $223C
2012: 7E 22 34 jmp  $2234
2015: FE 03 F0 ldx  $03F0
2018: EE 00    ldx  (x+$00)
201A: FF 02 61 stx  $0261
201D: 7A 03 CD dec  $03CD
2020: FE 03 F0 ldx  $03F0
2023: 8C 03 EE cmpx #$03EE
2026: 26 08    bne  $2030
2028: CE 03 D0 ldx  #$03D0
202B: FF 03 F0 stx  $03F0
202E: 20 05    bra  $2035
2030: 08       inx  
2031: 08       inx  
2032: FF 03 F0 stx  $03F0
2035: B6 02 61 lda  $0261
2038: 84 80    anda #$80
203A: 26 18    bne  $2054
203C: B6 04 10 lda  $0410
203F: 84 40    anda #$40
2041: 26 03    bne  $2046
2043: 7E 22 34 jmp  $2234
2046: FE 02 61 ldx  $0261
2049: FF 02 63 stx  $0263
204C: 86 20    lda  #$20
204E: B7 02 62 sta  $0262
2051: 7E 22 0A jmp  $220A
2054: B6 02 61 lda  $0261
2057: 84 20    anda #$20
2059: 26 03    bne  $205E
205B: 7E 20 E4 jmp  $20E4
205E: B6 04 10 lda  $0410
2061: 84 20    anda #$20
2063: 26 03    bne  $2068
2065: 7E 22 34 jmp  $2234
2068: B6 03 AC lda  $03AC
206B: F6 03 AD ldb  $03AD
206E: 58       aslb 
206F: 49       rola 
2070: CE 02 66 ldx  #$0266
2073: FF 04 F0 stx  $04F0
2076: F0 04 F1 subb $04F1
2079: B2 04 F0 sbca $04F0
207C: C0 01    subb #$01
207E: 82 00    sbca #$00
2080: F7 04 E5 stb  $04E5
2083: B7 04 E4 sta  $04E4
2086: FE 03 AC ldx  $03AC
2089: 09       dex  
208A: FF 03 AC stx  $03AC
208D: 7F 02 8E clr  $028E
2090: 20 31    bra  $20C3
2092: B6 02 8E lda  $028E
2095: 8B 02    adda #$02
2097: B7 02 8E sta  $028E
209A: FE 03 AC ldx  $03AC
209D: A6 00    lda  (x+$00)
209F: 44       lsra 
20A0: 44       lsra 
20A1: 44       lsra 
20A2: 44       lsra 
20A3: FE 04 E4 ldx  $04E4
20A6: A7 00    sta  (x+$00)
20A8: 09       dex  
20A9: FF 04 E4 stx  $04E4
20AC: FE 03 AC ldx  $03AC
20AF: A6 00    lda  (x+$00)
20B1: 84 0F    anda #$0F
20B3: FE 04 E4 ldx  $04E4
20B6: A7 00    sta  (x+$00)
20B8: 09       dex  
20B9: FF 04 E4 stx  $04E4
20BC: FE 03 AC ldx  $03AC
20BF: 09       dex  
20C0: FF 03 AC stx  $03AC
20C3: B6 03 AC lda  $03AC
20C6: F6 03 AD ldb  $03AD
20C9: CE 02 66 ldx  #$0266
20CC: FF 04 F0 stx  $04F0
20CF: F0 04 F1 subb $04F1
20D2: B2 04 F0 sbca $04F0
20D5: 24 BB    bcc  $2092
20D7: 86 40    lda  #$40
20D9: B7 02 62 sta  $0262
20DC: 86 80    lda  #$80
20DE: B7 02 64 sta  $0264
20E1: 7E 22 0A jmp  $220A
20E4: B6 02 61 lda  $0261
20E7: 84 40    anda #$40
20E9: 27 66    beq  $2151
20EB: B6 02 62 lda  $0262
20EE: 84 04    anda #$04
20F0: 27 08    beq  $20FA
20F2: B6 04 E7 lda  $04E7
20F5: 27 03    beq  $20FA
20F7: 7E 1F F3 jmp  $1FF3
20FA: B6 02 62 lda  $0262
20FD: 84 20    anda #$20
20FF: 27 08    beq  $2109
2101: B6 02 62 lda  $0262
2104: 84 22    anda #$22
2106: B7 02 62 sta  $0262
2109: B6 02 62 lda  $0262
210C: 84 01    anda #$01
210E: 27 06    beq  $2116
2110: BD 22 3C jsr  $223C
2113: 7E 1F F3 jmp  $1FF3
2116: B6 02 62 lda  $0262
2119: 84 32    anda #$32
211B: 27 1A    beq  $2137
211D: B6 04 10 lda  $0410
2120: 84 20    anda #$20
2122: 26 03    bne  $2127
2124: 7E 22 34 jmp  $2234
2127: B6 02 62 lda  $0262
212A: 84 32    anda #$32
212C: B7 02 64 sta  $0264
212F: 86 40    lda  #$40
2131: B7 02 62 sta  $0262
2134: 7E 22 0A jmp  $220A
2137: B6 02 62 lda  $0262
213A: 84 04    anda #$04
213C: 26 03    bne  $2141
213E: 7E 21 FB jmp  $21FB
2141: 86 10    lda  #$10
2143: B7 02 62 sta  $0262
2146: B6 03 86 lda  $0386
2149: 26 03    bne  $214E
214B: 7E 22 0A jmp  $220A
214E: 7E 21 FB jmp  $21FB
2151: FE 02 90 ldx  $0290
2154: 26 03    bne  $2159
2156: 7E 22 34 jmp  $2234
2159: B6 02 61 lda  $0261
215C: 84 0F    anda #$0F
215E: B7 04 E6 sta  $04E6
2161: FF 04 F0 stx  $04F0
2164: 4F       clra 
2165: F6 04 E6 ldb  $04E6
2168: 58       aslb 
2169: 49       rola 
216A: FB 04 F1 addb $04F1
216D: B9 04 F0 adca $04F0
2170: F7 04 F1 stb  $04F1
2173: B7 04 F0 sta  $04F0
2176: FE 04 F0 ldx  $04F0
2179: EE 0D    ldx  (x+$0D)
217B: FF 04 E4 stx  $04E4
217E: B6 02 62 lda  $0262
2181: 84 7F    anda #$7F
2183: B7 04 E6 sta  $04E6
2186: B7 02 65 sta  $0265
2189: FE 04 E4 ldx  $04E4
218C: FF 04 F0 stx  $04F0
218F: 4F       clra 
2190: F6 04 E6 ldb  $04E6
2193: 58       aslb 
2194: 49       rola 
2195: FB 04 F1 addb $04F1
2198: B9 04 F0 adca $04F0
219B: F7 04 F1 stb  $04F1
219E: B7 04 F0 sta  $04F0
21A1: FE 04 F0 ldx  $04F0
21A4: EE 00    ldx  (x+$00)
21A6: FF 02 63 stx  $0263
21A9: B6 02 63 lda  $0263
21AC: 84 40    anda #$40
21AE: 27 07    beq  $21B7
21B0: 86 01    lda  #$01
21B2: B7 04 E7 sta  $04E7
21B5: 20 03    bra  $21BA
21B7: 7F 04 E7 clr  $04E7
21BA: B6 02 62 lda  $0262
21BD: 84 80    anda #$80
21BF: 27 23    beq  $21E4
21C1: B6 04 E8 lda  $04E8
21C4: B8 02 8F eora $028F
21C7: B7 04 E8 sta  $04E8
21CA: 4D       tsta 
21CB: 27 03    beq  $21D0
21CD: 7E 1F F3 jmp  $1FF3
21D0: B6 02 63 lda  $0263
21D3: 84 40    anda #$40
21D5: 27 03    beq  $21DA
21D7: 7E 1F F3 jmp  $1FF3
21DA: B6 04 02 lda  $0402
21DD: 8A 08    ora  #$08
21DF: B7 04 02 sta  $0402
21E2: 20 03    bra  $21E7
21E4: 7F 04 E8 clr  $04E8
21E7: B6 02 62 lda  $0262
21EA: 84 80    anda #$80
21EC: B7 02 62 sta  $0262
21EF: B6 02 63 lda  $0263
21F2: 84 80    anda #$80
21F4: 26 05    bne  $21FB
21F6: B6 03 86 lda  $0386
21F9: 27 0F    beq  $220A
21FB: B6 04 10 lda  $0410
21FE: 84 02    anda #$02
2200: 27 32    beq  $2234
2202: CE 03 87 ldx  #$0387
2205: 86 04    lda  #$04
2207: 3F       swi  
2208: 20 0D    bra  $2217
220A: B6 04 10 lda  $0410
220D: 84 01    anda #$01
220F: 27 23    beq  $2234
2211: CE 02 9A ldx  #$029A
2214: 86 04    lda  #$04
2216: 3F       swi  
2217: CE 02 92 ldx  #$0292
221A: FF 04 EA stx  $04EA
221D: 86 01    lda  #$01
221F: B7 04 E9 sta  $04E9
2222: CE 04 E9 ldx  #$04E9
2225: 86 06    lda  #$06
2227: 3F       swi  
2228: CE 02 92 ldx  #$0292
222B: 6F 00    clr  (x+$00)
222D: 6F 01    clr  (x+$01)
222F: 6F 04    clr  (x+$04)
2231: 7E 1F F3 jmp  $1FF3
2234: 86 32    lda  #$32
2236: BD 08 1E jsr  $081E
2239: 7E 1F F3 jmp  $1FF3
223C: 7F 03 F5 clr  $03F5
223F: 7F 04 03 clr  $0403
2242: 39       rts  
2243: 86 32    lda  #$32
2245: FE 04 0E ldx  $040E
2248: A7 00    sta  (x+$00)
224A: B6 04 19 lda  $0419
224D: 84 04    anda #$04
224F: 27 0E    beq  $225F
2251: CE 1D 9C ldx  #$1D9C
2254: FF 04 04 stx  $0404
2257: FE 02 90 ldx  $0290
225A: FF 03 AC stx  $03AC
225D: 20 06    bra  $2265
225F: CE 1D AD ldx  #$1DAD
2262: FF 04 04 stx  $0404
2265: 86 9A    lda  #$9A
2267: B7 F7 C0 sta  $F7C0
226A: B6 04 19 lda  $0419
226D: B7 F7 C1 sta  $F7C1
2270: 39       rts  

; subroutine from jumptable $080C
2271: BD 32 ED jsr  $32ED
2274: B7 04 F2 sta  $04F2
2277: B6 FF E7 lda  $FFE7
227A: 81 08    cmpa #$08
227C: 26 08    bne  $2286
227E: B6 04 F2 lda  $04F2
2281: 84 DF    anda #$DF
2283: B7 04 F2 sta  $04F2
2286: B6 04 F2 lda  $04F2
2289: 84 01    anda #$01
228B: 27 14    beq  $22A1
228D: B6 04 F2 lda  $04F2
2290: 84 E1    anda #$E1
2292: F6 04 10 ldb  $0410
2295: B7 04 F3 sta  $04F3
2298: FA 04 F3 orb  $04F3
229B: F7 04 10 stb  $0410
229E: 7E 32 F5 jmp  $32F5
22A1: B6 04 10 lda  $0410
22A4: 8A 82    ora  #$82
22A6: B7 04 10 sta  $0410
22A9: 7E 32 F5 jmp  $32F5

; subroutine from jumptable $080F
22AC: BD 32 ED jsr  $32ED
22AF: B6 04 10 lda  $0410
22B2: 84 82    anda #$82
22B4: B7 04 10 sta  $0410
22B7: 7E 32 F5 jmp  $32F5

; subroutine from jumptable $0812
22BA: BD 32 ED jsr  $32ED
22BD: 86 06    lda  #$06
22BF: B7 04 02 sta  $0402
22C2: 7E 32 F5 jmp  $32F5

; subroutine from jumptable $0815
22C5: BD 32 ED jsr  $32ED
22C8: B7 04 F4 sta  $04F4
22CB: B6 02 2D lda  $022D
22CE: B4 03 FE anda $03FE
22D1: B7 04 F5 sta  $04F5
22D4: 7F 03 FE clr  $03FE
22D7: B6 04 F4 lda  $04F4
22DA: BA 04 F5 ora  $04F5
22DD: B7 03 FE sta  $03FE
22E0: 7E 32 F5 jmp  $32F5

; subroutine from jumptable $0818
22E3: BD 32 ED jsr  $32ED
22E6: B6 04 02 lda  $0402
22E9: 8A 08    ora  #$08
22EB: B7 04 02 sta  $0402
22EE: 7E 32 F5 jmp  $32F5

; subroutine from jumptable $081B
22F1: BD 32 ED jsr  $32ED
22F4: B6 04 02 lda  $0402
22F7: 8A 20    ora  #$20
22F9: B7 04 02 sta  $0402

; subroutine from jumptable $081E
22FC: 7E 32 F5 jmp  $32F5
22FF: BD 32 ED jsr  $32ED
2302: B7 04 F6 sta  $04F6
2305: FE 04 00 ldx  $0400
2308: A6 00    lda  (x+$00)
230A: 26 10    bne  $231C
230C: B6 04 02 lda  $0402
230F: 8A 10    ora  #$10
2311: B7 04 02 sta  $0402
2314: B6 04 F6 lda  $04F6
2317: A7 00    sta  (x+$00)
2319: 7E 32 F5 jmp  $32F5
231C: B6 04 F6 lda  $04F6
231F: B1 03 FF cmpa $03FF
2322: 23 03    bls  $2327
2324: B7 03 FF sta  $03FF
2327: 7E 32 F5 jmp  $32F5

; subroutine from jumptable $0821
232A: BD 32 ED jsr  $32ED
232D: B7 04 F7 sta  $04F7
2330: 26 05    bne  $2337
2332: 86 FF    lda  #$FF
2334: B7 04 F8 sta  $04F8
2337: B6 04 F7 lda  $04F7
233A: 81 01    cmpa #$01
233C: 26 03    bne  $2341
233E: 7F 04 F8 clr  $04F8
2341: B6 04 F8 lda  $04F8
2344: 26 08    bne  $234E
2346: CE 02 A2 ldx  #$02A2
2349: FF 04 F9 stx  $04F9
234C: 20 06    bra  $2354
234E: CE 03 8F ldx  #$038F
2351: FF 04 F9 stx  $04F9
2354: 86 0A    lda  #$0A
2356: B7 F7 D8 sta  $F7D8
2359: FE 04 F9 ldx  $04F9
235C: A6 02    lda  (x+$02)
235E: B7 F7 D9 sta  $F7D9
2361: 86 0B    lda  #$0B
2363: B7 F7 D8 sta  $F7D8
2366: A6 03    lda  (x+$03)
2368: B7 F7 D9 sta  $F7D9
236B: 86 0E    lda  #$0E
236D: B7 F7 D8 sta  $F7D8
2370: A6 00    lda  (x+$00)
2372: B7 F7 D9 sta  $F7D9
2375: 86 0F    lda  #$0F
2377: B7 F7 D8 sta  $F7D8
237A: A6 01    lda  (x+$01)
237C: B7 F7 D9 sta  $F7D9
237F: 7E 32 F5 jmp  $32F5

; subroutine from jumptable $0824
2382: FF 04 FB stx  $04FB
2385: BD 24 0E jsr  $240E
2388: 7F 02 B0 clr  $02B0
238B: BD 08 27 jsr  $0827
238E: FE 04 FB ldx  $04FB
2391: FF 04 FE stx  $04FE
2394: FF 02 AE stx  $02AE
2397: BD 32 ED jsr  $32ED
239A: 86 00    lda  #$00
239C: 20 17    bra  $23B5
239E: B6 04 FD lda  $04FD
23A1: B7 F7 D8 sta  $F7D8
23A4: FE 04 FE ldx  $04FE
23A7: A6 00    lda  (x+$00)
23A9: B7 F7 D9 sta  $F7D9
23AC: 08       inx  
23AD: FF 04 FE stx  $04FE
23B0: B6 04 FD lda  $04FD
23B3: 8B 01    adda #$01
23B5: B7 04 FD sta  $04FD
23B8: 81 0F    cmpa #$0F
23BA: 23 E2    bls  $239E
23BC: FE 02 AE ldx  $02AE
23BF: A6 12    lda  (x+$12)
23C1: B7 02 AC sta  $02AC
23C4: B7 F7 D0 sta  $F7D0
23C7: A6 13    lda  (x+$13)
23C9: 84 EF    anda #$EF
23CB: B7 02 AD sta  $02AD
23CE: A6 13    lda  (x+$13)
23D0: 84 10    anda #$10
23D2: B7 05 00 sta  $0500
23D5: B6 02 AD lda  $02AD
23D8: B7 F7 D2 sta  $F7D2
23DB: EE 0C    ldx  (x+$0C)
23DD: FF 02 A6 stx  $02A6
23E0: FE 02 AE ldx  $02AE
23E3: A6 01    lda  (x+$01)
23E5: B7 02 AA sta  $02AA
23E8: A6 06    lda  (x+$06)
23EA: 80 01    suba #$01
23EC: B7 02 AB sta  $02AB
23EF: EE 10    ldx  (x+$10)
23F1: FF 02 A8 stx  $02A8
23F4: 86 FF    lda  #$FF
23F6: FE 02 A8 ldx  $02A8
23F9: A7 01    sta  (x+$01)
23FB: BD 32 F5 jsr  $32F5
23FE: 8D 0E    bsr  $240E
2400: B6 05 00 lda  $0500
2403: 27 08    beq  $240D
2405: 86 01    lda  #$01
2407: B7 02 B0 sta  $02B0
240A: BD 08 27 jsr  $0827
240D: 39       rts  
240E: 0F       sei  
240F: 86 01    lda  #$01
2411: B7 03 CA sta  $03CA
2414: 0E       cli  
2415: B6 03 CA lda  $03CA
2418: 26 FB    bne  $2415
241A: 39       rts  

; subroutine from jumptable $0824
241B: B6 02 B0 lda  $02B0
241E: 26 0A    bne  $242A
2420: B6 02 AD lda  $02AD
2423: 84 EF    anda #$EF
2425: B7 02 AD sta  $02AD
2428: 20 08    bra  $2432
242A: B6 02 AD lda  $02AD
242D: 8A 10    ora  #$10
242F: B7 02 AD sta  $02AD
2432: B7 F7 D2 sta  $F7D2
2435: 39       rts  

; subroutine from jumtable $0851
2436: BD 32 ED jsr  $32ED
2439: B7 05 01 sta  $0501
243C: B6 FF E3 lda  $FFE3
243F: 84 40    anda #$40
2441: 27 07    beq  $244A
2443: B6 FF E3 lda  $FFE3
2446: 84 10    anda #$10
2448: 26 1A    bne  $2464
244A: F6 F7 C4 ldb  $F7C4
244D: B6 05 01 lda  $0501
2450: 26 02    bne  $2454
2452: C4 F7    andb #$F7
2454: 4A       deca 
2455: 26 02    bne  $2459
2457: CA 08    orb  #$08
2459: 4A       deca 
245A: 26 02    bne  $245E
245C: C8 08    eorb #$08
245E: F7 02 E6 stb  $02E6
2461: F7 F7 C4 stb  $F7C4
2464: 7E 32 F5 jmp  $32F5

; subroutine from jumptable $0827
2467: FF 05 07 stx  $0507
246A: EE 00    ldx  (x+$00)
246C: A6 00    lda  (x+$00)
246E: B7 05 02 sta  $0502
2471: FE 05 07 ldx  $0507
2474: EE 02    ldx  (x+$02)
2476: EE 00    ldx  (x+$00)
2478: FF 05 03 stx  $0503
247B: 7A 05 02 dec  $0502
247E: 27 0D    beq  $248D
2480: CE 02 E2 ldx  #$02E2
2483: FF 05 05 stx  $0505
2486: CE 02 D6 ldx  #$02D6
2489: 86 02    lda  #$02
248B: 20 0B    bra  $2498
248D: CE 02 DA ldx  #$02DA
2490: FF 05 05 stx  $0505
2493: CE 02 CA ldx  #$02CA
2496: 86 06    lda  #$06
2498: 5F       clrb 
2499: 6D 00    tst  (x+$00)
249B: 27 10    beq  $24AD
249D: 08       inx  
249E: 08       inx  
249F: 5C       incb 
24A0: 11       cba  
24A1: 26 F6    bne  $2499
24A3: FE 05 03 ldx  $0503
24A6: 86 02    lda  #$02
24A8: 3F       swi  
24A9: CE FF FA ldx  #$FFFA
24AC: 39       rts  
24AD: B6 05 03 lda  $0503
24B0: A7 00    sta  (x+$00)
24B2: B6 05 04 lda  $0504
24B5: A7 01    sta  (x+$01)
24B7: 4F       clra 
24B8: FB 05 06 addb $0506
24BB: B9 05 05 adca $0505
24BE: B7 05 05 sta  $0505
24C1: F7 05 06 stb  $0506
24C4: FE 05 05 ldx  $0505
24C7: 39       rts  
24C8: CE 02 CA ldx  #$02CA
24CB: F6 04 94 ldb  $0494
24CE: 20 0D    bra  $24DD
24D0: FF 05 09 stx  $0509
24D3: EE 00    ldx  (x+$00)
24D5: 86 04    lda  #$04
24D7: 3F       swi  
24D8: FE 05 09 ldx  $0509
24DB: 08       inx  
24DC: 08       inx  
24DD: 54       lsrb 
24DE: 25 F0    bcs  $24D0
24E0: 26 F9    bne  $24DB
24E2: 39       rts  
24E3: 7F 03 CA clr  $03CA
24E6: D6 35    ldb  $35
24E8: 27 1D    beq  $2507
24EA: 7A 00 35 dec  $0035
24ED: 26 18    bne  $2507
24EF: D6 36    ldb  $36
24F1: 26 14    bne  $2507
24F3: C6 0C    ldb  #$0C
24F5: F7 F7 14 stb  $F714
24F8: C6 C0    ldb  #$C0
24FA: F7 F7 20 stb  $F720
24FD: C6 82    ldb  #$82
24FF: D7 36    stb  $36
2501: CE 16 01 ldx  #$1601
2504: BD 33 18 jsr  $3318
2507: 86 A0    lda  #$A0
2509: CE 02 DA ldx  #$02DA
250C: 0C       clc  
250D: E6 00    ldb  (x+$00)
250F: 27 05    beq  $2516
2511: 6A 00    dec  (x+$00)
2513: 26 01    bne  $2516
2515: 0D       sec  
2516: 08       inx  
2517: 46       rora 
2518: 24 F3    bcc  $250D
251A: 0C       clc  
251B: E6 02    ldb  (x+$02)
251D: 27 0F    beq  $252E
251F: 6A 00    dec  (x+$00)
2521: 2B 09    bmi  $252C
2523: 26 0B    bne  $2530
2525: 6A 02    dec  (x+$02)
2527: 26 03    bne  $252C
2529: 0D       sec  
252A: 20 04    bra  $2530
252C: C6 32    ldb  #$32
252E: E7 00    stb  (x+$00)
2530: 08       inx  
2531: 46       rora 
2532: 24 E7    bcc  $251B
2534: 27 09    beq  $253F
2536: B7 04 94 sta  $0494
2539: CE 24 C9 ldx  #$24C9
253C: BD 33 18 jsr  $3318
253F: FE 04 88 ldx  $0488
2542: 09       dex  
2543: FF 04 88 stx  $0488
2546: 26 08    bne  $2550
2548: B6 03 FE lda  $03FE
254B: 84 7F    anda #$7F
254D: B7 03 FE sta  $03FE
2550: B6 F7 C4 lda  $F7C4
2553: B6 F7 C9 lda  $F7C9
2556: B6 F7 CA lda  $F7CA
2559: 3B       rti 

; subroutine from jumptable $0830
255A: BD 32 ED jsr  $32ED
255D: FF 05 0B stx  $050B
2560: A6 04    lda  (x+$04)
2562: 84 0F    anda #$0F
2564: B7 05 0D sta  $050D
2567: A6 07    lda  (x+$07)
2569: 84 08    anda #$08
256B: 26 03    bne  $2570
256D: 7E 26 02 jmp  $2602
2570: FF 26 C4 stx  $26C4
2573: B6 05 0D lda  $050D
2576: 8A D0    ora  #$D0
2578: B7 04 26 sta  $0426
257B: B6 05 0D lda  $050D
257E: 81 01    cmpa #$01
2580: 26 08    bne  $258A
2582: FE 26 C4 ldx  $26C4
2585: FF 04 45 stx  $0445
2588: 20 06    bra  $2590
258A: FE 26 C4 ldx  $26C4
258D: FF 03 CB stx  $03CB
2590: B6 02 3A lda  $023A
2593: 84 01    anda #$01
2595: 27 3A    beq  $25D1
2597: CE 80 F9 ldx  #$80F9
259A: DF 1D    stx  $1D
259C: FE 26 C4 ldx  $26C4
259F: C6 13    ldb  #$13
25A1: BD FE 2F jsr  $FE2F
25A4: B6 02 3A lda  $023A
25A7: B7 80 F6 sta  $80F6
25AA: BD 8E E9 jsr  $8EE9
25AD: FE 26 C4 ldx  $26C4
25B0: FF 05 13 stx  $0513
25B3: 4F       clra 
25B4: C6 09    ldb  #$09
25B6: FB 05 14 addb $0514
25B9: B9 05 13 adca $0513
25BC: F7 05 14 stb  $0514
25BF: B7 05 13 sta  $0513
25C2: FE 05 13 ldx  $0513
25C5: DF 1D    stx  $1D
25C7: CE 81 02 ldx  #$8102
25CA: C6 0A    ldb  #$0A
25CC: BD FE 2F jsr  $FE2F
25CF: 20 12    bra  $25E3
25D1: 86 10    lda  #$10
25D3: FE 26 C4 ldx  $26C4
25D6: EE 02    ldx  (x+$02)
25D8: A7 00    sta  (x+$00)
25DA: 86 03    lda  #$03
25DC: FE 26 C4 ldx  $26C4
25DF: EE 02    ldx  (x+$02)
25E1: A7 01    sta  (x+$01)
25E3: B6 05 0D lda  $050D
25E6: 81 04    cmpa #$04
25E8: 27 04    beq  $25EE
25EA: 81 05    cmpa #$05
25EC: 26 0E    bne  $25FC
25EE: FE 26 C4 ldx  $26C4
25F1: EE 02    ldx  (x+$02)
25F3: A6 00    lda  (x+$00)
25F5: 84 F8    anda #$F8
25F7: 26 03    bne  $25FC
25F9: 7E 32 F5 jmp  $32F5
25FC: BD 26 98 jsr  $2698
25FF: 7E 32 F5 jmp  $32F5
2602: FF 04 92 stx  $0492
2605: A6 06    lda  (x+$06)
2607: 84 01    anda #$01
2609: 81 01    cmpa #$01
260B: 26 3C    bne  $2649
260D: B6 05 0D lda  $050D
2610: B7 04 26 sta  $0426
2613: B6 05 0D lda  $050D
2616: 81 03    cmpa #$03
2618: 27 08    beq  $2622
261A: 81 04    cmpa #$04
261C: 27 04    beq  $2622
261E: 81 05    cmpa #$05
2620: 26 22    bne  $2644
2622: A6 01    lda  (x+$01)
2624: 81 01    cmpa #$01
2626: 26 17    bne  $263F
2628: FF 05 0E stx  $050E
262B: 86 04    lda  #$04
262D: B7 05 12 sta  $0512
2630: CE 05 12 ldx  #$0512
2633: FF 05 10 stx  $0510
2636: CE 05 0E ldx  #$050E
2639: BD 1B C7 jsr  $1BC7
263C: 7E 32 F5 jmp  $32F5
263F: 8D 3C    bsr  $267D
2641: 7E 32 F5 jmp  $32F5
2644: 8D 37    bsr  $267D
2646: 7E 32 F5 jmp  $32F5
2649: 86 10    lda  #$10
264B: EE 02    ldx  (x+$02)
264D: A7 00    sta  (x+$00)
264F: FE 04 92 ldx  $0492
2652: EE 02    ldx  (x+$02)
2654: A6 00    lda  (x+$00)
2656: B7 04 30 sta  $0430
2659: 86 57    lda  #$57
265B: FE 04 92 ldx  $0492
265E: EE 02    ldx  (x+$02)
2660: A7 01    sta  (x+$01)
2662: FE 04 92 ldx  $0492
2665: EE 02    ldx  (x+$02)
2667: A6 01    lda  (x+$01)
2669: B7 04 31 sta  $0431
266C: FF 04 2E stx  $042E
266F: 7C 04 32 inc  $0432
2672: FE 04 92 ldx  $0492
2675: EE 02    ldx  (x+$02)
2677: 86 04    lda  #$04
2679: 3F       swi  
267A: 7E 32 F5 jmp  $32F5
267D: FE 04 92 ldx  $0492
2680: A6 05    lda  (x+$05)
2682: B7 26 BB sta  $26BB
2685: A6 06    lda  (x+$06)
2687: B7 26 BC sta  $26BC
268A: 86 04    lda  #$04
268C: B7 26 BD sta  $26BD
268F: FF 26 C0 stx  $26C0
2692: FE 26 C2 ldx  $26C2
2695: 7E 1B 4A jmp  $1B4A
2698: FE 26 C4 ldx  $26C4
269B: EE 02    ldx  (x+$02)
269D: A6 00    lda  (x+$00)
269F: B7 04 35 sta  $0435
26A2: FE 26 C4 ldx  $26C4
26A5: EE 02    ldx  (x+$02)
26A7: A6 01    lda  (x+$01)
26A9: B7 04 36 sta  $0436
26AC: FF 04 33 stx  $0433
26AF: 7C 04 37 inc  $0437
26B2: FE 26 C4 ldx  $26C4
26B5: EE 02    ldx  (x+$02)
26B7: 86 04    lda  #$04
26B9: 3F       swi  
26BA: 39       rts  

               org  $26BB
               fcb  $00
               org  $26BC
               fcb  $00, 
               org  $26BD
               fcb  $04, $03, $03
               
               org  $26C0
               fdb  $0000
               fdb  $26BB
               fdb  $0000
               
26C6: 96 24    lda  $24
26C8: B7 04 29 sta  $0429
26CB: 96 24    lda  $24
26CD: 26 0D    bne  $26DC
26CF: 86 AC    lda  #$AC
26D1: B7 04 25 sta  $0425
26D4: 96 42    lda  $42
26D6: B7 04 28 sta  $0428
26D9: 7E 92 BC jmp  $92BC
26DC: 81 01    cmpa #$01
26DE: 27 07    beq  $26E7
26E0: 81 03    cmpa #$03
26E2: 27 03    beq  $26E7
26E4: 7E 28 90 jmp  $2890
26E7: B6 01 44 lda  $0144
26EA: B7 04 25 sta  $0425
26ED: 96 42    lda  $42
26EF: B7 04 28 sta  $0428
26F2: B6 01 44 lda  $0144
26F5: 81 12    cmpa #$12
26F7: 26 12    bne  $270B
26F9: BD 29 D2 jsr  $29D2
26FC: DE 31    ldx  $31
26FE: 6F 01    clr  (x+$01)
2700: BD 29 F3 jsr  $29F3
2703: 86 1F    lda  #$1F
2705: B7 04 24 sta  $0424
2708: 7E 29 AA jmp  $29AA
270B: 81 22    cmpa #$22
270D: 26 15    bne  $2724
270F: BD 29 D2 jsr  $29D2
2712: B6 01 49 lda  $0149
2715: DE 31    ldx  $31
2717: A7 01    sta  (x+$01)
2719: BD 29 F3 jsr  $29F3
271C: 86 2E    lda  #$2E
271E: B7 04 24 sta  $0424
2721: 7E 29 9B jmp  $299B
2724: 81 23    cmpa #$23
2726: 26 15    bne  $273D
2728: BD 29 D2 jsr  $29D2
272B: B6 01 49 lda  $0149
272E: DE 31    ldx  $31
2730: A7 01    sta  (x+$01)
2732: BD 29 F3 jsr  $29F3
2735: 86 2B    lda  #$2B
2737: B7 04 24 sta  $0424
273A: 7E 29 A2 jmp  $29A2
273D: 81 24    cmpa #$24
273F: 26 15    bne  $2756
2741: BD 29 D2 jsr  $29D2
2744: B6 01 49 lda  $0149
2747: DE 31    ldx  $31
2749: A7 01    sta  (x+$01)
274B: BD 29 F3 jsr  $29F3
274E: 86 2F    lda  #$2F
2750: B7 04 24 sta  $0424
2753: 7E 29 AA jmp  $29AA
2756: 81 26    cmpa #$26
2758: 26 23    bne  $277D
275A: BD 29 B2 jsr  $29B2
275D: B6 05 15 lda  $0515
2760: 27 0F    beq  $2771
2762: BD 29 F3 jsr  $29F3
2765: 86 01    lda  #$01
2767: DE 31    ldx  $31
2769: A7 01    sta  (x+$01)
276B: 7F 00 2B clr  $002B
276E: 7E 29 96 jmp  $2996
2771: 86 28    lda  #$28
2773: B7 01 04 sta  $0104
2776: 86 03    lda  #$03
2778: 97 2B    sta  $2B
277A: 7E 29 86 jmp  $2986
277D: 81 32    cmpa #$32
277F: 26 15    bne  $2796
2781: 86 3F    lda  #$3F
2783: B7 04 24 sta  $0424
2786: BD 29 AA jsr  $29AA
2789: DE 31    ldx  $31
278B: 6F 01    clr  (x+$01)
278D: 7F 01 46 clr  $0146
2790: 7F 01 47 clr  $0147
2793: 7E 29 F3 jmp  $29F3
2796: 81 33    cmpa #$33
2798: 26 07    bne  $27A1
279A: 86 03    lda  #$03
279C: 97 2B    sta  $2B
279E: 7E 29 96 jmp  $2996
27A1: 81 43    cmpa #$43
27A3: 26 15    bne  $27BA
27A5: B6 01 49 lda  $0149
27A8: DE 31    ldx  $31
27AA: A7 01    sta  (x+$01)
27AC: BD 29 D2 jsr  $29D2
27AF: BD 29 F3 jsr  $29F3
27B2: 86 4E    lda  #$4E
27B4: B7 04 24 sta  $0424
27B7: 7E 29 9B jmp  $299B
27BA: 81 44    cmpa #$44
27BC: 26 22    bne  $27E0
27BE: B6 01 49 lda  $0149
27C1: DE 31    ldx  $31
27C3: A7 01    sta  (x+$01)
27C5: B6 01 4C lda  $014C
27C8: 84 0F    anda #$0F
27CA: 81 04    cmpa #$04
27CC: 27 07    beq  $27D5
27CE: B6 01 46 lda  $0146
27D1: 84 F8    anda #$F8
27D3: 27 03    beq  $27D8
27D5: BD 29 F3 jsr  $29F3
27D8: 86 4B    lda  #$4B
27DA: B7 04 24 sta  $0424
27DD: 7E 29 A2 jmp  $29A2
27E0: 81 45    cmpa #$45
27E2: 26 12    bne  $27F6
27E4: B6 01 49 lda  $0149
27E7: DE 31    ldx  $31
27E9: A7 01    sta  (x+$01)
27EB: BD 29 F3 jsr  $29F3
27EE: 86 4F    lda  #$4F
27F0: B7 04 24 sta  $0424
27F3: 7E 29 AA jmp  $29AA
27F6: 81 46    cmpa #$46
27F8: 26 16    bne  $2810
27FA: BD 29 B2 jsr  $29B2
27FD: B6 05 15 lda  $0515
2800: 27 07    beq  $2809
2802: BD 29 F3 jsr  $29F3
2805: DE 31    ldx  $31
2807: 6F 01    clr  (x+$01)
2809: 86 03    lda  #$03
280B: 97 2B    sta  $2B
280D: 7E 29 96 jmp  $2996
2810: 81 A1    cmpa #$A1
2812: 26 1E    bne  $2832
2814: BD 29 B2 jsr  $29B2
2817: B6 05 15 lda  $0515
281A: 27 0A    beq  $2826
281C: BD 29 F3 jsr  $29F3
281F: 86 01    lda  #$01
2821: 97 2B    sta  $2B
2823: 7E 29 96 jmp  $2996
2826: 86 A8    lda  #$A8
2828: B7 01 04 sta  $0104
282B: 86 03    lda  #$03
282D: 97 2B    sta  $2B
282F: 7E 29 86 jmp  $2986
2832: 81 A2    cmpa #$A2
2834: 26 1B    bne  $2851
2836: BD 29 B2 jsr  $29B2
2839: B6 05 15 lda  $0515
283C: 27 07    beq  $2845
283E: DE 31    ldx  $31
2840: 6F 01    clr  (x+$01)
2842: BD 29 F3 jsr  $29F3
2845: 86 A8    lda  #$A8
2847: B7 01 04 sta  $0104
284A: 86 03    lda  #$03
284C: 97 2B    sta  $2B
284E: 7E 29 86 jmp  $2986
2851: 81 B1    cmpa #$B1
2853: 26 1E    bne  $2873
2855: BD 29 B2 jsr  $29B2
2858: B6 05 15 lda  $0515
285B: 27 0A    beq  $2867
285D: BD 29 F3 jsr  $29F3
2860: 86 01    lda  #$01
2862: 97 2B    sta  $2B
2864: 7E 29 96 jmp  $2996
2867: 86 B8    lda  #$B8
2869: B7 01 04 sta  $0104
286C: 86 03    lda  #$03
286E: 97 2B    sta  $2B
2870: 7E 29 86 jmp  $2986
2873: 81 C1    cmpa #$C1
2875: 26 16    bne  $288D
2877: BD 29 B2 jsr  $29B2
287A: B6 05 15 lda  $0515
287D: 27 07    beq  $2886
287F: BD 29 F3 jsr  $29F3
2882: DE 31    ldx  $31
2884: 6F 01    clr  (x+$01)
2886: 86 03    lda  #$03
2888: 97 2B    sta  $2B
288A: 7E 29 96 jmp  $2996
288D: 7E 92 BC jmp  $92BC
2890: 81 02    cmpa #$02
2892: 26 03    bne  $2897
2894: 7E 92 BC jmp  $92BC
2897: 81 05    cmpa #$05
2899: 26 0E    bne  $28A9
289B: B6 01 44 lda  $0144
289E: B7 04 25 sta  $0425
28A1: 96 42    lda  $42
28A3: B7 04 28 sta  $0428
28A6: 7E 92 BC jmp  $92BC
28A9: 81 06    cmpa #$06
28AB: 27 03    beq  $28B0
28AD: 7E 29 4B jmp  $294B
28B0: 86 CA    lda  #$CA
28B2: B7 04 25 sta  $0425
28B5: 96 42    lda  $42
28B7: B7 04 27 sta  $0427
28BA: DE 31    ldx  $31
28BC: DF A9    stx  $A9
28BE: A6 02    lda  (x+$02)
28C0: 26 03    bne  $28C5
28C2: 7E 92 BC jmp  $92BC
28C5: DE 31    ldx  $31
28C7: A6 04    lda  (x+$04)
28C9: 84 0F    anda #$0F
28CB: B7 05 16 sta  $0516
28CE: 81 03    cmpa #$03
28D0: 27 08    beq  $28DA
28D2: 96 30    lda  $30
28D4: A7 00    sta  (x+$00)
28D6: 86 01    lda  #$01
28D8: A7 01    sta  (x+$01)
28DA: 86 01    lda  #$01
28DC: 97 2B    sta  $2B
28DE: B6 05 16 lda  $0516
28E1: 81 01    cmpa #$01
28E3: 26 0A    bne  $28EF
28E5: 86 11    lda  #$11
28E7: B7 01 04 sta  $0104
28EA: BD 29 86 jsr  $2986
28ED: 20 4A    bra  $2939
28EF: 81 02    cmpa #$02
28F1: 26 0A    bne  $28FD
28F3: 86 21    lda  #$21
28F5: B7 01 04 sta  $0104
28F8: BD 29 86 jsr  $2986
28FB: 20 3C    bra  $2939
28FD: 81 03    cmpa #$03
28FF: 26 09    bne  $290A
2901: 86 31    lda  #$31
2903: B7 01 04 sta  $0104
2906: 8D 7E    bsr  $2986
2908: 20 2F    bra  $2939
290A: 81 04    cmpa #$04
290C: 26 17    bne  $2925
290E: 86 41    lda  #$41
2910: B7 01 04 sta  $0104
2913: EE 0A    ldx  (x+$0A)
2915: DF 27    stx  $27
2917: DE 31    ldx  $31
2919: EE 0C    ldx  (x+$0C)
291B: DF 29    stx  $29
291D: 8D 67    bsr  $2986
291F: 86 05    lda  #$05
2921: 97 25    sta  $25
2923: 20 14    bra  $2939
2925: 81 05    cmpa #$05
2927: 26 09    bne  $2932
2929: 86 51    lda  #$51
292B: B7 01 04 sta  $0104
292E: 8D 56    bsr  $2986
2930: 20 07    bra  $2939
2932: 86 37    lda  #$37
2934: B7 04 2A sta  $042A
2937: 8D 22    bsr  $295B
2939: CE 01 08 ldx  #$0108
293C: DF 1D    stx  $1D
293E: DE 31    ldx  $31
2940: C6 13    ldb  #$13
2942: BD FE 2F jsr  $FE2F
2945: 96 44    lda  $44
2947: B7 01 05 sta  $0105
294A: 39       rts  
294B: 81 08    cmpa #$08
294D: 26 07    bne  $2956
294F: 86 03    lda  #$03
2951: B7 04 2A sta  $042A
2954: 20 05    bra  $295B
2956: 86 02    lda  #$02
2958: B7 04 2A sta  $042A
295B: BD 32 ED jsr  $32ED
295E: DE 31    ldx  $31
2960: DF A9    stx  $A9
2962: A6 02    lda  (x+$02)
2964: 27 13    beq  $2979
2966: DE 31    ldx  $31
2968: 6F 01    clr  (x+$01)
296A: 86 10    lda  #$10
296C: B7 01 46 sta  $0146
296F: B6 04 2A lda  $042A
2972: B7 01 47 sta  $0147
2975: 8D 7C    bsr  $29F3
2977: 20 03    bra  $297C
2979: BD 92 BC jsr  $92BC
297C: BD 32 F5 jsr  $32F5
297F: 86 EF    lda  #$EF
2981: B7 04 24 sta  $0424
2984: 20 24    bra  $29AA
2986: 86 01    lda  #$01
2988: 97 25    sta  $25
298A: B6 03 B1 lda  $03B1
298D: 97 26    sta  $26
298F: B6 01 04 lda  $0104
2992: B7 04 24 sta  $0424
2995: 39       rts  
2996: 86 02    lda  #$02
2998: 97 25    sta  $25
299A: 39       rts  
299B: 7F 00 25 clr  $0025
299E: 7F 00 2B clr  $002B
29A1: 39       rts  
29A2: 7F 00 25 clr  $0025
29A5: 86 01    lda  #$01
29A7: 97 2B    sta  $2B
29A9: 39       rts  
29AA: 7F 00 25 clr  $0025
29AD: 86 03    lda  #$03
29AF: 97 2B    sta  $2B
29B1: 39       rts  
29B2: 7F 05 15 clr  $0515
29B5: DE 31    ldx  $31
29B7: A6 04    lda  (x+$04)
29B9: B1 01 4C cmpa $014C
29BC: 26 13    bne  $29D1
29BE: A6 05    lda  (x+$05)
29C0: B1 01 4D cmpa $014D
29C3: 26 0C    bne  $29D1
29C5: A6 06    lda  (x+$06)
29C7: B1 01 4E cmpa $014E
29CA: 26 05    bne  $29D1
29CC: 86 01    lda  #$01
29CE: B7 05 15 sta  $0515
29D1: 39       rts  
29D2: DE 31    ldx  $31
29D4: FF 05 17 stx  $0517
29D7: 4F       clra 
29D8: C6 09    ldb  #$09
29DA: FB 05 18 addb $0518
29DD: B9 05 17 adca $0517
29E0: F7 05 18 stb  $0518
29E3: B7 05 17 sta  $0517
29E6: FE 05 17 ldx  $0517
29E9: DF 1D    stx  $1D
29EB: CE 01 51 ldx  #$0151
29EE: C6 0A    ldb  #$0A
29F0: 7E FE 2F jmp  $FE2F
29F3: DE 31    ldx  $31
29F5: A6 04    lda  (x+$04)
29F7: 84 40    anda #$40
29F9: 27 16    beq  $2A11
29FB: B6 01 46 lda  $0146
29FE: EE 02    ldx  (x+$02)
2A00: AA 00    ora  (x+$00)
2A02: B7 01 46 sta  $0146
2A05: B6 01 47 lda  $0147
2A08: DE 31    ldx  $31
2A0A: EE 02    ldx  (x+$02)
2A0C: AA 01    ora  (x+$01)
2A0E: B7 01 47 sta  $0147
2A11: B6 01 46 lda  $0146
2A14: DE 31    ldx  $31
2A16: EE 02    ldx  (x+$02)
2A18: A7 00    sta  (x+$00)
2A1A: B7 04 30 sta  $0430
2A1D: B6 01 47 lda  $0147
2A20: DE 31    ldx  $31
2A22: EE 02    ldx  (x+$02)
2A24: A7 01    sta  (x+$01)
2A26: B7 04 31 sta  $0431
2A29: FF 04 2E stx  $042E
2A2C: 7C 04 32 inc  $0432
2A2F: DE 31    ldx  $31
2A31: EE 02    ldx  (x+$02)
2A33: 86 04    lda  #$04
2A35: 3F       swi  
2A36: 39       rts  
2A37: 96 24    lda  $24
2A39: B7 30 BE sta  $30BE
2A3C: DE 31    ldx  $31
2A3E: DF 6C    stx  $6C
2A40: A6 04    lda  (x+$04)
2A42: 84 04    anda #$04
2A44: 27 05    beq  $2A4B
2A46: BD 2F BF jsr  $2FBF
2A49: 20 03    bra  $2A4E
2A4B: BD 30 99 jsr  $3099
2A4E: 96 6E    lda  $6E
2A50: B7 01 04 sta  $0104
2A53: 96 6E    lda  $6E
2A55: 84 FE    anda #$FE
2A57: 97 D1    sta  $D1
2A59: 86 01    lda  #$01
2A5B: 97 2B    sta  $2B
2A5D: 7F 00 25 clr  $0025
2A60: B6 30 BE lda  $30BE
2A63: 81 01    cmpa #$01
2A65: 27 07    beq  $2A6E
2A67: 81 05    cmpa #$05
2A69: 27 03    beq  $2A6E
2A6B: 7E 2A F0 jmp  $2AF0
2A6E: 86 02    lda  #$02
2A70: 97 25    sta  $25
2A72: 7F 00 2B clr  $002B
2A75: B6 01 45 lda  $0145
2A78: 81 80    cmpa #$80
2A7A: 25 03    bcs  $2A7F
2A7C: 7E 2D 68 jmp  $2D68
2A7F: B6 01 42 lda  $0142
2A82: 81 FE    cmpa #$FE
2A84: 26 2D    bne  $2AB3
2A86: DE AB    ldx  $AB
2A88: FF 05 21 stx  $0521
2A8B: 4F       clra 
2A8C: C6 0A    ldb  #$0A
2A8E: FB 05 22 addb $0522
2A91: B9 05 21 adca $0521
2A94: F7 05 22 stb  $0522
2A97: B7 05 21 sta  $0521
2A9A: FE 05 21 ldx  $0521
2A9D: DF 1D    stx  $1D
2A9F: CE 01 47 ldx  #$0147
2AA2: 86 16    lda  #$16
2AA4: C6 39    ldb  #$39
2AA6: BD FE 28 jsr  $FE28
2AA9: 7F 00 25 clr  $0025
2AAC: 86 03    lda  #$03
2AAE: 97 2B    sta  $2B
2AB0: 7E 2D 42 jmp  $2D42
2AB3: 96 C2    lda  $C2
2AB5: 27 03    beq  $2ABA
2AB7: 7E 2D D6 jmp  $2DD6
2ABA: 96 D1    lda  $D1
2ABC: 81 02    cmpa #$02
2ABE: 26 06    bne  $2AC6
2AC0: DE 93    ldx  $93
2AC2: DF 2C    stx  $2C
2AC4: 20 21    bra  $2AE7
2AC6: 81 12    cmpa #$12
2AC8: 27 03    beq  $2ACD
2ACA: 7E 2B D2 jmp  $2BD2
2ACD: 96 93    lda  $93
2ACF: 26 0A    bne  $2ADB
2AD1: FE 01 49 ldx  $0149
2AD4: DF 91    stx  $91
2AD6: FE 01 4B ldx  $014B
2AD9: DF 93    stx  $93
2ADB: FE 01 4B ldx  $014B
2ADE: DF 2C    stx  $2C
2AE0: B6 01 45 lda  $0145
2AE3: DE 6C    ldx  $6C
2AE5: A7 00    sta  (x+$00)
2AE7: 86 02    lda  #$02
2AE9: 97 2B    sta  $2B
2AEB: 97 25    sta  $25
2AED: 7E 2D 45 jmp  $2D45
2AF0: 81 09    cmpa #$09
2AF2: 26 0D    bne  $2B01
2AF4: DE 6C    ldx  $6C
2AF6: 86 80    lda  #$80
2AF8: C6 7C    ldb  #$7C
2AFA: E7 01    stb  (x+$01)
2AFC: A7 00    sta  (x+$00)
2AFE: 7E 2D 82 jmp  $2D82
2B01: 81 08    cmpa #$08
2B03: 26 0D    bne  $2B12
2B05: DE 6C    ldx  $6C
2B07: 86 80    lda  #$80
2B09: C6 7B    ldb  #$7B
2B0B: E7 01    stb  (x+$01)
2B0D: A7 00    sta  (x+$00)
2B0F: 7E 2D 82 jmp  $2D82
2B12: 81 06    cmpa #$06
2B14: 26 56    bne  $2B6C
2B16: 86 01    lda  #$01
2B18: 97 25    sta  $25
2B1A: B6 01 42 lda  $0142
2B1D: 81 FE    cmpa #$FE
2B1F: 26 31    bne  $2B52
2B21: 86 F0    lda  #$F0
2B23: B7 01 04 sta  $0104
2B26: 86 18    lda  #$18
2B28: 97 26    sta  $26
2B2A: CE 01 07 ldx  #$0107
2B2D: DF 1D    stx  $1D
2B2F: DE AB    ldx  $AB
2B31: FF 05 21 stx  $0521
2B34: 4F       clra 
2B35: C6 0A    ldb  #$0A
2B37: FB 05 22 addb $0522
2B3A: B9 05 21 adca $0521
2B3D: F7 05 22 stb  $0522
2B40: B7 05 21 sta  $0521
2B43: FE 05 21 ldx  $0521
2B46: C6 15    ldb  #$15
2B48: BD FE 2F jsr  $FE2F
2B4B: 86 14    lda  #$14
2B4D: 97 34    sta  $34
2B4F: 7E 2D 45 jmp  $2D45
2B52: B6 06 03 lda  $0603
2B55: B7 01 05 sta  $0105
2B58: 96 30    lda  $30
2B5A: 97 A5    sta  $A5
2B5C: 96 6F    lda  $6F
2B5E: 27 04    beq  $2B64
2B60: 81 08    cmpa #$08
2B62: 26 6E    bne  $2BD2
2B64: DE 6C    ldx  $6C
2B66: A6 00    lda  (x+$00)
2B68: 97 6F    sta  $6F
2B6A: 20 66    bra  $2BD2
2B6C: 4D       tsta 
2B6D: 26 49    bne  $2BB8
2B6F: B6 01 43 lda  $0143
2B72: 84 0F    anda #$0F
2B74: 81 0B    cmpa #$0B
2B76: 26 03    bne  $2B7B
2B78: 7E 2D 45 jmp  $2D45
2B7B: 86 04    lda  #$04
2B7D: 97 25    sta  $25
2B7F: 96 D1    lda  $D1
2B81: 81 04    cmpa #$04
2B83: 27 08    beq  $2B8D
2B85: 81 06    cmpa #$06
2B87: 27 04    beq  $2B8D
2B89: 81 22    cmpa #$22
2B8B: 26 0B    bne  $2B98
2B8D: DE 93    ldx  $93
2B8F: DF 27    stx  $27
2B91: DE 91    ldx  $91
2B93: DF 29    stx  $29
2B95: 7E 2D 45 jmp  $2D45
2B98: 81 A2    cmpa #$A2
2B9A: 27 04    beq  $2BA0
2B9C: 81 A4    cmpa #$A4
2B9E: 26 12    bne  $2BB2
2BA0: DE AB    ldx  $AB
2BA2: EE 08    ldx  (x+$08)
2BA4: DF 27    stx  $27
2BA6: DE AB    ldx  $AB
2BA8: A6 07    lda  (x+$07)
2BAA: 97 2A    sta  $2A
2BAC: 7F 00 29 clr  $0029
2BAF: 7E 2D 45 jmp  $2D45
2BB2: 7F 00 25 clr  $0025
2BB5: 7E 2D 45 jmp  $2D45
2BB8: 86 02    lda  #$02
2BBA: 97 25    sta  $25
2BBC: 96 D1    lda  $D1
2BBE: 81 12    cmpa #$12
2BC0: 26 0D    bne  $2BCF
2BC2: DE 6C    ldx  $6C
2BC4: A6 00    lda  (x+$00)
2BC6: 81 40    cmpa #$40
2BC8: 24 03    bcc  $2BCD
2BCA: 7E 2D 45 jmp  $2D45
2BCD: 20 03    bra  $2BD2
2BCF: 7F 00 2B clr  $002B
2BD2: 4F       clra 
2BD3: D6 6F    ldb  $6F
2BD5: DE 6C    ldx  $6C
2BD7: E7 00    stb  (x+$00)
2BD9: 97 6F    sta  $6F
2BDB: FB 30 D9 addb $30D9
2BDE: B9 30 D8 adca $30D8
2BE1: F7 05 1A stb  $051A
2BE4: B7 05 19 sta  $0519
2BE7: FE 05 19 ldx  $0519
2BEA: EE 00    ldx  (x+$00)
2BEC: 6E 00    jmp  (x+$00)

; SWI routine $10
2BEE: BD 2F D0 jsr  $2FD0
2BF1: DE 53    ldx  $53
2BF3: 26 05    bne  $2BFA
2BF5: 7F 00 75 clr  $0075
2BF8: 20 11    bra  $2C0B
2BFA: 8C FF FE cmpx #$FFFE
2BFD: 27 0C    beq  $2C0B
2BFF: CE 00 75 ldx  #$0075
2C02: DF 1D    stx  $1D
2C04: DE 53    ldx  $53
2C06: C6 08    ldb  #$08
2C08: BD FE 2F jsr  $FE2F
2C0B: DE 55    ldx  $55
2C0D: 26 05    bne  $2C14
2C0F: 7F 00 74 clr  $0074
2C12: 20 0B    bra  $2C1F
2C14: 8C FF FE cmpx #$FFFE
2C17: 27 06    beq  $2C1F
2C19: DE 55    ldx  $55
2C1B: A6 00    lda  (x+$00)
2C1D: 97 74    sta  $74
2C1F: DE 57    ldx  $57
2C21: 26 05    bne  $2C28
2C23: 7F 00 7D clr  $007D
2C26: 20 11    bra  $2C39
2C28: 8C FF FE cmpx #$FFFE
2C2B: 27 0C    beq  $2C39
2C2D: CE 00 7D ldx  #$007D
2C30: DF 1D    stx  $1D
2C32: DE 57    ldx  $57
2C34: C6 08    ldb  #$08
2C36: BD FE 2F jsr  $FE2F
2C39: DE 59    ldx  $59
2C3B: 8C FF FE cmpx #$FFFE
2C3E: 27 04    beq  $2C44
2C40: DE 59    ldx  $59
2C42: DF A7    stx  $A7
2C44: DE 5B    ldx  $5B
2C46: 26 08    bne  $2C50
2C48: 7F 00 A2 clr  $00A2
2C4B: 7F 00 A1 clr  $00A1
2C4E: 20 09    bra  $2C59
2C50: 8C FF FE cmpx #$FFFE
2C53: 27 04    beq  $2C59
2C55: DE 5B    ldx  $5B
2C57: DF A1    stx  $A1
2C59: DE 5D    ldx  $5D
2C5B: 26 06    bne  $2C63
2C5D: 7F 00 9D clr  $009D
2C60: 7E 2D 45 jmp  $2D45
2C63: 8C FF FE cmpx #$FFFE
2C66: 26 03    bne  $2C6B
2C68: 7E 2D 45 jmp  $2D45
2C6B: DE 5D    ldx  $5D
2C6D: DF 9D    stx  $9D
2C6F: 7E 2D 45 jmp  $2D45

; SWI routine $0E
2C72: BD 2F BD jsr  $2FBD
2C75: CE 00 AD ldx  #$00AD
2C78: DF 1D    stx  $1D
2C7A: DE 6C    ldx  $6C
2C7C: FF 05 21 stx  $0521
2C7F: 4F       clra 
2C80: C6 0A    ldb  #$0A
2C82: FB 05 22 addb $0522
2C85: B9 05 21 adca $0521
2C88: F7 05 22 stb  $0522
2C8B: B7 05 21 sta  $0521
2C8E: FE 05 21 ldx  $0521
2C91: C6 15    ldb  #$15
2C93: BD FE 2F jsr  $FE2F
2C96: 7F 00 AE clr  $00AE
2C99: DE 53    ldx  $53
2C9B: 26 05    bne  $2CA2
2C9D: 7F 00 C1 clr  $00C1
2CA0: 20 0C    bra  $2CAE
2CA2: 8C FF FE cmpx #$FFFE
2CA5: 27 07    beq  $2CAE
2CA7: DE 53    ldx  $53
2CA9: BD 33 B6 jsr  $33B6
2CAC: 97 C1    sta  $C1
2CAE: DE 55    ldx  $55
2CB0: 26 05    bne  $2CB7
2CB2: 7F 00 AD clr  $00AD
2CB5: 20 0B    bra  $2CC2
2CB7: 8C FF FE cmpx #$FFFE
2CBA: 27 06    beq  $2CC2
2CBC: DE 55    ldx  $55
2CBE: A6 00    lda  (x+$00)
2CC0: 97 AD    sta  $AD
2CC2: DE 57    ldx  $57
2CC4: 26 05    bne  $2CCB
2CC6: 7F 00 AF clr  $00AF
2CC9: 20 11    bra  $2CDC
2CCB: 8C FF FE cmpx #$FFFE
2CCE: 27 0C    beq  $2CDC
2CD0: CE 00 AF ldx  #$00AF
2CD3: DF 1D    stx  $1D
2CD5: DE 57    ldx  $57
2CD7: C6 08    ldb  #$08
2CD9: BD FE 2F jsr  $FE2F
2CDC: DE 59    ldx  $59
2CDE: 26 05    bne  $2CE5
2CE0: 7F 00 B7 clr  $00B7
2CE3: 20 11    bra  $2CF6
2CE5: 8C FF FE cmpx #$FFFE
2CE8: 27 0C    beq  $2CF6
2CEA: CE 00 B7 ldx  #$00B7
2CED: DF 1D    stx  $1D
2CEF: DE 59    ldx  $59
2CF1: C6 08    ldb  #$08
2CF3: BD FE 2F jsr  $FE2F
2CF6: DE 5B    ldx  $5B
2CF8: 26 05    bne  $2CFF
2CFA: 7F 00 BF clr  $00BF
2CFD: 20 0B    bra  $2D0A
2CFF: 8C FF FE cmpx #$FFFE
2D02: 27 06    beq  $2D0A
2D04: DE 5B    ldx  $5B
2D06: EE 00    ldx  (x+$00)
2D08: DF BF    stx  $BF
2D0A: DE 6C    ldx  $6C
2D0C: FF 05 21 stx  $0521
2D0F: 4F       clra 
2D10: C6 0A    ldb  #$0A
2D12: FB 05 22 addb $0522
2D15: B9 05 21 adca $0521
2D18: F7 05 22 stb  $0522
2D1B: B7 05 21 sta  $0521
2D1E: FE 05 21 ldx  $0521
2D21: DF 1D    stx  $1D
2D23: CE 00 AD ldx  #$00AD
2D26: C6 15    ldb  #$15
2D28: BD FE 2F jsr  $FE2F
2D2B: 7E 32 A7 jmp  $32A7 ; jumps back to end of SWI routine

; SWI routine $1A
2D2E: BD 30 14 jsr  $3014
2D31: 96 9D    lda  $9D
2D33: 27 05    beq  $2D3A
2D35: FE 30 B2 ldx  $30B2
2D38: 6E 00    jmp  (x+$00)
2D3A: 86 01    lda  #$01
2D3C: 97 6E    sta  $6E
2D3E: 86 02    lda  #$02
2D40: 97 6F    sta  $6F
2D42: BD 30 56 jsr  $3056
2D45: 96 C2    lda  $C2
2D47: 27 0C    beq  $2D55
2D49: DE AB    ldx  $AB
2D4B: 96 6E    lda  $6E
2D4D: D6 6F    ldb  $6F
2D4F: E7 06    stb  (x+$06)
2D51: A7 05    sta  (x+$05)
2D53: 20 03    bra  $2D58
2D55: BD 30 26 jsr  $3026
2D58: B6 30 BE lda  $30BE
2D5B: 81 80    cmpa #$80
2D5D: 25 03    bcs  $2D62
2D5F: 7E 32 A7 jmp  $32A7  ; jumps back to end of SWI routine


2D62: 86 80    lda  #$80
2D64: B7 30 BE sta  $30BE
2D67: 39       rts  
2D68: DE 6C    ldx  $6C
2D6A: B6 01 45 lda  $0145
2D6D: F6 01 46 ldb  $0146
2D70: E7 01    stb  (x+$01)
2D72: A7 00    sta  (x+$00)
2D74: B6 03 B0 lda  $03B0
2D77: 84 7F    anda #$7F
2D79: B7 03 B0 sta  $03B0
2D7C: 7F 07 5B clr  $075B
2D7F: 7F 07 5A clr  $075A
2D82: 96 33    lda  $33
2D84: 26 06    bne  $2D8C
2D86: 86 02    lda  #$02
2D88: 97 25    sta  $25
2D8A: 20 03    bra  $2D8F
2D8C: 7F 00 25 clr  $0025
2D8F: 86 03    lda  #$03
2D91: 97 2B    sta  $2B
2D93: DE 6C    ldx  $6C
2D95: 86 02    lda  #$02
2D97: 3F       swi  
2D98: 20 AB    bra  $2D45
2D9A: DE 6C    ldx  $6C
2D9C: 86 04    lda  #$04
2D9E: 3F       swi  
2D9F: 20 A4    bra  $2D45
2DA1: B6 03 B0 lda  $03B0
2DA4: 84 7F    anda #$7F
2DA6: B7 03 B0 sta  $03B0
2DA9: 7F 07 5B clr  $075B
2DAC: 7F 07 5A clr  $075A
2DAF: 96 C2    lda  $C2
2DB1: 26 23    bne  $2DD6
2DB3: B6 01 04 lda  $0104
2DB6: 81 02    cmpa #$02
2DB8: 25 1C    bcs  $2DD6
2DBA: 81 06    cmpa #$06
2DBC: 22 18    bhi  $2DD6
2DBE: 81 05    cmpa #$05
2DC0: 27 14    beq  $2DD6
2DC2: 96 70    lda  $70
2DC4: 81 80    cmpa #$80
2DC6: 25 D2    bcs  $2D9A
2DC8: CE 30 B2 ldx  #$30B2
2DCB: EE 02    ldx  (x+$02)
2DCD: 6E 00    jmp  (x+$00)
2DCF: 86 02    lda  #$02
2DD1: 97 26    sta  $26
2DD3: 7E 2D 45 jmp  $2D45
2DD6: 86 03    lda  #$03
2DD8: 97 2B    sta  $2B
2DDA: 20 BE    bra  $2D9A

; SWI routine $12
2DDC: BD 2F FD jsr  $2FFD
2DDF: 86 12    lda  #$12
2DE1: 97 6E    sta  $6E
2DE3: BD 30 1B jsr  $301B
2DE6: 7F 00 93 clr  $0093
2DE9: 86 04    lda  #$04
2DEB: 97 6F    sta  $6F
2DED: 86 08    lda  #$08
2DEF: B7 30 C1 sta  $30C1
2DF2: 86 01    lda  #$01
2DF4: B7 30 C3 sta  $30C3
2DF7: 86 FE    lda  #$FE
2DF9: B7 30 C0 sta  $30C0
2DFC: DE 6C    ldx  $6C
2DFE: FF 30 C4 stx  $30C4
2E01: FE 30 C6 ldx  $30C6
2E04: BD 1B 4A jsr  $1B4A
2E07: 7E 2D 45 jmp  $2D45
2E0A: CE 01 0F ldx  #$010F
2E0D: DF 1D    stx  $1D
2E0F: CE 00 74 ldx  #$0074
2E12: C6 11    ldb  #$11
2E14: BD FE 2F jsr  $FE2F
2E17: 86 1C    lda  #$1C
2E19: 97 26    sta  $26
2E1B: FE 07 5A ldx  $075A
2E1E: 9C 6C    cmpx $6C
2E20: 26 08    bne  $2E2A
2E22: B6 03 B0 lda  $03B0
2E25: 8A 80    ora  #$80
2E27: B7 03 B0 sta  $03B0
2E2A: CE 01 06 ldx  #$0106
2E2D: DF 1D    stx  $1D
2E2F: DE AB    ldx  $AB
2E31: FF 05 21 stx  $0521
2E34: 4F       clra 
2E35: C6 0C    ldb  #$0C
2E37: FB 05 22 addb $0522
2E3A: B9 05 21 adca $0521
2E3D: F7 05 22 stb  $0522
2E40: B7 05 21 sta  $0521
2E43: FE 05 21 ldx  $0521
2E46: C6 08    ldb  #$08
2E48: BD FE 2F jsr  $FE2F
2E4B: DE AB    ldx  $AB
2E4D: A6 0A    lda  (x+$0A)
2E4F: B7 01 0E sta  $010E
2E52: 7E 2D 45 jmp  $2D45

; SWI routine $18
2E55: BD 2F FD jsr  $2FFD
2E58: 96 70    lda  $70
2E5A: 8A 10    ora  #$10
2E5C: 97 6E    sta  $6E
2E5E: 96 74    lda  $74
2E60: 26 08    bne  $2E6A
2E62: 96 6E    lda  $6E
2E64: 8A 80    ora  #$80
2E66: 97 6E    sta  $6E
2E68: 20 1C    bra  $2E86
2E6A: 81 44    cmpa #$44
2E6C: 26 15    bne  $2E83
2E6E: 96 7D    lda  $7D
2E70: 26 14    bne  $2E86
2E72: CE 00 7D ldx  #$007D
2E75: DF 1D    stx  $1D
2E77: CE 30 DA ldx  #$30DA
2E7A: 86 08    lda  #$08
2E7C: C6 07    ldb  #$07
2E7E: BD FE 28 jsr  $FE28
2E81: 20 03    bra  $2E86
2E83: BD 30 1B jsr  $301B
2E86: 86 06    lda  #$06
2E88: 97 6F    sta  $6F
2E8A: 7F 00 71 clr  $0071
2E8D: 7E 2D ED jmp  $2DED
2E90: 86 08    lda  #$08
2E92: 97 6F    sta  $6F
2E94: 7E 2E 0A jmp  $2E0A
2E97: CE 00 85 ldx  #$0085
2E9A: DF 1D    stx  $1D
2E9C: CE 01 47 ldx  #$0147
2E9F: 86 10    lda  #$10
2EA1: C6 39    ldb  #$39
2EA3: BD FE 28 jsr  $FE28
2EA6: 86 02    lda  #$02
2EA8: B7 01 04 sta  $0104
2EAB: 96 74    lda  $74
2EAD: 81 56    cmpa #$56
2EAF: 27 08    beq  $2EB9
2EB1: 81 52    cmpa #$52
2EB3: 27 04    beq  $2EB9
2EB5: 81 54    cmpa #$54
2EB7: 26 0E    bne  $2EC7
2EB9: 7F 00 A2 clr  $00A2
2EBC: 7F 00 A1 clr  $00A1
2EBF: 96 70    lda  $70
2EC1: 8A 20    ora  #$20
2EC3: 97 70    sta  $70
2EC5: 20 14    bra  $2EDB
2EC7: DE 89    ldx  $89
2EC9: 96 8B    lda  $8B
2ECB: D6 8C    ldb  $8C
2ECD: BD FD 1A jsr  $FD1A
2ED0: DF 95    stx  $95
2ED2: 96 8B    lda  $8B
2ED4: D6 8C    ldb  $8C
2ED6: BD FC A1 jsr  $FCA1
2ED9: DF 89    stx  $89
2EDB: 7F 00 9A clr  $009A
2EDE: 7F 00 99 clr  $0099
2EE1: 7F 00 9C clr  $009C
2EE4: 7F 00 9B clr  $009B
2EE7: DE 9D    ldx  $9D
2EE9: DF 9F    stx  $9F
2EEB: DF 97    stx  $97
2EED: DE A1    ldx  $A1
2EEF: 26 03    bne  $2EF4
2EF1: 7E 2D A1 jmp  $2DA1
2EF4: 96 9D    lda  $9D
2EF6: D6 9E    ldb  $9E
2EF8: E7 01    stb  (x+$01)
2EFA: A7 00    sta  (x+$00)
2EFC: 7E 2D A1 jmp  $2DA1

; SWI routine $24
2EFF: BD 2F CC jsr  $2FCC
2F02: DE 53    ldx  $53
2F04: DF A3    stx  $A3
2F06: DE 9B    ldx  $9B
2F08: 08       inx  
2F09: DF 9B    stx  $9B
2F0B: 96 70    lda  $70
2F0D: 84 BF    anda #$BF
2F0F: 97 70    sta  $70
2F11: 20 27    bra  $2F3A

; SWI routine $20
2F13: BD 2F CC jsr  $2FCC
2F16: DE 53    ldx  $53
2F18: EE 00    ldx  (x+$00)
2F1A: DF 9B    stx  $9B
2F1C: 96 70    lda  $70
2F1E: 8A 40    ora  #$40
2F20: 97 70    sta  $70
2F22: 7F 00 A3 clr  $00A3
2F25: 20 13    bra  $2F3A

; SWI routine $1E
2F27: BD 2F CC jsr  $2FCC
2F2A: DE 55    ldx  $55
2F2C: DF A3    stx  $A3
2F2E: DE 53    ldx  $53
2F30: EE 00    ldx  (x+$00)
2F32: DF 9B    stx  $9B
2F34: 96 70    lda  $70
2F36: 8A 40    ora  #$40
2F38: 97 70    sta  $70
2F3A: DE 8D    ldx  $8D
2F3C: 27 38    beq  $2F76
2F3E: 96 9D    lda  $9D
2F40: 27 07    beq  $2F49
2F42: CE 30 B2 ldx  #$30B2
2F45: EE 04    ldx  (x+$04)
2F47: 6E 00    jmp  (x+$00)
2F49: 96 9B    lda  $9B
2F4B: D6 9C    ldb  $9C
2F4D: D0 8E    subb $8E
2F4F: 92 8D    sbca $8D
2F51: 2E 23    bgt  $2F76
2F53: 2D 03    blt  $2F58
2F55: 5D       tstb 
2F56: 26 1E    bne  $2F76
2F58: DE A3    ldx  $A3
2F5A: DF 93    stx  $93
2F5C: DE 8B    ldx  $8B
2F5E: DF 91    stx  $91
2F60: 96 A3    lda  $A3
2F62: 26 03    bne  $2F67
2F64: 7E 2D 9A jmp  $2D9A
2F67: DE 9B    ldx  $9B
2F69: DF 72    stx  $72
2F6B: 86 02    lda  #$02
2F6D: 97 6E    sta  $6E
2F6F: 86 0A    lda  #$0A
2F71: 97 6F    sta  $6F
2F73: 7E 2D 42 jmp  $2D42
2F76: 86 40    lda  #$40
2F78: DE 6C    ldx  $6C
2F7A: A7 00    sta  (x+$00)
2F7C: 7E 2D 82 jmp  $2D82
2F7F: 86 06    lda  #$06
2F81: 97 26    sta  $26
2F83: DE 72    ldx  $72
2F85: FF 01 06 stx  $0106
2F88: DE 91    ldx  $91
2F8A: FF 01 08 stx  $0108
2F8D: 7E 2D 45 jmp  $2D45
2F90: CE 30 B2 ldx  #$30B2
2F93: EE 06    ldx  (x+$06)
2F95: 6E 00    jmp  (x+$00)
2F97: CE 30 B2 ldx  #$30B2
2F9A: EE 08    ldx  (x+$08)
2F9C: 6E 00    jmp  (x+$00)

; SWI routine $26
2F9E: 8D 2C    bsr  $2FCC
2FA0: DE 53    ldx  $53
2FA2: DF A3    stx  $A3
2FA4: 96 9D    lda  $9D
2FA6: 27 07    beq  $2FAF
2FA8: CE 30 B2 ldx  #$30B2
2FAB: EE 0A    ldx  (x+$0A)
2FAD: 6E 00    jmp  (x+$00)
2FAF: DE A3    ldx  $A3
2FB1: DF 93    stx  $93
2FB3: DE 9B    ldx  $9B
2FB5: DF 72    stx  $72
2FB7: 86 04    lda  #$04
2FB9: 97 6E    sta  $6E
2FBB: 20 B2    bra  $2F6F
2FBD: 8D 16    bsr  $2FD5
2FBF: DE 6C    ldx  $6C
2FC1: DF AB    stx  $AB
2FC3: EE 05    ldx  (x+$05)
2FC5: DF 6E    stx  $6E
2FC7: 86 FF    lda  #$FF
2FC9: 97 C2    sta  $C2
2FCB: 39       rts  
2FCC: 8D 07    bsr  $2FD5
2FCE: 20 67    bra  $3037
2FD0: 8D 03    bsr  $2FD5
2FD2: 7E 30 99 jmp  $3099
2FD5: 30       tsx  
2FD6: EE 07    ldx  (x+$07)
2FD8: DF 51    stx  $51
2FDA: EE 00    ldx  (x+$00)
2FDC: DF 6C    stx  $6C
2FDE: CE 00 51 ldx  #$0051
2FE1: 08       inx  
2FE2: 08       inx  
2FE3: FF 05 1B stx  $051B
2FE6: DE 51    ldx  $51
2FE8: 08       inx  
2FE9: 08       inx  
2FEA: DF 51    stx  $51
2FEC: A6 00    lda  (x+$00)
2FEE: E6 01    ldb  (x+$01)
2FF0: FE 05 1B ldx  $051B
2FF3: E7 01    stb  (x+$01)
2FF5: A7 00    sta  (x+$00)
2FF7: 8C 00 5D cmpx #$005D
2FFA: 26 E5    bne  $2FE1
2FFC: 39       rts  
2FFD: 30       tsx  
2FFE: E6 03    ldb  (x+$03)
3000: EE 05    ldx  (x+$05)
3002: C4 18    andb #$18
3004: E7 07    stb  (x+$07)
3006: DF 6C    stx  $6C
3008: BD 30 99 jsr  $3099
300B: DE 6C    ldx  $6C
300D: 6F 00    clr  (x+$00)
300F: 6F 01    clr  (x+$01)
3011: 6F 04    clr  (x+$04)
3013: 39       rts  
3014: 30       tsx  
3015: EE 05    ldx  (x+$05)
3017: DF 6C    stx  $6C
3019: 20 1C    bra  $3037
301B: 96 7D    lda  $7D
301D: 27 06    beq  $3025
301F: 96 6E    lda  $6E
3021: 8A 01    ora  #$01
3023: 97 6E    sta  $6E
3025: 39       rts  
3026: DE 6C    ldx  $6C
3028: 08       inx  
3029: 08       inx  
302A: 08       inx  
302B: 08       inx  
302C: 08       inx  
302D: DF 1D    stx  $1D
302F: CE 00 6E ldx  #$006E
3032: C6 3B    ldb  #$3B
3034: 7E FE 2F jmp  $FE2F
3037: DE 6C    ldx  $6C
3039: A6 04    lda  (x+$04)
303B: 84 20    anda #$20
303D: 27 11    beq  $3050
303F: A6 00    lda  (x+$00)
3041: 81 80    cmpa #$80
3043: 25 0B    bcs  $3050
3045: A6 04    lda  (x+$04)
3047: 8A A0    ora  #$A0
3049: A7 04    sta  (x+$04)
304B: 31       ins  
304C: 31       ins  
304D: 7E 32 A7 jmp  $32A7 ; jumps back to end of SWI routine


3050: DE 6C    ldx  $6C
3052: 6F 04    clr  (x+$04)
3054: 20 43    bra  $3099
3056: 86 06    lda  #$06
3058: B7 30 C1 sta  $30C1
305B: 96 C2    lda  $C2
305D: 26 0D    bne  $306C
305F: 96 6E    lda  $6E
3061: 84 FE    anda #$FE
3063: 81 12    cmpa #$12
3065: 26 05    bne  $306C
3067: 86 0A    lda  #$0A
3069: B7 30 C1 sta  $30C1
306C: 96 6E    lda  $6E
306E: 81 07    cmpa #$07
3070: 22 12    bhi  $3084
3072: CE 00 A5 ldx  #$00A5
3075: FF 05 1D stx  $051D
3078: CE 30 C1 ldx  #$30C1
307B: FF 05 1F stx  $051F
307E: CE 05 1D ldx  #$051D
3081: 7E 1B C7 jmp  $1BC7
3084: DE AB    ldx  $AB
3086: A6 1F    lda  (x+$1F)
3088: B7 30 C0 sta  $30C0
308B: DE 6C    ldx  $6C
308D: FF 30 C4 stx  $30C4
3090: 7F 30 C3 clr  $30C3
3093: FE 30 C6 ldx  $30C6
3096: 7E 1B 4A jmp  $1B4A
3099: CE 00 6E ldx  #$006E
309C: DF 1D    stx  $1D
309E: DE 6C    ldx  $6C
30A0: 08       inx  
30A1: 08       inx  
30A2: 08       inx  
30A3: 08       inx  
30A4: 08       inx  
30A5: C6 3B    ldb  #$3B
30A7: BD FE 2F jsr  $FE2F
30AA: DE A7    ldx  $A7
30AC: DF AB    stx  $AB
30AE: 7F 00 C2 clr  $00C2
30B1: 39       rts  

               org  $30B2
               fdb  $3508
               fdb  $37EC
               fdb  $353b
               fdb  $3827
               fdb  $37BD
               fdb  $3763

               org  $30BE
               fcb  $ff
               fcb  $00, $00, $00, $02, $00, $00, $00

               org  $30C6
               fdb  $30BF
               fdb  $2DA1
               fdb  $2DCF
               fdb  $2E0A
               fdb  $2E90
               fdb  $2E97
               fdb  $2F7F
               fdb  $2F90
               fdb  $2F97
               fdb  $30C8

               org  $30DA
               fcc  "SYSVTOC"

; SWI routine $00
30E1: 30       tsx  
30E2: EE 03    ldx  (x+$03)
30E4: 9F 0E    sts  $0E
30E6: AE 02    lds  (x+$02)
30E8: A6 05    lda  (x+$05)
30EA: 36       psha 
30EB: A6 04    lda  (x+$04)
30ED: 36       psha 
30EE: 4F       clra 
30EF: 36       psha 
30F0: 36       psha 
30F1: 36       psha 
30F2: 36       psha 
30F3: 36       psha 
30F4: E6 06    ldb  (x+$06)
30F6: EE 00    ldx  (x+$00)
30F8: DF 10    stx  $10
30FA: A7 00    sta  (x+$00)
30FC: A7 01    sta  (x+$01)
30FE: A7 04    sta  (x+$04)
3100: AF 06    sts  (x+$06)
3102: 9E 0E    lds  $0E
3104: DE 0A    ldx  $0A
3106: A6 05    lda  (x+$05)
3108: 5D       tstb 
3109: 2B 09    bmi  $3114
310B: EB 05    addb (x+$05)
310D: 11       cba  
310E: 23 0B    bls  $311B
3110: C6 FF    ldb  #$FF
3112: 20 07    bra  $311B
3114: EB 05    addb (x+$05)
3116: 11       cba  
3117: 24 02    bcc  $311B
3119: C6 01    ldb  #$01
311B: DE 10    ldx  $10
311D: E7 05    stb  (x+$05)
311F: CE 00 00 ldx  #$0000
3122: DF 12    stx  $12
3124: DE 0C    ldx  $0C
3126: 20 04    bra  $312C
3128: DF 12    stx  $12
312A: EE 08    ldx  (x+$08)
312C: A6 05    lda  (x+$05)
312E: 11       cba  
312F: 24 F7    bcc  $3128
3131: 08       inx  
3132: 9F 0E    sts  $0E
3134: 0F       sei  
3135: 35       txs  
3136: DE 10    ldx  $10
3138: AF 08    sts  (x+$08)
313A: A6 04    lda  (x+$04)
313C: 8A 01    ora  #$01
313E: A7 04    sta  (x+$04)
3140: 9E 10    lds  $10
3142: DE 12    ldx  $12
3144: 27 04    beq  $314A
3146: AF 08    sts  (x+$08)
3148: 20 02    bra  $314C
314A: 9F 0C    sts  $0C
314C: 9E 0E    lds  $0E
314E: 0E       cli  
314F: 7E 32 A7 jmp  $32A7 ; jumps back to SWI entry routine

; SWI routine $02
3152: 30       tsx  
3153: EE 03    ldx  (x+$03)
3155: E6 04    ldb  (x+$04)
3157: CA 20    orb  #$20
3159: E7 04    stb  (x+$04)
315B: 20 05    bra  $3162

; SWI routine $04
315D: 30       tsx  
315E: EE 03    ldx  (x+$03)
3160: E6 04    ldb  (x+$04)
3162: 2B EB    bmi  $314F
3164: CA 80    orb  #$80
3166: E7 04    stb  (x+$04)
3168: 58       aslb 
3169: 2A E4    bpl  $314F
316B: EE 02    ldx  (x+$02)
316D: E6 04    ldb  (x+$04)
316F: 56       rorb 
3170: 25 DD    bcs  $314F
3172: DF 10    stx  $10
3174: E6 05    ldb  (x+$05)
3176: 20 A7    bra  $311F

; SWI routine $06
3178: 30       tsx  
3179: EE 03    ldx  (x+$03)
317B: E6 00    ldb  (x+$00)
317D: 2A 01    bpl  $3180
317F: 50       negb 
3180: 08       inx  
3181: DF 14    stx  $14
3183: EE 00    ldx  (x+$00)
3185: A6 04    lda  (x+$04)
3187: 8A 40    ora  #$40
3189: A7 04    sta  (x+$04)
318B: 96 0A    lda  $0A
318D: A7 02    sta  (x+$02)
318F: 96 0B    lda  $0B
3191: A7 03    sta  (x+$03)
3193: DE 14    ldx  $14
3195: 08       inx  
3196: 5A       decb 
3197: 26 E7    bne  $3180
3199: DE 0A    ldx  $0A
319B: E6 04    ldb  (x+$04)
319D: CA 02    orb  #$02
319F: E7 04    stb  (x+$04)
31A1: DF 10    stx  $10
31A3: E6 05    ldb  (x+$05)
31A5: EE 08    ldx  (x+$08)
31A7: DF 0C    stx  $0C
31A9: 7E 31 1F jmp  $311F
31AC: 30       tsx  
31AD: EE 03    ldx  (x+$03)
31AF: 4F       clra 
31B0: E6 00    ldb  (x+$00)
31B2: D7 16    stb  $16
31B4: 2A 23    bpl  $31D9
31B6: 08       inx  
31B7: DF 14    stx  $14
31B9: EE 00    ldx  (x+$00)
31BB: E6 04    ldb  (x+$04)
31BD: 2B 2E    bmi  $31ED
31BF: DE 14    ldx  $14
31C1: 08       inx  
31C2: 4C       inca 
31C3: 7C 00 16 inc  $0016
31C6: 26 EE    bne  $31B6
31C8: DE 0A    ldx  $0A
31CA: E6 04    ldb  (x+$04)
31CC: CA 02    orb  #$02
31CE: C4 FE    andb #$FE
31D0: E7 04    stb  (x+$04)
31D2: EE 08    ldx  (x+$08)
31D4: DF 0C    stx  $0C
31D6: 7E 32 A7 jmp  $32A7  ; jumps to to end of SWI routine


31D9: 5F       clrb 
31DA: 08       inx  
31DB: DF 14    stx  $14
31DD: EE 00    ldx  (x+$00)
31DF: 6D 04    tst  (x+$04)
31E1: 2A E5    bpl  $31C8
31E3: EA 04    orb  (x+$04)
31E5: DE 14    ldx  $14
31E7: 08       inx  
31E8: 7A 00 16 dec  $0016
31EB: 26 ED    bne  $31DA
31ED: C4 20    andb #$20
31EF: 30       tsx  
31F0: A7 02    sta  (x+$02)
31F2: E7 01    stb  (x+$01)
31F4: DE 0A    ldx  $0A
31F6: E6 04    ldb  (x+$04)
31F8: C4 FD    andb #$FD
31FA: E7 04    stb  (x+$04)
31FC: 7E 32 A7 jmp  $32A7  ; jumps back to end of SWI routine

; SWI routine $08
31FF: 8D 03    bsr  $3204
3201: 7E 31 55 jmp  $3155
3204: DE 0A    ldx  $0A
3206: EE 08    ldx  (x+$08)
3208: DF 0C    stx  $0C
320A: DE 0A    ldx  $0A
320C: 39       rts  

; SWI routine $0A
320D: 8D F5    bsr  $3204
320F: 7E 31 60 jmp  $3160

; SWI routine $0C
3212: 30       tsx  
3213: EE 03    ldx  (x+$03)
3215: E6 04    ldb  (x+$04)
3217: C4 FD    andb #$FD
3219: E7 04    stb  (x+$04)
321B: 56       rorb 
321C: 24 E3    bcc  $3201
321E: DF 17    stx  $17
3220: EE 08    ldx  (x+$08)
3222: DF 10    stx  $10
3224: DE 0C    ldx  $0C
3226: DF 12    stx  $12
3228: EE 08    ldx  (x+$08)
322A: 9C 17    cmpx $17
322C: 26 F8    bne  $3226
322E: DE 12    ldx  $12
3230: D6 10    ldb  $10
3232: E7 08    stb  (x+$08)
3234: D6 11    ldb  $11
3236: E7 09    stb  (x+$09)
3238: 7E 31 52 jmp  $3152
323B: BD 32 ED jsr  $32ED
323E: 86 3F    lda  #$3F
3240: B7 F7 C5 sta  $F7C5
3243: 7C 00 65 inc  $0065
3246: DE 0A    ldx  $0A
3248: A6 08    lda  (x+$08)
324A: 27 1E    beq  $326A
324C: 86 08    lda  #$08
324E: AA 04    ora  (x+$04)
3250: A7 04    sta  (x+$04)
3252: 96 20    lda  $20
3254: 36       psha 
3255: 96 1F    lda  $1F
3257: 36       psha 
3258: 96 1E    lda  $1E
325A: 36       psha 
325B: 96 1D    lda  $1D
325D: 36       psha 
325E: 96 1C    lda  $1C
3260: 36       psha 
3261: 96 1B    lda  $1B
3263: 36       psha 
3264: 96 1A    lda  $1A
3266: 36       psha 
3267: 96 19    lda  $19
3269: 36       psha 
326A: 9F 6A    sts  $6A
326C: DE 5F    ldx  $5F
326E: 9C 61    cmpx $61
3270: 27 19    beq  $328B
3272: 35       txs  
3273: 08       inx  
3274: 08       inx  
3275: 8C 03 AB cmpx #$03AB
3278: 26 03    bne  $327D
327A: CE 03 93 ldx  #$0393
327D: DF 5F    stx  $5F
327F: 30       tsx  
3280: BE 32 EB lds  $32EB
3283: EE 00    ldx  (x+$00)
3285: 0E       cli  
3286: AD 00    jsr  (x+$00)
3288: 0F       sei  
3289: 20 E1    bra  $326C
328B: 9E 6A    lds  $6A
328D: 0E       cli  
328E: 20 17    bra  $32A7  ; jumps back to end of SWI routine

; Entrypoint of SWI routine
3290: BD 32 ED jsr  $32ED
3293: 0E       cli  
3294: 7C 00 65 inc  $0065  
3297: 9B 67    adda $67    ; A contain which routine to start. Seems to be an even number
3299: 97 69    sta  $69    ; Do a 16 bit add off A with $67 $66 to $68 $69
329B: 96 66    lda  $66    ; Somewhere the value of $67$68 need to be initiated. Maybe at $47F3? Sets $085A.
329D: 89 00    adca #$00
329F: 97 68    sta  $68
32A1: DE 68    ldx  $68    ; X should now contain $085A + the value in A used for specifying which routine to use.
32A3: EE 00    ldx  (x+$00) ; Load the jump table value into X 
32A5: 6E 00    jmp  (x+$00) ; And jump there. I was a bit fooled and though it was two level indiretcion. But in fact it does jump to the address of X not to the address pointed to by X.
; All routines jump back here
32A7: 7A 00 65 dec  $0065
32AA: 26 3E    bne  $32EA
32AC: DE 0A    ldx  $0A
32AE: 9C 0C    cmpx $0C
32B0: 27 08    beq  $32BA
32B2: AF 06    sts  (x+$06)
32B4: DE 0C    ldx  $0C
32B6: AE 06    lds  (x+$06)
32B8: DF 0A    stx  $0A
32BA: E6 04    ldb  (x+$04)
32BC: C5 08    bitb #$08
32BE: 27 1C    beq  $32DC
32C0: C4 F7    andb #$F7
32C2: E7 04    stb  (x+$04)
32C4: 32       pula 
32C5: 97 19    sta  $19
32C7: 32       pula 
32C8: 97 1A    sta  $1A
32CA: 32       pula 
32CB: 97 1B    sta  $1B
32CD: 32       pula 
32CE: 97 1C    sta  $1C
32D0: 32       pula 
32D1: 97 1D    sta  $1D
32D3: 32       pula 
32D4: 97 1E    sta  $1E
32D6: 32       pula 
32D7: 97 1F    sta  $1F
32D9: 32       pula 
32DA: 97 20    sta  $20
32DC: C4 02    andb #$02
32DE: 27 06    beq  $32E6
32E0: 7C 00 65 inc  $0065
32E3: 7E 31 AC jmp  $31AC
32E6: 0F       sei  
32E7: BD 32 F5 jsr  $32F5
32EA: 3B       rti  
; End of SWI routine

               org  $32EB
               fdb  $0542

; 32EB: 05       illegal
; 32EC: 42       illegal

; subroutine 
32ED: 36       psha 
32EE: 86 80    lda  #$80
32F0: B7 04 1A sta  $041A
32F3: 32       pula 
32F4: 39       rts  

; subroutine jumptable $083F
32F5: 36       psha 
32F6: 07       tpa  
32F7: 0F       sei  
32F8: FF 33 16 stx  $3316
32FB: B7 33 15 sta  $3315
32FE: DE 5F    ldx  $5F
3300: 9C 61    cmpx $61
3302: 27 05    beq  $3309
3304: 86 37    lda  #$37
3306: B7 F7 C5 sta  $F7C5
3309: 7F 04 1A clr  $041A
330C: FE 33 16 ldx  $3316
330F: B6 33 15 lda  $3315
3312: 06       tap  
3313: 32       pula 
3314: 39       rts  

               org  $3315
               fcb  $D4
               fdb  $068F

;3315: D4 06    andb $06
;3317: 8F 
               org  $3318
; subroutine
3318: 07       inx
3319: 0F       sei
331A: 9F 63    sts  $63
331C: 35       txs  
331D: DE 61    ldx  $61
331F: AF 00    sts  (x+$00)
3321: 08       inx  
3322: 08       inx  
3323: 8C 03 AB cmpx #$03AB
3326: 26 03    bne  $332B
3328: CE 03 93 ldx  #$0393
332B: DF 61    stx  $61
332D: 9E 63    lds  $63
332F: F6 04 1A ldb  $041A
3332: 26 05    bne  $3339
3334: C6 37    ldb  #$37
3336: F7 F7 C5 stb  $F7C5
3339: 06       tap  
333A: 39       rts  


333B: 86 02    lda  #$02
333D: 97 25    sta  $25
333F: 86 03    lda  #$03
3341: 97 2B    sta  $2B
3343: 96 24    lda  $24
3345: 81 01    cmpa #$01
3347: 26 37    bne  $3380
3349: B6 01 44 lda  $0144
334C: 81 02    cmpa #$02
334E: 26 08    bne  $3358
3350: FE 02 4F ldx  $024F
3353: 27 02    beq  $3357
3355: 6E 00    jmp  (x+$00)
3357: 39       rts  
3358: 4D       tsta 
3359: 26 0F    bne  $336A
335B: FE 01 45 ldx  $0145
335E: FF 05 43 stx  $0543
3361: 7F 01 09 clr  $0109
3364: 86 26    lda  #$26
3366: 97 26    sta  $26
3368: 20 2C    bra  $3396
336A: FE 01 45 ldx  $0145
336D: DF 1D    stx  $1D
336F: FE 01 47 ldx  $0147
3372: DF 1F    stx  $1F
3374: CE 01 4A ldx  #$014A
3377: B6 01 47 lda  $0147
337A: F6 01 48 ldb  $0148
337D: 7E FE 34 jmp  $FE34
3380: 4D       tsta 
3381: 26 12    bne  $3395
3383: B6 05 43 lda  $0543
3386: F6 05 44 ldb  $0544
3389: CB 20    addb #$20
338B: 89 00    adca #$00
338D: F7 05 44 stb  $0544
3390: B7 05 43 sta  $0543
3393: 20 01    bra  $3396
3395: 39       rts  
3396: CE 01 0A ldx  #$010A
3399: DF 1D    stx  $1D
339B: FE 05 43 ldx  $0543
339E: C6 20    ldb  #$20
33A0: BD FE 2F jsr  $FE2F
33A3: 86 01    lda  #$01
33A5: 97 25    sta  $25
33A7: 7C 01 09 inc  $0109
33AA: B6 01 09 lda  $0109
33AD: 81 08    cmpa #$08
33AF: 27 04    beq  $33B5
33B1: 86 01    lda  #$01
33B3: 97 2B    sta  $2B
33B5: 39       rts  

; subroutine jumtable $0842
33B6: FF 05 45 stx  $0545
33B9: EE 00    ldx  (x+$00)
33BB: DF D2    stx  $D2
33BD: FE 05 45 ldx  $0545
33C0: EE 02    ldx  (x+$02)
33C2: DF D4    stx  $D4
33C4: 86 FF    lda  #$FF
33C6: B7 05 47 sta  $0547
33C9: 96 D5    lda  $D5
33CB: 81 20    cmpa #$20
33CD: 26 29    bne  $33F8
33CF: 96 D4    lda  $D4
33D1: 81 20    cmpa #$20
33D3: 26 11    bne  $33E6
33D5: DE D2    ldx  $D2
33D7: 8C 43 50 cmpx #$4350
33DA: 27 03    beq  $33DF
33DC: 7E 34 60 jmp  $3460
33DF: 86 FE    lda  #$FE
33E1: B7 05 47 sta  $0547
33E4: 20 7A    bra  $3460
33E6: 81 53    cmpa #$53
33E8: 26 76    bne  $3460
33EA: DE D2    ldx  $D2
33EC: 8C 46 44 cmpx #$4644
33EF: 26 6F    bne  $3460
33F1: 86 FD    lda  #$FD
33F3: B7 05 47 sta  $0547
33F6: 20 68    bra  $3460
33F8: 96 D4    lda  $D4
33FA: 81 30    cmpa #$30
33FC: 25 62    bcs  $3460
33FE: 81 33    cmpa #$33
3400: 22 5E    bhi  $3460
3402: 96 D5    lda  $D5
3404: 81 30    cmpa #$30
3406: 25 58    bcs  $3460
3408: 81 39    cmpa #$39
340A: 22 54    bhi  $3460
340C: 96 D4    lda  $D4
340E: 84 0F    anda #$0F
3410: 16       tab  
3411: 48       asla 
3412: 48       asla 
3413: 1B       aba  
3414: 48       asla 
3415: D6 D5    ldb  $D5
3417: C4 0F    andb #$0F
3419: 1B       aba  
341A: B7 05 48 sta  $0548
341D: 81 01    cmpa #$01
341F: 25 3F    bcs  $3460
3421: 81 28    cmpa #$28
3423: 22 3B    bhi  $3460
3425: 80 01    suba #$01
3427: 48       asla 
3428: 48       asla 
3429: B7 05 48 sta  $0548
342C: DE D2    ldx  $D2
342E: 8C 46 44 cmpx #$4644
3431: 26 07    bne  $343A
3433: 8B 02    adda #$02
3435: B7 05 48 sta  $0548
3438: 20 20    bra  $345A
343A: 8C 50 55 cmpx #$5055
343D: 26 05    bne  $3444
343F: 7C 05 48 inc  $0548
3442: 20 16    bra  $345A
3444: 8C 58 55 cmpx #$5855
3447: 26 07    bne  $3450
3449: 8B 03    adda #$03
344B: B7 05 48 sta  $0548
344E: 20 0A    bra  $345A
3450: 8C 44 55 cmpx #$4455
3453: 27 05    beq  $345A
3455: 86 FF    lda  #$FF
3457: B7 05 48 sta  $0548
345A: B6 05 48 lda  $0548
345D: B7 05 47 sta  $0547
3460: B6 05 47 lda  $0547
3463: 39       rts  

; subroutine from jumptable $0845
3464: 97 1A    sta  $1A
3466: 4F       clra 
; subroutine from jumtable $084E
3467: D7 1C    stb  $1C
3469: 97 1B    sta  $1B
346B: 0D       sec  
346C: 20 05    bra  $3473

; subroutine from jumtable $084B
346E: 4F       clra 

; subroutine from jumtable $0848
346F: BD FE 56 jsr  $FE56
3472: 0C       clc  
3473: 07       tpa  
3474: 36       psha 
3475: 96 1D    lda  $1D
3477: D6 1E    ldb  $1E
3479: 37       pshb 
347A: 36       psha 
347B: D6 20    ldb  $20
347D: 96 1F    lda  $1F
347F: 37       pshb 
3480: 36       psha 
3481: 2A 20    bpl  $34A3
3483: 84 7F    anda #$7F
3485: DE 1D    ldx  $1D
3487: E0 01    subb (x+$01)
3489: A2 00    sbca (x+$00)
348B: D7 20    stb  $20
348D: 97 1F    sta  $1F
348F: A6 00    lda  (x+$00)
3491: E6 01    ldb  (x+$01)
3493: 08       inx  
3494: 08       inx  
3495: DF 1D    stx  $1D
3497: DB 1E    addb $1E
3499: 99 1D    adca $1D
349B: D7 1E    stb  $1E
349D: 97 1D    sta  $1D
349F: 96 1F    lda  $1F
34A1: D6 20    ldb  $20
34A3: D0 1C    subb $1C
34A5: 92 1B    sbca $1B
34A7: 24 06    bcc  $34AF
34A9: DE 1F    ldx  $1F
34AB: DF 1B    stx  $1B
34AD: 4F       clra 
34AE: 5F       clrb 
34AF: D7 20    stb  $20
34B1: 97 1F    sta  $1F
34B3: 30       tsx  
34B4: A6 04    lda  (x+$04)
34B6: 46       rora 
34B7: 24 09    bcc  $34C2
34B9: DE 1D    ldx  $1D
34BB: BD FE 44 jsr  $FE44
34BE: DF 1D    stx  $1D
34C0: 20 03    bra  $34C5
34C2: BD FE 9B jsr  $FE9B
34C5: 32       pula 
34C6: 33       pulb 
34C7: 30       tsx  
34C8: EE 00    ldx  (x+$00)
34CA: 31       ins  
34CB: 31       ins  
34CC: 31       ins  
34CD: 4D       tsta 
34CE: 2A 12    bpl  $34E2
34D0: DF 1D    stx  $1D
34D2: D7 20    stb  $20
34D4: 97 1F    sta  $1F
34D6: A6 00    lda  (x+$00)
34D8: E6 01    ldb  (x+$01)
34DA: DB 1C    addb $1C
34DC: 99 1B    adca $1B
34DE: E7 01    stb  (x+$01)
34E0: A7 00    sta  (x+$00)
34E2: 39       rts  


34E3: 00       illegal
34E4: 00       illegal
34E5: 00       illegal
34E6: 00       illegal
34E7: 00       illegal
34E8: 00       illegal
34E9: 00       illegal
34EA: 00       illegal
34EB: 00       illegal
34EC: 00       illegal
34ED: 00       illegal
34EE: 00       illegal
34EF: 00       illegal
34F0: 00       illegal
34F1: 00       illegal
34F2: 00       illegal
34F3: 00       illegal
34F4: 00       illegal
34F5: 00       illegal
34F6: 00       illegal
34F7: 00       illegal
34F8: 00       illegal
34F9: 00       illegal
34FA: 00       illegal
34FB: 00       illegal
34FC: 00       illegal
34FD: 00       illegal
34FE: 00       illegal
34FF: 00       illegal
start:	
3500: CE 05 49 ldx  #$0549
3503: DF 1D    stx  $1D
3505: CE 40 A4 ldx  #$40A4
; Entry from jump table at $30B2
3508: C6 0B    ldb  #$0B
350A: BD FE 2F jsr  $FE2F
350D: CE 32 3B ldx  #$323B
3510: FF 01 81 stx  $0181  
3513: CE 32 90 ldx  #$3290   ; Address of SWI routine
3516: FF 01 9C stx  $019C    ; SWI interrupt jump vector 
3519: 7F 06 0B clr  $060B
351C: 7F 06 0A clr  $060A
351F: 8E 06 DE lds  #$06DE
3522: CE 00 1C ldx  #$001C
3525: DF 1F    stx  $1F
3527: CE 01 BD ldx  #$01BD
352A: 7F 00 1A clr  $001A
352D: 4F       clra 
352E: C6 1D    ldb  #$1D
3530: BD FE 15 jsr  $FE15
3533: B6 F7 D2 lda  $F7D2
3536: 84 EF    anda #$EF
3538: B7 F7 D2 sta  $F7D2
; Entry from jump table at $30B2
353B: B6 FF E7 lda  $FFE7  ; Checking the PROMID!
353E: 81 07    cmpa #$07   ; If it is 7 then disable plenty of jump entries. But we are a 01. 07= PCU 4171
3540: 27 43    beq  $3585
3542: B6 F7 C6 lda  $F7C6
3545: 8A 10    ora  #$10
3547: B7 F7 C6 sta  $F7C6
354A: C6 F0    ldb  #$F0
354C: FE 40 55 ldx  $4055
354F: E7 00    stb  (x+$00)
3551: B6 F7 C6 lda  $F7C6
3554: 84 EF    anda #$EF
3556: B7 F7 C6 sta  $F7C6
3559: FE 40 55 ldx  $4055
355C: A6 00    lda  (x+$00)
355E: 81 F0    cmpa #$F0
3560: 27 55    beq  $35B7
3562: B6 F7 C6 lda  $F7C6
3565: 8A 10    ora  #$10
3567: B7 F7 C6 sta  $F7C6
356A: A6 00    lda  (x+$00)
356C: 81 F0    cmpa #$F0
356E: 26 47    bne  $35B7
3570: B6 02 E8 lda  $02E8
3573: 8A 80    ora  #$80
3575: B7 02 E8 sta  $02E8
3578: DF 1D    stx  $1D
357A: CE 3A 55 ldx  #$3A55
357D: 86 06    lda  #$06
357F: 5F       clrb 
3580: BD FE 30 jsr  $FE30
3583: 20 32    bra  $35B7
3585: 86 39    lda  #$39  ; This is the RTS instruction
3587: B7 08 0C sta  $080C ; essentially disabling many of the jumptable entries!
358A: B7 08 0F sta  $080F
358D: B7 08 12 sta  $0812
3590: B7 08 15 sta  $0815
3593: B7 08 18 sta  $0818
3596: B7 08 1B sta  $081B
3599: B7 08 1E sta  $081E
359C: B7 08 21 sta  $0821
359F: B7 08 24 sta  $0824
35A2: B7 08 27 sta  $0827
35A5: B7 08 2D sta  $082D
35A8: B7 08 51 sta  $0851
35AB: CE F8 00 ldx  #$F800
35AE: FF 02 A6 stx  $02A6
35B1: CE F8 01 ldx  #$F801
35B4: FF 02 A8 stx  $02A8
35B7: B6 F7 C6 lda  $F7C6
35BA: 84 EF    anda #$EF
35BC: B7 F7 C6 sta  $F7C6
35BF: B6 FF E7 lda  $FFE7  ; Checking PROMID once more. 
35C2: 81 07    cmpa #$07   ; 07 is the PCU 4171
35C4: 27 0D    beq  $35D3
35C6: CE 7F 81 ldx  #$7F81
35C9: DF 1D    stx  $1D
35CB: CE 40 84 ldx  #$4084
35CE: C6 08    ldb  #$08
35D0: BD FE 2F jsr  $FE2F
35D3: BD 47 DC jsr  $47DC
35D6: CE 04 47 ldx  #$0447
35D9: FF 05 56 stx  $0556
35DC: CE 04 86 ldx  #$0486
35DF: FF 05 58 stx  $0558
35E2: CE 1C 8E ldx  #$1C8E
35E5: FF 05 5A stx  $055A
35E8: 86 03    lda  #$03
35EA: B7 05 5C sta  $055C
35ED: 4F       clra 
35EE: CE 05 56 ldx  #$0556
35F1: 3F       swi  
35F2: BD 41 46 jsr  $4146
35F5: B6 FF E7 lda  $FFE7  ; Check PROMID..
35F8: 81 07    cmpa #$07
35FA: 27 0D    beq  $3609
35FC: 86 80    lda  #$80
35FE: B7 02 54 sta  $0254
3601: B6 01 40 lda  $0140
3604: B7 02 39 sta  $0239
3607: 20 05    bra  $360E
3609: 86 FF    lda  #$FF
360B: B7 02 39 sta  $0239
360E: B6 01 40 lda  $0140
3611: B7 02 3A sta  $023A
3614: CE 01 40 ldx  #$0140
3617: DF 4A    stx  $4A
3619: CE 00 40 ldx  #$0040
361C: DF 4C    stx  $4C
361E: BD 1A DE jsr  $1ADE
3621: 86 05    lda  #$05
3623: B7 06 03 sta  $0603
3626: CE 01 BD ldx  #$01BD
3629: FF 05 56 stx  $0556
362C: CE 40 8C ldx  #$408C
362F: FF 05 58 stx  $0558
3632: CE 00 00 ldx  #$0000
3635: FF 05 5A stx  $055A
3638: FF 05 5E stx  $055E
363B: FF 05 5C stx  $055C
363E: FF 05 60 stx  $0560
3641: CE 05 56 ldx  #$0556
3644: 86 0E    lda  #$0E
3646: 3F       swi  
3647: FE 3A 36 ldx  $3A36
364A: BD 08 24 jsr  $0824
364D: CE 78 30 ldx  #$7830
3650: FF 02 A2 stx  $02A2
3653: 86 42    lda  #$42
3655: B7 02 A4 sta  $02A4
3658: 86 0A    lda  #$0A
365A: B7 02 A5 sta  $02A5
365D: B6 FF E7 lda  $FFE7  ; PROMID...
3660: 81 07    cmpa #$07
3662: 27 3B    beq  $369F
3664: BD 40 AF jsr  $40AF
3667: CE 03 46 ldx  #$0346
366A: FF 05 56 stx  $0556
366D: CE 03 85 ldx  #$0385
3670: FF 05 58 stx  $0558
3673: CE 1F 3B ldx  #$1F3B
3676: FF 05 5A stx  $055A
3679: 86 02    lda  #$02
367B: B7 05 5C sta  $055C
367E: 4F       clra 
367F: CE 05 56 ldx  #$0556
3682: 3F       swi  
3683: CE 03 06 ldx  #$0306
3686: FF 05 56 stx  $0556
3689: CE 03 45 ldx  #$0345
368C: FF 05 58 stx  $0558
368F: CE 0B C7 ldx  #$0BC7
3692: FF 05 5A stx  $055A
3695: 86 01    lda  #$01
3697: B7 05 5C sta  $055C
369A: 4F       clra 
369B: CE 05 56 ldx  #$0556
369E: 3F       swi  
369F: CE 4F 53 ldx  #$4F53
36A2: FF 09 18 stx  $0918
36A5: CE 06 E5 ldx  #$06E5
36A8: FF 09 1A stx  $091A
36AB: 7F 09 1D clr  $091D
36AE: 7F 09 1C clr  $091C
36B1: 86 20    lda  #$20
36B3: B7 09 1F sta  $091F
36B6: CE 09 21 ldx  #$0921
36B9: DF 1D    stx  $1D
36BB: CE 40 90 ldx  #$4090
36BE: C6 04    ldb  #$04
36C0: BD FE 2F jsr  $FE2F
36C3: B6 01 B1 lda  $01B1
36C6: 26 03    bne  $36CB
36C8: BD 39 2F jsr  $392F
36CB: 86 80    lda  #$80
36CD: C6 00    ldb  #$00
36CF: 50       negb 
36D0: 25 01    bcs  $36D3
36D2: 4A       deca 
36D3: 43       coma 
36D4: 20 15    bra  $36EB
36D6: 86 AA    lda  #$AA
36D8: FE 40 79 ldx  $4079
36DB: A7 00    sta  (x+$00)
36DD: 86 55    lda  #$55
36DF: A7 01    sta  (x+$01)
36E1: B6 40 79 lda  $4079
36E4: F6 40 7A ldb  $407A
36E7: CB 02    addb #$02
36E9: 89 00    adca #$00
36EB: F7 40 7A stb  $407A
36EE: B7 40 79 sta  $4079
36F1: 86 09    lda  #$09
36F3: C6 81    ldb  #$81
36F5: 50       negb 
36F6: 25 01    bcs  $36F9
36F8: 4A       deca 
36F9: 43       coma 
36FA: F7 05 55 stb  $0555
36FD: B7 05 54 sta  $0554
3700: B6 40 79 lda  $4079
3703: F6 40 7A ldb  $407A
3706: F0 05 55 subb $0555
3709: B2 05 54 sbca $0554
370C: 2D C8    blt  $36D6
370E: 26 03    bne  $3713
3710: 5D       tstb 
3711: 27 C3    beq  $36D6
3713: CE F6 7C ldx  #$F67C
3716: FF 02 C7 stx  $02C7
3719: 86 80    lda  #$80
371B: C6 00    ldb  #$00
371D: 50       negb 
371E: 25 01    bcs  $3721
3720: 4A       deca 
3721: 43       coma 
3722: 7E 38 0A jmp  $380A
3725: FE 40 79 ldx  $4079
3728: A6 00    lda  (x+$00)
372A: 81 AA    cmpa #$AA
372C: 26 03    bne  $3731
372E: 7E 37 FA jmp  $37FA
3731: 86 80    lda  #$80
3733: C6 00    ldb  #$00
3735: 50       negb 
3736: 25 01    bcs  $3739
3738: 4A       deca 
3739: 43       coma 
373A: F7 05 55 stb  $0555
373D: B7 05 54 sta  $0554
3740: B6 40 79 lda  $4079
3743: F6 40 7A ldb  $407A
3746: F0 05 55 subb $0555
3749: B2 05 54 sbca $0554
374C: 26 0C    bne  $375A
374E: 5D       tstb 
374F: 26 09    bne  $375A
3751: CE 7F FC ldx  #$7FFC
3754: FF 02 C7 stx  $02C7
3757: 7E 38 00 jmp  $3800
375A: 86 40    lda  #$40
375C: C6 00    ldb  #$00
375E: 50       negb 
375F: 25 01    bcs  $3762
3761: 4A       deca 
3762: 43       coma 
3763: F7 05 55 stb  $0555
3766: B7 05 54 sta  $0554
3769: B6 40 79 lda  $4079
376C: F6 40 7A ldb  $407A
376F: F0 05 55 subb $0555
3772: B2 05 54 sbca $0554
3775: 26 0B    bne  $3782

; swi A = $36 - probably not a SWI routine...
3777: 5D       tstb 
3778: 26 08    bne  $3782
377A: CE BF FC ldx  #$BFFC
377D: FF 02 C7 stx  $02C7
3780: 20 7E    bra  $3800
3782: 86 30    lda  #$30
3784: C6 00    ldb  #$00
3786: 50       negb 
3787: 25 01    bcs  $378A; $3788 is also an entry. But then it will start on the $01 instruction which is a NOP. Fully OK. But strange.
3789: 4A       deca 
378A: 43       coma 
378B: F7 05 55 stb  $0555
378E: B7 05 54 sta  $0554
3791: B6 40 79 lda  $4079
3794: F6 40 7A ldb  $407A
3797: F0 05 55 subb $0555
379A: B2 05 54 sbca $0554
379D: 26 0B    bne  $37AA
379F: 5D       tstb 
37A0: 26 08    bne  $37AA
37A2: CE CF FC ldx  #$CFFC
37A5: FF 02 C7 stx  $02C7
37A8: 20 56    bra  $3800
37AA: 86 20    lda  #$20
37AC: C6 00    ldb  #$00
37AE: 50       negb 
37AF: 25 01    bcs  $37B2
37B1: 4A       deca 
37B2: 43       coma 
37B3: F7 05 55 stb  $0555
37B6: B7 05 54 sta  $0554
37B9: B6 40 79 lda  $4079
37BC: F6 40 7A ldb  $407A
37BF: F0 05 55 subb $0555
37C2: B2 05 54 sbca $0554
37C5: 26 0B    bne  $37D2
37C7: 5D       tstb 
37C8: 26 08    bne  $37D2
37CA: CE DF FC ldx  #$DFFC
37CD: FF 02 C7 stx  $02C7
37D0: 20 2E    bra  $3800
37D2: 86 10    lda  #$10
37D4: C6 00    ldb  #$00
37D6: 50       negb 
37D7: 25 01    bcs  $37DA
37D9: 4A       deca 
37DA: 43       coma 
37DB: F7 05 55 stb  $0555
37DE: B7 05 54 sta  $0554
37E1: B6 40 79 lda  $4079
37E4: F6 40 7A ldb  $407A
37E7: F0 05 55 subb $0555
37EA: B2 05 54 sbca $0554  ; There is a jump entry going to $37EC. 54 = LSR B
37ED: 26 78    bne  $3867
37EF: 5D       tstb 
37F0: 26 75    bne  $3867
37F2: CE EF FC ldx  #$EFFC
37F5: FF 02 C7 stx  $02C7
37F8: 20 06    bra  $3800
37FA: A6 01    lda  (x+$01)
37FC: 81 55    cmpa #$55
37FE: 26 67    bne  $3867

; SWI routine $1C .. Strange... Since it never jumps back..
3800: B6 40 79 lda  $4079
3803: F6 40 7A ldb  $407A
3806: CB 02    addb #$02
3808: 89 00    adca #$00
380A: F7 40 7A stb  $407A
380D: B7 40 79 sta  $4079
3810: 86 09    lda  #$09
3812: C6 81    ldb  #$81
3814: 50       negb 
3815: 25 01    bcs  $3818
3817: 4A       deca 
3818: 43       coma 
3819: F7 05 55 stb  $0555
381C: B7 05 54 sta  $0554
381F: B6 40 79 lda  $4079  ; $381B is an entry point! SWI $24 Strange!?
3822: F6 40 7A ldb  $407A
3825: F0 05 55 subb $0555  ; $3827 is an entrypoint. But 55 is not a valid instruction.
3828: B2 05 54 sbca $0554
382B: 2E 10    bgt  $383D
382D: 2D 03    blt  $3832
382F: 5D       tstb 
3830: 26 0B    bne  $383D
3832: FE 02 C7 ldx  $02C7
3835: 8C F6 7C cmpx #$F67C
3838: 26 03    bne  $383D
383A: 7E 37 25 jmp  $3725
383D: 86 80    lda  #$80
383F: C6 00    ldb  #$00
3841: 20 11    bra  $3854
3843: FE 40 79 ldx  $4079
3846: 6F 01    clr  (x+$01)
3848: 6F 00    clr  (x+$00)
384A: B6 40 79 lda  $4079
384D: F6 40 7A ldb  $407A
3850: CB 02    addb #$02
3852: 89 00    adca #$00
3854: F7 40 7A stb  $407A
3857: B7 40 79 sta  $4079
385A: C0 FE    subb #$FE
385C: 82 83    sbca #$83
385E: 2D E3    blt  $3843
3860: 26 03    bne  $3865
3862: 5D       tstb 
3863: 27 DE    beq  $3843
3865: 20 17    bra  $387E
3867: CE 06 E5 ldx  #$06E5
386A: DF 1D    stx  $1D
386C: CE 40 7B ldx  #$407B
386F: 86 4B    lda  #$4B
3871: C6 09    ldb  #$09
3873: BD FE 28 jsr  $FE28
3876: FE 06 67 ldx  $0667
3879: BD 08 2D jsr  $082D
387C: 20 FE    bra  $387C
387E: B6 01 B0 lda  $01B0
3881: 26 03    bne  $3886
3883: 7E 39 11 jmp  $3911
3886: CE 01 DD ldx  #$01DD
3889: FF 05 56 stx  $0556
388C: CE 01 BD ldx  #$01BD
388F: FF 05 5E stx  $055E
3892: 86 46    lda  #$46
3894: B7 05 66 sta  $0566
3897: CE 05 66 ldx  #$0566
389A: FF 05 5A stx  $055A
389D: CE 40 94 ldx  #$4094
38A0: FF 05 58 stx  $0558
38A3: CE 00 00 ldx  #$0000
38A6: FF 05 5C stx  $055C
38A9: FF 05 60 stx  $0560
38AC: FF 05 62 stx  $0562
38AF: CE 05 56 ldx  #$0556
38B2: 86 10    lda  #$10
38B4: 3F       swi  
38B5: B6 01 B0 lda  $01B0
38B8: B7 09 16 sta  $0916
38BB: 86 FF    lda  #$FF
38BD: B7 09 17 sta  $0917
38C0: BD 10 95 jsr  $1095
38C3: B6 01 E1 lda  $01E1
38C6: 84 20    anda #$20
38C8: 27 4A    beq  $3914
38CA: CE 01 DD ldx  #$01DD
38CD: FF 09 70 stx  $0970
38D0: A6 01    lda  (x+$01)
38D2: B7 01 AF sta  $01AF
38D5: A6 00    lda  (x+$00)
38D7: B7 01 AE sta  $01AE
38DA: CE 06 E5 ldx  #$06E5
38DD: DF 1D    stx  $1D
38DF: CE 40 9C ldx  #$409C
38E2: C6 08    ldb  #$08
38E4: BD FE 2F jsr  $FE2F
38E7: CE 06 ED ldx  #$06ED
38EA: DF 1D    stx  $1D
38EC: CE 3A 38 ldx  #$3A38
38EF: 86 43    lda  #$43
38F1: C6 1D    ldb  #$1D
38F3: BD FE 28 jsr  $FE28
38F6: B6 01 AE lda  $01AE
38F9: BD 0A 4D jsr  $0A4D
38FC: FF 07 00 stx  $0700
38FF: B6 01 AF lda  $01AF
3902: BD 0A 4D jsr  $0A4D
3905: FF 07 0B stx  $070B
3908: FE 06 67 ldx  $0667
390B: BD 08 2D jsr  $082D
390E: 7E 38 86 jmp  $3886
3911: 7F 09 17 clr  $0917
3914: BD 46 89 jsr  $4689
3917: 86 7C    lda  #$7C
3919: B7 06 94 sta  $0694
391C: FE 02 6F ldx  $026F
391F: BC 05 52 cmpx $0552
3922: 26 08    bne  $392C
3924: B6 02 E8 lda  $02E8
3927: 8A 40    ora  #$40
3929: B7 02 E8 sta  $02E8
392C: 7E 09 72 jmp  $0972
392F: CE 06 E5 ldx  #$06E5
3932: DF 1D    stx  $1D
3934: CE 40 5B ldx  #$405B
3937: 86 4B    lda  #$4B
3939: C6 16    ldb  #$16
393B: BD FE 28 jsr  $FE28
393E: FE 06 67 ldx  $0667
3941: BD 08 2D jsr  $082D
3944: CE 01 DD ldx  #$01DD
3947: FF 05 56 stx  $0556
394A: CE 01 BD ldx  #$01BD
394D: FF 05 5E stx  $055E
3950: 86 46    lda  #$46
3952: B7 05 67 sta  $0567
3955: CE 05 67 ldx  #$0567
3958: FF 05 5A stx  $055A
395B: CE 40 71 ldx  #$4071
395E: FF 05 58 stx  $0558
3961: CE 00 00 ldx  #$0000
3964: FF 05 5C stx  $055C
3967: FF 05 60 stx  $0560
396A: FF 05 62 stx  $0562
396D: CE 05 56 ldx  #$0556
3970: 86 10    lda  #$10
3972: 3F       swi  
3973: CE 01 DD ldx  #$01DD
3976: C6 18    ldb  #$18
3978: 86 18    lda  #$18
397A: 3F       swi  
397B: CE 01 DD ldx  #$01DD
397E: FF 05 57 stx  $0557
3981: 86 01    lda  #$01
3983: B7 05 56 sta  $0556
3986: CE 05 56 ldx  #$0556
3989: 86 06    lda  #$06
398B: 3F       swi  
398C: 5D       tstb 
398D: 26 52    bne  $39E1
398F: B6 FF E7 lda  $FFE7  ; PROMID
3992: 81 07    cmpa #$07
3994: 27 08    beq  $399E
3996: B6 02 39 lda  $0239
3999: B7 60 10 sta  $6010
399C: 20 06    bra  $39A4
399E: B6 02 3A lda  $023A
39A1: B7 60 10 sta  $6010
39A4: 8D 3C    bsr  $39E2
39A6: CE 64 10 ldx  #$6410
39A9: FF 40 57 stx  $4057
39AC: 8D 34    bsr  $39E2
39AE: CE 68 10 ldx  #$6810
39B1: FF 40 57 stx  $4057
39B4: 8D 2C    bsr  $39E2
39B6: CE 80 00 ldx  #$8000
39B9: FF 40 57 stx  $4057
39BC: A6 00    lda  (x+$00)
39BE: 43       coma 
39BF: A7 00    sta  (x+$00)
39C1: A1 00    cmpa (x+$00)
39C3: 26 05    bne  $39CA
39C5: 43       coma 
39C6: A7 00    sta  (x+$00)
39C8: 8D 18    bsr  $39E2
39CA: CE 01 DD ldx  #$01DD
39CD: 86 1A    lda  #$1A
39CF: 3F       swi  
39D0: CE 01 DD ldx  #$01DD
39D3: FF 05 57 stx  $0557
39D6: 86 01    lda  #$01
39D8: B7 05 56 sta  $0556
39DB: CE 05 56 ldx  #$0556
39DE: 86 06    lda  #$06
39E0: 3F       swi  
39E1: 39       rts  

; subroutine
39E2: FE 40 59 ldx  $4059
39E5: 08       inx  
39E6: FF 40 59 stx  $4059
39E9: CE 01 DD ldx  #$01DD
39EC: FF 05 56 stx  $0556
39EF: CE 40 59 ldx  #$4059
39F2: FF 05 58 stx  $0558
39F5: CE 05 56 ldx  #$0556
39F8: 86 20    lda  #$20
39FA: 3F       swi  
39FB: CE 01 DD ldx  #$01DD
39FE: FF 05 57 stx  $0557
3A01: 86 01    lda  #$01
3A03: B7 05 56 sta  $0556
3A06: CE 05 56 ldx  #$0556
3A09: 86 06    lda  #$06
3A0B: 3F       swi  
3A0C: CE 01 DD ldx  #$01DD
3A0F: FF 05 56 stx  $0556
3A12: FE 40 57 ldx  $4057
3A15: FF 05 58 stx  $0558
3A18: CE 04 00 ldx  #$0400
3A1B: FF 05 5A stx  $055A
3A1E: CE 05 56 ldx  #$0556
3A21: 86 26    lda  #$26
3A23: 3F       swi  
3A24: CE 01 DD ldx  #$01DD
3A27: FF 05 57 stx  $0557
3A2A: 86 01    lda  #$01
3A2C: B7 05 56 sta  $0556
3A2F: CE 05 56 ldx  #$0556
3A32: 86 06    lda  #$06
3A34: 3F       swi  
3A35: 39       rts 

               org  $3A36
               fdb  $F90B
               
3A36: F9 0B
               org  $3A38
               fcc  " FAILURE  STATUS = XX  TYPE ="

3A55: 00       illegal
3A56: 00       illegal
3A57: 00       illegal
3A58: 00       illegal
3A59: 00       illegal
3A5A: 00       illegal
3A5B: 00       illegal
3A5C: 00       illegal
3A5D: 00       illegal
3A5E: 00       illegal
3A5F: 00       illegal
3A60: 00       illegal
3A61: 00       illegal
3A62: 00       illegal
3A63: 00       illegal
3A64: 00       illegal
3A65: 00       illegal
3A66: 00       illegal
3A67: 18       illegal
3A68: 18       illegal
3A69: 18       illegal
3A6A: 18       illegal
3A6B: 18       illegal
3A6C: 18       illegal
3A6D: 00       illegal
3A6E: 00       illegal
3A6F: 18       illegal
3A70: 00       illegal
3A71: 00       illegal
3A72: 00       illegal
3A73: 00       illegal
3A74: 00       illegal
3A75: 00       illegal
3A76: 33       pulb 
3A77: 33       pulb 
3A78: 66 00    ror  (x+$00)
3A7A: 00       illegal
3A7B: 00       illegal
3A7C: 00       illegal
3A7D: 00       illegal
3A7E: 00       illegal
3A7F: 00       illegal
3A80: 00       illegal
3A81: 00       illegal
3A82: 00       illegal
3A83: 00       illegal
3A84: 00       illegal
3A85: 00       illegal
3A86: 00       illegal
3A87: 22 22    bhi  $3AAB
3A89: 7F 22 22 clr  $2222
3A8C: 22 7F    bhi  $3B0D
3A8E: 22 22    bhi  $3AB2
3A90: 00       illegal
3A91: 00       illegal
3A92: 00       illegal
3A93: 00       illegal
3A94: 00       illegal
3A95: 00       illegal
3A96: 08       inx  
3A97: 3E       wai  
3A98: 49       rola 
3A99: 48       asla 
3A9A: 48       asla 
3A9B: 3E       wai  
3A9C: 09       dex  
3A9D: 09       dex  
3A9E: 49       rola 
3A9F: 3E       wai  
3AA0: 08       inx  
3AA1: 00       illegal
3AA2: 00       illegal
3AA3: 00       illegal
3AA4: 00       illegal
3AA5: 00       illegal
3AA6: 00       illegal
3AA7: 20 51    bra  $3AFA
3AA9: 22 04    bhi  $3AAF
3AAB: 08       inx  
3AAC: 10       sba  
3AAD: 22 45    bhi  $3AF4
3AAF: 02       illegal
3AB0: 00       illegal
3AB1: 00       illegal
3AB2: 00       illegal
3AB3: 00       illegal
3AB4: 00       illegal
3AB5: 00       illegal
3AB6: 00       illegal
3AB7: 30       tsx  
3AB8: 48       asla 
3AB9: 48       asla 
3ABA: 48       asla 
3ABB: 30       tsx  
3ABC: 4A       deca 
3ABD: 44       lsra 
3ABE: 4A       deca 
3ABF: 31       ins  
3AC0: 00       illegal
3AC1: 00       illegal
3AC2: 00       illegal
3AC3: 00       illegal
3AC4: 00       illegal
3AC5: 00       illegal
3AC6: 18       illegal
3AC7: 18       illegal
3AC8: 30       tsx  
3AC9: 00       illegal
3ACA: 00       illegal
3ACB: 00       illegal
3ACC: 00       illegal
3ACD: 00       illegal
3ACE: 00       illegal
3ACF: 00       illegal
3AD0: 00       illegal
3AD1: 00       illegal
3AD2: 00       illegal
3AD3: 00       illegal
3AD4: 00       illegal
3AD5: 00       illegal
3AD6: 04       illegal
3AD7: 08       inx  
3AD8: 10       sba  
3AD9: 10       sba  
3ADA: 10       sba  
3ADB: 10       sba  
3ADC: 10       sba  
3ADD: 10       sba  
3ADE: 10       sba  
3ADF: 08       inx  
3AE0: 04       illegal
3AE1: 00       illegal
3AE2: 00       illegal
3AE3: 00       illegal
3AE4: 00       illegal
3AE5: 00       illegal
3AE6: 10       sba  
3AE7: 08       inx  
3AE8: 04       illegal
3AE9: 04       illegal
3AEA: 04       illegal
3AEB: 04       illegal
3AEC: 04       illegal
3AED: 04       illegal
3AEE: 04       illegal
3AEF: 08       inx  
3AF0: 10       sba  
3AF1: 00       illegal
3AF2: 00       illegal
3AF3: 00       illegal
3AF4: 00       illegal
3AF5: 00       illegal
3AF6: 00       illegal
3AF7: 00       illegal
3AF8: 08       inx  
3AF9: 49       rola 
3AFA: 2A 1C    bpl  $3B18
3AFC: 2A 49    bpl  $3B47
3AFE: 08       inx  
3AFF: 00       illegal
3B00: 00       illegal
3B01: 00       illegal
3B02: 00       illegal
3B03: 00       illegal
3B04: 00       illegal
3B05: 00       illegal
3B06: 00       illegal
3B07: 00       illegal
3B08: 08       inx  
3B09: 08       inx  
3B0A: 08       inx  
3B0B: 7F 08 08 clr  $0808
3B0E: 08       inx  
3B0F: 00       illegal
3B10: 00       illegal
3B11: 00       illegal
3B12: 00       illegal
3B13: 00       illegal
3B14: 00       illegal
3B15: 00       illegal
3B16: 00       illegal
3B17: 00       illegal
3B18: 00       illegal
3B19: 00       illegal
3B1A: 00       illegal
3B1B: 00       illegal
3B1C: 00       illegal
3B1D: 00       illegal
3B1E: 18       illegal
3B1F: 18       illegal
3B20: 30       tsx  
3B21: 00       illegal
3B22: 00       illegal
3B23: 00       illegal
3B24: 00       illegal
3B25: 00       illegal
3B26: 00       illegal
3B27: 00       illegal
3B28: 00       illegal
3B29: 00       illegal
3B2A: 00       illegal
3B2B: 3E       wai  
3B2C: 00       illegal
3B2D: 00       illegal
3B2E: 00       illegal
3B2F: 00       illegal
3B30: 00       illegal
3B31: 00       illegal
3B32: 00       illegal
3B33: 00       illegal
3B34: 00       illegal
3B35: 00       illegal
3B36: 00       illegal
3B37: 00       illegal
3B38: 00       illegal
3B39: 00       illegal
3B3A: 00       illegal
3B3B: 00       illegal
3B3C: 00       illegal
3B3D: 00       illegal
3B3E: 00       illegal
3B3F: 18       illegal
3B40: 00       illegal
3B41: 00       illegal
3B42: 00       illegal
3B43: 00       illegal
3B44: 00       illegal
3B45: 00       illegal
3B46: 02       illegal
3B47: 02       illegal
3B48: 04       illegal
3B49: 04       illegal
3B4A: 08       inx  
3B4B: 08       inx  
3B4C: 10       sba  
3B4D: 10       sba  
3B4E: 20 20    bra  $3B70
3B50: 00       illegal
3B51: 00       illegal
3B52: 00       illegal
3B53: 00       illegal
3B54: 00       illegal
3B55: 00       illegal
3B56: 3E       wai  
3B57: 63 41    com  (x+$41)
3B59: 49       rola 
3B5A: 49       rola 
3B5B: 49       rola 
3B5C: 49       rola 
3B5D: 41       illegal
3B5E: 63 3E    com  (x+$3E)
3B60: 00       illegal
3B61: 00       illegal
3B62: 00       illegal
3B63: 00       illegal
3B64: 00       illegal
3B65: 00       illegal
3B66: 0C       clc  
3B67: 1C       illegal
3B68: 34       des  
3B69: 04       illegal
3B6A: 04       illegal
3B6B: 04       illegal
3B6C: 04       illegal
3B6D: 04       illegal
3B6E: 04       illegal
3B6F: 04       illegal
3B70: 00       illegal
3B71: 00       illegal
3B72: 00       illegal
3B73: 00       illegal
3B74: 00       illegal
3B75: 00       illegal
3B76: 3E       wai  
3B77: 63 01    com  (x+$01)
3B79: 03       illegal
3B7A: 06       tap  
3B7B: 0C       clc  
3B7C: 18       illegal
3B7D: 30       tsx  
3B7E: 60 7F    neg  (x+$7F)
3B80: 00       illegal
3B81: 00       illegal
3B82: 00       illegal
3B83: 00       illegal
3B84: 00       illegal
3B85: 00       illegal
3B86: 3E       wai  
3B87: 63 01    com  (x+$01)
3B89: 03       illegal
3B8A: 0E       cli  
3B8B: 03       illegal
3B8C: 01       nop  
3B8D: 01       nop  
3B8E: 63 3E    com  (x+$3E)
3B90: 00       illegal
3B91: 00       illegal
3B92: 00       illegal
3B93: 00       illegal
3B94: 00       illegal
3B95: 00       illegal
3B96: 02       illegal
3B97: 06       tap  
3B98: 0E       cli  
3B99: 1A       illegal
3B9A: 32       pula 
3B9B: 62       illegal
3B9C: 7F 02 02 clr  $0202
3B9F: 02       illegal
3BA0: 00       illegal
3BA1: 00       illegal
3BA2: 00       illegal
3BA3: 00       illegal
3BA4: 00       illegal
3BA5: 00       illegal
3BA6: 7F 40 40 clr  $4040
3BA9: 5E       illegal
3BAA: 43       coma 
3BAB: 01       nop  
3BAC: 01       nop  
3BAD: 01       nop  
3BAE: 63 3E    com  (x+$3E)
3BB0: 00       illegal
3BB1: 00       illegal
3BB2: 00       illegal
3BB3: 00       illegal
3BB4: 00       illegal
3BB5: 00       illegal
3BB6: 06       tap  
3BB7: 0C       clc  
3BB8: 18       illegal
3BB9: 30       tsx  
3BBA: 6E 63    jmp  (x+$63)
3BBC: 41       illegal
3BBD: 41       illegal
3BBE: 63 3E    com  (x+$3E)
3BC0: 00       illegal
3BC1: 00       illegal
3BC2: 00       illegal
3BC3: 00       illegal
3BC4: 00       illegal
3BC5: 00       illegal
3BC6: 7F 01 03 clr  $0103
3BC9: 06       tap  
3BCA: 0C       clc  
3BCB: 18       illegal
3BCC: 10       sba  
3BCD: 10       sba  
3BCE: 10       sba  
3BCF: 10       sba  
3BD0: 00       illegal
3BD1: 00       illegal
3BD2: 00       illegal
3BD3: 00       illegal
3BD4: 00       illegal
3BD5: 00       illegal
3BD6: 1C       illegal
3BD7: 36       psha 
3BD8: 22 22    bhi  $3BFC
3BDA: 3E       wai  
3BDB: 63 41    com  (x+$41)
3BDD: 41       illegal
3BDE: 63 3E    com  (x+$3E)
3BE0: 00       illegal
3BE1: 00       illegal
3BE2: 00       illegal
3BE3: 00       illegal
3BE4: 00       illegal
3BE5: 00       illegal
3BE6: 3E       wai  
3BE7: 63 41    com  (x+$41)
3BE9: 41       illegal
3BEA: 63 3A    com  (x+$3A)
3BEC: 0C       clc  
3BED: 18       illegal
3BEE: 30       tsx  
3BEF: 60 00    neg  (x+$00)
3BF1: 00       illegal
3BF2: 00       illegal
3BF3: 00       illegal
3BF4: 00       illegal
3BF5: 00       illegal
3BF6: 00       illegal
3BF7: 00       illegal
3BF8: 00       illegal
3BF9: 18       illegal
3BFA: 00       illegal
3BFB: 00       illegal
3BFC: 00       illegal
3BFD: 00       illegal
3BFE: 18       illegal
3BFF: 00       illegal
3C00: 00       illegal
3C01: 00       illegal
3C02: 00       illegal
3C03: 00       illegal
3C04: 00       illegal
3C05: 00       illegal
3C06: 00       illegal
3C07: 00       illegal
3C08: 00       illegal
3C09: 18       illegal
3C0A: 00       illegal
3C0B: 00       illegal
3C0C: 00       illegal
3C0D: 00       illegal
3C0E: 18       illegal
3C0F: 18       illegal
3C10: 30       tsx  
3C11: 00       illegal
3C12: 00       illegal
3C13: 00       illegal
3C14: 00       illegal
3C15: 00       illegal
3C16: 00       illegal
3C17: 00       illegal
3C18: 00       illegal
3C19: 07       tpa  
3C1A: 1C       illegal
3C1B: 60 1C    neg  (x+$1C)
3C1D: 07       tpa  
3C1E: 00       illegal
3C1F: 00       illegal
3C20: 00       illegal
3C21: 00       illegal
3C22: 00       illegal
3C23: 00       illegal
3C24: 00       illegal
3C25: 00       illegal
3C26: 00       illegal
3C27: 00       illegal
3C28: 00       illegal
3C29: 00       illegal
3C2A: 3E       wai  
3C2B: 00       illegal
3C2C: 3E       wai  
3C2D: 00       illegal
3C2E: 00       illegal
3C2F: 00       illegal
3C30: 00       illegal
3C31: 00       illegal
3C32: 00       illegal
3C33: 00       illegal
3C34: 00       illegal
3C35: 00       illegal
3C36: 00       illegal
3C37: 00       illegal
3C38: 00       illegal
3C39: 70 1C 03 neg  $1C03
3C3C: 1C       illegal
3C3D: 70 00 00 neg  $0000
3C40: 00       illegal
3C41: 00       illegal
3C42: 00       illegal
3C43: 00       illegal
3C44: 00       illegal
3C45: 00       illegal
3C46: 00       illegal
3C47: 3E       wai  
3C48: 63 41    com  (x+$41)
3C4A: 03       illegal
3C4B: 0E       cli  
3C4C: 08       inx  
3C4D: 08       inx  
3C4E: 00       illegal
3C4F: 08       inx  
3C50: 00       illegal
3C51: 00       illegal
3C52: 00       illegal
3C53: 00       illegal
3C54: 00       illegal
3C55: 00       illegal
3C56: 01       nop  
3C57: 02       illegal
3C58: 7F 40 40 clr  $4040
3C5B: 78 40 40 asl  $4040
3C5E: 40       nega 
3C5F: 7F 00 00 clr  $0000
3C62: 00       illegal
3C63: 00       illegal
3C64: 00       illegal
3C65: 00       illegal
3C66: 00       illegal
3C67: 1C       illegal
3C68: 36       psha 
3C69: 63 41    com  (x+$41)
3C6B: 41       illegal
3C6C: 7F 41 41 clr  $4141
3C6F: 41       illegal
3C70: 00       illegal
3C71: 00       illegal
3C72: 00       illegal
3C73: 00       illegal
3C74: 00       illegal
3C75: 00       illegal
3C76: 00       illegal
3C77: 7E 43 41 jmp  $4341
3C7A: 46       rora 
3C7B: 7C 46 41 inc  $4641
3C7E: 43       coma 
3C7F: 7E 00 00 jmp  $0000
3C82: 00       illegal
3C83: 00       illegal
3C84: 00       illegal
3C85: 00       illegal
3C86: 00       illegal
3C87: 3E       wai  
3C88: 63 40    com  (x+$40)
3C8A: 40       nega 
3C8B: 40       nega 
3C8C: 40       nega 
3C8D: 40       nega 
3C8E: 63 3E    com  (x+$3E)
3C90: 00       illegal
3C91: 00       illegal
3C92: 00       illegal
3C93: 00       illegal
3C94: 00       illegal
3C95: 00       illegal
3C96: 00       illegal
3C97: 7C 46 43 inc  $4643
3C9A: 41       illegal
3C9B: 41       illegal
3C9C: 41       illegal
3C9D: 43       coma 
3C9E: 46       rora 
3C9F: 7C 00 00 inc  $0000
3CA2: 00       illegal
3CA3: 00       illegal
3CA4: 00       illegal
3CA5: 00       illegal
3CA6: 00       illegal
3CA7: 7F 40 40 clr  $4040
3CAA: 40       nega 
3CAB: 78 40 40 asl  $4040
3CAE: 40       nega 
3CAF: 7F 00 00 clr  $0000
3CB2: 00       illegal
3CB3: 00       illegal
3CB4: 00       illegal
3CB5: 00       illegal
3CB6: 00       illegal
3CB7: 7F 40 40 clr  $4040
3CBA: 40       nega 
3CBB: 78 40 40 asl  $4040
3CBE: 40       nega 
3CBF: 40       nega 
3CC0: 00       illegal
3CC1: 00       illegal
3CC2: 00       illegal
3CC3: 00       illegal
3CC4: 00       illegal
3CC5: 00       illegal
3CC6: 00       illegal
3CC7: 3E       wai  
3CC8: 63 40    com  (x+$40)
3CCA: 40       nega 
3CCB: 4F       clra 
3CCC: 41       illegal
3CCD: 41       illegal
3CCE: 63 3E    com  (x+$3E)
3CD0: 00       illegal
3CD1: 00       illegal
3CD2: 00       illegal
3CD3: 00       illegal
3CD4: 00       illegal
3CD5: 00       illegal
3CD6: 00       illegal
3CD7: 41       illegal
3CD8: 41       illegal
3CD9: 41       illegal
3CDA: 41       illegal
3CDB: 7F 41 41 clr  $4141
3CDE: 41       illegal
3CDF: 41       illegal
3CE0: 00       illegal
3CE1: 00       illegal
3CE2: 00       illegal
3CE3: 00       illegal
3CE4: 00       illegal
3CE5: 00       illegal
3CE6: 00       illegal
3CE7: 1C       illegal
3CE8: 08       inx  
3CE9: 08       inx  
3CEA: 08       inx  
3CEB: 08       inx  
3CEC: 08       inx  
3CED: 08       inx  
3CEE: 08       inx  
3CEF: 1C       illegal
3CF0: 00       illegal
3CF1: 00       illegal
3CF2: 00       illegal
3CF3: 00       illegal
3CF4: 00       illegal
3CF5: 00       illegal
3CF6: 00       illegal
3CF7: 02       illegal
3CF8: 02       illegal
3CF9: 02       illegal
3CFA: 02       illegal
3CFB: 02       illegal
3CFC: 02       illegal
3CFD: 02       illegal
3CFE: 66 3C    ror  (x+$3C)
3D00: 00       illegal
3D01: 00       illegal
3D02: 00       illegal
3D03: 00       illegal
3D04: 00       illegal
3D05: 00       illegal
3D06: 00       illegal
3D07: 43       coma 
3D08: 46       rora 
3D09: 4C       inca 
3D0A: 58       aslb 
3D0B: 70 58 4C neg  $584C
3D0E: 46       rora 
3D0F: 43       coma 
3D10: 00       illegal
3D11: 00       illegal
3D12: 00       illegal
3D13: 00       illegal
3D14: 00       illegal
3D15: 00       illegal
3D16: 00       illegal
3D17: 20 20    bra  $3D39
3D19: 20 20    bra  $3D3B
3D1B: 20 20    bra  $3D3D
3D1D: 20 20    bra  $3D3F
3D1F: 3F       swi  
3D20: 00       illegal
3D21: 00       illegal
3D22: 00       illegal
3D23: 00       illegal
3D24: 00       illegal
3D25: 00       illegal
3D26: 00       illegal
3D27: 41       illegal
3D28: 63 77    com  (x+$77)
3D2A: 5D       tstb 
3D2B: 49       rola 
3D2C: 41       illegal
3D2D: 41       illegal
3D2E: 41       illegal
3D2F: 41       illegal
3D30: 00       illegal
3D31: 00       illegal
3D32: 00       illegal
3D33: 00       illegal
3D34: 00       illegal
3D35: 00       illegal
3D36: 00       illegal
3D37: 41       illegal
3D38: 61       illegal
3D39: 71       illegal
3D3A: 59       rolb 
3D3B: 4D       tsta 
3D3C: 47       asra 
3D3D: 43       coma 
3D3E: 41       illegal
3D3F: 41       illegal
3D40: 00       illegal
3D41: 00       illegal
3D42: 00       illegal
3D43: 00       illegal
3D44: 00       illegal
3D45: 00       illegal
3D46: 00       illegal
3D47: 1C       illegal
3D48: 36       psha 
3D49: 63 41    com  (x+$41)
3D4B: 41       illegal
3D4C: 41       illegal
3D4D: 63 36    com  (x+$36)
3D4F: 1C       illegal
3D50: 00       illegal
3D51: 00       illegal
3D52: 00       illegal
3D53: 00       illegal
3D54: 00       illegal
3D55: 00       illegal
3D56: 00       illegal
3D57: 3E       wai  
3D58: 23 21    bls  $3D7B
3D5A: 23 2E    bls  $3D8A
3D5C: 20 20    bra  $3D7E
3D5E: 20 20    bra  $3D80
3D60: 00       illegal
3D61: 00       illegal
3D62: 00       illegal
3D63: 00       illegal
3D64: 00       illegal
3D65: 00       illegal
3D66: 00       illegal
3D67: 3E       wai  
3D68: 63 41    com  (x+$41)
3D6A: 41       illegal
3D6B: 41       illegal
3D6C: 41       illegal
3D6D: 41       illegal
3D6E: 6B       illegal
3D6F: 3E       wai  
3D70: 08       inx  
3D71: 08       inx  
3D72: 00       illegal
3D73: 00       illegal
3D74: 00       illegal
3D75: 00       illegal
3D76: 00       illegal
3D77: 7C 46 42 inc  $4642
3D7A: 46       rora 
3D7B: 7C 58 4C inc  $584C
3D7E: 46       rora 
3D7F: 43       coma 
3D80: 00       illegal
3D81: 00       illegal
3D82: 00       illegal
3D83: 00       illegal
3D84: 00       illegal
3D85: 00       illegal
3D86: 00       illegal
3D87: 3C       illegal
3D88: 66 60    ror  (x+$60)
3D8A: 30       tsx  
3D8B: 1C       illegal
3D8C: 06       tap  
3D8D: 03       illegal
3D8E: 63 3E    com  (x+$3E)
3D90: 00       illegal
3D91: 00       illegal
3D92: 00       illegal
3D93: 00       illegal
3D94: 00       illegal
3D95: 00       illegal
3D96: 00       illegal
3D97: 7F 08 08 clr  $0808
3D9A: 08       inx  
3D9B: 08       inx  
3D9C: 08       inx  
3D9D: 08       inx  
3D9E: 08       inx  
3D9F: 08       inx  
3DA0: 00       illegal
3DA1: 00       illegal
3DA2: 00       illegal
3DA3: 00       illegal
3DA4: 00       illegal
3DA5: 00       illegal
3DA6: 00       illegal
3DA7: 41       illegal
3DA8: 41       illegal
3DA9: 41       illegal
3DAA: 41       illegal
3DAB: 41       illegal
3DAC: 41       illegal
3DAD: 41       illegal
3DAE: 63 3E    com  (x+$3E)
3DB0: 00       illegal
3DB1: 00       illegal
3DB2: 00       illegal
3DB3: 00       illegal
3DB4: 00       illegal
3DB5: 00       illegal
3DB6: 00       illegal
3DB7: 41       illegal
3DB8: 41       illegal
3DB9: 41       illegal
3DBA: 41       illegal
3DBB: 41       illegal
3DBC: 63 36    com  (x+$36)
3DBE: 1C       illegal
3DBF: 08       inx  
3DC0: 00       illegal
3DC1: 00       illegal
3DC2: 00       illegal
3DC3: 00       illegal
3DC4: 00       illegal
3DC5: 00       illegal
3DC6: 00       illegal
3DC7: 41       illegal
3DC8: 41       illegal
3DC9: 41       illegal
3DCA: 41       illegal
3DCB: 49       rola 
3DCC: 5D       tstb 
3DCD: 77 63 41 asr  $6341
3DD0: 00       illegal
3DD1: 00       illegal
3DD2: 00       illegal
3DD3: 00       illegal
3DD4: 00       illegal
3DD5: 00       illegal
3DD6: 00       illegal
3DD7: 41       illegal
3DD8: 63 36    com  (x+$36)
3DDA: 1C       illegal
3DDB: 08       inx  
3DDC: 1C       illegal
3DDD: 36       psha 
3DDE: 63 41    com  (x+$41)
3DE0: 00       illegal
3DE1: 00       illegal
3DE2: 00       illegal
3DE3: 00       illegal
3DE4: 00       illegal
3DE5: 00       illegal
3DE6: 00       illegal
3DE7: 41       illegal
3DE8: 63 36    com  (x+$36)
3DEA: 1C       illegal
3DEB: 08       inx  
3DEC: 08       inx  
3DED: 08       inx  
3DEE: 08       inx  
3DEF: 08       inx  
3DF0: 00       illegal
3DF1: 00       illegal
3DF2: 00       illegal
3DF3: 00       illegal
3DF4: 00       illegal
3DF5: 00       illegal
3DF6: 00       illegal
3DF7: 7F 03 06 clr  $0306
3DFA: 0C       clc  
3DFB: 18       illegal
3DFC: 30       tsx  
3DFD: 60 40    neg  (x+$40)
3DFF: 7F 00 00 clr  $0000
3E02: 00       illegal
3E03: 00       illegal
3E04: 00       illegal
3E05: 00       illegal
3E06: 41       illegal
3E07: 1C       illegal
3E08: 36       psha 
3E09: 63 41    com  (x+$41)
3E0B: 41       illegal
3E0C: 7F 41 41 clr  $4141
3E0F: 41       illegal
3E10: 00       illegal
3E11: 00       illegal
3E12: 00       illegal
3E13: 00       illegal
3E14: 00       illegal
3E15: 00       illegal
3E16: 41       illegal
3E17: 1C       illegal
3E18: 36       psha 
3E19: 63 41    com  (x+$41)
3E1B: 41       illegal
3E1C: 41       illegal
3E1D: 63 36    com  (x+$36)
3E1F: 1C       illegal
3E20: 00       illegal
3E21: 00       illegal
3E22: 00       illegal
3E23: 00       illegal
3E24: 00       illegal
3E25: 00       illegal
3E26: 08       inx  
3E27: 14       illegal
3E28: 08       inx  
3E29: 36       psha 
3E2A: 63 41    com  (x+$41)
3E2C: 7F 41 41 clr  $4141
3E2F: 41       illegal
3E30: 00       illegal
3E31: 00       illegal
3E32: 00       illegal
3E33: 00       illegal
3E34: 00       illegal
3E35: 00       illegal
3E36: 41       illegal
3E37: 00       illegal
3E38: 41       illegal
3E39: 41       illegal
3E3A: 41       illegal
3E3B: 41       illegal
3E3C: 41       illegal
3E3D: 41       illegal
3E3E: 63 3E    com  (x+$3E)
3E40: 00       illegal
3E41: 00       illegal
3E42: 00       illegal
3E43: 00       illegal
3E44: 00       illegal
3E45: 00       illegal
3E46: 00       illegal
3E47: 00       illegal
3E48: 00       illegal
3E49: 00       illegal
3E4A: 00       illegal
3E4B: 00       illegal
3E4C: 00       illegal
3E4D: 00       illegal
3E4E: 00       illegal
3E4F: 00       illegal
3E50: 00       illegal
3E51: 00       illegal
3E52: 00       illegal
3E53: 00       illegal
3E54: 00       illegal
3E55: 00       illegal
3E56: 00       illegal
3E57: 02       illegal
3E58: 04       illegal
3E59: 3C       illegal
3E5A: 42       illegal
3E5B: 42       illegal
3E5C: 5C       incb 
3E5D: 40       nega 
3E5E: 42       illegal
3E5F: 3C       illegal
3E60: 00       illegal
3E61: 00       illegal
3E62: 00       illegal
3E63: 00       illegal
3E64: 00       illegal
3E65: 00       illegal
3E66: 00       illegal
3E67: 00       illegal
3E68: 00       illegal
3E69: 1C       illegal
3E6A: 22 02    bhi  $3E6E
3E6C: 3E       wai  
3E6D: 42       illegal
3E6E: 46       rora 
3E6F: 3A       illegal
3E70: 00       illegal
3E71: 00       illegal
3E72: 00       illegal
3E73: 00       illegal
3E74: 00       illegal
3E75: 00       illegal
3E76: 00       illegal
3E77: 40       nega 
3E78: 40       nega 
3E79: 5C       incb 
3E7A: 62       illegal
3E7B: 42       illegal
3E7C: 42       illegal
3E7D: 42       illegal
3E7E: 62       illegal
3E7F: 5C       incb 
3E80: 00       illegal
3E81: 00       illegal
3E82: 00       illegal
3E83: 00       illegal
3E84: 00       illegal
3E85: 00       illegal
3E86: 00       illegal
3E87: 00       illegal
3E88: 00       illegal
3E89: 3C       illegal
3E8A: 42       illegal
3E8B: 40       nega 
3E8C: 40       nega 
3E8D: 40       nega 
3E8E: 42       illegal
3E8F: 3C       illegal
3E90: 00       illegal
3E91: 00       illegal
3E92: 00       illegal
3E93: 00       illegal
3E94: 00       illegal
3E95: 00       illegal
3E96: 00       illegal
3E97: 02       illegal
3E98: 02       illegal
3E99: 3A       illegal
3E9A: 46       rora 
3E9B: 42       illegal
3E9C: 42       illegal
3E9D: 42       illegal
3E9E: 46       rora 
3E9F: 3A       illegal
3EA0: 00       illegal
3EA1: 00       illegal
3EA2: 00       illegal
3EA3: 00       illegal
3EA4: 00       illegal
3EA5: 00       illegal
3EA6: 00       illegal
3EA7: 00       illegal
3EA8: 00       illegal
3EA9: 3C       illegal
3EAA: 42       illegal
3EAB: 42       illegal
3EAC: 5C       incb 
3EAD: 40       nega 
3EAE: 42       illegal
3EAF: 3C       illegal
3EB0: 00       illegal
3EB1: 00       illegal
3EB2: 00       illegal
3EB3: 00       illegal
3EB4: 00       illegal
3EB5: 00       illegal
3EB6: 00       illegal
3EB7: 0E       cli  
3EB8: 10       sba  
3EB9: 38       illegal
3EBA: 10       sba  
3EBB: 10       sba  
3EBC: 10       sba  
3EBD: 10       sba  
3EBE: 10       sba  
3EBF: 10       sba  
3EC0: 00       illegal
3EC1: 00       illegal
3EC2: 00       illegal
3EC3: 00       illegal
3EC4: 00       illegal
3EC5: 00       illegal
3EC6: 00       illegal
3EC7: 00       illegal
3EC8: 00       illegal
3EC9: 3C       illegal
3ECA: 42       illegal
3ECB: 42       illegal
3ECC: 42       illegal
3ECD: 42       illegal
3ECE: 46       rora 
3ECF: 3A       illegal
3ED0: 02       illegal
3ED1: 02       illegal
3ED2: 1C       illegal
3ED3: 00       illegal
3ED4: 00       illegal
3ED5: 00       illegal
3ED6: 00       illegal
3ED7: 40       nega 
3ED8: 40       nega 
3ED9: 5C       incb 
3EDA: 62       illegal
3EDB: 42       illegal
3EDC: 42       illegal
3EDD: 42       illegal
3EDE: 42       illegal
3EDF: 42       illegal
3EE0: 00       illegal
3EE1: 00       illegal
3EE2: 00       illegal
3EE3: 00       illegal
3EE4: 00       illegal
3EE5: 00       illegal
3EE6: 00       illegal
3EE7: 08       inx  
3EE8: 00       illegal
3EE9: 08       inx  
3EEA: 08       inx  
3EEB: 08       inx  
3EEC: 08       inx  
3EED: 08       inx  
3EEE: 08       inx  
3EEF: 08       inx  
3EF0: 00       illegal
3EF1: 00       illegal
3EF2: 00       illegal
3EF3: 00       illegal
3EF4: 00       illegal
3EF5: 00       illegal
3EF6: 00       illegal
3EF7: 08       inx  
3EF8: 00       illegal
3EF9: 08       inx  
3EFA: 08       inx  
3EFB: 08       inx  
3EFC: 08       inx  
3EFD: 08       inx  
3EFE: 08       inx  
3EFF: 08       inx  
3F00: 08       inx  
3F01: 08       inx  
3F02: 30       tsx  
3F03: 00       illegal
3F04: 00       illegal
3F05: 00       illegal
3F06: 00       illegal
3F07: 40       nega 
3F08: 40       nega 
3F09: 44       lsra 
3F0A: 48       asla 
3F0B: 50       negb 
3F0C: 70 48 44 neg  $4844
3F0F: 42       illegal
3F10: 00       illegal
3F11: 00       illegal
3F12: 00       illegal
3F13: 00       illegal
3F14: 00       illegal
3F15: 00       illegal
3F16: 00       illegal
3F17: 10       sba  
3F18: 10       sba  
3F19: 10       sba  
3F1A: 10       sba  
3F1B: 10       sba  
3F1C: 10       sba  
3F1D: 10       sba  
3F1E: 10       sba  
3F1F: 0C       clc  
3F20: 00       illegal
3F21: 00       illegal
3F22: 00       illegal
3F23: 00       illegal
3F24: 00       illegal
3F25: 00       illegal
3F26: 00       illegal
3F27: 00       illegal
3F28: 00       illegal
3F29: 76 49 49 ror  $4949
3F2C: 49       rola 
3F2D: 49       rola 
3F2E: 49       rola 
3F2F: 49       rola 
3F30: 00       illegal
3F31: 00       illegal
3F32: 00       illegal
3F33: 00       illegal
3F34: 00       illegal
3F35: 00       illegal
3F36: 00       illegal
3F37: 00       illegal
3F38: 00       illegal
3F39: 5C       incb 
3F3A: 62       illegal
3F3B: 42       illegal
3F3C: 42       illegal
3F3D: 42       illegal
3F3E: 42       illegal
3F3F: 42       illegal
3F40: 00       illegal
3F41: 00       illegal
3F42: 00       illegal
3F43: 00       illegal
3F44: 00       illegal
3F45: 00       illegal
3F46: 00       illegal
3F47: 00       illegal
3F48: 00       illegal
3F49: 3C       illegal
3F4A: 42       illegal
3F4B: 42       illegal
3F4C: 42       illegal
3F4D: 42       illegal
3F4E: 42       illegal
3F4F: 3C       illegal
3F50: 00       illegal
3F51: 00       illegal
3F52: 00       illegal
3F53: 00       illegal
3F54: 00       illegal
3F55: 00       illegal
3F56: 00       illegal
3F57: 00       illegal
3F58: 00       illegal
3F59: 3C       illegal
3F5A: 42       illegal
3F5B: 42       illegal
3F5C: 42       illegal
3F5D: 42       illegal
3F5E: 62       illegal
3F5F: 5C       incb 
3F60: 40       nega 
3F61: 40       nega 
3F62: 40       nega 
3F63: 00       illegal
3F64: 00       illegal
3F65: 00       illegal
3F66: 00       illegal
3F67: 00       illegal
3F68: 00       illegal
3F69: 3C       illegal
3F6A: 42       illegal
3F6B: 42       illegal
3F6C: 42       illegal
3F6D: 42       illegal
3F6E: 46       rora 
3F6F: 3A       illegal
3F70: 02       illegal
3F71: 02       illegal
3F72: 02       illegal
3F73: 00       illegal
3F74: 00       illegal
3F75: 00       illegal
3F76: 00       illegal
3F77: 00       illegal
3F78: 00       illegal
3F79: 16       tab  
3F7A: 18       illegal
3F7B: 10       sba  
3F7C: 10       sba  
3F7D: 10       sba  
3F7E: 10       sba  
3F7F: 10       sba  
3F80: 00       illegal
3F81: 00       illegal
3F82: 00       illegal
3F83: 00       illegal
3F84: 00       illegal
3F85: 00       illegal
3F86: 00       illegal
3F87: 00       illegal
3F88: 00       illegal
3F89: 3C       illegal
3F8A: 42       illegal
3F8B: 30       tsx  
3F8C: 0C       clc  
3F8D: 02       illegal
3F8E: 42       illegal
3F8F: 3C       illegal
3F90: 00       illegal
3F91: 00       illegal
3F92: 00       illegal
3F93: 00       illegal
3F94: 00       illegal
3F95: 00       illegal
3F96: 00       illegal
3F97: 10       sba  
3F98: 10       sba  
3F99: 38       illegal
3F9A: 10       sba  
3F9B: 10       sba  
3F9C: 10       sba  
3F9D: 10       sba  
3F9E: 10       sba  
3F9F: 0C       clc  
3FA0: 00       illegal
3FA1: 00       illegal
3FA2: 00       illegal
3FA3: 00       illegal
3FA4: 00       illegal
3FA5: 00       illegal
3FA6: 00       illegal
3FA7: 00       illegal
3FA8: 00       illegal
3FA9: 42       illegal
3FAA: 42       illegal
3FAB: 42       illegal
3FAC: 42       illegal
3FAD: 42       illegal
3FAE: 42       illegal
3FAF: 3C       illegal
3FB0: 00       illegal
3FB1: 00       illegal
3FB2: 00       illegal
3FB3: 00       illegal
3FB4: 00       illegal
3FB5: 00       illegal
3FB6: 00       illegal
3FB7: 00       illegal
3FB8: 00       illegal
3FB9: 41       illegal
3FBA: 41       illegal
3FBB: 41       illegal
3FBC: 41       illegal
3FBD: 22 14    bhi  $3FD3
3FBF: 08       inx  
3FC0: 00       illegal
3FC1: 00       illegal
3FC2: 00       illegal
3FC3: 00       illegal
3FC4: 00       illegal
3FC5: 00       illegal
3FC6: 00       illegal
3FC7: 00       illegal
3FC8: 00       illegal
3FC9: 41       illegal
3FCA: 41       illegal
3FCB: 41       illegal
3FCC: 49       rola 
3FCD: 55       illegal
3FCE: 63 41    com  (x+$41)
3FD0: 00       illegal
3FD1: 00       illegal
3FD2: 00       illegal
3FD3: 00       illegal
3FD4: 00       illegal
3FD5: 00       illegal
3FD6: 00       illegal
3FD7: 00       illegal
3FD8: 00       illegal
3FD9: 41       illegal
3FDA: 22 14    bhi  $3FF0
3FDC: 08       inx  
3FDD: 14       illegal
3FDE: 22 41    bhi  $4021
3FE0: 00       illegal
3FE1: 00       illegal
3FE2: 00       illegal
3FE3: 00       illegal
3FE4: 00       illegal
3FE5: 00       illegal
3FE6: 00       illegal
3FE7: 00       illegal
3FE8: 00       illegal
3FE9: 42       illegal
3FEA: 42       illegal
3FEB: 42       illegal
3FEC: 42       illegal
3FED: 42       illegal
3FEE: 46       rora 
3FEF: 3A       illegal
3FF0: 02       illegal
3FF1: 02       illegal
3FF2: 3C       illegal
3FF3: 00       illegal
3FF4: 00       illegal
3FF5: 00       illegal
3FF6: 00       illegal
3FF7: 00       illegal
3FF8: 00       illegal
3FF9: 7E 04 08 jmp  $0408
3FFC: 10       sba  
3FFD: 20 40    bra  $403F
3FFF: 7E 00 00 jmp  $0000
4002: 00       illegal
4003: 00       illegal
4004: 00       illegal
4005: 00       illegal
4006: 00       illegal
4007: 24 00    bcc  $4009
4009: 1C       illegal
400A: 22 02    bhi  $400E
400C: 3E       wai  
400D: 42       illegal
400E: 46       rora 
400F: 3A       illegal
4010: 00       illegal
4011: 00       illegal
4012: 00       illegal
4013: 00       illegal
4014: 00       illegal
4015: 00       illegal
4016: 00       illegal
4017: 24 00    bcc  $4019
4019: 3C       illegal
401A: 42       illegal
401B: 42       illegal
401C: 42       illegal
401D: 42       illegal
401E: 42       illegal
401F: 3C       illegal
4020: 00       illegal
4021: 00       illegal
4022: 00       illegal
4023: 00       illegal
4024: 00       illegal
4025: 00       illegal
4026: 08       inx  
4027: 14       illegal
4028: 08       inx  
4029: 1C       illegal
402A: 22 02    bhi  $402E
402C: 3E       wai  
402D: 42       illegal
402E: 46       rora 
402F: 3A       illegal
4030: 00       illegal
4031: 00       illegal
4032: 00       illegal
4033: 00       illegal
4034: 00       illegal
4035: 00       illegal
4036: 00       illegal
4037: 42       illegal
4038: 00       illegal
4039: 42       illegal
403A: 42       illegal
403B: 42       illegal
403C: 42       illegal
403D: 42       illegal
403E: 42       illegal
403F: 3C       illegal
4040: 00       illegal
4041: 00       illegal
4042: 00       illegal
4043: 00       illegal
4044: 00       illegal
4045: 00       illegal
4046: 00       illegal
4047: 18       illegal
4048: 18       illegal
4049: 18       illegal
404A: 18       illegal
404B: 00       illegal
404C: 18       illegal
404D: 18       illegal
404E: 18       illegal
404F: 18       illegal
4050: 00       illegal
4051: 00       illegal
4052: 00       illegal
4053: 00       illegal
4054: 00       illegal
4055: 72       illegal
4056: 00       illegal
4057: 60 10    neg  (x+$10)
4059: 00       illegal
405A: 00       illegal

               org  $405B
               fcc  "RESET-DUMP IN PROGRESSIPLDUMP "

4079: 00    bra  $407A
407A: 00       illegal
               org  $407B
               fcc  "MRW ERROR"
               fcc  "*OS*
               fcc  "    FDS "

4090: 00    bra  $4091
4091: 00       illegal
4092: 00       illegal
4093: 00       illegal
               org  $4094
               fcc "SYSIPL  NIP LOADE98058 7037"


; subroutine called from $3664
40AF: CE 03 D0 ldx  #$03D0
40B2: FF 03 CE stx  $03CE
40B5: FF 03 F0 stx  $03F0
40B8: 7F 03 CD clr  $03CD
40BB: 7F 02 8E clr  $028E
40BE: 7F 02 91 clr  $0291
40C1: 7F 02 90 clr  $0290
40C4: 7F 04 10 clr  $0410
40C7: 86 01    lda  #$01
40C9: B7 05 6C sta  $056C
40CC: CE 05 6C ldx  #$056C
40CF: FF 05 68 stx  $0568
40D2: CE 41 44 ldx  #$4144
40D5: FF 05 6A stx  $056A
40D8: CE 05 68 ldx  #$0568
40DB: BD 24 67 jsr  $2467
40DE: FF 04 00 stx  $0400
40E1: 7F 04 03 clr  $0403
40E4: 7F 03 F5 clr  $03F5
40E7: CE 1D 70 ldx  #$1D70
40EA: FF 01 8A stx  $018A
40ED: 7F 04 02 clr  $0402
40F0: 86 88    lda  #$88
40F2: B7 04 19 sta  $0419
40F5: 7F 03 FE clr  $03FE
40F8: 86 01    lda  #$01
40FA: B7 05 6D sta  $056D
40FD: CE 05 6D ldx  #$056D
4100: FF 05 68 stx  $0568
4103: CE 41 42 ldx  #$4142
4106: FF 05 6A stx  $056A
4109: CE 05 68 ldx  #$0568
410C: BD 24 67 jsr  $2467
410F: FF 04 0E stx  $040E
4112: CE 02 66 ldx  #$0266
4115: FF 03 AC stx  $03AC
4118: CE 04 11 ldx  #$0411
411B: 6F 00    clr  (x+$00)
411D: 6F 01    clr  (x+$01)
411F: 6F 04    clr  (x+$04)
4121: CE 02 92 ldx  #$0292
4124: 6F 00    clr  (x+$00)
4126: 6F 01    clr  (x+$01)
4128: 6F 04    clr  (x+$04)
412A: 86 A0    lda  #$A0
412C: FE 04 0E ldx  $040E
412F: A7 00    sta  (x+$00)
4131: CE 1D AD ldx  #$1DAD
4134: FF 04 04 stx  $0404
4137: 86 9A    lda  #$9A
4139: B7 F7 C0 sta  $F7C0
413C: 86 88    lda  #$88
413E: B7 F7 C1 sta  $F7C1
4141: 39       rts


               org  $4142
               fdb  $0406
               fdb  $03F6

               org  $4146
; the disassembly lost track here

4146: CE 24 E3 ldx  #$24E3
4149: FF 01 84 stx  $0184
414C: 39       rts  

; subroutine called from $4689
414D: B6 02 C7 lda  $02C7
4150: F6 02 C8 ldb  $02C8
4153: C0 FC    subb #$FC
4155: 82 BF    sbca #$BF
4157: 25 05    bcs  $415E
4159: 86 80    lda  #$80
415B: B7 04 23 sta  $0423
415E: 7F F7 53 clr  $F753
4161: 86 FF    lda  #$FF
4163: B7 F7 52 sta  $F752
4166: 86 04    lda  #$04
4168: B7 F7 53 sta  $F753
416B: 86 55    lda  #$55
416D: B7 F7 52 sta  $F752
4170: F6 F7 52 ldb  $F752
4173: C1 55    cmpb #$55
4175: 27 03    beq  $417A
4177: 7E 46 26 jmp  $4626
417A: 86 AA    lda  #$AA
417C: B7 F7 52 sta  $F752
417F: F6 F7 52 ldb  $F752
4182: C1 AA    cmpb #$AA
4184: 27 03    beq  $4189
4186: 7E 46 26 jmp  $4626
4189: B6 04 23 lda  $0423
418C: 8A 40    ora  #$40
418E: B7 04 23 sta  $0423
4191: 81 C0    cmpa #$C0
4193: 27 03    beq  $4198
4195: 7E 46 26 jmp  $4626
4198: CE 83 85 ldx  #$8385
419B: FF 01 87 stx  $0187
419E: CE 01 DD ldx  #$01DD
41A1: FF 05 70 stx  $0570
41A4: CE 01 BD ldx  #$01BD
41A7: FF 05 78 stx  $0578
41AA: 86 41    lda  #$41
41AC: B7 05 80 sta  $0580
41AF: CE 05 80 ldx  #$0580
41B2: FF 05 74 stx  $0574
41B5: CE 46 71 ldx  #$4671
41B8: FF 05 72 stx  $0572
41BB: CE 46 79 ldx  #$4679
41BE: FF 05 76 stx  $0576
41C1: CE 00 00 ldx  #$0000
41C4: FF 05 7A stx  $057A
41C7: FF 05 7C stx  $057C
41CA: CE 05 70 ldx  #$0570
41CD: 86 10    lda  #$10
41CF: 3F       swi  
41D0: BD 46 3E jsr  $463E
41D3: CE 01 DD ldx  #$01DD
41D6: FF 05 70 stx  $0570
41D9: CE FF FE ldx  #$FFFE
41DC: FF 05 78 stx  $0578
41DF: FF 05 74 stx  $0574
41E2: CE 46 81 ldx  #$4681
41E5: FF 05 72 stx  $0572
41E8: CE FF FE ldx  #$FFFE
41EB: FF 05 76 stx  $0576
41EE: CE 00 00 ldx  #$0000
41F1: FF 05 7A stx  $057A
41F4: FF 05 7C stx  $057C
41F7: CE 05 70 ldx  #$0570
41FA: 86 10    lda  #$10
41FC: 3F       swi  
41FD: BD 46 3E jsr  $463E
4200: CE 01 DD ldx  #$01DD
4203: FF 05 70 stx  $0570
4206: CE FF FE ldx  #$FFFE
4209: FF 05 78 stx  $0578
420C: FF 05 74 stx  $0574
420F: CE 46 69 ldx  #$4669
4212: FF 05 72 stx  $0572
4215: CE FF FE ldx  #$FFFE
4218: FF 05 76 stx  $0576
421B: CE 00 00 ldx  #$0000
421E: FF 05 7A stx  $057A
4221: FF 05 7C stx  $057C
4224: CE 05 70 ldx  #$0570
4227: 86 10    lda  #$10
4229: 3F       swi  
422A: BD 46 3E jsr  $463E
422D: B6 02 3A lda  $023A
4230: 44       lsra 
4231: 44       lsra 
4232: B7 46 62 sta  $4662
4235: B6 FF E7 lda  $FFE7
4238: 81 07    cmpa #$07
423A: 26 2D    bne  $4269
423C: CE 81 15 ldx  #$8115
423F: DF 1D    stx  $1D
4241: CE 9C 87 ldx  #$9C87
4244: FF 05 81 stx  $0581
4247: 4F       clra 
4248: F6 46 62 ldb  $4662
424B: 58       aslb 
424C: 49       rola 
424D: 58       aslb 
424E: 49       rola 
424F: 58       aslb 
4250: 49       rola 
4251: 58       aslb 
4252: 49       rola 
4253: FB 05 82 addb $0582
4256: B9 05 81 adca $0581
4259: F7 05 82 stb  $0582
425C: B7 05 81 sta  $0581
425F: FE 05 81 ldx  $0581
4262: C6 10    ldb  #$10
4264: BD FE 2F jsr  $FE2F
4267: 20 2B    bra  $4294
4269: CE 81 15 ldx  #$8115
426C: DF 1D    stx  $1D
426E: CE 9A 07 ldx  #$9A07
4271: FF 05 81 stx  $0581
4274: 4F       clra 
4275: F6 46 62 ldb  $4662
4278: 58       aslb 
4279: 49       rola 
427A: 58       aslb 
427B: 49       rola 
427C: 58       aslb 
427D: 49       rola 
427E: 58       aslb 
427F: 49       rola 
4280: FB 05 82 addb $0582
4283: B9 05 81 adca $0581
4286: F7 05 82 stb  $0582
4289: B7 05 81 sta  $0581
428C: FE 05 81 ldx  $0581
428F: C6 10    ldb  #$10
4291: BD FE 2F jsr  $FE2F
4294: 7F 9A 07 clr  $9A07
4297: B6 46 63 lda  $4663
429A: F6 46 64 ldb  $4664
429D: 7E 43 27 jmp  $4327
42A0: 86 01    lda  #$01
42A2: 20 6D    bra  $4311
42A4: FE 46 63 ldx  $4663
42A7: FF 05 81 stx  $0581
42AA: 4F       clra 
42AB: F6 9A 08 ldb  $9A08
42AE: FB 05 82 addb $0582
42B1: B9 05 81 adca $0581
42B4: F7 05 82 stb  $0582
42B7: B7 05 81 sta  $0581
42BA: FE 05 81 ldx  $0581
42BD: 09       dex  
42BE: A6 00    lda  (x+$00)
42C0: B1 81 15 cmpa $8115
42C3: 26 47    bne  $430C
42C5: FE 46 63 ldx  $4663
42C8: FF 05 81 stx  $0581
42CB: 4F       clra 
42CC: F6 9A 08 ldb  $9A08
42CF: FB 05 82 addb $0582
42D2: B9 05 81 adca $0581
42D5: F7 05 82 stb  $0582
42D8: B7 05 81 sta  $0581
42DB: FE 05 81 ldx  $0581
42DE: 09       dex  
42DF: A6 00    lda  (x+$00)
42E1: B7 9A 07 sta  $9A07
42E4: FE 46 63 ldx  $4663
42E7: FF 46 67 stx  $4667
42EA: CE 81 25 ldx  #$8125
42ED: DF 1D    stx  $1D
42EF: FE 46 67 ldx  $4667
42F2: FF 05 81 stx  $0581
42F5: 4F       clra 
42F6: C6 0D    ldb  #$0D
42F8: FB 05 82 addb $0582
42FB: B9 05 81 adca $0581
42FE: F7 05 82 stb  $0582
4301: B7 05 81 sta  $0581
4304: FE 05 81 ldx  $0581
4307: C6 3C    ldb  #$3C
4309: BD FE 2F jsr  $FE2F
430C: B6 9A 08 lda  $9A08
430F: 8B 01    adda #$01
4311: B7 9A 08 sta  $9A08
4314: 81 08    cmpa #$08
4316: 22 05    bhi  $431D
4318: B6 9A 07 lda  $9A07
431B: 27 87    beq  $42A4
431D: B6 46 63 lda  $4663
4320: F6 46 64 ldb  $4664
4323: CB 50    addb #$50
4325: 89 00    adca #$00
4327: F7 46 64 stb  $4664
432A: B7 46 63 sta  $4663
432D: F0 46 66 subb $4666
4330: B2 46 65 sbca $4665
4333: 22 0D    bhi  $4342
4335: 26 03    bne  $433A
4337: 5D       tstb 
4338: 26 08    bne  $4342
433A: B6 9A 07 lda  $9A07
433D: 26 03    bne  $4342
433F: 7E 42 A0 jmp  $42A0
4342: B6 81 23 lda  $8123
4345: 84 80    anda #$80
4347: 27 15    beq  $435E
4349: B6 81 4A lda  $814A
434C: 84 EF    anda #$EF
434E: F6 81 23 ldb  $8123
4351: C4 40    andb #$40
4353: 54       lsrb 
4354: 54       lsrb 
4355: F7 05 6F stb  $056F
4358: BA 05 6F ora  $056F
435B: B7 81 4A sta  $814A
435E: B6 81 23 lda  $8123
4361: 84 20    anda #$20
4363: 27 13    beq  $4378
4365: B6 81 52 lda  $8152
4368: 84 E3    anda #$E3
436A: F6 81 23 ldb  $8123
436D: C4 1C    andb #$1C
436F: F7 05 6F stb  $056F
4372: BA 05 6F ora  $056F
4375: B7 81 52 sta  $8152
4378: B6 81 15 lda  $8115
437B: 81 09    cmpa #$09
437D: 27 05    beq  $4384
437F: FE A3 62 ldx  $A362
4382: 20 03    bra  $4387
4384: FE A4 02 ldx  $A402
4387: FF 9A 09 stx  $9A09
438A: CE 81 61 ldx  #$8161
438D: FF 05 81 stx  $0581
4390: FE 9A 09 ldx  $9A09
4393: A6 00    lda  (x+$00)
4395: 08       inx  
4396: FF 9A 09 stx  $9A09
4399: 09       dex  
439A: 09       dex  
439B: F6 81 15 ldb  $8115
439E: C1 09    cmpb #$09
43A0: 27 07    beq  $43A9
43A2: BC A3 64 cmpx $A364
43A5: 26 07    bne  $43AE
43A7: 20 10    bra  $43B9
43A9: BC A4 04 cmpx $A404
43AC: 27 0B    beq  $43B9
43AE: FE 05 81 ldx  $0581
43B1: A7 00    sta  (x+$00)
43B3: 08       inx  
43B4: FF 05 81 stx  $0581
43B7: 20 D7    bra  $4390
43B9: B6 81 15 lda  $8115
43BC: 81 09    cmpa #$09
43BE: 20 1C    bra  $43DC ; jumps there...

43C0: 05       illegal
43C1: 81 F7    cmpa #$F7
43C3: 05       illegal
43C4: 82 B7    sbca #$B7
43C6: 05       illegal
43C7: 81 FE    cmpa #$FE
43C9: 05       illegal
43CA: 81 B6    cmpa #$B6
43CC: 05       illegal
43CD: 6E A7    jmp  (x+$A7)
43CF: 00       illegal
43D0: FE 9A 09 ldx  $9A09
43D3: 09       dex  
43D4: FF 9A 09 stx  $9A09
43D7: FE 9A 09 ldx  $9A09
43DA: 26 B4    bne  $4390

; jumps here
43DC: B6 9A 07 lda  $9A07
43DF: B7 81 15 sta  $8115
43E2: B6 9A 07 lda  $9A07
43E5: 26 08    bne  $43EF
43E7: B6 02 EA lda  $02EA
43EA: 8A 20    ora  #$20
43EC: B7 02 EA sta  $02EA
43EF: B6 81 3B lda  $813B
43F2: 27 0E    beq  $4402
43F4: B6 81 40 lda  $8140
43F7: 81 02    cmpa #$02
43F9: 26 07    bne  $4402
43FB: 86 01    lda  #$01
43FD: B7 82 BA sta  $82BA
4400: 20 03    bra  $4405
4402: 7F 82 BA clr  $82BA
4405: 86 01    lda  #$01
4407: B7 F7 59 sta  $F759
440A: B6 81 17 lda  $8117
440D: 26 26    bne  $4435
440F: FE 46 67 ldx  $4667
4412: A6 08    lda  (x+$08)
4414: 81 FF    cmpa #$FF
4416: 27 07    beq  $441F
4418: A6 08    lda  (x+$08)
441A: B7 81 17 sta  $8117
441D: 20 16    bra  $4435
441F: A6 0A    lda  (x+$0A)
4421: B7 F7 58 sta  $F758
4424: A6 0B    lda  (x+$0B)
4426: B7 F7 5A sta  $F75A
4429: A6 0C    lda  (x+$0C)
442B: B7 F7 5B sta  $F75B
442E: 86 DC    lda  #$DC
4430: B7 81 17 sta  $8117
4433: 20 7F    bra  $44B4
4435: 81 03    cmpa #$03
4437: 26 0F    bne  $4448
4439: 86 82    lda  #$82
443B: B7 F7 58 sta  $F758
443E: 7F F7 5A clr  $F75A
4441: 86 6E    lda  #$6E
4443: B7 F7 5B sta  $F75B
4446: 20 6C    bra  $44B4
4448: 81 06    cmpa #$06
444A: 26 0F    bne  $445B
444C: 86 82    lda  #$82
444E: B7 F7 58 sta  $F758
4451: 7F F7 5A clr  $F75A
4454: 86 36    lda  #$36
4456: B7 F7 5B sta  $F75B
4459: 20 59    bra  $44B4
445B: 81 12    cmpa #$12
445D: 26 0F    bne  $446E
445F: 86 82    lda  #$82
4461: B7 F7 58 sta  $F758
4464: 7F F7 5A clr  $F75A
4467: 86 1B    lda  #$1B
4469: B7 F7 5B sta  $F75B
446C: 20 46    bra  $44B4
446E: 81 24    cmpa #$24
4470: 26 0F    bne  $4481
4472: 86 82    lda  #$82
4474: B7 F7 58 sta  $F758
4477: 7F F7 5A clr  $F75A
447A: 86 0D    lda  #$0D
447C: B7 F7 5B sta  $F75B
447F: 20 33    bra  $44B4
4481: 81 48    cmpa #$48
4483: 26 0F    bne  $4494
4485: 86 82    lda  #$82
4487: B7 F7 58 sta  $F758
448A: 7F F7 5A clr  $F75A
448D: 86 06    lda  #$06
448F: B7 F7 5B sta  $F75B
4492: 20 20    bra  $44B4
4494: 81 96    cmpa #$96
4496: 26 0F    bne  $44A7
4498: 86 86    lda  #$86
449A: B7 F7 58 sta  $F758
449D: 7F F7 5A clr  $F75A
44A0: 86 06    lda  #$06
44A2: B7 F7 5B sta  $F75B
44A5: 20 0D    bra  $44B4
44A7: 86 EE    lda  #$EE
44A9: B7 81 17 sta  $8117
44AC: B6 02 EA lda  $02EA
44AF: 8A 10    ora  #$10
44B1: B7 02 EA sta  $02EA
44B4: 7F F7 59 clr  $F759
44B7: B6 81 55 lda  $8155
44BA: 88 FF    eora #$FF
44BC: F6 81 54 ldb  $8154
44BF: B7 05 6E sta  $056E
44C2: F4 05 6E andb $056E
44C5: F7 82 BC stb  $82BC
44C8: B6 82 BC lda  $82BC
44CB: B7 F7 58 sta  $F758
44CE: 7F F7 51 clr  $F751
44D1: B6 81 37 lda  $8137
44D4: B7 F7 50 sta  $F750
44D7: 86 04    lda  #$04
44D9: B7 F7 51 sta  $F751
44DC: B6 81 3A lda  $813A
44DF: B7 F7 50 sta  $F750
44E2: 7F F7 53 clr  $F753
44E5: B6 81 47 lda  $8147
44E8: B7 F7 52 sta  $F752
44EB: 86 04    lda  #$04
44ED: B7 F7 53 sta  $F753
44F0: B6 81 4A lda  $814A
44F3: B7 F7 52 sta  $F752
44F6: B6 F7 52 lda  $F752
44F9: B7 9A 07 sta  $9A07
44FC: B6 F7 50 lda  $F750
44FF: B7 9A 07 sta  $9A07
4502: 7F 80 8D clr  $808D
4505: 7F 80 8E clr  $808E
4508: B6 81 30 lda  $8130
450B: 81 01    cmpa #$01
450D: 26 49    bne  $4558
450F: B6 9A 07 lda  $9A07
4512: B4 81 2C anda $812C
4515: 26 12    bne  $4529
4517: B6 F7 51 lda  $F751
451A: 84 FC    anda #$FC
451C: B7 F7 51 sta  $F751
451F: 8A 02    ora  #$02
4521: BA 81 2E ora  $812E
4524: B7 F7 51 sta  $F751
4527: 20 0E    bra  $4537
4529: B6 F7 51 lda  $F751
452C: 84 FC    anda #$FC
452E: B7 F7 51 sta  $F751
4531: BA 81 2E ora  $812E
4534: B7 F7 51 sta  $F751
4537: B6 9A 07 lda  $9A07
453A: B8 81 39 eora $8139
453D: B7 80 8D sta  $808D
4540: B4 81 2C anda $812C
4543: 27 10    beq  $4555
4545: B6 80 8D lda  $808D
4548: 84 3F    anda #$3F
454A: B4 81 38 anda $8138
454D: BA 81 2D ora  $812D
4550: B7 80 8D sta  $808D
4553: 20 03    bra  $4558
4555: 7F 80 8D clr  $808D
4558: B6 81 36 lda  $8136
455B: 81 01    cmpa #$01
455D: 26 49    bne  $45A8
455F: B6 9A 07 lda  $9A07
4562: B4 81 32 anda $8132
4565: 26 12    bne  $4579
4567: B6 F7 51 lda  $F751
456A: 84 C7    anda #$C7
456C: B7 F7 51 sta  $F751
456F: 8A 10    ora  #$10
4571: BA 81 34 ora  $8134
4574: B7 F7 51 sta  $F751
4577: 20 0E    bra  $4587
4579: B6 F7 51 lda  $F751
457C: 84 C7    anda #$C7
457E: B7 F7 51 sta  $F751
4581: BA 81 34 ora  $8134
4584: B7 F7 51 sta  $F751
4587: B6 9A 07 lda  $9A07
458A: B8 81 39 eora $8139
458D: B7 80 8E sta  $808E
4590: B4 81 32 anda $8132
4593: 27 10    beq  $45A5
4595: B6 80 8E lda  $808E
4598: 84 3F    anda #$3F
459A: B4 81 38 anda $8138
459D: BA 81 33 ora  $8133
45A0: B7 80 8E sta  $808E
45A3: 20 03    bra  $45A8
45A5: 7F 80 8E clr  $808E
45A8: B6 81 2C lda  $812C
45AB: BA 81 32 ora  $8132
45AE: F6 F7 50 ldb  $F750
45B1: B7 05 6E sta  $056E
45B4: F4 05 6E andb $056E
45B7: B6 81 2C lda  $812C
45BA: BA 81 32 ora  $8132
45BD: F7 05 6F stb  $056F
45C0: F6 9A 07 ldb  $9A07
45C3: B7 05 6E sta  $056E
45C6: F4 05 6E andb $056E
45C9: B6 05 6F lda  $056F
45CC: 11       cba  
45CD: 27 03    beq  $45D2
45CF: 7E 44 F6 jmp  $44F6
45D2: B6 80 8D lda  $808D
45D5: BA 80 8E ora  $808E
45D8: B7 80 89 sta  $8089
45DB: B7 80 88 sta  $8088
45DE: B6 80 89 lda  $8089
45E1: B7 80 87 sta  $8087
45E4: 84 80    anda #$80
45E6: 27 08    beq  $45F0
45E8: B6 80 87 lda  $8087
45EB: 84 BF    anda #$BF
45ED: B7 80 87 sta  $8087
45F0: B6 80 87 lda  $8087
45F3: 84 C0    anda #$C0
45F5: 27 08    beq  $45FF
45F7: B6 02 EA lda  $02EA
45FA: 8A 08    ora  #$08
45FC: B7 02 EA sta  $02EA
45FF: 86 03    lda  #$03
4601: B7 F7 60 sta  $F760
4604: B6 81 52 lda  $8152
4607: B7 82 BB sta  $82BB
460A: B6 81 52 lda  $8152
460D: B7 F7 60 sta  $F760
4610: B6 F7 50 lda  $F750
4613: 84 FE    anda #$FE
4615: B7 F7 50 sta  $F750
4618: BA 82 BA ora  $82BA
461B: B7 F7 50 sta  $F750
461E: B6 02 3A lda  $023A
4621: 8A 01    ora  #$01
4623: B7 02 3A sta  $023A
4626: B6 04 23 lda  $0423
4629: 81 C0    cmpa #$C0
462B: 27 0A    beq  $4637
462D: 86 80    lda  #$80
462F: B7 02 EA sta  $02EA
4632: 86 FC    lda  #$FC
4634: B7 02 3A sta  $023A
4637: CE 26 C6 ldx  #$26C6
463A: FF 06 0A stx  $060A
463D: 39       rts  

; subroutine
463E: CE 01 DD ldx  #$01DD
4641: 86 12    lda  #$12
4643: 3F       swi  
4644: CE 01 DD ldx  #$01DD
4647: FF 05 71 stx  $0571
464A: 86 01    lda  #$01
464C: B7 05 70 sta  $0570
464F: CE 05 70 ldx  #$0570
4652: 86 06    lda  #$06
4654: 3F       swi  
4655: 5D       tstb 
4656: 26 01    bne  $4659
4658: 39       rts  
4659: B6 02 EA lda  $02EA
465C: 8A 40    ora  #$40
465E: B7 02 EA sta  $02EA
4661: 39       rts  

               org  $4662
               fcb  $00
               fcb  $9F
               fcb  $0E
               fdb  $A27E
               fdb  $0000
             

               org  $4669
               fcc  "PRDEF   PUPROGRMSYSLIB  PRSTRAPS"
               
; routine called from $3914
4689: BD 41 4D jsr  $414D
468C: 86 17    lda  #$17
468E: B7 03 B1 sta  $03B1
4691: B6 02 EA lda  $02EA
4694: 84 80    anda #$80
4696: 27 03    beq  $469B
4698: 7E 47 DB jmp  $47DB
469B: FE 83 21 ldx  $8321
469E: DF DD    stx  $DD
46A0: CE 80 A7 ldx  #$80A7
46A3: FF 80 09 stx  $8009
46A6: B6 80 09 lda  $8009
46A9: F6 80 0A ldb  $800A
46AC: CB 2C    addb #$2C
46AE: 89 00    adca #$00
46B0: F7 80 0C stb  $800C
46B3: B7 80 0B sta  $800B
46B6: 86 28    lda  #$28
46B8: B7 80 0D sta  $800D
46BB: FE 80 09 ldx  $8009
46BE: FF 80 0E stx  $800E
46C1: B6 81 15 lda  $8115
46C4: B7 80 17 sta  $8017
46C7: B6 81 16 lda  $8116
46CA: B7 80 18 sta  $8018
46CD: B6 81 19 lda  $8119
46D0: B7 80 19 sta  $8019
46D3: B6 81 1A lda  $811A
46D6: B7 80 1A sta  $801A
46D9: B6 81 19 lda  $8119
46DC: 26 06    bne  $46E4
46DE: B6 81 25 lda  $8125
46E1: B7 80 19 sta  $8019
46E4: B6 81 15 lda  $8115
46E7: 81 08    cmpa #$08
46E9: 26 26    bne  $4711
46EB: B6 81 1B lda  $811B
46EE: 27 04    beq  $46F4
46F0: 81 80    cmpa #$80
46F2: 25 08    bcs  $46FC
46F4: B6 81 26 lda  $8126
46F7: B7 80 1B sta  $801B
46FA: 20 03    bra  $46FF
46FC: B7 80 1B sta  $801B
46FF: B6 81 27 lda  $8127
4702: BB 81 1C adda $811C
4705: B7 80 1C sta  $801C
4708: 81 80    cmpa #$80
470A: 25 0B    bcs  $4717
470C: 7F 80 1C clr  $801C
470F: 20 06    bra  $4717
4711: 7F 80 1B clr  $801B
4714: 7F 80 1C clr  $801C
4717: B6 81 3D lda  $813D
471A: 84 3F    anda #$3F
471C: C6 80    ldb  #$80
471E: B7 05 83 sta  $0583
4721: FA 05 83 orb  $0583
4724: F7 80 E5 stb  $80E5
4727: 86 FF    lda  #$FF
4729: B7 80 86 sta  $8086
472C: 86 02    lda  #$02
472E: B7 82 01 sta  $8201
4731: 86 2B    lda  #$2B
4733: B7 82 0D sta  $820D
4736: 86 03    lda  #$03
4738: B7 82 19 sta  $8219
473B: 86 33    lda  #$33
473D: B7 82 25 sta  $8225
4740: 86 3B    lda  #$3B
4742: B7 82 31 sta  $8231
4745: B6 81 30 lda  $8130
4748: 81 01    cmpa #$01
474A: 26 21    bne  $476D
474C: B6 81 2F lda  $812F
474F: 84 01    anda #$01
4751: B7 82 8F sta  $828F
4754: B6 81 2E lda  $812E
4757: 84 01    anda #$01
4759: B7 82 90 sta  $8290
475C: 86 01    lda  #$01
475E: B7 82 91 sta  $8291
4761: B6 81 2B lda  $812B
4764: B7 82 92 sta  $8292
4767: B6 81 2C lda  $812C
476A: B7 82 94 sta  $8294
476D: B6 81 36 lda  $8136
4770: 81 01    cmpa #$01
4772: 26 2D    bne  $47A1
4774: B6 82 8F lda  $828F
4777: BA 81 35 ora  $8135
477A: 84 09    anda #$09
477C: B7 82 8F sta  $828F
477F: B6 82 90 lda  $8290
4782: BA 81 34 ora  $8134
4785: 84 09    anda #$09
4787: B7 82 90 sta  $8290
478A: 86 01    lda  #$01
478C: B7 82 91 sta  $8291
478F: B6 82 92 lda  $8292
4792: BA 81 31 ora  $8131
4795: B7 82 92 sta  $8292
4798: B6 82 94 lda  $8294
479B: BA 81 32 ora  $8132
479E: B7 82 94 sta  $8294
47A1: CE 82 98 ldx  #$8298
47A4: FF 82 A0 stx  $82A0
47A7: FF 82 9E stx  $829E
47AA: B6 81 24 lda  $8124
47AD: 84 01    anda #$01
47AF: 26 08    bne  $47B9
47B1: B6 83 20 lda  $8320
47B4: 84 BF    anda #$BF
47B6: B7 83 20 sta  $8320
47B9: FE 83 21 ldx  $8321
47BC: FF 82 C0 stx  $82C0
47BF: CE 80 46 ldx  #$8046
47C2: FF 05 84 stx  $0584
47C5: CE 80 85 ldx  #$8085
47C8: FF 05 86 stx  $0586
47CB: CE 87 E4 ldx  #$87E4
47CE: FF 05 88 stx  $0588
47D1: 86 FD    lda  #$FD
47D3: B7 05 8A sta  $058A
47D6: 4F       clra 
47D7: CE 05 84 ldx  #$0584
47DA: 3F       swi  
47DB: 39       rts  
; Routine to setup jumptable
47DC: CE 06 8F ldx  #$068F
47DF: DF 0A    stx  $0A
47E1: DF 0C    stx  $0C
47E3: 7E 47 E6 jmp  $47E6
47E6: CE 03 93 ldx  #$0393
47E9: DF 5F    stx  $5F
47EB: CE 03 93 ldx  #$0393
47EE: DF 61    stx  $61
47F0: 7F 00 65 clr  $0065
47F3: CE 08 5A ldx  #$085A
47F6: DF 66    stx  $66
47F8: 39       rts  
;
47F9: 22 83    bhi  $477E
47FB: 10       sba  
47FC: 12       asx1 (s+1)
47FD: 12       asx1 (s+1)
47FE: 37       pshb 
