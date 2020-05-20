# Hercules Integration

The intention is to get the Alfaskop terminal up and running with the Hercules IBM mainframe emulator. What was the best way to interface a 3270 terminal to Hercules? The obvious answer would be over TN3270. But is it the best solution? Not necessarily.

Making it TN3270 compatible is a some what over-engineered solution. It creates a need to full application layer suppport for the 3270 BSC protocol so that the 3270 data stream can be sent over it. 

Inside Herucules there are support for emulating both the older 2703 and the newer 3705. In the doumentation can be found that Hercules can be configured for BSC communication if we enable the virtual 2703 with LNCNTL=BSC.

But did TCAM in MVS (OS/VS2 or predecessor OS/VS) support the 2703 to connect to are remotely attached 3270 terminal? The IBM document [OS/VS TCAM Concepts and Facilities](http://www.bitsavers.org/pdf/ibm/370/OS_VS/GC30-2042-0_OS_VS_TCAM_Concepts_and_Facilities_Nov74.pdf) gave  the answer:

![TCAM Support table](https://github.com/MattisLind/alfaskop_emu/raw/master/pics/TCAM-support-3270.jpg)


Unfortunately the mnauals online is quite scattered. I.e the full set of mamnuals for MVS (OS/VS2) is not found. Particurlary the guides for TCAM and TSO are missing in some cases. I found an older manual for the OS/VS2 predecessor the IBM 360 operating system called OS for the TSO function, [The Time Sharing Option Guide](http://www.bitsavers.org/pdf/ibm/360/os/tso/GC28-6698-5_Time_Sharing_Option_Guide_Jul72.pdf).

Page 75 describes how the implementation of TSO with TCAM takes place. It describes what steps to take and how to do it. 

The steps needed are
 * Tailor a MCP program for TSO and TCAM. 
 * Write a catalogued procedure for starting TSO

But the essential macro LINEGRP is not very well described when it comes to newer termninals since the manual predates the 3270 terminals. This is needed to complete the first step.

Since I was not very used to building software on IBM systems this seemed to be a daunting task. Luckily I happened to find a post in the H390-MVS group where Doug Wegscheid had described how he made TCAM & TSO work under MVS for a regular line oriented terminal. Would it be possible to get the same work for a remotely attached 3270?
Other people chimed in in the discussion and pointed me to the source code for the MVS 3.8j system.

[TSOMCP](https://github.com/moshix/MVS38j.SYS1.MACLIB/blob/master/TSOMCP)
, [LINEGRP](https://github.com/moshix/MVS38j.SYS1.MACLIB/blob/master/LINEGRP) and [LISTTA](https://github.com/moshix/MVS38j.SYS1.MACLIB/blob/master/LISTTA) macros are the relevant macros for completing the first bullet above. The source code gave some additional insights how the parameter shold be set in a proper manner. Together with reading a lot of old manuals I and iterating a few times I finally came up with a JCL file that made it through without errors. The resulting JCL file which was 95% identical to what Doug had come up with but with the LINEGRP parameters changed and LISTTA macro added.

```
//TCAMSTG1 JOB (MATTIS),TCAM.R3270,CLASS=A,MSGCLASS=A,MSGLEVEL=(1,1)
//ASM EXEC ASMFC,PARM.ASM='DECK',REGION.ASM=512K
//ASM.SYSUT1 DD UNIT=SYSDA
//ASM.SYSUT2 DD UNIT=SYSDA
//ASM.SYSUT3 DD UNIT=SYSDA
//ASM.SYSPUNCH  DD  DSN=&&TEMP,DISP=(MOD,PASS),SPACE=(CYL,(1,1)),
//             UNIT=SYSDA,DCB=(DSORG=PS,RECFM=FB,LRECL=80,BLKSIZE=800)
//ASM.SYSIN DD *
         PRINT GEN
         LINEGRP TERM=327R,DDNAME=R3270,LINENO=01,                     +
               DIAL=NO,UNITNO=1,SCREEN=(24,080),TERMNO=(8)
         LISTTA RLN=1,ADDR=(4040,40C1,40C2,40C3,40C4,40C5,40C6,40C7)
         END
/*
//*TCAMSTG2 JOB CLASS=A,MSGCLASS=A,MSGLEVEL=(1,1)
//ASM2    EXEC  PGM=IEUASM,PARM=LOAD,REGION=512K
//*            COND=(4,LT,ASMFC)
//SYSLIB DD    DSNAME=SYS1.MACLIB,DISP=SHR
//SYSUT1 DD    DSNAME=&SYSUT1,UNIT=SYSDA,SPACE=(1700,(400,50)),
//             SEP=(SYSLIB)
//SYSUT2 DD    DSNAME=&SYSUT2,UNIT=SYSDA,SPACE=(1700,(400,50))
//SYSUT3 DD    DSNAME=&SYSUT3,SPACE=(1700,(400,50)),
//             UNIT=(SYSDA)
//SYSPRINT DD  SYSOUT=A
//SYSPUNCH DD  SYSOUT=B
//SYSGO    DD  DSNAME=&LOADSET,UNIT=SYSDA,SPACE=(80,(200,50)),
//             DISP=(MOD,PASS)
//SYSIN DD    DSN=&&TEMP,DISP=(OLD,DELETE),UNIT=SYSDA
//LKED   EXEC  PGM=IEWL,PARM='XREF,LIST,LET,CALL,AC=1',REGION=512K
//*            COND=(4,LT,ASM2)
//SYSLIN DD    DSNAME=&LOADSET,DISP=(OLD,DELETE)
//SYSLMOD DD DISP=SHR,DSN=SYS2.LINKLIB(IEDQTCAM)
//SYSUT1 DD    DSNAME=&SYSUT1,UNIT=(SYSDA),
//             SPACE=(1024,(50,20))
//SYSPRINT DD  SYSOUT=A
//SYSLIB DD DISP=SHR,DSN=SYS1.TELCMLIB
```
 
When this has been successfully processed by JES a new job to create a start procedure need to be run. This job defines a program TP that is linked to the TCU unit a 604. The start procedure was essentially identical to the one Doug has come up with with a different line specifying the 2703 unit at address 604.

```
//TCAMPRCS JOB (MATTIS),TCAM.PROC,CLASS=A,MSGLEVEL=(1,1)
//TCAM     EXEC PGM=IEBUPDTE
//SYSPRINT DD  SYSOUT=A
//SYSUT1   DD  DISP=SHR,DSN=SYS2.PROCLIB
//SYSUT2   DD  DISP=SHR,DSN=SYS2.PROCLIB
//SYSIN    DD  DATA
./ ADD NAME=TP
//TCAM     EXEC PGM=IEDQTCAM,ROLL=(NO,NO),TIME=1440,DPRTY=(15,15),
//             REGION=256K
//STEPLIB  DD  DSN=SYS2.LINKLIB,DISP=SHR
//SYSABEND DD  SYSOUT=A,SPACE=(CYL,(20,10),RLSE)
//R3270    DD  UNIT=604
``` 

Hercules need to be configured to have a 2703 TCU at address 604 which is done by adding this to the configuration file.

```
0604    2703    lport=32701 lnctl=BSC dial=IN
```

And before the TP program can be run one need to have the system sysgen:ed to have a TCU at address 604. I followed the guidlines that Jay Moeseley provided for generating a MVS 3.8j system from scratch. In this sysgen there are already a suitable 2703 configured. But in case not, these lines has to be added to the MVS sysgen.

```
BSC3@6   IODEVICE                                               C03630000
            UNIT=BSC3,                                          C03640000
            ADAPTER=BSCA,                                       C03650000
            TCU=2703,                                           C03660000
            ADDRESS=604                                          03670000
*
```

After a re-IPL of the system I could do a S TP to have TSOMCP started. If I then connected a netcat instance to port 32701 (as specified in the Hercules config above) I received output "7@@@@-". This is BSC for EOT 40 40 40 40 ENQ and is essentially a specific POLL message to control unit 0 and terminal 0.
  
 At the same time message started poping up on the console terminal attached to the Hercules system.
 
 ```
 4000 14.17.01 STC   14  $HASP373 TP       STARTED
4000 14.17.01 STC   14  IEF403I TP - STARTED - TIME=14.17.01
0140 14.17.33 STC   14  IEA000I 604,TOT,02,0E00,01E3,04**4040,,TP      ,14.17.33
0140 14.17.54 STC   14  IEA000I 604,TOT,02,0E00,01E3,04**40C1,,TP      ,14.17.54
0140 14.18.15 STC   14  IEA000I 604,TOT,02,0E00,01E3,04**40C2,,TP      ,14.18.15
0140 14.18.37 STC   14  IEA000I 604,TOT,02,0E00,01E3,04**40C3,,TP      ,14.18.36
0140 14.18.58 STC   14  IEA000I 604,TOT,02,0E00,01E3,04**40C4,,TP      ,14.18.58
0140 14.19.19 STC   14  IEA000I 604,TOT,02,0E00,01E3,04**40C5,,TP      ,14.19.19
0140 14.19.40 STC   14  IEA000I 604,TOT,02,0E00,01E3,04**40C6,,TP      ,14.19.40
 ```

Most likely these errors comes from the fact that there are no response received from the terminals which are polled.
