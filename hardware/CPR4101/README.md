# CPR4101 Hardware and firmware

![CPR4101](https://github.com/MattisLind/alfaskop_emu/raw/master/pics/CPR4101_small.png)

The CPR4101 is a 44 x 37 x 31 cm box. It has an internal chassis made out of sheet metal which is housed in a brown/beige plastic housing.
In the chasssis there is a CPB board which has the main microprocessor, then there is a TAB board which has slots for SS3 communication ports on TUA boards.
In addition to this there is a extension MRW-A board which has 32 kbyte of memory and a SCA board for communication with the host.

[Information leaflet (in Swedish)](http://storage.datormuseum.se/u/96935524/Datormusuem/Alfaskop/Alfaskop-kommunikationsenhet-4101.pdf)

![CPR4101 internal](https://github.com/MattisLind/alfaskop_emu/raw/master/pics/CPR4101_internal_small.png)

## Hardware

![Hardware list](https://github.com/MattisLind/alfaskop_emu/raw/master/hardware/CPR4101/CPR4101_HardwareList.jpg)

### CPB board

The CPB board has the main 6800 microprocessor, 32 kbyte of memory, 4 6854 ADLC chips, the 6844 DMA controller chip and provide the
main functionality of the CPR4101. There are one EPROM, two bipolar PROM and two 82S100 type PLA on the board

| IC location |  Component      |Type |  File |
|-------------|-----------------|-----|-------|
|     IC24    |Fairchild 93459DC|PLA  |[E3405970032100](https://github.com/MattisLind/alfaskop_emu/raw/master/hardware/CPR4101/CPB_E34060_0010_IC24_E3405970032100_Fairchild_93459DC.bin)|
|     IC36    |Fairchild 93459DC|PLA  |[E3405970013600](https://github.com/MattisLind/alfaskop_emu/raw/master/hardware/CPR4101/CPB_E34060_0010_IC36_E3405970013600_Fairchild_93459DC.bin)|
|   IC43      |Signetics N82S126N| PROM|[E3405972144300](https://github.com/MattisLind/alfaskop_emu/raw/master/hardware/CPR4101/CPB_E34060_0010_IC43_E3405972144300_Signetics_N82S126N.bin)|
|   IC47      |Fujitsu MBM2716  |PROM |[E3405870034703](https://github.com/MattisLind/alfaskop_emu/raw/master/hardware/CPR4101/CPB_E34060_0010_IC47_E3405870034703_Fujitsu_MBM2716.bin)|
|    IC70     |MMI 6330-1J    |  EPROM| [E3405970027001](https://github.com/MattisLind/alfaskop_emu/raw/master/hardware/CPR4101/CPB_E34060_0010_IC70_E3405970027001_MMI_6330-1J.bin)| 


#### Component side

![CPB board component side](https://github.com/MattisLind/alfaskop_emu/raw/master/hardware/CPR4101/CPB_E34060_0010_ComponentSide.jpg)

#### Solder side

![CPB board solder side](https://github.com/MattisLind/alfaskop_emu/raw/master/hardware/CPR4101/CPB_E34060_0010_SolderSide.jpg)



### MRW-A board

The MRW-A board has 32 kbyte expansion memory. There are one 16 16 kbit DRAM memory chips and some logic on this board. There is one PROM.

| IC location |  Component      | Type|  File |
|-------------|-----------------|-----|-------|
|     IC2    |NS DM74S387N |PROM  |[E3405970320200](https://github.com/MattisLind/alfaskop_emu/raw/master/hardware/CPR4101/MRW-A_E34191_0010_IC2_E3405970320200_NS_DM74S387N.bin)|

#### Component side

![MRW-A board component side](https://github.com/MattisLind/alfaskop_emu/raw/master/hardware/CPR4101/MRW-A_E34191_0010_ComponentSide.jpg)

#### Solder side

![MRW-A board solder side](https://github.com/MattisLind/alfaskop_emu/raw/master/hardware/CPR4101/MRW-A_E34191_0010_SolderSide.jpg)


### SCA board

The SCA board implements the interface to the host. Either this can be using the 6854 ADLC chip or the 6852 SSDA chip. The latter is for implementing the IBM BSC protocols. One port is V.24 the other is X.21.

| IC location |  Component      | Type|  File |
|-------------|-----------------|-----|-------|
|     IC1    |NS DM74S387N |PROM  |[E3405970230100](https://github.com/MattisLind/alfaskop_emu/raw/master/hardware/CPR4101/SCA_E34194_0000_IC1_E3405970230100_Harris_MI-7602-5.bin)|

#### Component side

![SCA board component side](https://github.com/MattisLind/alfaskop_emu/raw/master/hardware/CPR4101/SCA_E34194_0000_ComponentSide.jpg)

#### Solder side

![SCA board solder side](https://github.com/MattisLind/alfaskop_emu/raw/master/hardware/CPR4101/SCA_E34194_0000_SolderSide.jpg)

### SCA Cable

![SCA cable tag](https://github.com/MattisLind/alfaskop_emu/raw/master/pics/SCA_cable.jpg)

The SCA cable connects from the SCA board to the DSUB on the sheet metal front inside the CPR unit.

![SCA cable](https://github.com/MattisLind/alfaskop_emu/raw/master/pics/SCA-cable2.jpg)

The SCA board connector has quite peculiar numbering used in the schematic

![SCA connector numbering](https://github.com/MattisLind/alfaskop_emu/raw/master/pics/SCA_connector.jpg)

| DB25 pin |    V.24 function    |SCA connector P11 pin |  SCA board function |
|-------------|-----------------|-----|-------|
|     2    |101 |2  | RD|

The connectors mates with the red dot marking pin 1.

![SCA connector numbering](https://github.com/MattisLind/alfaskop_emu/raw/master/pics/SCA-connector2.jpg)

### TAB board

The TAB board has four independent SS3 MODEMs that extracts the emedded clock signal and the data. They synchrnizes the clock to the remot sender. It connects to the CPB boards and up to foru TUA boards. The PROM on the TAB board are identical to the one found on the TIA board and no dump is taken on the PROM chip on this board.

#### Component side

![TAB board component side](https://github.com/MattisLind/alfaskop_emu/raw/master/hardware/CPR4101/TAB_E34073_0000_ComponentSide.jpg)

#### Solder side

![TAB board solder side](https://github.com/MattisLind/alfaskop_emu/raw/master/hardware/CPR4101/TAB_E34073_0000_SolderSide.jpg)


### TUA board

The TUA board contain the interfacing hardware to conect to the SS3 network. It also contain the cross connect chip that allow communication between ports. It interfaces to the TAB board. 

#### Component side

![TUA board component side](https://github.com/MattisLind/alfaskop_emu/raw/master/hardware/CPR4101/TUA_E34181_0001_ComponentSide.jpg)

#### Solder side

![TUA board solder side](https://github.com/MattisLind/alfaskop_emu/raw/master/hardware/CPR4101/TUA_E34181_0001_SolderSide.jpg)


### UPB

The UPB board is the power supply of the CPR4101. The RIFA MP capacitors has been changed since these are prone to crack and explode with a lot of black smoke.

#### Component side

![UPB board component side](https://github.com/MattisLind/alfaskop_emu/raw/master/hardware/CPR4101/UPB_E34068_0011_ComponentSide.jpg)

#### Solder side

![UPB board solder side](https://github.com/MattisLind/alfaskop_emu/raw/master/hardware/CPR4101/UPB_E34068_0011_SolderSide.jpg)

## Restoration

Of course a lot of dust has gathered throughout the years operation so a thorough cleaning was the first thing to do. While tearing the unit appart there were appearant that one of the TUA board had suffered from an exploding and burning tantalum capacitor. In this case not just the capacitor was bad but portion of the edge of the card was severly damaged as well as several adajacent components. It was decided that the system was to be run using one TUA card.

![Burnt tanbtalum capacitor](https://github.com/MattisLind/alfaskop_emu/raw/master/pics/BurntTantalumCapacitor.jpg)


Then when testing the power supply under load, 10A on the 5V, 0.8 A on the +12 and -12V, it was recognized that it sounded unhealty and the voltages never reached the spec.

![Bad capacitors](https://github.com/MattisLind/alfaskop_emu/raw/master/pics/BadCapacitor.jpg)

A couple of capacitors where the suspects and one of them measured bad and was replaced.

After all this and putting the system together it started up without any tantalum capacitor explosions and one of the LEDs started to blink after a while indicating that it tried to boot from the floppy over the SS3 network.
