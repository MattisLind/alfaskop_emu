# SDLC bridge

This is an attemmpt to interface a Informer 213, a portable 3178 compatible terminal with integrated 3274 comatible cluster controller, to the Hercules mainframe emulator.
This terminal needs a SDLC compatible interface. This project also discusses how to create the relevnat configuration in the MVS / VTAM environment
to achieve this and what changed is needed to the comm3705 module in Hercules.

![Informer 213](https://i.imgur.com/M9zcy7E.png)

## VTAM configuration
I use the  TK4- MVS dirstribuition as the basis for all experimentation. But the existing configuration of VTAM in TK4- is more complex than necessary, possibly to include a number of features avaiable in the comm3705 code of Hercules. First it defines remote 3705 nodes. Something that is not really necessary and secondly it also add a Switched SNA Major Node configuration. To have an as simple VTAM configuration I have been trying to create a config with one single channel attached local 3705 communictation controller and one single terminal attached (through a 3274 or similar).

The configuration is located in the SYS1.VTAMLST(N07) member.

```
PCCU1    PCCU  MAXDATA=3780,                                           +                 1
               CUADDR=660,                                             +                16
               AUTODMP=NO,                                             +                16
               AUTOIPL=NO,                                             +                16
               AUTOSYN=YES,                                            +                16
               INITEST=NO                                                               16
BUILD1   BUILD ANS=YES,                                                +                 1
               CHANTYP=1,                                              +                16
               LOADLIB=VTAMLIB,                                        +                16
               MAXSUBA=31,                                             +                16
               MODEL=3705,                                             +                16
               NEWNAME=N07,                                            +                16
               OLT=NO,                                                 +                16
               SUBAREA=7,                                              +                16
               TYPGEN=NCP                                                               16
H1       HOST BFRPAD=28,                                               +                 1
               MAXBFRU=2,                                              +                16
               STATMOD=YES,                                            +                16
               UNITSZ=4016                                                              16
N07G1    GROUP DIAL=NO,                                                +                 1
               ISTATUS=ACTIVE,                                         +                16
               LNCTL=SDLC,                                             +                16
               SSCPFM=USS3270                                                           16
N07L2    LINE                                                                            1
N07P2    PU    ISTATUS=ACTIVE,                                         +                 1
               MAXDATA=3780,                                           +                16
               DISCNT=YES,                                             +                16
               PUTYPE=2,                                               +                16
               MAXLU=16,                                               +                16
               IDBLK=017,                                              +                16
               IDNUM=00017,                                            +                16
               ADDR=C1                                                                  16
N07L21   LU    VPACING=0,                                              +                 1
               BATCH=NO,                                               +                16
               SSCPFM=USS3270,                                         +                16
               LOCADDR=3,BUFLIM=2,USSTAB=BSPUDT01,                     +                16
               ISTATUS=ACTIVE,LUTYPE=2,                                +                16
               MODETAB=BSPLMT02                                                         16
         GENEND                                                                         10
         
```
It defines a 3705, attached to channel address 660. There is one line N07L2, with a PU (Physical Unit) called N07P2 (which is the 3274 itself) and one LU (Logical Unit) called N07L21. The names chosen is supposed to match existing configuration in SYS1.VTAMSRC(N07R). This file is read when VTAM is started and compiled into a binary file. This file is then placed in the SYS1.VTAMOBJ as member N07. It is very important to remove these binary caches when changing the text file.

```
         MACRO                                                                          10
&LABEL   RRTTAB &KEYLN=255,&UNITN=1,&BUFPD=28,&NODEL=0,&SUBAREA=0                        1
         LCLA  &AN(16)                                                                  10
&AN(1)   SETA  32768                                                                     1
&AN(2)   SETA  16384                                                                     1
&AN(3)   SETA  8192                                                                      1
&AN(4)   SETA  4096                                                                      1
&AN(5)   SETA  2048                                                                      1
&AN(6)   SETA  1024                                                                      1
&AN(7)   SETA  512                                                                       1
&AN(8)   SETA  256                                                                       1
&AN(9)   SETA  128                                                                       1
&AN(10)  SETA  64                                                                        1
&AN(11)  SETA  32                                                                        1
&AN(12)  SETA  16                                                                        1
&AN(13)  SETA  8                                                                         1
&AN(14)  SETA  4                                                                         1
&AN(15)  SETA  2                                                                         1
&AN(16)  SETA  1                                                                         1
         GBLA  &PNETADR                                                                 10
&PNETADR SETA  &AN(&NODEL)*&SUBAREA                                                      1
         GBLA  &RSID                                                                    10
&RSID    SETA  0                                                                         1
RRTHDRS  DS    0H                                                                        1
         DC    AL2(RRTHDRE-RRTHDRS) RRTHDRLN  HEADER SIZE                               10
         DC    AL2(&KEYLN)      +2 RRTKEYLN (TSOMCP UNITSZ?)                            10
         DC    AL1(&UNITN)      +4 RRTUNITN (DCBUNTCT)                                  10
         DC    AL1(0)           +5 RRTUNITR                                             10
         DC    AL1(0)           +6 RRTKEYLR                                             10
         DC    AL1(&BUFPD)      +7 RRTBUFPD                                             10
         DC    AL1(0)           +8 RRTXTPD                                              10
         DC    AL1(&NODEL)      +9 RRTNODEL #BITS IN SUBAREA                            10
RRTHDRE  DS    0H                                                                        1
         MEND                                                                           10
.*********************************************************************                   1
         MACRO                                                                          10
&TERMNM  RRTENT &RMTP1=0,&RMTP2=0                                                        1
         GBLA  &PNETADR                                                                 10
         GBLA  &RSID                                                                    10
         DC    CL8'&TERMNM'                                                             10
         DC    AL2(&PNETADR+&RSID)                                                      10
         DC    XL1'&RMTP1'                                                              10
         DC    XL1'&RMTP2'                                                              10
&RSID    SETA  &RSID+1                                                                   1
.* IS RSID=1 SUPPOSED TO BE 'RESERVED' ?                                                 1
         MEND                                                                           10
.*********************************************************************                   1
         MACRO                                                                          10
&LABEL   RRTEND                                                                          1
&LABEL   DC     X'FF'                                                                    1
         DC     XL11'0'                                                                 10
         MEND                                                                           10
.*********************************************************************                   1
N07R     START                                                                           1
         PRINT GEN                                                                      10
         RRTTAB KEYLN=252,UNITN=15,BUFPD=28,NODEL=5,SUBAREA=7                           10
N07      RRTENT RMTP1=0,RMTP2=20                                                         1
N07L1    RRTENT RMTP1=B8,RMTP2=20                                                        1
N07L2    RRTENT RMTP1=B8,RMTP2=20                                                        1
N07L3    RRTENT RMTP1=B8,RMTP2=20                                                        1
N07P1    RRTENT RMTP1=78,RMTP2=20                                                        1
N07L11   RRTENT RMTP1=38,RMTP2=20                                                        1
N07L12   RRTENT RMTP1=38,RMTP2=20                                                        1
N07L13   RRTENT RMTP1=38,RMTP2=20                                                        1
N07P2    RRTENT RMTP1=78,RMTP2=20                                                        1
N07L21   RRTENT RMTP1=38,RMTP2=20                                                        1
N07P3    RRTENT RMTP1=78,RMTP2=20                                                        1
N07L31   RRTENT RMTP1=38,RMTP2=20                                                        1
N07LN08  RRTENT RMTP1=B8,RMTP2=20                                                        1
N07PN08  RRTENT RMTP1=78,RMTP2=20                                                        1
$LUPOOL  RRTENT RMTP1=38,RMTP2=20                                                        1
         RRTEND                                                                         10
         END   N07R  

```
This file is actually a IBM S/370 Macro assembly program. As can been seen there are the definitions for N07L2 and N07P2 and N07L21 already there. So it was not necessary to assembler and link this file, which otherwise would have been needed.

During startup I now see messages:

```
11:13:19 10.13.19 STC   98  IST097I  VARY     ACCEPTED
11:13:19 10.13.19 STC   98  IST116I  MEMBER T3278S11 NOT FOUND ON VTAM DEFINITION LIBRARY
11:13:19 10.13.19 STC   98  IST061I  VARY FAILED- ID= T3278S11 UNKNOWN TO VTAM
```

This due to the member SYS1.PARMLIB(SNAACT) is not correct. It has to have a VARY command the activate the terminal, N07L21.
```
***********************************************************************                  1
*                                                                     *                  1
* Name: SYS1.PARMLIB(SNAACT)                                          *                  1
*                                                                     *                  1
* Desc: Set VTAM SNA LUs to logon to the SNA network solicitor        *                  1
*                                                                     *                  1
***********************************************************************                  1
PARM NOECHO                                                                              1
PARM NOREPLYU                                                                            1
CMD V NET,ACT,ID=N07L21,LOGON=SNASOL,LOGMODE=MHP3278E
```

This should in theory run the SNA solicitor on terminal N07L21 in 3278 mode defined by MHP3278E. But it doesn't work. Apparently some extra step is needed to activate this. Need further investigation.

But the same command can be given on the console and then the terminal will be activated and it will be possible to login.
```
V NET,ACT,ID=N07L21,LOGON=SNASOL,LOGMODE=MHP3278E
```
Unfortunately as soon as the connection from the TN3270 client is down VTAM will detect some kind of fault and the same command need to be re-issued to be able to login. This also need further investigation.

## SDLC

Next step would be to understand a bit more on how to communicate with the Informer 213. It does SDLC over regular V.24/ V.28 line. The intention is to code a small STM32F103 bluepill to do SDLC encoding / decoding.

## Links

### SNA

* [SNA Introduction to Sessions Between Logical Units](http://bitsavers.trailing-edge.com/pdf/ibm/sna/GC20-1869-2_SNA_Introduction_to_Sessions_Between_Logical_Units_Dec79.pdf)
* [Systems Network Architecture Reference Summary](http://www.bitsavers.org/pdf/ibm/sna/GA27-3136-2_Systems_Network_Architecture_Reference_Summary_Oct78.pdf)
* [SNA Technical Overview](http://www.bitsavers.org/pdf/ibm/sna/GC30-3073-1_Systems_Network_Architecture_Technical_Overview_May85.pdf)
### VTAM
* [Introduction to VTAM](http://www.bitsavers.org/pdf/ibm/sna/vtam/GC27-6987-5_Introduction_to_VTAM_Apr76.pdf)
* [VTAM Macro Langauge Reference](http://www.bitsavers.org/pdf/ibm/sna/vtam/GC27-6995-2_VTAM_Macro_Language_Reference_Dec74.pdf)
* [System Programming Library: VTAM](http://www.prycroft6.com.au/misc/download/GC28-0688-2_SPL_VTAM_Level2_Dec77OCR.pdf)
* [VTAM Concepts and Planning](http://bitsavers.informatik.uni-stuttgart.de/pdf/ibm/sna/vtam/GC27-6998-2_VTAM_Concepts_and_Planning_Aug75.pdf)
### SDLC
* [SDLC General Information](http://bitsavers.informatik.uni-stuttgart.de/pdf/ibm/datacomm/GA27-3093-2_SDLC_General_Information_Mar79.pdf)
* [SDLC Concepts](http://bitsavers.informatik.uni-stuttgart.de/pdf/ibm/datacomm/GA27-3093-3_SDLC_Concepts_Jun86.pdf)

### Other
* [Matt Burke's work on DSLw to interconnect SNA / SDLC](https://www.9track.net/hercules/dlsw/)
* [SNA / SDLC quick guide by Clif Anderson](https://www.cliffa1994.com/snasteps.htm)
* [SDLC overview](https://www.euclideanspace.com/coms/protocol/sdlc/index.htm)
* [VTAM/NCP Node Definition Example](http://ps-2.kev009.com/tl/techlib/manuals/adoclib/3270hcon/hconugd/definvta.htm)
* [Course on SNA / VTAM](http://bitsavers.informatik.uni-stuttgart.de/pdf/ibm/sna/Kaptronix_SNA.pdf)
