## Reverse engineer the TWIB board

![TWIB board](https://github.com/MattisLind/alfaskop_emu/raw/master/pics/TWIB_ComponentSide.jpg)

In an attempt to interface to the SS3 bus the easiest was to actually reuse one of the Ericsson made TWIB PC-bus boards that happened to be available. The board is very simple and has just the Intel 8274 HDLC chip and some adress decoding as well as DMA and interrupt logic. Apart for that there is also a twin wire MODEM circuitry including the Ferranti ULA.

First step of the reverse engineering was to layout the schematic identical to the board layout and trace out all connections using a ohm-meeter.
![Step 1](https://github.com/MattisLind/alfaskop_emu/raw/master/pics/TWIB_reverse_engineer_step1.png)

Then a new schematic was done based on the actual functions of the board. Adress decoding, Two-wire modem, DIPSWitches bus driver, 8274 chip etc.

![Step 2](https://github.com/MattisLind/alfaskop_emu/raw/master/pics/TWIB_reverse_engineer_tidyup.png)


The outcome gave that the adress bus is only partly decoded. Only address A0-A10 is used. Adress A4-A10 is compared with the switch settings. Adress A0 and A1 is connected to the 8274 chip via a couple of AND gates that allow for DMA operations. A2 high enable the DIPSW onto the bus and A3 high enable the 8274 on the bus. The signal AEN need to be high for the card to be selected. The signals IOR and IOW tell the board if there is a Read or Write operation taking place. RESET sigal will reset the 8274 and the modem chip.  The 8274 need a clock signal which is less than 4 MHz which is derived form the PC BUS 4.77 MHz clock signal which is divided by two in a 74S74 chip.

The intention is to connect a STM32 uController to the board and interface it with the D0-D7 signals, A0 and A1 signals, IOR and IOW signals and the RESET signal. A10-A4 are all set to low and the corresponding DIP switches are set accordingly. A3 is set high and A2 is set low. A small clock oscillator circuit is used to create a signal which is lower than 8 MHz.


### Spare secondary channel

The TWIB board has a unpopulated header with 26 pins which presuambly should be connected to a DB25 connector. There are space for a 1488 driver  (IC13) and a 1489 receiver (IC16). Connections with the 8274 is not included in the schematic above.

| 8274 pin    |  8274 function         | 8274 direction | IC16 pin|  IC13 pin | 26 pin header pin |
|-------------|------------------------|--------|------------------|---------------------|--------|
|     4       |  /RxCB               | in    |        11         |                   |  17 |
|     5       |  /CDb               | in    |        6         |                   |  W2:pin 7 |
|     6       |  /CTSb               | in    |        8         |                   |  5 |
|     7       |  /TxCb               | in    |        11         |                   | 17 |
|     8       |  TxDb               | out    |                 |        2           |  2|
|     9       |  RxDb               | in    |        3         |                   | 3 |
|     10       |  /RTSb               | out    |                 |        9           | 4 |
|     20       |  /DTRb               | out    |                 |        6           | 20 |


### Cable between TWIB board and CPR4101 SCA board 

| 26 pin header | DSUB25 in CPR4101|
|---------------|------------------|
|  17           |     24           |
|  W2 pin 7     |     20           |
|  5            |      4           |
|  4            |      5           |
|  2            |      3           |
|  3            |      2           |
|               |     15 to pin 24 |
|               |     17 to pin 24 |

The clock inputs may be using the internal clock but as this is set in software, the best is to jumper them in the connector to get a proper send and receive clock.

### DB25 attached to the TWIB board

|  DB25 pin | 1488/1489 pin | 8274 pin | 8274 Function |
|-----------|---------------|----------|---------------|
|     2     |  1: 1489      |    9     |    RXb        |
|     3     |  3: 1488      |    8     |    TXb        |
|     4     |  10: 1489     |    6     |    CTSb       |
|     5     |  8: 1488      |    10    |    RTSb       |
|     7     |    GND        |          |               |
|     8     |  6:1488       |   26     |    DTRb       |
|    15/17  |  13:1489      |   7,4    |   TXCb / RXCb |
|    20     |  4:1489       |    5     |    CDb        |



