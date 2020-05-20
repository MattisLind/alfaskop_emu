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
TCAM     TSOMCP UNITSIZ=255
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