# Hercules Integration

The intention is to get the Alfaskop terminal up and running with the Hercules IBM mainframe emulator. What was the best way to interface a 3270 terminal to Hercules? The obvious answer would be over TN3270. But is it the best solution? Not necessarily.

Making it TN3270 compatible is a some what over-engineered solution. It creates a need to full application layer suppport for the 3270 BSC protocol so that the 3270 data stream can be sent over it. 

But when reading the documentation for the [Hercules config file](http://www.hercules-390.org/hercconf.html) this line caught my eye:
```
( Preliminary 2703 BSC Support )
Describes a BSC emulation line entry to either link 2 Hercules engines or a custom made program emulating a 2780, 3780 or 3x74, or a custom made program interfacing to a real BSC line.

```
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

After a re-IPL of the system I could do a **S TP** to have TSOMCP started. If I then connected a netcat instance to port 32701 (as specified in the Hercules config above) I received output "7@@@@-". This is BSC for EOT 40 40 40 40 ENQ and is essentially a specific POLL message to control unit 0 and terminal 0.
  
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


## Testing with herculesIntegration test program

So to verify how Hercules behaved I made a quick test program based on the BSC protocol handler I created earlier. It is called herculesIntegration and it just tries to respond as well as possible to the messages received from Hercules.



This is an example run of the herculesIntegration program and the debug output is not meant to be beauitful in any way.
```
Read data from line: 37
Received 37 in state 0
msgType = 0
Got EOT
Read data from line: 40
Received 40 in state 0
Read data from line: 40
Received 40 in state 7
Read data from line: FFFFFFC6
Received C6 in state 7
Read data from line: FFFFFFC6
Received C6 in state 7
Read data from line: 2D
Received 2D in state 10
msgType = 1
POLL CU=40 DV=C6
Sent 01 got back ret=1
Sent 6C got back ret=1
Sent D9 got back ret=1
Sent 02 got back ret=1
Sent 40 got back ret=1
Sent C6 got back ret=1
Sent 40 got back ret=1
Sent C1 got back ret=1
Sent 03 got back ret=1
Sent 62 got back ret=1
Sent 50 got back ret=1
Read data from line: 10
Received 10 in state 0
Read data from line: 61
Received 61 in state 3
msgType = 5
Got ACK1
Sent 37 got back ret=1
Read data from line: 37
Received 37 in state 0
msgType = 0
Got EOT
Read data from line: 40
Received 40 in state 0
Read data from line: 40
Received 40 in state 7
Read data from line: FFFFFFC7
Received C7 in state 7
Read data from line: FFFFFFC7
Received C7 in state 7
Read data from line: 2D
Received 2D in state 10
msgType = 1
POLL CU=40 DV=C7
Sent 01 got back ret=1
Sent 6C got back ret=1
Sent D9 got back ret=1
Sent 02 got back ret=1
Sent 40 got back ret=1
Sent C7 got back ret=1
Sent C2 got back ret=1
Sent 40 got back ret=1
Sent 03 got back ret=1
Sent A3 got back ret=1
Sent D4 got back ret=1
Read data from line: 10
Received 10 in state 0
Read data from line: 61
Received 61 in state 3
msgType = 5
Got ACK1
Sent 37 got back ret=1
Read data from line: 61
Received 61 in state 0
Read data from line: 61
Received 61 in state 7
Read data from line: 61
Received 61 in state 7
Read data from line: 61
Received 61 in state 7
Read data from line: 61
Received 61 in state 10
msgType = 11
Got ERROR
Read data from line: 61
Received 61 in state 0
Read data from line: 61
Received 61 in state 7
Read data from line: 61
Received 61 in state 7
Read data from line: 61
Received 61 in state 7
Read data from line: 61
Received 61 in state 10
msgType = 11
Got ERROR
```

What can be seen is that all POLL messages start with a EOT to so to say reset the line. Thh EOT is the followed by the two control unit address bytes and two station identifer bytes. Four addresseing bytes in total. Lastly followed by a ENQ to signifiy the poll request.

The first insight is that Hercules doesn't send the SYN characaters at all. It might be so that the 2703 hardware ands the SYN characters so that they are not at all handled by the driver. But from a interfacing standpoint this could be a complications since the SYN characters provide framing. According the [3274 Control Unit Description and Programmers Guide page 4-14 (172)](http://bitsavers.trailing-edge.com/pdf/ibm/3274/GA23-0061-1_3274_Control_Unit_Description_and_Programmers_Guide_Jan84.pdf) it appears that the the first EOT is meant to be framed in its own message unit and no joint together with the following ENQ message. Meaning that before the EOT there shall be two SYN characters and it shall be followed by a PAD character. The manual states that the TUS is responsible for adding these charcaters. 

This would provide framing and help to differentiate it from the other message units. Otherwise it all ends up in a stream of characters that need to be parsed. So a suggestion is that Hercules 2703 emulations as an option provide inclusion of SYN and PAD characters so that the framing can be discerned from the data more easily. 

A proper anser to a poll message is either a simple EOT or a status message. The hercules responder was preprogrammed to respond slightly differently depending on what station was addressed. So the first station just respnded witha EOT and the others with a ststus message. As can be seen the status message is received by Hercules and processed by the TCAM and a ACK1 response is returned. To which the test program simply responds with en EOT to terminate the poll. TCAM will then poll the next station and continue with the others in a round robin fashion. When all stations are responding properly there is no error messages in the MVS log and on the console screen.

## A login prompt in the traces

While working on the herculesIntgration test client I discovered that when there was a bug in the testprogra in that it failed to respond with an EOT to the ACK1 signal at one point in the flow, TCAM would send a message. *IKJ54017A TERMINAL ERROR, REENTER INPUT*. Of course it was coded in EBCDIC but some hand decoding revealed it. 

That was quite interesting. Was there a way to send real data towards the system that could provoke some other output? I did further reading of the 3274 manuals and it showed that you could send some key presses in message back when the POLL was received. I opted for hardcoding the client to send PA1, PA2, and PA3 keys in response for every POLL received. Now I got another message, *IKJ54011I TSO NOT ACTIVE* it read. Googling this message gave a link to a page by Max where it simply said I failed to start TSO properly. 

I had to do the **F TP,TS=START** command. This command gave the log message saying *IKJ019I TIME SHARING IS INITIALIZED* in the ordinary console log. That sounded promising and when I hand decoed the data received sure enough there were a *IKJ54012A ENTER LOGON -* in the traces of the hercules test client.

To turn off time sharing the command is **F TP,TS=STOP** and the **Z TP** to stop the procedure


### Hercules bug

There seems to be a problem in Hercules in that when TCAM / TSO is sytopped by the Z TP command hercules seems to get into a spion where it just starts sending the last transmitted byte over and over again in a tight loop. The test program log file quickly wnet to almost 400 megabyte worth of logdata. Just disconnecting the socket and reconnecting again doesn't solve the problem. The only way is to bring down the operating system running and re-IPL it.

Looking in the log above it can be seen that the last sent byte was the 61h as part of the ACK1 message from hercules. The response from the test program is a plain EOT and then there is continous bytes of 61h coming on the line.

## Other relevant IBM manuals that I browsed while researching this topic:
 * [TCAM Programmers Guide and Reference Manual Rel 20.1](http://bitsavers.informatik.uni-stuttgart.de/pdf/ibm/360/os/tcam/GC30-2024-1_OS_TCAM_Programmers_Guide_and_Reference_Manual_Rel_20.1_Sep71.pdf
)
 * [OS/VS TCAM Concepts and Facilities](http://www.bitsavers.org/pdf/ibm/370/OS_VS/GC30-2042-0_OS_VS_TCAM_Concepts_and_Facilities_Nov74.pdf)
 * [OS/MFT and OS/MVT TCAM Programmers Guide Rel 21](http://bitsavers.org/pdf/ibm/360/os/tcam/GC30-2024-3_OS_MFT_and_OS_MVT_TCAM_Programmers_Guide_Rel_21_Jul72.pdf)
 * [OS TCAM Users Guide Rel 20.1](http://www.bitsavers.org/pdf/ibm/360/os/tcam/GC30-2025-0_OS_TCAM_Users_Guide_Rel_20.1_Jan72.pdf)
 * [OS/VS2 MVS Programming Library TSO](https://ia801604.us.archive.org/17/items/bitsavers_ibm370OSVS06291OSVS2MVSProgrammingLibraryTSORel3.7_4123765/GC28-0629-1_OS_VS2_MVS_Programming_Library_TSO_Rel_3.7_Nov76.pdf)
 * [360 OS Time Sharing Option Guide](http://www.bitsavers.org/pdf/ibm/360/os/tso/GC28-6698-5_Time_Sharing_Option_Guide_Jul72.pdf)
 * [TSO Optione Guide Rel 20.1](http://bitsavers.informatik.uni-stuttgart.de/pdf/ibm/360/os/R20.1_Mar71/GC28-6698-3_TSO_Option_Guide_Rel_20.1_Jun71.pdf)
 * [MVS 3.8 Cookbook](http://www.bsp-gmbh.com/turnkey/cookbook/pdf/mvs38bas.pdf
)
 * [System Productivity Facility
for MVS](http://www.computinghistory.org.uk/downloads/10096)
 * [System Programming Library: TSO Extensions
Installation and Planning ](http://www.computinghistory.org.uk/downloads/10255)
 * [Introduction to OS/VS2 Release 2](http://bitsavers.informatik.uni-stuttgart.de/pdf/ibm/370/OS_VS2/Release_2_1973/GC28-0661-1_Introduction_to_OS_VS2_Release_2_Mar73.pdf)
 * [OS/VS2 System Generation Reference Release 3.8](http://bitsavers.trailing-edge.com/pdf/ibm/370/OS_VS2/Release_3.8_1978/GC26-3792-8_OS_VS2_System_Generation_Reference_Release_3.8_Oct80.pdf)
 * [3270 Intro to Programming](http://bitsavers.trailing-edge.com/pdf/ibm/3270/GC27-6999-2_Intro_To_Programming_3270_Aug77.pdf)
* [OS/MFT and OS/MVT TCAM Logic Release 21.0](http://129.69.211.95/pdf/ibm/360/os/tcam/GY30-2029-3_OS_MFT_and_OS_MVT_TCAM_Logic_Release_21.0_Jul72.pdf)
 * [OS/VS1 Programmers Digest](http://www.bitsavers.org/pdf/ibm/370/OS_VS1/GC24-5091-3_OS_VS1_Rel_3_Programmers_Reference_Digest_Dec73.pdf)
 * [2703 Transmission Control Component Description](http://bitsavers.trailing-edge.com/pdf/ibm/2703/GA27-2703-1_2703_Transmission_Ctl_Component_Descr_May67.pdf)
 * [3274 Control Unit Description and Programmers Guide](http://bitsavers.trailing-edge.com/pdf/ibm/3274/GA23-0061-1_3274_Control_Unit_Description_and_Programmers_Guide_Jan84.pdf)
 * [General Information Binary Synchronous Communication - Third edition](http://bitsavers.org/pdf/ibm/datacomm/GA27-3004-2_General_Information_Binary_Synchronous_Communications_Oct70.pdf)
 * [General Information Binary Synchronous Communication - First edition](http://bitsavers.org/pdf/ibm/datacomm/A27-3004-0_bisyncGenDescr.pdf)
 
 ## Links
 
  * [Hercules IBM Main fram emulator](http://www.hercules-390.eu/)
  * [groups.io H390-MVS non-3270 TSO solution for bare MVS or TK3 (TK4 already has it...)](https://groups.io/g/H390-MVS/topic/non_3270_tso_solution_for/74007998?p=,,,20,0,0,0::recentpostdate%2Fsticky,,,20,2,0,74007998)
  * [Guide to installing TSO under MVT on Hercules](http://www.clueful.co.uk/mbeattie/hercules/tso.html)
  * [yahoo groups archieve of turnkey-mvs group: TTY TSI via 2703](https://turnkey-mvs.yahoogroups.narkive.com/McyCzPjS/tty-tso-via-2703)
  * [yahoo groups archive of hercules-390: New Async 2703 TTY/2741 driver: request to include into Hercules](https://hercules-390.yahoogroups.narkive.com/B1RUA16u/new-async-2703-tty-2741-driver-request-to-include-into-hercules-mainline)
  * [Pages of Max H. Parke](http://www.lightlink.com/mhp/2703/)
  * [The 2703 BSCA Adapter works!](https://hercules-390.yahoogroups.narkive.com/sSHXTiLW/the-2703-bsca-adapter-works)
  * [Thread on H390 groups.io discussing issues](https://hercules-390.groups.io/g/group/topic/bsca_driver_in_2703_emulation/74369780) 
