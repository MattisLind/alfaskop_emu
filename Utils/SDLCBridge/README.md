# SDLC bridge

This is an attemmpt to interface a Informer 213, a portable 3178 compatible terminal with integrated 3274 comatible cluster controller, to the Hercules mainframe emulator.
This terminal needs a SDLC compatible interface. This project also discusses how to create the relevnat configuration in the MVS / VTAM environment
to achieve this and what changed is needed to the comm3705 module in Hercules.

![Informer 213](https://i.imgur.com/M9zcy7E.png)

## VTAM configuration
I use the  TK4- MVS dirstribuition as the basis for all experimentation. But the existing configuration of VTAM in TK4- is more complex than necessary, possibly to include a number of features avaiable in the comm3705 code of Hercules. First it defines remote 3705 nodes. Something that is not really necessary and secondly it also add a Switched SNA Major Node configuration. To have an as simple VTAM configuration I have been trying to create a config with one single channel attached local 3705 communictation controller and one single terminal attached (through a 3274 or similar).

So the steps are:

1. Edit the SYS1.VTAMLST(ATCCON01) member to reflect your config
2. Edit the SYS1.VTAMLST(N07) member for the config of your NCP.
3. Erase all members of SYS1.VTAMOBJ to that they will not interfere. These members will be rebuilt as soon as VTAM starts.
4. Edit the SYS1.VTAMSRC(N07R) so that it matches SYS1.VTAMLST(N07). Make sure you have added a line for printing the assembly listing output.
5. Submit the N07R job for execution. It will create the SYS1.VTAMOBJ(N07R) member in the process when assembling and linking. It also produces interesting output on your prnter. Check it.

### ATCCON01

This is my SYS1.VTAMLST(ATCCON01) 

```
***********************************************************************                  1
*  STARTLIST   T K 4 -                                                *                  1
***********************************************************************                  1
ATSO,                              /* TSO application major node     */X                 1
ASNASOL,                           /* SNA network solicitor          */X                 1
AJRP,                              /* JRP (JES2 remote print)        */X                 1
L3274,                             /* local non-SNA major node       */X                 1
N07                                /* local  3705 NCP subarea  7     */                  1
```
It is possible to name the file something else than N07 of course. But it has to match with the SYS1.VTAMSRC member with an R on it.


### N07
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

### N07R

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
This file is actually a IBM S/370 Macro assembly program. As can been seen there are the definitions for N07L2 and N07P2 and N07L21 already there. 

When the N07R member is assembled and linked module it give you interesting information as the macros in it is expanded which can be useful to have. So run the submit the N07R job but check that a line for outputing the assembly listing is included in the job. Add this line somewhere among the top JCL statments:

```
//ASM.SYSPRINT DD SYSOUT=A                                                               1
```

This will print to the printer which handles class A printouts. An excerpt of the printout would look like this:

```
000000                               54 N07R     START
                                     55          PRINT GEN
                                     56          RRTTAB KEYLN=252,UNITN=15,BUFPD=28,NODEL=5,SUBAREA=7
000000                               57+RRTHDRS  DS    0H
000000 000A                          58+         DC    AL2(RRTHDRE-RRTHDRS) RRTHDRLN  HEADER SIZE
000002 00FC                          59+         DC    AL2(252)         +2 RRTKEYLN (TSOMCP UNITSZ?)
000004 0F                            60+         DC    AL1(15)          +4 RRTUNITN (DCBUNTCT)
000005 00                            61+         DC    AL1(0)           +5 RRTUNITR
000006 00                            62+         DC    AL1(0)           +6 RRTKEYLR
000007 1C                            63+         DC    AL1(28)          +7 RRTBUFPD
000008 00                            64+         DC    AL1(0)           +8 RRTXTPD
000009 05                            65+         DC    AL1(5)           +9 RRTNODEL #BITS IN SUBAREA
00000A                               66+RRTHDRE  DS    0H
                                     67 N07      RRTENT RMTP1=0,RMTP2=20
00000A D5F0F74040404040              68+         DC    CL8'N07'
000012 3800                          69+         DC    AL2(14336+0)
000014 00                            70+         DC    XL1'0'
000015 20                            71+         DC    XL1'20'
                                     72 N07L1    RRTENT RMTP1=B8,RMTP2=20
000016 D5F0F7D3F1404040              73+         DC    CL8'N07L1'
00001E 3801                          74+         DC    AL2(14336+1)
000020 B8                            75+         DC    XL1'B8'
000021 20                            76+         DC    XL1'20'
                                     77 N07L2    RRTENT RMTP1=B8,RMTP2=20
000022 D5F0F7D3F2404040              78+         DC    CL8'N07L2'
00002A 3802                          79+         DC    AL2(14336+2)
00002C B8                            80+         DC    XL1'B8'
00002D 20                            81+         DC    XL1'20'
                                     82 N07L3    RRTENT RMTP1=B8,RMTP2=20
00002E D5F0F7D3F3404040              83+         DC    CL8'N07L3'
000036 3803                          84+         DC    AL2(14336+3)
000038 B8                            85+         DC    XL1'B8'
000039 20                            86+         DC    XL1'20'
                                     87 N07P1    RRTENT RMTP1=78,RMTP2=20
00003A D5F0F7D7F1404040              88+         DC    CL8'N07P1'
000042 3804                          89+         DC    AL2(14336+4)
000044 78                            90+         DC    XL1'78'
000045 20                            91+         DC    XL1'20'
                                     92 N07L11   RRTENT RMTP1=38,RMTP2=20
000046 D5F0F7D3F1F14040              93+         DC    CL8'N07L11'
00004E 3805                          94+         DC    AL2(14336+5)
000050 38                            95+         DC    XL1'38'
000051 20                            96+         DC    XL1'20'
                                     97 N07L12   RRTENT RMTP1=38,RMTP2=20
000052 D5F0F7D3F1F24040              98+         DC    CL8'N07L12'
00005A 3806                          99+         DC    AL2(14336+6)
00005C 38                           100+         DC    XL1'38'
00005D 20                           101+         DC    XL1'20'
                                    102 N07L13   RRTENT RMTP1=38,RMTP2=20
00005E D5F0F7D3F1F34040             103+         DC    CL8'N07L13'
000066 3807                         104+         DC    AL2(14336+7)
000068 38                           105+         DC    XL1'38'
000069 20                           106+         DC    XL1'20'
                                    107 N07P2    RRTENT RMTP1=78,RMTP2=20
00006A D5F0F7D7F2404040             108+         DC    CL8'N07P2'
000072 3808                         109+         DC    AL2(14336+8)
000074 78                           110+         DC    XL1'78'
000075 20                           111+         DC    XL1'20'
                                    112 N07L21   RRTENT RMTP1=38,RMTP2=20
000076 D5F0F7D3F2F14040             113+         DC    CL8'N07L21'
00007E 3809                         114+         DC    AL2(14336+9)
000080 38                           115+         DC    XL1'38'
000081 20                           116+         DC    XL1'20'
                                    117 N07P3    RRTENT RMTP1=78,RMTP2=20
000082 D5F0F7D7F3404040             118+         DC    CL8'N07P3'
00008A 380A                         119+         DC    AL2(14336+10)
00008C 78                           120+         DC    XL1'78'
00008D 20                           121+         DC    XL1'20'
                                    122 N07L31   RRTENT RMTP1=38,RMTP2=20
00008E D5F0F7D3F3F14040             123+         DC    CL8'N07L31'
000096 380B                         124+         DC    AL2(14336+11)
000098 38                           125+         DC    XL1'38'
000099 20                           126+         DC    XL1'20'
                                    127 N07LN08  RRTENT RMTP1=B8,RMTP2=20
00009A D5F0F7D3D5F0F840             128+         DC    CL8'N07LN08'
0000A2 380C                         129+         DC    AL2(14336+12)
0000A4 B8                           130+         DC    XL1'B8'
0000A5 20                           131+         DC    XL1'20'
                                    132 N07PN08  RRTENT RMTP1=78,RMTP2=20
0000A6 D5F0F7D7D5F0F840             133+         DC    CL8'N07PN08'
0000AE 380D                         134+         DC    AL2(14336+13)
0000B0 78                           135+         DC    XL1'78'
0000B1 20                           136+         DC    XL1'20'
                                    137 $LUPOOL  RRTENT RMTP1=38,RMTP2=20
0000B2 5BD3E4D7D6D6D340             138+         DC    CL8'$LUPOOL'
0000BA 380E                         139+         DC    AL2(14336+14)
0000BC 38                           140+         DC    XL1'38'
0000BD 20                           141+         DC    XL1'20'
                                    142          RRTEND
0000BE FF                           143+         DC     X'FF'
0000BF 0000000000000000             144+         DC     XL11'0'
000000                              145          END   N07R
```
This is the RRT table and it show address information for the system.

What to to look for is the information on lines 69, 74, 109 and 114. 
N07 which is the 3705 itself is at subarea 8 address 0.
```
000012 3800                          69+         DC    AL2(14336+0)
```
N07L1 is at subarea 7 address 1.
```
00001E 3801                          74+         DC    AL2(14336+1)
```
N07P2 is at subarea 7 address 8.
```
000072 3808                         109+         DC    AL2(14336+8)
```
N07L21 is at subarea 7 address 9.
```
00007E 3809                         114+         DC    AL2(14336+9)
```
Please note that we have already decided that MAXSUBA=31 which means that 5 bits are used for subarea and the remaining 11 bits is the node address. So for example the address 3808 is in binary 0011 1000 0000 1000 or regrouped as 00111 and 00000001000 which is then 7 and 8, which is the address of the LU.


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

This should in theory run the SNA solicitor on terminal N07L21 in 3278 mode defined by MHP3278E. But it doesn't work. ~~Apparently some extra step is needed to activate this. Need further investigation.~~

It turned out that there were a completely different file that did the job during startup, SYS1.PARMLIB(STARTSTD).
```
***********************************************************************                  1
*                                                                     *                  1
* Name: SYS1.PARMLIB(STARTSTD)                                        *                  1
*                                                                     *                  1
* Desc: Full TK4- startup script                                      *                  1
*                                                                     *                  1
***********************************************************************                  1
PARM NOECHO                                                                              1
PARM NOREPLYU                                                                            1
CMD $CA,ALL                                                                              1
CMD V 480,ONLINE                                                                         1
CMD MN JOBNAMES,T                                                                        1
CMD MN SESS,T                                                                            1
CMD S DYNAMASK                                                                           1
WAIT 2                                                                                   1
CMD S NET                                                                                1
CMD S TP                                                                                 1
CMD S MF1.MF1                                                                            1
CMD $SA,ALL                                                                              1
CMD $TA,I=3600,'$SI1-I4'                                                                 1
CMD $TOSC1,D=J                                                                           1
CMD $TOSC2,D=J                                                                           1
CMD $TOSC3,D=T                                                                           1
CMD $TOSC4,D=T                                                                           1
CMD $SRDR1                                                                               1
CMD $SPRT1                                                                               1
CMD $SPRT2                                                                               1
CMD $SPRT3                                                                               1
CMD $SLINE1                                                                              1
CMD $SLINE2                                                                              1
CMD $SLINE3                                                                              1
CMD $SLINE4                                                                              1
CMD $SPUNCH1                                                                             1
WAIT 2                                                                                   1
CMD F TP,TS=START                                                                        1
WAIT 2                                                                                   1
CMD S SNASOL                                                                             1
CMD S JRP                                                                                1
WAIT 20                                                                                  1
CMD V NET,ACT,ID=N07L21,LOGON=SNASOL,LOGMODE=MHP3278E                                    1
WAIT 5                                                                                   1
CMD F TP,LOAD=T07,T07                                                                    1
WAIT 2                                                                                   1
CMD S INISDSTD                                                                           1
COM SE 'MVS038J MVS 3.8j TK4- system initialization complete',BRDCST                     1

```
Changing the ID to N07201 solved the problem. Also removed the startup for nodes that were not present.

But the same command can be given on the console and then the terminal will be activated and it will be possible to login.
```
V NET,ACT,ID=N07L21,LOGON=SNASOL,LOGMODE=MHP3278E
```
Unfortunately as soon as the connection from the TN3270 client is down VTAM will detect some kind of fault and the same command need to be re-issued to be able to login. ~~This also need further investigation.~~

This patch from Max Parke resolves the problem with disconnecting the TN3270.

> Here are two suggestions, should clean up some of the crashes and other weird stuff ...

> At the top of make_sna_requests4(), place a return statement (right after the local variables defs).  Do the same in 
> make_sna_requests5().   The '4' function is really not useful in the non-dial case.  Likewise '5' sends INOP which seems to
> cause the error messages at logoff time...

> In an ideal world the sending of INOP would not be done during a "normal" disconnect, but should still be there in the case
> where it was originally intended - not sure offhand what the proper conditions were...
```
diff --git a/comm3705.c b/comm3705.c
index 7b9450e..60a3921 100644
--- a/comm3705.c
+++ b/comm3705.c
@@ -1745,6 +1745,7 @@ static void make_sna_requests4 (COMMADPT *ca, int flag, BYTE pu_type) {
     int     ru_size;
     U32     stids;
     void    *eleptr;
+    return;
     eleptr = get_bufpool(&ca->freeq);
     if (!eleptr)  {
         WRMSG(HHC01020, "E", SSID_TO_LCSS(ca->dev->ssid), ca->dev->devnum, "SNA request4");
@@ -1813,6 +1814,7 @@ static void make_sna_requests5 (COMMADPT *ca) {
     BYTE    *ru_ptr;
     int     ru_size;
     void    *eleptr;
+    return;
     eleptr = get_bufpool(&ca->freeq);
     if (!eleptr)  {
         WRMSG(HHC01020, "E", SSID_TO_LCSS(ca->dev->ssid), ca->dev->devnum, "SNA request5");
```




## SDLC

Next step would be to understand a bit more on how to communicate with the Informer 213. It does SDLC over regular V.24/ V.28 line. The intention is to code a small STM32F103 bluepill to do SDLC encoding / decoding.

I had an exchange of with an [expert in SAN / SDLC / VTAM](http://www.lightlink.com/mhp/3705/) which gave these comments:

> As for running SNA over SDLC, I don't think there's anything special - I believe the SNA data is sent in SDLC "I" frames.  I'd expect
> that a SNRM followed by an ACTPU should get some sort of response out of the controller.  In writing the SDLC driver the only tricky
> part I remember would be the proper setting of the P/F (poll/final) bit.  I don't remember the specific rules.  The exception to the
> "everything is an I frame" rule would apply in the case of XID, which was used in the switched (dialup) case.  The IDNUM/IDBLK fields 
> in the SDLC XID were used by NCP to generate a request-contact (REQCONT) request which was part of the VTAM dial protocol.

> if you do send a SNRM make sure you get a UA in reply.  Then exchange a few RR (receiver ready) SDLC frames prior to attempting the ACTPU...

> This starts to get at the heart of what the "boundary function" really means.  In the real world the NCP would not send the SNRM until
> first having received the CONTACT request from VTAM.  When UA is received the link immediately enters normal response mode and normal
> polling commences.  Meanwhile the receipt of the UA also causes NCP to send the CONTACTED request to VTAM which in turn eventually
> sends ACTPU.  It is probably not an error to send the ACTPU right on the heels of the UA but that might tempt the timing bugs to make
> an appearance   [in comm3705 at present, the CONTACTED is sent much sooner].

> Another function not done in comm3705.c but might be added would be proper modem lead control (for DTR and DSR) conditioned on the 
> ACTLINK and DACTLINK functions...

So the basic idea is to do some rudimentary testing using the STM32 sending a SNRM message, waiting for the UA frame acknowledgment and thensend an ACTPU to activate the PU inside the terminal (i.e. the 3274).

## SNA message trace
This is a trace from MVS startup to shutdown including a logon and then issuing a shutdown command from the terminal.
```
21:54:32 HHC01062D 0:0660 COMM: WR: 1F00 3800 0800 0001 000C 6B8000 110255 ACTPU
21:54:32 HHC01062D 0:0660 COMM: RD: 1F00 0800 3800 0001 000D EB8000 1102D5 ACTPU
21:54:32 HHC01062D 0:0660 COMM: WR: 1F00 3800 0800 0002 0004 6B8000 A0     SDT
21:54:32 HHC01062D 0:0660 COMM: RD: 1F00 0800 3800 0002 0004 EB8000 A0     SDT
21:54:32 HHC01062D 0:0660 COMM: WR: 1E00 3800 0800 0001 001D 0B8000 010211 SETCV[01]
21:54:32 HHC01062D 0:0660 COMM: RD: 1E00 0800 3800 0001 0006 8B8000 010211 SETCV
21:54:32 HHC01062D 0:0660 COMM: WR: 1E00 3800 0800 0002 000B 0B8000 010211 SETCV[05]
21:54:32 HHC01062D 0:0660 COMM: RD: 1E00 0800 3800 0002 0006 8B8000 010211 SETCV
21:54:32 HHC01062D 0:0660 COMM: WR: 1E00 3800 0800 0003 0008 0B8000 01020A ACTLINK
21:54:32 HHC01062D 0:0660 COMM: RD: 1E00 0800 3800 0003 0006 8B8000 01020A ACTLINK
21:54:32 HHC01062D 0:0660 COMM: WR: 1E00 3800 0800 0004 000B 0B8000 010211 SETCV[05]
21:54:32 HHC01062D 0:0660 COMM: RD: 1E00 0800 3800 0004 0006 8B8000 010211 SETCV
21:54:32 HHC01062D 0:0660 COMM: WR: 1E00 3800 0800 0005 0008 0B8000 010201 CONTACT
21:54:32 HHC01062D 0:0660 COMM: RD: 1E00 0800 3800 0005 0006 8B8000 010201 CONTACT
21:54:32 HHC01062D 0:0660 COMM: RD: 1C00 0800 3800 0001 0009 0B0000 010280 CONTACTED
21:54:32 HHC01062D 0:0660 COMM: WR: 1F00 3808 0800 0001 000C 6B8000 110101 ACTPU
21:54:32 HHC01062D 0:0660 COMM: RD: 1F00 0800 3808 0001 0005 EB8000 1101   ACTPU
21:55:37 HHC01062D 0:0660 COMM: WR: 1F00 3809 0800 0001 0006 6B8000 0D0101 ACTLU
21:55:37 HHC01062D 0:0660 COMM: RD: 1F00 0800 3809 0001 0004 EB8000 0D     ACTLU
21:55:37 HHC01062D 0:0660 COMM: WR: 1F00 3809 0801 0001 0026 6B8000 310103 BIND
21:55:37 HHC01062D 0:0660 COMM: RD: 1F00 0801 3809 0001 0004 EB8000 31     BIND
21:55:37 HHC01062D 0:0660 COMM: WR: 1F00 3809 0801 0002 0004 6B8000 A0     SDT
21:55:37 HHC01062D 0:0660 COMM: RD: 1F00 0801 3809 0002 0004 EB8000 A0     SDT
21:55:37 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 0001 0009 0390A0 F30005 
21:55:48 HHC01062D 0:0660 COMM: RD: 1C00 0800 3800 0002 000E 0B0000 010284 REQCONT
21:55:52 HHC01062D 0:0660 COMM: RD: 1C00 0801 3809 0001 0004 039020 6D     
21:55:52 HHC01062D 0:0660 COMM: WR: 1C00 3809 0801 0000 0007 979000 000000 
21:55:52 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 0002 009B 039040 7EC311 
21:55:53 HHC01062D 0:0660 COMM: WR: 1F00 3809 0801 0003 0004 6B8000 A1     
21:55:53 HHC01062D 0:0660 COMM: RD: 1F00 0801 3809 0003 0004 EB8000 A1     
21:55:53 HHC01062D 0:0660 COMM: WR: 1F00 3809 0801 0001 0005 6B8000 3202   UNBIND
21:55:53 HHC01062D 0:0660 COMM: RD: 1F00 0801 3809 0001 0004 EB8000 32     UNBIND
21:55:53 HHC01062D 0:0660 COMM: WR: 1F00 3809 0801 0001 0026 6B8000 310103 BIND
21:55:53 HHC01062D 0:0660 COMM: RD: 1F00 0801 3809 0001 0004 EB8000 31     BIND
21:55:53 HHC01062D 0:0660 COMM: WR: 1F00 3809 0801 0002 0004 6B8000 A0     SDT
21:55:53 HHC01062D 0:0660 COMM: RD: 1F00 0801 3809 0002 0004 EB8000 A0     SDT
21:55:53 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 0001 0009 0390A0 F30005 
21:55:53 HHC01062D 0:0660 COMM: RD: 1C00 0801 3809 0001 00B7 039020 88000E 
21:55:53 HHC01062D 0:0660 COMM: WR: 1C00 3809 0801 0000 0007 979000 000000 
21:55:53 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 0002 00B1 039020 7EC311 
21:56:03 HHC01062D 0:0660 COMM: RD: 1C00 0801 3809 0002 0015 039020 7D404D 
21:56:03 HHC01062D 0:0660 COMM: WR: 1C00 3809 0801 0000 0007 979000 000000 
21:56:03 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 0003 009B 039040 7EC311 
21:56:04 HHC01062D 0:0660 COMM: WR: 1F00 3809 0801 0003 0004 6B8000 A1     
21:56:04 HHC01062D 0:0660 COMM: RD: 1F00 0801 3809 0003 0004 EB8000 A1     
21:56:04 HHC01062D 0:0660 COMM: WR: 1F00 3809 0801 0001 0005 6B8000 3202   UNBIND
21:56:04 HHC01062D 0:0660 COMM: RD: 1F00 0801 3809 0001 0004 EB8000 32     UNBIND
21:56:04 HHC01062D 0:0660 COMM: WR: 1F00 3809 0801 0001 002F 6B8000 310103 BIND
21:56:04 HHC01062D 0:0660 COMM: RD: 1F00 0801 3809 0001 0004 EB8000 31     BIND
21:56:04 HHC01062D 0:0660 COMM: WR: 1F00 3809 0801 0002 0004 6B8000 A0     SDT
21:56:04 HHC01062D 0:0660 COMM: RD: 1F00 0801 3809 0002 0004 EB8000 A0     SDT
21:56:04 HHC01062D 0:0660 COMM: WR: 1F00 3809 0801 0003 0004 6B8000 A1     
21:56:04 HHC01062D 0:0660 COMM: RD: 1F00 0801 3809 0003 0004 EB8000 A1     
21:56:04 HHC01062D 0:0660 COMM: WR: 1F00 3809 0801 0001 0005 6B8000 3202   UNBIND
21:56:04 HHC01062D 0:0660 COMM: RD: 1F00 0801 3809 0001 0004 EB8000 32     UNBIND
21:56:04 HHC01062D 0:0660 COMM: WR: 1F00 3809 0801 0001 0033 6B8000 310103 BIND
21:56:04 HHC01062D 0:0660 COMM: RD: 1F00 0801 3809 0001 0004 EB8000 31     BIND
21:56:04 HHC01062D 0:0660 COMM: WR: 1F00 3809 0801 0002 0004 6B8000 A0     SDT
21:56:04 HHC01062D 0:0660 COMM: RD: 1F00 0801 3809 0002 0004 EB8000 A0     SDT
21:56:04 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 0001 000E 038080 F5C311 
21:56:04 HHC01062D 0:0660 COMM: RD: 1E00 0801 3809 0001 0003 838000 00     
21:56:04 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 0002 0009 038000 F30005 
21:56:04 HHC01062D 0:0660 COMM: RD: 1E00 0801 3809 0002 0003 838000 00     
21:56:04 HHC01062D 0:0660 COMM: RD: 1C00 0801 3809 0001 00B7 039020 88000E 
21:56:04 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 0003 0050 038020 7EC311 
21:56:04 HHC01062D 0:0660 COMM: RD: 1E00 0801 3809 0003 0003 838000 00     
21:56:14 HHC01062D 0:0660 COMM: RD: 1C00 0801 3809 0002 000F 039020 7DC2E6 
21:56:14 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 0004 004B 038020 F1C311 
21:56:14 HHC01062D 0:0660 COMM: RD: 1E00 0801 3809 0004 0003 838000 00     
21:56:18 HHC01062D 0:0660 COMM: RD: 1C00 0801 3809 0003 0015 039020 7DC87C 
21:56:18 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 0005 004A 038020 F1C311 
21:56:18 HHC01062D 0:0660 COMM: RD: 1E00 0801 3809 0005 0003 838000 00     
21:56:32 HHC01062D 0:0660 COMM: RD: 1C00 0801 3809 0004 0015 039020 7DD27C 
21:56:32 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 0006 004A 038020 F1C311 
21:56:32 HHC01062D 0:0660 COMM: RD: 1E00 0801 3809 0006 0003 838000 00     
21:56:33 HHC01062D 0:0660 COMM: RD: 1C00 0801 3809 0005 0006 039020 7D5CF0 
21:56:33 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 0007 004B 038020 F1C311 
21:56:33 HHC01062D 0:0660 COMM: RD: 1E00 0801 3809 0007 0003 838000 00     
21:56:33 HHC01062D 0:0660 COMM: RD: 1C00 0801 3809 0006 0006 039020 7D6060 
21:56:33 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 0008 004B 038020 F1C311 
21:56:33 HHC01062D 0:0660 COMM: RD: 1E00 0801 3809 0008 0003 838000 00     
21:56:34 HHC01062D 0:0660 COMM: RD: 1C00 0801 3809 0007 0006 039020 7DE450 
21:56:34 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 0009 005A 038020 F1C311 
21:56:34 HHC01062D 0:0660 COMM: RD: 1E00 0801 3809 0009 0003 838000 00     
21:56:34 HHC01062D 0:0660 COMM: RD: 1C00 0801 3809 0008 0006 039020 7DE840 
21:56:34 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 000A 0028 038020 F1C311 
21:56:34 HHC01062D 0:0660 COMM: RD: 1E00 0801 3809 000A 0003 838000 00     
21:56:35 HHC01062D 0:0660 COMM: RD: 1C00 0801 3809 0009 0006 039020 7D6A60 
21:56:35 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 000B 0028 038020 F1C311 
21:56:35 HHC01062D 0:0660 COMM: RD: 1E00 0801 3809 000B 0003 838000 00     
21:56:39 HHC01062D 0:0660 COMM: RD: 1C00 0801 3809 000A 000F 039020 7D6DC6 
21:56:39 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 000C 0034 038020 F1C311 
21:56:39 HHC01062D 0:0660 COMM: RD: 1E00 0801 3809 000C 0003 838000 00     
21:56:42 HHC01062D 0:0660 COMM: RD: 1C00 0801 3809 000B 000F 039020 7DF2C7 
21:56:42 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 000D 004F 038000 7EC111 
21:56:42 HHC01062D 0:0660 COMM: RD: 1E00 0801 3809 000D 0003 838000 00     
21:56:42 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 000E 0025 038000 F1C111 
21:56:42 HHC01062D 0:0660 COMM: RD: 1E00 0801 3809 000E 0003 838000 00     
21:56:43 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 000F 0103 029000 F1C111 
21:56:43 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 0010 0103 009000 501DC8 
21:56:43 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 0011 00A9 018000 404040 
21:56:43 HHC01062D 0:0660 COMM: RD: 1E00 0801 3809 0011 0003 838000 00     
21:56:43 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 0012 0014 038020 F1C311 
21:56:43 HHC01062D 0:0660 COMM: RD: 1E00 0801 3809 0012 0003 838000 00     
21:56:45 HHC01062D 0:0660 COMM: RD: 1C00 0801 3809 000C 0006 039020 7D4CE5 
21:56:45 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 0013 000D 038000 F1C311 
21:56:45 HHC01062D 0:0660 COMM: RD: 1E00 0801 3809 0013 0003 838000 00     
21:56:46 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 0014 000D 038000 F1C311 
21:56:46 HHC01062D 0:0660 COMM: RD: 1E00 0801 3809 0014 0003 838000 00     
21:56:46 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 0015 0103 029000 F1C111 
21:56:46 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 0016 0040 018000 96A388 
21:56:46 HHC01062D 0:0660 COMM: RD: 1E00 0801 3809 0016 0003 838000 00     
21:56:46 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 0017 0014 038020 F1C311 
21:56:46 HHC01062D 0:0660 COMM: RD: 1E00 0801 3809 0017 0003 838000 00     
21:56:46 HHC01062D 0:0660 COMM: RD: 1C00 0801 3809 000D 0006 039020 7D4DF5 
21:56:46 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 0018 000D 038000 F1C311 
21:56:46 HHC01062D 0:0660 COMM: RD: 1E00 0801 3809 0018 0003 838000 00     
21:56:46 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 0019 0103 029000 F14111 
21:56:46 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 001A 0103 009000 42F1C8 
21:56:46 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 001B 0103 009000 42F6E3 
21:56:46 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 001C 0103 009000 284100 
21:56:46 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 001D 0103 009000 401D60 
21:56:46 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 001E 0103 009000 410028 
21:56:46 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 001F 0103 009000 0011D5 
21:56:46 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 0020 0095 018000 410028 
21:56:46 HHC01062D 0:0660 COMM: RD: 1E00 0801 3809 0020 0003 838000 00     
21:56:46 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 0021 0012 038000 F1C311 
21:56:47 HHC01062D 0:0660 COMM: RD: 1E00 0801 3809 0021 0003 838000 00     
21:56:47 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 0022 0015 038000 F1C211 
21:56:47 HHC01062D 0:0660 COMM: RD: 1E00 0801 3809 0022 0003 838000 11     
21:56:47 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 0023 0006 038000 F1C213 
21:56:47 HHC01062D 0:0660 COMM: RD: 1E00 0801 3809 0023 0003 838000 A0     
21:56:47 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 0024 0005 038020 F1C2   
21:56:47 HHC01062D 0:0660 COMM: RD: 1E00 0801 3809 0024 0003 838000 01     
21:56:54 HHC01062D 0:0660 COMM: RD: 1C00 0801 3809 000E 000A 039020 F3C54D 
21:56:54 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 0025 0006 038000 7EC313 
21:56:54 HHC01062D 0:0660 COMM: RD: 1E00 0801 3809 0025 0003 838000 01     
21:56:54 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 0026 0103 029000 F1C111 
21:56:54 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 0027 001E 018000 5C5C5C 
21:56:54 HHC01062D 0:0660 COMM: RD: 1E00 0801 3809 0027 0003 838000 01     
21:56:55 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 0028 0016 038020 F1C311 
21:56:55 HHC01062D 0:0660 COMM: RD: 1E00 0801 3809 0028 0003 838000 01     
21:56:55 HHC01062D 0:0660 COMM: RD: 1C00 0801 3809 000F 0006 039020 F3C650 
21:56:55 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 0029 0016 038020 F1C311 
21:56:55 HHC01062D 0:0660 COMM: RD: 1E00 0801 3809 0029 0003 838000 11     
21:56:56 HHC01062D 0:0660 COMM: RD: 1C00 0801 3809 0010 0006 039020 F3C8F0 
21:56:56 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 002A 0016 038020 F1C311 
21:56:56 HHC01062D 0:0660 COMM: RD: 1E00 0801 3809 002A 0003 838000 31     
21:57:05 HHC01062D 0:0660 COMM: RD: 1C00 0801 3809 0011 0011 039020 7D4BD8 
21:57:05 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 002B 0030 038000 F1C111 
21:57:05 HHC01062D 0:0660 COMM: RD: 1E00 0801 3809 002B 0003 838000 01     
21:57:05 HHC01062D 0:0660 COMM: WR: 1E00 3809 0801 002C 0016 038020 F1C311 
21:57:05 HHC01062D 0:0660 COMM: RD: 1E00 0801 3809 002C 0003 838000 6D     
21:57:53 HHC01062D 0:0660 COMM: WR: 1F00 3809 0801 0003 0008 4B8000 C90001 
21:57:53 HHC01062D 0:0660 COMM: RD: 1F00 0801 3809 0003 0004 CB8000 C9     
21:58:02 HHC01062D 0:0660 COMM: WR: 1F00 3809 0801 0004 0004 6B8000 A1     
21:58:02 HHC01062D 0:0660 COMM: RD: 1F00 0801 3809 0004 0004 EB8000 A1     
21:58:02 HHC01062D 0:0660 COMM: WR: 1F00 3809 0801 0001 0005 6B8000 3201   UNBIND
21:58:02 HHC01062D 0:0660 COMM: WR: 1E00 3800 0800 0006 000B 0B8000 010211 SETCV[05]
21:58:02 HHC01062D 0:0660 COMM: RD: 1F00 0801 3809 0001 0004 EB8000 32     UNBIND
21:58:02 HHC01062D 0:0660 COMM: RD: 1E00 0800 3800 0006 0006 8B8000 010211 SETCV
21:58:02 HHC01062D 0:0660 COMM: WR: 1F00 3809 0800 0003 0004 6B8000 0E     DACTLU
21:58:02 HHC01062D 0:0660 COMM: RD: 1F00 0800 3809 0003 0004 EB8000 0E     DACTLU
21:58:02 HHC01062D 0:0660 COMM: WR: 1F00 3808 0800 0003 0005 6B8000 1202   DACTPU
21:58:02 HHC01062D 0:0660 COMM: RD: 1F00 0800 3808 0003 0004 EB8000 12     DACTPU
21:58:02 HHC01062D 0:0660 COMM: WR: 1E00 3800 0800 0007 0008 0B8000 010202 DISCONTACT
21:58:02 HHC01062D 0:0660 COMM: RD: 1E00 0800 3800 0007 0006 8B8000 010202 DISCONTACT
21:58:02 HHC01062D 0:0660 COMM: WR: 1E00 3800 0800 0008 0008 0B8000 01020B DACTLINK
21:58:02 HHC01062D 0:0660 COMM: RD: 1E00 0800 3800 0008 0006 8B8000 01020B DACTLINK
21:58:02 HHC01062D 0:0660 COMM: WR: 1F00 3800 0800 0004 0005 6B8000 1201   DACTPU
21:58:02 HHC01062D 0:0660 COMM: RD: 1F00 0800 3800 0004 0004 EB8000 12     DACTPU
```

## SDLC implementation in STM32 Blue pill.


### Tx

The general idea is to receive frames over serial line. 

There is an End Of Record (EOR) in the data received which indicate when to insert CRC bytes and generate closing flag. Just as little safty measure there is a simple checksum in the serial protcols. ~~The byte just before the EOR is the checksum byte and should be the sum of bytes received until then. When everything is OK the sum should be zero when the EOR is received. If not zeros a REJECT is sent back. A REJECT is 0xff 0xfd. If the frame is OK then 0xff 0xfe is sent back when the frame has been sent. A timeout is needed on the sending side as well. It has to be related to the actual sending speed.~~ It turns out that including the escape in the checksum process will not work since you might end up with 0xff as the checksum and then you need to escape it which will then affect the checksum... An data 0xff has to be escaped with double 0xff to work.

Data is then formatted into HDLC and moved into a sending buffer. The SPI routine checks is there are possible to send a byte from the buffer. Whenever it SPI interface is empty a new byte is read from the buffer and written to the SPI interface. When the sending buffer is empty the SPI will continue to send 0xff to indicate IDLE condition. 

As data is received and de-escaped it is handled by the hdlc formatting routine. It takes has several states. In state IDLE when receiving a character it will start the frame by sending a flag. Then it will transfer to state FLAG SENT. In FLAG SENT all bytes are processed bit by bit, from ~~MSB to LSB~~ LSB to MSB. If the bit is a zero the output data byte will be shifted one step ~~left~~ right, thus shufting in a 0. If the bit is a one there is a counter that counts the number of ones that has been sent already. If this counter is five then a zero bit is inserted prior to shifting in the one bit. The counter is reset to zero at this time.

There is also a bit counter that counts from 0 to 8. It counts each bit shifted in into the one byte output buffer. When 8 bits has been shifted in, including extra zeroes that has been inserted, it will transfer the byte to the output buffer queue for sending. The bit counter will then be reset to zero again.  

When all data has been sent there might be a number of residual bits that has not yet been sent in the output buffer byte depening on how many extra zeroes that has been inserted. If this is the case the flag byte will be shifted in rather than just sent directly. To fill up to 8 full bits idle one bits will be shifted in after the flag byte prior to moving it to the output sending buffer.

### Rx

Since receiving is a time critical task bytes has to be received from the SPI interface immediately and put into a buffer. All SDLC processing code will read byte by byte from the buffer rather than from the SPI device to minimize the risk for overrun. To further improve this DMA can be used to transfer the data without involving the CPU at all. Will be invesigated in the future.

The DDLC processor has two states, IDLE and ACTIVE. IDLE when it is waiting for receving the flag and ACTIVE when receiving data. As with transmit each byte is scanned from LSB to MSB. If a bit is a one then oneCounter is incremented. If oneCounter is 6 and the current bit is 0 then we have a flag. Then we switch states, either from IDLE to ACTIVE or from ACTIVE to IDLE. If ACTIVE state and oneCounter is 7 then we have an abort. The current frame shall be discarded and state goes to IDLE.
In ACTIVE state and oneCounter is 5 and current bit is 0 means that this is an inserted 0 bit. This shall be disregarded from. Thus do nothing. In all other cases when in ACTIVE state it shall copy the current bit into the input byte buffer, shifting it in to the right from MSB to LSB. The bitCounter is incremented at each time. If the bitCounter is 8 then the current input byte is transfered to the buffer and the bitCounter is reset to 0.

When in ACTIVE state and a flag is received, this means that the current frame is terminated and that it shall be processed by next layer. Thus a flag is signalling that the current frame is ready for processing.

The data that has been processed by the SDLC input processor is then read from the buffer by the task that frames data for sending over the serial line. This is simply reading the stream of bytes and inserting escaping 0xff characters whenever necessary. The EOR marker will be sent as the last couple of characters.

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

### NCP
* [IBM 3705 Communicatons Controller Network Control Program Generation and Utilities, Guide and Reference Manual](http://bitsavers.org/pdf/ibm/3704_3705/GC30-3000_3705_NCPGEN_Apr72.pdf)

### 3274
* [3274 Control Unit Description and Programmers Guide](http://bitsavers.trailing-edge.com/pdf/ibm/3274/GA23-0061-1_3274_Control_Unit_Description_and_Programmers_Guide_Jan84.pdf)

### Other
* [Matt Burke's work on DSLw to interconnect SNA / SDLC](https://www.9track.net/hercules/dlsw/)
* [SNA / SDLC quick guide by Clif Anderson](https://www.cliffa1994.com/snasteps.htm)
* [SDLC overview](https://www.euclideanspace.com/coms/protocol/sdlc/index.htm)
* [VTAM/NCP Node Definition Example](http://ps-2.kev009.com/tl/techlib/manuals/adoclib/3270hcon/hconugd/definvta.htm)
* [Course on SNA / VTAM](http://bitsavers.informatik.uni-stuttgart.de/pdf/ibm/sna/Kaptronix_SNA.pdf)
