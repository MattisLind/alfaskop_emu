# alfaskop_emu

![Alfaskop 4110](https://github.com/MattisLind/alfaskop_emu/raw/master/pics/Alfaskop_console_mode.png)


This project aims to make a Alfaskop 4110 running towards the Hercules IBM emulator and run the MEMO SW.

The Alfaskop terminal was a big success for the early Swedish IT industry. In total 900 000 units were delivered world wide.
More information about the Alfaskop Series 41, marketing material and technical documents can be found [here.](http://www.datormuseum.se/peripherals/terminals/alfaskop)

There are today not one single Alfaskop Series 41 terminal that is able to run and show what is was like. The root cause
is that the system as a whole  is quite complex. The system 41 terminal of Display Unit (DU) requires a communication processor and a floppy drive (FD) to be able to run. It also has no software built in but loads this from the cluster.


The basic idea is to use MAME to emulate the CP and the FD. All technical documentation and schematics are available and is scanned.
![Alfaskop 4110](https://github.com/MattisLind/alfaskop_emu/raw/master/pics/Alfaskop_emu_architecure.png)


To communicate between the various entities of the cluster a TCP variant of the two wire bus will be created eumlating the 32 ports of the CP. To interface to the real Alfaskop DU 4110 a two-wire bus to TCP bridge will be created. In the first implementation it will use an Ericsson TWIB PC board connected to a small uController and a ESP32. Later on the interfacing will be done using a CPLD connected to a ESP32. The CPLD will handle HDLC and include the MODEM.



## Interfacing with SS3

![Two wire connector female](https://i.imgur.com/YzAfB2gl.png)
![Two wire connector male](https://github.com/MattisLind/alfaskop_emu/raw/master/pics/TwinaxConnectorMale_small.png)


The special twinax connnector used for the Alfaskop series was devolped by Ossi Carlsson AB, an ELDON AB company. The bus called SS3 which employed a 9.585 MHz (half the pixel clock of the terminal) clock to recover the approximately 300 kbit/s signal modulated by FFSK. The signalling over the link employed HDLC. Initially the FFSK modem was implemented using discrete TTL circuits and a bipolar PROM. Later on a Ferranti ULA (custom IC) was designed which did the entire modulation and demodulation process. 

![TWIB board](https://i.imgur.com/grnMKvj.jpg)

In an attempt to interface to the SS3 bus the easiest was to actually reuse one of the Ericsson made TWIB PC-bus boards that happened to be available. The board is very simple and has just the Intel 8274 HDLC chip and some adress decoding as well as DMA and interrupt logic. Apart for that there is also a twin wire MODEM circuitry including the Ferranti ULA.


## Alfaskop software

The Alfaskop Series 41 was primarily used as a terminal with emulating various terminal types, like IBM 3278, UNIVAC UTS 400, DEC VT100 etc. The Alfaskop series of terminals were programmed in a special language, SPL. From the beginning this meant StanSAAB programming Language and was a modified variant of PL/1 programming language.

Later on other software was developed for the Alfaskop series 41, like Alfaword, which was a wordprocessing package. Another package was called Alfaform. There was also a port of the UCSD p-system to the System 41 series. Together with FD4120 floppy drive a complete personal computer was formed. The only software found this far is the 3278 terminal emulation software to be used in the clustered configuraration (4016).

The system software diskette 4016 has been found at Dansk Datahistorisk Förening. This disk has origninally been with SAS. People there will make an image dump of this disk
and provide it to use.

![Alfaskop in MAME](https://github.com/MattisLind/alfaskop_emu/raw/master/pics/SoftwareDisks.jpg)
 

## 3270 protocol

The Alfaskop terminals were mostly used for emulating the IBM 3270 terminal series. Although other emulations were available. The software provided from DDHF is the 3270 BSC variant. The 3270 data stream is described in [this](http://bitsavers.trailing-edge.com/pdf/ibm/3270/GA23-0059-4_3270_Data_Stream_Programmers_Reference_Dec88.pdf) document. The [documentatation](http://bitsavers.org/pdf/ibm/3274/GA23-0061-1_3274_Control_Unit_Description_and_Programmers_Guide_Jan84.pdf) for the IBM 3274 Control Unit provide relevant information on how the communication towards the host takes place. The communicationprocessor could either be connected locally to the IBM main frame or remotely using a dial-up or leased line. In the host end there is a [2703](http://bitsavers.informatik.uni-stuttgart.de/pdf/ibm/2703/GA27-2703-1_2703_Transmission_Ctl_Component_Descr_May67.pdf) or [3704](http://bitsavers.informatik.uni-stuttgart.de/pdf/ibm/3704_3705/GC30-3004-5_3704_3705_Communications_Controller_Principles_of_Operation_May1979.pdf) or similar IBM communication unit that interfaces towards the IBM processor. The line normally used 9600 bps syncrounous BSC communication described in [this](http://bitsavers.trailing-edge.com/pdf/ibm/datacomm/GA27-3004-2_General_Information_Binary_Synchronous_Communications_Oct70.pdf) document.

