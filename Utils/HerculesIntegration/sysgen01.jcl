//SYSGEN01 JOB (SYSGEN),'ASSEMBLE STAGE 1',                             00010000
//             CLASS=A,MSGCLASS=A,MSGLEVEL=(1,1)                        00020000
/*JOBPARM  LINES=100                                                    00030000
//*                                                                     00040000
//********************************************************************* 00050000
//* VERIFY STAGE 1 DECK AND PRODUCE STAGE 2 JOBSTREAMS                * 00060000
//*   1) DELETE OUTPUT FILE ON WORK01, IF IT EXISTS                   * 00070000
//*   2) ASSEMBLE STAGE 1 DECK                                        * 00080000
//*   3) IF ASSEMBLY HAS NO ERRORS, SUBMIT SECONDARY JOB TO COPY      * 00090000
//*      OUTPUT FROM STAGE 1 ASSEMBLY ONTO TAPE                       * 00100000
//********************************************************************* 00110000
//*                                                                     00120000
//CLEANUP  EXEC PGM=IEHPROGM                                            00130000
//*                                                                     00140000
//* ***************************************************************** * 00150000
//* DELETE STAGE 1 OUTPUT FROM PRIOR RUN (IF ANY)                     * 00160000
//* ***************************************************************** * 00170000
//*                                                                     00180000
//SYSPRINT DD  SYSOUT=*                                                 00190000
//DD1      DD  UNIT=3350,VOL=SER=WORK01,DISP=OLD                        00200000
//SYSIN    DD  *                                                        00210000
  SCRATCH DSNAME=SYS1.STAGE1.OUTPUT,VOL=3350=WORK01,PURGE               00220000
//*                                                                     00230000
//ASMBLR   EXEC PGM=ASMBLR,PARM='LIST,NOLOAD,DECK,NOXREF',REGION=2056K  00240000
//*                                                                     00250000
//* ***************************************************************** * 00260000
//* ASSEMBLE STAGE 1                                                  * 00270000
//* ***************************************************************** * 00280000
//*                                                                     00290000
//SYSPRINT DD  SYSOUT=*                                                 00300000
//SYSLIB   DD  DSN=SYS1.AMODGEN,DISP=SHR                                00310000
//         DD  DSN=SYS1.AGENLIB,DISP=SHR                                00320000
//SYSPUNCH DD  DSN=SYS1.STAGE1.OUTPUT,DISP=(NEW,KEEP),                  00330000
//             UNIT=3350,VOL=SER=WORK01,                                00340000
//             SPACE=(TRK,(30,30),RLSE),                                00350000
//             DCB=(RECFM=FB,LRECL=80,BLKSIZE=3120)                     00360000
//SYSUT1   DD  UNIT=SYSDA,SPACE=(CYL,(35,10))                           00370000
//SYSUT2   DD  UNIT=SYSDA,SPACE=(CYL,(35,10))                           00380000
//SYSUT3   DD  UNIT=SYSDA,SPACE=(CYL,(50,10))                           00390000
//SYSIN    DD  *                                                        00400000
         PRINT ON,NOGEN,NODATA                                          00410000
*                                                                       00420000
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 00430000
*                      INPUT/OUTPUT CHANNELS                          * 00440000
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 00450000
*                                                                       00460000
MPLXR    CHANNEL                                                       C00470000
               ADDRESS=(0),                                            C00480000
               TYPE=MULTIPLEXOR                                         00490000
*                                                                       00500000
SELECTOR CHANNEL                                                       C00510000
               ADDRESS=(1,2,3,4,5,6),                                  C00520000
               TYPE=SELECTOR                                            00530000
         EJECT                                                          00540000
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 00550000
*                         SYSTEM CONSOLES                             * 00560000
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 00570000
*                                                                       00580000
CONSMST  CONSOLE                                                       C00590000
               MCONS=010,                                              C00600000
               ALTCONS=009,                                            C00610000
               AREA=04,                                                C00620000
               PFK=12,                                                 C00630000
               ROUTCDE=ALL                                              00640000
*                                                                       00650000
CONSALT  CONSOLE                                                       C00660000
               SECONS=009,                                             C00670000
               ALTCONS=010,                                            C00680000
               AREA=04,                                                C00690000
               PFK=12,                                                 C00700000
               ROUTCDE=ALL                                              00710000
*                                                                       00720000
CONSHC   CONSOLE                                                       C00730000
               SECONS=O-015,                                           C00740000
               ALTCONS=009,                                            C00750000
               ROUTCDE=ALL                                              00760000
*                                                                       00770000
MSTCONS  IODEVICE                                                      C00780000
               UNIT=3277,                                              C00790000
               MODEL=2,                                                C00800000
               ADDRESS=010,                                            C00810000
               FEATURE=(EBKY3277,DOCHAR,KB78KEY,AUDALRM,NUMLOCK,SELPEN) 00820000
*                                                                       00830000
ALTCONS  IODEVICE                                                      C00840000
               UNIT=3277,                                              C00850000
               MODEL=2,                                                C00860000
               ADDRESS=009,                                            C00870000
               FEATURE=(EBKY3277,DOCHAR,KB78KEY,AUDALRM,NUMLOCK,SELPEN) 00880000
*                                                                       00890000
HCCONS   IODEVICE                                                      C00900000
               UNIT=1403,                                              C00910000
               MODEL=2,                                                C00920000
               ADDRESS=015                                              00930000
         EJECT                                                          00940000
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 00950000
*                          CHANNEL 0 DEVICES                          * 00960000
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 00970000
*                                                                       00980000
RDR00A   IODEVICE                                                      C00990000
               UNIT=3505,                                              C01000000
               ADDRESS=00A,                                            C01010000
               FEATURE=CARDIMAGE                                        01020000
*                                                                       01030000
PCH00B   IODEVICE                                                      C01040000
               UNIT=3525,                                              C01050000
               ADDRESS=00B,                                            C01060000
               FEATURE=CARDIMAGE                                        01070000
*                                                                       01080000
RDR00C   IODEVICE                                                      C01090000
               UNIT=2540R,                                             C01100000
               MODEL=1,                                                C01110000
               ADDRESS=00C,                                            C01120000
               FEATURE=CARDIMAGE                                        01130000
*                                                                       01140000
PCH00D   IODEVICE                                                      C01150000
               UNIT=2540P,                                             C01160000
               MODEL=1,                                                C01170000
               ADDRESS=00D,                                            C01180000
               FEATURE=CARDIMAGE                                        01190000
*                                                                       01200000
PRT00E   IODEVICE                                                      C01210000
               UNIT=1403,                                              C01220000
               MODEL=N1,                                               C01230000
               ADDRESS=00E,                                            C01240000
               FEATURE=UNVCHSET                                         01250000
*                                                                       01260000
PRT00F   IODEVICE                                                      C01270000
               UNIT=3211,                                              C01280000
               ADDRESS=00F                                              01290000
*                                                                       01300000
RDR01A   IODEVICE                                                      C01310000
               UNIT=2540R,                                             C01320000
               MODEL=1,                                                C01330000
               ADDRESS=01A,                                            C01340000
               FEATURE=CARDIMAGE                                        01350000
*                                                                       01360000
PCH01B   IODEVICE                                                      C01370000
               UNIT=2540P,                                             C01380000
               MODEL=1,                                                C01390000
               ADDRESS=01B,                                            C01400000
               FEATURE=CARDIMAGE                                        01410000
*                                                                       01420000
RDR01C   IODEVICE                                                      C01430000
               UNIT=2540R,                                             C01440000
               MODEL=1,                                                C01450000
               ADDRESS=01C,                                            C01460000
               FEATURE=CARDIMAGE                                        01470000
*                                                                       01480000
PCH01D   IODEVICE                                                      C01490000
               UNIT=2540P,                                             C01500000
               MODEL=1,                                                C01510000
               ADDRESS=01D,                                            C01520000
               FEATURE=CARDIMAGE                                        01530000
*                                                                       01540000
PRT01E   IODEVICE                                                      C01550000
               UNIT=1403,                                              C01560000
               MODEL=N1,                                               C01570000
               ADDRESS=01E,                                            C01580000
               FEATURE=UNVCHSET                                         01590000
*                                                                       01600000
PRT01F   IODEVICE                                                      C01610000
               UNIT=3211,                                              C01620000
               ADDRESS=01F                                              01630000
         EJECT                                                          01640000
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 01650000
*                          CHANNEL 1 DEVICES                          * 01660000
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 01670000
*                                                                       01680000
T2401@1  IODEVICE                                                      C01690000
               UNIT=2401,                                              C01700000
               MODEL=6,                                                C01710000
               ADDRESS=(100,4),                                        C01720000
               FEATURE=(9-TRACK,DUALDENS)                               01730000
*                                                                       01740000
T3420@1  IODEVICE                                                      C01750000
               UNIT=3420,                                              C01760000
               MODEL=8,                                                C01770000
               ADDRESS=(110,4),                                        C01780000
               FEATURE=(9-TRACK,OPT1600)                                01790000
*                                                                       01800000
D2314@1  IODEVICE                                                      C01810000
               UNIT=2314,                                              C01820000
               ADDRESS=(120,8)                                          01830000
*                                                                       01840000
D33301@1 IODEVICE                                                      C01850000
               MODEL=1,                                                C01860000
               UNIT=3330,                                              C01870000
               ADDRESS=(130,8)                                          01880000
*                                                                       01890000
D33302@1 IODEVICE                                                      C01900000
               MODEL=11,                                               C01910000
               UNIT=3330,                                              C01920000
               ADDRESS=(138,8)                                          01930000
*                                                                       01940000
D3340@1  IODEVICE                                                      C01950000
               UNIT=3340,                                              C01960000
               ADDRESS=(140,8)                                          01970000
*                                                                       01980000
D3350@1  IODEVICE                                                      C01990000
               UNIT=3350,                                              C02000000
               ADDRESS=(150,8)                                          02010000
*                                                                       02020000
D3375@1  IODEVICE                                                      C02030000
               UNIT=3375,                                              C02040000
               ADDRESS=(170,8)                                          02050000
*                                                                       02060000
D3380@1  IODEVICE                                                      C02070000
               UNIT=3380,                                              C02080000
               ADDRESS=(180,8)                                          02090000
*                                                                       02100000
D3390@1  IODEVICE                                                      C02110000
               UNIT=3390,                                              C02120000
               ADDRESS=(190,8)                                          02130000
         EJECT                                                          02140000
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 02150000
*                          CHANNEL 2 DEVICES                          * 02160000
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 02170000
*                                                                       02180000
T2401@2  IODEVICE                                                      C02190000
               UNIT=2401,                                              C02200000
               MODEL=6,                                                C02210000
               ADDRESS=(200,4),                                        C02220000
               FEATURE=(9-TRACK,DUALDENS)                               02230000
*                                                                       02240000
T3420@2  IODEVICE                                                      C02250000
               UNIT=3420,                                              C02260000
               MODEL=8,                                                C02270000
               ADDRESS=(210,4),                                        C02280000
               FEATURE=(9-TRACK,OPT1600)                                02290000
*                                                                       02300000
D2314@2  IODEVICE                                                      C02310000
               UNIT=2314,                                              C02320000
               ADDRESS=(220,8)                                          02330000
*                                                                       02340000
D33301@2 IODEVICE                                                      C02350000
               MODEL=1,                                                C02360000
               UNIT=3330,                                              C02370000
               ADDRESS=(230,8)                                          02380000
*                                                                       02390000
D33302@2 IODEVICE                                                      C02400000
               MODEL=11,                                               C02410000
               UNIT=3330,                                              C02420000
               ADDRESS=(238,8)                                          02430000
*                                                                       02440000
D3340@2  IODEVICE                                                      C02450000
               UNIT=3340,                                              C02460000
               ADDRESS=(240,8)                                          02470000
*                                                                       02480000
D3350@2  IODEVICE                                                      C02490000
               UNIT=3350,                                              C02500000
               ADDRESS=(250,8)                                          02510000
*                                                                       02520000
D3375@2  IODEVICE                                                      C02530000
               UNIT=3375,                                              C02540000
               ADDRESS=(270,8)                                          02550000
*                                                                       02560000
D3380@2  IODEVICE                                                      C02570000
               UNIT=3380,                                              C02580000
               ADDRESS=(280,8)                                          02590000
*                                                                       02600000
D3390@2  IODEVICE                                                      C02610000
               UNIT=3390,                                              C02620000
               ADDRESS=(290,8)                                          02630000
         EJECT                                                          02640000
*                                                                       02650000
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 02660000
*                          CHANNEL 3 DEVICES                          * 02670000
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 02680000
*                                                                       02690000
T2401@3  IODEVICE                                                      C02700000
               UNIT=2401,                                              C02710000
               MODEL=6,                                                C02720000
               ADDRESS=(300,4),                                        C02730000
               FEATURE=(9-TRACK,DUALDENS)                               02740000
*                                                                       02750000
T3420@3  IODEVICE                                                      C02760000
               UNIT=3420,                                              C02770000
               MODEL=8,                                                C02780000
               ADDRESS=(310,4),                                        C02790000
               FEATURE=(9-TRACK,OPT1600)                                02800000
*                                                                       02810000
D2314@3  IODEVICE                                                      C02820000
               UNIT=2314,                                              C02830000
               ADDRESS=(320,8)                                          02840000
*                                                                       02850000
D33301@3 IODEVICE                                                      C02860000
               MODEL=1,                                                C02870000
               UNIT=3330,                                              C02880000
               ADDRESS=(330,8)                                          02890000
*                                                                       02900000
D33302@3 IODEVICE                                                      C02910000
               MODEL=11,                                               C02920000
               UNIT=3330,                                              C02930000
               ADDRESS=(338,8)                                          02940000
*                                                                       02950000
D3340@3  IODEVICE                                                      C02960000
               UNIT=3340,                                              C02970000
               ADDRESS=(340,8)                                          02980000
*                                                                       02990000
D3350@3  IODEVICE                                                      C03000000
               UNIT=3350,                                              C03010000
               ADDRESS=(350,8)                                          03020000
*                                                                       03030000
D3375@3  IODEVICE                                                      C03040000
               UNIT=3375,                                              C03050000
               ADDRESS=(370,8)                                          03060000
*                                                                       03070000
D3380@3  IODEVICE                                                      C03080000
               UNIT=3380,                                              C03090000
               ADDRESS=(380,8)                                          03100000
*                                                                       03110000
D3390@3  IODEVICE                                                      C03120000
               UNIT=3390,                                              C03130000
               ADDRESS=(390,8)                                          03140000
         EJECT                                                          03150000
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 03160000
*                          CHANNEL 4 DEVICES                          * 03170000
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 03180000
T3278@4  IODEVICE                                                      C03190000
               UNIT=3277,                                              C03200000
               MODEL=2,                                                C03210000
               ADDRESS=(400,32),                                       C03220000
               FEATURE=(EBKY3277,DOCHAR,KB78KEY,AUDALRM,NUMLOCK)        03230000
         EJECT                                                          03240000
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 03250000
*                          CHANNEL 5 DEVICES                          * 03260000
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 03270000
CTC1@5   IODEVICE                                                      C03280000
               UNIT=CTC,                                               C03290000
               ADDRESS=(500,4)                                          03300000
*                                                                       03310000
CTC2@5   IODEVICE                                                      C03320000
               UNIT=CTC,                                               C03330000
               FEATURE=(370),                                          C03340000
               ADDRESS=(510,4)                                          03350000
         EJECT                                                          03360000
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 03370000
*                          CHANNEL 6 DEVICES                          * 03380000
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 03390000
C37051@6 IODEVICE                                                      C03400000
               UNIT=3705,                                              C03410000
               ADAPTER=CA1,                                            C03420000
               ADDRESS=600                                              03430000
*                                                                       03440000
C37052@6 IODEVICE                                                      C03450000
               UNIT=3705,                                              C03460000
               ADAPTER=CA2,                                            C03470000
               ADDRESS=601                                              03480000
*                                                                       03490000
BSC1@6   IODEVICE                                                      C03500000
               UNIT=BSC1,                                              C03510000
               ADAPTER=BSCA,                                           C03520000
               TCU=2703,                                               C03530000
               ADDRESS=602                                              03540000
*                                                                       03550000
BSC2@6   IODEVICE                                                      C03560000
               UNIT=BSC2,                                              C03570000
               ADAPTER=BSCA,                                           C03580000
               TCU=2703,                                               C03590000
               FEATURE=(AUTOANSR,AUTOCALL),                            C03600000
               ADDRESS=603                                              03610000
*                                                                       03620000
BSC3@6   IODEVICE                                                      C03630000
               UNIT=BSC3,                                              C03640000
               ADAPTER=BSCA,                                           C03650000
               TCU=2703,                                               C03660000
               ADDRESS=604                                              03670000
*                                                                       03680000
T2740C@6  IODEVICE                                                     C03690000
               UNIT=2740C,                                             C03700000
               ADAPTER=IBM1,                                           C03710000
               TCU=2701,                                               C03720000
               FEATURE=(AUTOANSR,CHECKING),                            C03730000
               ADDRESS=605                                              03740000
*                                                                       03750000
T2740X@6  IODEVICE                                                     C03760000
               UNIT=2740X,                                             C03770000
               ADAPTER=IBM1,                                           C03780000
               TCU=2701,                                               C03790000
               FEATURE=(AUTOANSR,CHECKING),                            C03800000
               ADDRESS=606                                              03810000
*                                                                       03820000
T2741P@6  IODEVICE                                                     C03830000
               UNIT=2741P,                                             C03840000
               ADAPTER=IBM1,                                           C03850000
               TCU=2701,                                               C03860000
               FEATURE=(AUTOANSR),                                     C03870000
               ADDRESS=607                                              03880000
*                                                                       03890000
T2741C@6  IODEVICE                                                     C03900000
               UNIT=2741C,                                             C03910000
               ADAPTER=IBM1,                                           C03920000
               TCU=2701,                                               C03930000
               FEATURE=(AUTOANSR),                                     C03940000
               ADDRESS=608                                              03950000
*                                                                       03960000
T1030@6   IODEVICE                                                     C03970000
               UNIT=1030,                                              C03980000
               ADAPTER=IBM2,                                           C03990000
               TCU=2701,                                               C04000000
               ADDRESS=609                                              04010000
*                                                                       04020000
T115A@6   IODEVICE                                                     C04030000
               UNIT=115A,                                              C04040000
               ADAPTER=TELE1,                                          C04050000
               TCU=2701,                                               C04060000
               FEATURE=(AUTOANSR),                                     C04070000
               ADDRESS=60A                                              04080000
*                                                                       04090000
T83B3@6   IODEVICE                                                     C04100000
               UNIT=83B3,                                              C04110000
               ADAPTER=TELE1,                                          C04120000
               TCU=2701,                                               C04130000
               FEATURE=(AUTOANSR),                                     C04140000
               ADDRESS=60B                                              04150000
*                                                                       04160000
T2265@6   IODEVICE                                                     C04170000
               UNIT=2265,                                              C04180000
               ADAPTER=IBM3,                                           C04190000
               TCU=2701,                                               C04200000
               FEATURE=(AUTOANSR),                                     C04210000
               ADDRESS=60C                                              04220000
*                                                                       04230000
TWX@6    IODEVICE                                                      C04240000
               UNIT=TWX,                                               C04250000
               ADAPTER=TELE2,                                          C04260000
               TCU=2703,                                               C04270000
               FEATURE=(AUTOANSR),                                     C04280000
               ADDRESS=(60D,4)                                          04290000
*                                                                       04300000
WTTA@6   IODEVICE                                                      C04310000
               UNIT=WTTA,                                              C04320000
               ADAPTER=TELEW,                                          C04330000
               TCU=2703,                                               C04340000
               FEATURE=(AUTOANSR),                                     C04350000
               ADDRESS=(611,4)                                          04360000
         EJECT                                                          04370000
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 04380000
*                      SYMBOLIC DEVICE NAMES                          * 04390000
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 04400000
SYSRDR   UNITNAME                                                      C04410000
               NAME=SYSRDR,                                            C04420000
               UNIT=(00A)                                               04430000
*                                                                       04440000
SYSDA    UNITNAME                                                      C04450000
               NAME=SYSDA,                                             C04460000
               UNIT=((130,8),(138,8),(140,8),(150,8),                  C04470000
               (170,8),(180,8),(190,8))                                 04480000
*                                                                       04490000
SYSDA    UNITNAME                                                      C04500000
               NAME=SYSDA,                                             C04510000
               UNIT=((230,8),(238,8),(240,8),(250,8),                  C04520000
               (270,8),(280,8),(290,8))                                 04530000
*                                                                       04540000
SYSDA    UNITNAME                                                      C04550000
               NAME=SYSDA,                                             C04560000
               UNIT=((330,8),(338,8),(340,8),(350,8),                  C04570000
               (370,8),(380,8),(390,8))                                 04580000
*                                                                       04590000
SORTDA   UNITNAME                                                      C04600000
               NAME=SORTDA,                                            C04610000
               UNIT=((120,8),(220,8),(320,8))                           04620000
*                                                                       04630000
SYSALLDA UNITNAME                                                      C04640000
               NAME=SYSALLDA,                                          C04650000
               UNIT=((120,8),(220,8),(320,8))                           04660000
*                                                                       04670000
SYSALLDA UNITNAME                                                      C04680000
               NAME=SYSALLDA,                                          C04690000
               UNIT=((130,8),(138,8),(140,8),(150,8),                  C04700000
               (170,8),(180,8),(190,8))                                 04710000
*                                                                       04720000
SYSALLDA UNITNAME                                                      C04730000
               NAME=SYSALLDA,                                          C04740000
               UNIT=((230,8),(238,8),(240,8),(250,8),                  C04750000
               (270,8),(280,8),(290,8))                                 04760000
*                                                                       04770000
SYSALLDA UNITNAME                                                      C04780000
               NAME=SYSALLDA,                                          C04790000
               UNIT=((330,8),(338,8),(340,8),(350,8),                  C04800000
               (370,8),(380,8),(390,8))                                 04810000
*                                                                       04820000
TAPE     UNITNAME                                                      C04830000
               NAME=TAPE,                                              C04840000
               UNIT=((100,4),(110,4),(200,4),(210,4),(300,4),(310,4))   04850000
*                                                                       04860000
SYSSQ    UNITNAME                                                      C04870000
               NAME=SYSSQ,                                             C04880000
               UNIT=((100,4),(110,4),(200,4),(210,4),(300,4),(310,4),  C04890000
               (130,8),(138,8),(140,8),(150,8),                        C04900000
               (170,8),(180,8),(190,8),                                C04910000
               (230,8),(238,8),(240,8),(250,8),                        C04920000
               (270,8),(280,8),(290,8),                                C04930000
               (330,8),(338,8),(340,8),(350,8),                        C04940000
               (370,8),(380,8),(390,8))                                 04950000
*                                                                       04960000
T2401    UNITNAME                                                      C04970000
               NAME=T2401,                                             C04980000
               UNIT=((100,4),(200,4),(300,4))                           04990000
*                                                                       05000000
T3420    UNITNAME                                                      C05010000
               NAME=T3420,                                             C05020000
               UNIT=((110,4),(210,4),(310,4))                           05030000
         EJECT                                                          05040000
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 05050000
*                         VIRTUAL I/O DEVICES                         * 05060000
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 05070000
* THE DEVICES SPECIFIED FOR THE VIO UNITNAME ARE 3350.  IF VIO IS USED  05080000
* THE EMULATED DEVICE WILL TAKE ON THE CHARACTERISTICS OF A 3350.       05090000
*                                                                       05100000
VIO      UNITNAME                                                      C05110000
               NAME=VIO,                                               C05120000
               VIO=YES,                                                C05130000
               UNIT=((150,8),(250,8),(350,8))                           05140000
         EJECT                                                          05150000
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 05160000
*                       CONTROL PROGRAM OPTIONS                       * 05170000
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 05180000
*                                                                       05190000
CTLPG    CTRLPROG ASCII=INCLUDE,     ASCII TRANSLATE ROUTINE           C05200000
               OPTIONS=(RER,         REDUCED ERROR RECOVERY            C05210000
               DEVSTAT,              OFFLINE NOT READY DEVICES AT IPL  C05220000
               BLDL),                BLDL IN FIXED STORAGE             C05240000
               SQA=5,                # 64K ADDITIONAL SQA BLOCKS       C05250000
               REAL=128,             # 1K V=R BLOCKS                   C05260000
               STORAGE=0,            DETERMINE MAX REAL DYNAMICALLY    C05270000
               WARN=0,               IGNORE POWER WARN FEATURE         C05280000
               ACRCODE=YES,          ALTERNATE PROCESSOR RECOVERY      C05290000
               APFLIB=(SYS1.VTAMLIB,MVSRES, VTAM REQUIRES              C05300000
               SYS1.INDMAC,MVSRES),         IND=YES REQUIRES           C05310000
               CSA=3072,             # 1K BLOCKS CSA                   C05320000
               VRREGN=64,            DEFAULT V=R REGION                C05330000
               TZ=(E,1)              ONE HOUR EAST OF GMT               05340000
         EJECT                                                          05350000
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 05360000
*                     JOB SCHEDULER OPTIONS                           * 05370000
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 05380000
*                                                                       05390000
SCHDL    SCHEDULR BCLMT=100,              BROADCAST NOTICE LIMIT       C05400000
               HARDCPY=(015,ALL,CMDS),    RECORD EVERYTHING ON HC LOG  C05410000
               PRISUB=JES2,               JES2 SUBSYSTEM               C05420000
               DEVPREF=(3350,3380,3330-1, DEVICE ALLOCATION PREFERENCE C05430000
               3330,3390,3340)                                          05440000
         EJECT                                                          05450000
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 05460000
*                           TSO OPTIONS                               * 05470000
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 05480000
*                                                                       05490000
TSOOPTS  TSO CMDS=YES,LOGLINE=4,LOGTIME=50                              05500000
         EJECT                                                          05510000
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 05520000
*                      OPTIONAL ACCESS METHODS                        * 05530000
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 05540000
*                                                                       05550000
OPTAM    DATAMGT                                                       C05560000
               ACSMETH=(BTAM,     BASIC TELECOMMUNICATIONS             C05570000
               ISAM,              INDEXED SEQUENTIAL                   C05580000
               TCAM,              TELECOMMUNICATIONS                   C05590000
               VTAM,              VIRTUAL TELECOMMUNCATIONS            C05600000
               GAM),              GRAPHICS                             C05610000
               IND=YES,           3270 SUPPORT                         C05620000
               TABLE=ALL,         ALL CHARACTER TABLES FOR 3800        C05630000
               UCSDFLT=ALL        USE DEFAULT UNIV CHAR SET             05640000
         EJECT                                                          05650000
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 05660000
*                         SYSTEM DATASETS                             * 05670000
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 05680000
*                                                                       05690000
BRODCAST DATASET BRODCAST,VOL=(MVSRES,3350),SPACE=(CYL,(1))             05700000
CMDLIB   DATASET CMDLIB,VOL=(MVSRES,3350),SPACE=(CYL,(3,1,71))          05710000
DCMLIB   DATASET DCMLIB,VOL=(MVSRES,3350),SPACE=(CYL,(1,,35))           05720000
DUMP00   DATASET DUMP00,VOL=(MVSRES,3350),SPACE=(CYL,(30))              05730000
DUMP01   DATASET DUMP01,VOL=(MVSRES,3350),SPACE=(CYL,(30))              05740000
DUMP02   DATASET DUMP02,VOL=(MVSRES,3350),SPACE=(CYL,(30))              05750000
HELP     DATASET HELP,VOL=(MVSRES,3350),SPACE=(CYL,(3,1,71))            05760000
IMAGE    DATASET IMAGELIB,VOL=(MVSRES,3350),SPACE=(CYL,(1,,35))         05770000
INDMAC   DATASET INDMAC,VOL=(MVSRES,3350),SPACE=(CYL,(3,1,71))          05780000
LINKLIB  DATASET LINKLIB,VOL=(MVSRES,3350),SPACE=(CYL,(20,1,323))       05790000
LPALIB   DATASET LPALIB,VOL=(MVSRES,3350),SPACE=(CYL,(20,1,360)),      C05800000
               PDS=SYS2.LOCAL.LPALIB,                                  C05810000
               MEMBERS=(IGC0024{,        SVC 240                       C05820000
               IGC0024A,                 SVC 241                       C05830000
               IGC0024B,                 SVC 242                       C05840000
               IGC0024C,                 SVC 243                       C05850000
               IGC0024D,                 SVC 244                       C05860000
               IGC0024E,                 SVC 245                       C05870000
               IGC0024F,                 SVC 246                       C05880000
               IGC0024G,                 SVC 247                       C05890000
               IGC0024H,                 SVC 248                       C05900000
               IGC0024I,                 SVC 249                       C05910000
               IGC0025{,                 SVC 250                       C05920000
               IGC0025A,                 SVC 251                       C05930000
               IGC0025B,                 SVC 252                       C05940000
               IGC0025C,                 SVC 253                       C05950000
               IGC0025D,                 SVC 254                       C05960000
               IGC0025E)                 SVC 255                        05970000
MACLIB   DATASET MACLIB,VOL=(MVSRES,3350),SPACE=(CYL,(30,1,107))        05980000
MANX     DATASET MANX,VOL=(MVSRES,3350),SPACE=(CYL,(6))                 05990000
MANY     DATASET MANY,VOL=(MVSRES,3350),SPACE=(CYL,(6))                 06000000
NUCLEUS  DATASET NUCLEUS,VOL=(MVSRES,3350),SPACE=(CYL,(10,,20))         06010000
PAGE01   DATASET PAGEDSN=SYS1.PAGELPA,                                 C06020000
               VOL=(PAGE00,3350),SPACE=(CYL,(185))                      06030000
PAGE02   DATASET PAGEDSN=SYS1.PAGECSA,                                 C06040000
               VOL=(PAGE00,3350),SPACE=(CYL,(185))                      06050000
PAGE03   DATASET PAGEDSN=SYS1.PAGEL00,                                 C06060000
               VOL=(PAGE00,3350),SPACE=(CYL,(184))                      06070000
STGINDX  DATASET STGINDEX,VOL=(MVSRES,3350),SPACE=(CYL,(2))             06080000
PARMLIB  DATASET PARMLIB,VOL=(MVSRES,3350),SPACE=(CYL,(8,,40))          06090000
PROCLIB  DATASET PROCLIB,VOL=(MVSRES,3350),SPACE=(CYL,(6,1,71))         06100000
SAMPLIB  DATASET SAMPLIB,VOL=(MVSRES,3350),SPACE=(CYL,(10,1,20))        06110000
SVCLIB   DATASET SVCLIB,VOL=(MVSRES,3350),SPACE=(CYL,(2,1,35))          06120000
TCAMMAC  DATASET TCOMMAC,VOL=(MVSRES,3350),SPACE=(CYL,(3,1,35))         06130000
TELCMLB  DATASET TELCMLIB,VOL=(MVSRES,3350),SPACE=(CYL,(4,1,71))        06140000
UADS     DATASET UADS,VOL=(MVSRES,3350),SPACE=(CYL,(1,1,35))            06150000
VSCATLG  DATASET VSCATLG,NAME=SYS1.VSAM.MASTER.CATALOG                  06160000
VTAMLB   DATASET VTAMLIB,VOL=(MVSRES,3350),SPACE=(CYL,(4,1,35))         06170000
         EJECT                                                          06180000
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 06190000
*                          USER SVCS                                  * 06200000
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 06210000
*                                                                       06220000
*                  + REQUIRED - SPECIFIES USER SVC AS A DECIMAL NUMBER; 06230000
*                  | MUST BE UNIQUE AND WITHIN THE RANGE 200-255.       06240000
*                  |                                                    06250000
*                  |   + REQUIRED - SPECIFIES SVC TYPE AS 1, 2, 3, 4,   06260000
*                  |   | 5, OR 6.                                       06270000
*                  |   |                                                06280000
*                  |   |  + OPTIONAL - SPECIFIES VALUE(S) TO INDICATE   06290000
*                  |   |  | WHICH LOCKS TO OBTAIN BEFORE ENTRY TO SVC;  06300000
*                  |   |  | L1=LOCAL, L2=CMS, L3=SRM, L4=SALLOC9,       06310000
*                  |   |  | L5=DISPATCHER; INVALID FOR TYPE 6 SVC.      06320000
*                  |   |  |                                             06330000
*                  |   |  |  + OPTIONAL - CODE FC01 RESTRICTS USE OF    06340000
*                  |   |  |  | THE SVC TO AUTHORIZED STEPS; IF NOT      06350000
*                  |   |  |  | SPECIFIED, FC00 IS ASSUMED MAKING SVC    06360000
*                  |   |  |  | UNRESTRICTED.                            06370000
*                  |   |  |  |                                          06380000
*                  |   |  |  |    + OPTIONAL - SPECIFIES THAT SVC RUNS  06390000
*                  |   |  |  |    | NON-PREMPTIBLE FOR I/O INTERRUPTS.  06400000
*                  |   |  |  |    |                                     06410000
*                  V   V  V  V    V                                     06420000
*     SVCTABLE SVC-255-T1-L1-FC00-NP                                    06430000
         SVCTABLE                                                      C06440000
               SVC-255-T3-L1-FC00,     OPEN                            C06450000
               SVC-254-T4-FC00,        OPEN                            C06460000
               SVC-253-T3-FC00,        OPEN                            C06470000
               SVC-252-T4-FC00,        OPEN                            C06480000
               SVC-251-T3-FC00,        OPEN                            C06490000
               SVC-250-T4-FC00,        OPEN                            C06500000
               SVC-249-T3-FC00,        OPEN                            C06510000
               SVC-248-T4-FC00,        FSE                             C06520000
               SVC-247-T3-FC00,        OPEN                            C06530000
               SVC-246-T4-FC00,        OPEN                            C06540000
               SVC-245-T3-FC00,        OPEN                            C06550000
               SVC-244-T4-FC00,        AUTHORIZATION                   C06560000
               SVC-243-T3-FC00,        OPEN                            C06570000
               SVC-242-T4-FC00,        OPEN                            C06580000
               SVC-241-T3-FC00,        OPEN                            C06590000
               SVC-240-T4-FC00         OPEN                             06600000
         EJECT                                                          06610000
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 06620000
*                           GENERATE                                  * 06630000
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 06640000
*                                                                       06650000
         GENERATE GENTYPE=ALL,        FULL SYSGEN                      C06660000
               INDEX=SYS1,            HIGH LEVEL QUALIFIER FOR DS      C06670000
               JCLASS=A,              JOB CLASS                        C06680000
               OBJPDS=SYS1.OBJPDS,    OBJECT DATASETS                  C06690000
               OCLASS=A,              OUTPUT CLASS                     C06700000
               RESVOL=(MVSRES,3350)   SYSRES VOLUME                     06710000
         END                                                            06720000
/*                                                                      06730000
//*                                                                     06740000
//IEBGENER EXEC PGM=IEBGENER,COND=(0,NE,ASMBLR)                         06750000
//*                                                                     06760000
//* ***************************************************************** * 06770000
//* IF ASMBLR RC=0000, SUBMIT CONTINUATION JOB TO INTERNAL READER.    * 06780000
//* ***************************************************************** * 06790000
//*                                                                     06800000
//SYSPRINT DD  DUMMY                                                    06810000
//SYSIN    DD  DUMMY                                                    06820000
//SYSUT1   DD  DATA,DLM='><'                                            06830000
//SYSGEN01 JOB (SYSGEN),'STAGE2 DECK TO TAPE',                          06840000
//             CLASS=A,MSGCLASS=A,MSGLEVEL=(1,1)                        06850000
/*JOBPARM  CARDS=15000                                                  06860000
//*                                                                     06870000
//* ***************************************************************** * 06880000
//* THIS JOB CONTINUATION SUBMITTED BY SUCCESSFUL SYSGEN01            * 06890000
//* ***************************************************************** * 06900000
//*                                                                     06910000
//PUNCH   EXEC PGM=IEBGENER                                             06920000
//*                                                                     06930000
//* ***************************************************************** * 06940000
//* COPY STAGE 1 OUTPUT DECK TO TAPE                                  * 06950000
//* ***************************************************************** * 06960000
//*                                                                     06970000
//SYSPRINT DD  DUMMY                                                    06980000
//SYSIN    DD  DUMMY                                                    06990000
//SYSUT1   DD  DISP=SHR,DSN=SYS1.STAGE1.OUTPUT,UNIT=3350,VOL=SER=WORK01 07000000
//SYSUT2   DD  UNIT=(TAPE,,DEFER),DSN=STAGE1.OUTPUT,VOL=SER=STAGE1,     07010000
//             LABEL=(1,SL),DISP=(,KEEP)                                07020000
//*        END OF SUBMITTED SYSGEN01                                    07030000
><                                                                      07040000
//SYSUT2   DD  SYSOUT=(A,INTRDR)                                        07050000
//*         END OF PRIMARY SYSGEN01                                     07060000
