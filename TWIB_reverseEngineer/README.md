## Reverse engineer the TWIB board

![TWIB board](https://github.com/MattisLind/alfaskop_emu/raw/master/pics/TWIB_ComponentSide.jpg)

In an attempt to interface to the SS3 bus the easiest was to actually reuse one of the Ericsson made TWIB PC-bus boards that happened to be available. The board is very simple and has just the Intel 8274 HDLC chip and some adress decoding as well as DMA and interrupt logic. Apart for that there is also a twin wire MODEM circuitry including the Ferranti ULA.

First step of the reverse engineering was to layout the schematic identical to the board layout and trace out all connections using a ohm-meeter.
![Step 1](https://github.com/MattisLind/alfaskop_emu/raw/master/pics/TWIB_reverse_engineer_step1.png)

Then a new schematic was done based on the actual functions of the board. Adress decoding, Two-wire modem, DIPSWitches bus driver, 8274 chip etc.

![Step 2](https://github.com/MattisLind/alfaskop_emu/raw/master/pics/TWIB_reverse_engineer_tidyup.png)


The outcome gave that the adress bus is only partly decoded. Only address A0-A10 is used. Adress A4-A10 is compared with the switch settings. Adress A0 and A1 is connected to the 8274 chip via a couple of AND gates that allow for DMA operations. A2 high enable the DIPSW onto the bus and A3 high enable the 8274 on the bus. The signal AEN need to be high for the card to be selected. The signals IOR and IOW tell the board if there is a Read or Write operation taking place. RESET sigal will reset the 8274 and the modem chip.  The 8274 need a clock signal which is less than 4 MHz which is derived form the PC BUS 4.77 MHz clock signal which is divided by two in a 74S74 chip.

The intention is to connect a STM32 uController to the board and interface it with the D0-D7 signals, A0 and A1 signals, IOR and IOW signals and the RESET signal. A10-A4 are all set to low and the corresponding DIP switches are set accordingly. A3 is set high and A2 is set low. A small clock oscillator circuit is used to create a signal which is lower than 8 MHz.
