# alfaskop_emu
This project aims to make a Alfaskop 4110 running towards the Hercules IBM emulator and run the MEMO SW.

The Alfaskop terminal was a big success for the early Swedishg IT industry. In total 900 000 units were delivered world wide.
More information about the Alfaskop Series 41, marketing material and technical documents can be found [here.](http://www.datormuseum.se/peripherals/terminals/alfaskop)

There are today not one single Alfaskop Series 41 terminal that is able to run and show what is was like. The root cause
is that the system as a whole  is quite complex. The system 41 terminal of Diaplay Unit (DU) requires a communication processor 
and a floppy drive (FD) to be able to run. It also has no software built in but loads this from the cluster.

The system software diskette 4016 has been found at Dansk Datahistorisk Förening. This disk has origninally been with SAS. People there will make an image dump of this disk
and provide it to use.

The basic idea is to use MAME to emulate the CP and the FD. All technical documentation and schematics are available and is scanned.

![Alfaskop in MAME](https://i.imgur.com/yO6jXmll.png)

Lacking is the IPL BOOT ROM of the real hardware unless DDHF happens to have a CP4101 and FD4120 in their possession.

To communicate between the various entities of the cluster a TCP variant of the two wire bus will be created eumlating the 32 ports of the 
CP. To interface to the real Alfaskop DU 4110 a two-wire bus to TCP bridge will be created. In the first implementation it will
use an Ericsson TWIB PC board connected to a small uController and a Raspberry Pi Zero W.

![Two wire connector](https://i.imgur.com/YzAfB2gl.png)

The special twinax connnector used for the Alfaskop series was devolped by Ossi Carlsson AB, an ELDON AB company. The bus called SS3 which employed a 9.585 MHz (half the pixel clock of the terminal) clock to recover the approximately 300 kbit/s signal modulated by FFSK. The signalling over the link employed HDLC. Initially the FFSK modem was implemented using discrete TTL circuits and a bipolar PROM. Later on a Ferranti ULA (custom IC) was designed which did the entire modulation and demodulation process. 

## Interfacing with SS3

![TWIB board](https://i.imgur.com/grnMKvj.jpg)

In an attempt to interface to the SS3 bus the easiest was to actually reuse one of the Ericsson made TWIB PC-bus boards that happened to be available. The board is very simple and has just the Intel 8274 HDLC chip and some adress decoding as well as DMA and interrupt logic. Apart for that there is also a twin wire MODEM circuitry including the Ferranti ULA.

First step of the reverse engineering was to layout the schematic identical to the board layout and trace out all connections using a ohm-meeter. Then a new schematic was done based on the actual functions of the board. Adress decoding, Two-wire modem, DIPSWitches bus driver, 8274 chip etc. 

The outcome gave that the adress bus is only partly decoded. Only address A0-A10 is used. Adress A4-A10 is compared with the switch settings. Adress A0 and A1 is connected to the 8274 chip via a couple of AND gates that allow for DMA operations. A2 high enable the DIPSW onto the bus and A3 high enable the 8274 on the bus. The signal AEN need to be high for the card to be selected. The signals IOR and IOW tell the board if there is a Read or Write operation taking place. RESET sigal will RESET the 8274 and the modem chip.  The 8274 need a clock signal which is less than 4 MHz which is derived form the PC BUS 4.77 MHz clock signal which is divided by two in a 74S74 chip.

The intention is to connect a STM32 uController to the board and interface it with the D0-D7 signals, A0 and A1 signals, IOR and IOW signals and the RESET signal. A10-A4 are all set to low and the corresponding DIP switches are set accordingly. A3 is set high and A2 is set low. A small clock oscillator circuit is used to create a signal which is lower than 8 MHz.


## Alfaskop sowtware

The Alfaskop series of terminals were programmed in a spcial language, SPL. From the beginning this meant StanSAAB programming Language and was a modified variant of PL/1 programming language. 

## 3270 protocol

The Alfaskop terminals were mostly used for emulating the IBM 3270 terminal series. Although other emulations were available. The software provided from DDHF is the 3270 BSC variant. The 3270 data stream is described in [this](http://bitsavers.trailing-edge.com/pdf/ibm/3270/GA23-0059-4_3270_Data_Stream_Programmers_Reference_Dec88.pdf) document. The communicationprocessor could either be connected locally to the IBM main frame or remotely using a dial-up or leased line. The line normally used 9600 bps syncrounous BSC communication described in (http://bitsavers.trailing-edge.com/pdf/ibm/datacomm/GA27-3004-2_General_Information_Binary_Synchronous_Communications_Oct70.pdf)[this] document.

