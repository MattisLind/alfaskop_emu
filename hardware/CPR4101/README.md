# CPR4101 Hardware and firmware

The CPR4101 is a 60 x 40 x 40 cm box. It has an internal chassis made out of sheet metal which is housed in a brown/beige plastic housing.
In the chasssis there is a CPB board which has the main microprocessor, then there is a TAB board which has slots for SS3 communication ports on TUA boards.
In addition to this there is a extension MRW-A board which has 32 kbyte of memory and a SCA board for communication with the host.

## CPB board

### Component side

![CPB board component side](https://github.com/MattisLind/alfaskop_emu/raw/master/hardware/CPR4101/CPB_E34060_0010_ComponentSide.jpg)

### Solder side

![CPB board solder side](https://github.com/MattisLind/alfaskop_emu/raw/master/hardware/CPR4101/CPB_E34060_0010_SolderSide.jpg)

The CPB board has the main 6800 microprocessor, 32 kbyte of memory, 4 6854 ADLC chips, the 6844 DMA controller chip and provide the
main functionality of the CPR4101. There are one EPROM, two bipolar PROM and two 82S100 type PLA on the board

| IC location |  Component      |     |  File |
|-------------|-----------------|-----|-------|
|     IC24    |Fairchild 93459DC|PLA  |[E3405970032100](https://github.com/MattisLind/alfaskop_emu/raw/master/hardware/CPR4101/CPB_E34060_0010_IC24_E3405970032100_Fairchild_93459DC.bin)|
|     IC36    |Fairchild 93459DC|PLA  |[E3405970013600](https://github.com/MattisLind/alfaskop_emu/raw/master/hardware/CPR4101/CPB_E34060_0010_IC36_E3405970013600_Fairchild_93459DC.bin)|
|   IC43      |Signetics N82S126N| PROM|[E3405972144300](https://github.com/MattisLind/alfaskop_emu/raw/master/hardware/CPR4101/CPB_E34060_0010_IC43_E3405972144300_Signetics_N82S126N.bin)|
|   IC47      |Fujitsu MBM2716  |PROM |[E3405870034703](https://github.com/MattisLind/alfaskop_emu/raw/master/hardware/CPR4101/CPB_E34060_0010_IC47_E3405870034703_Fujitsu_MBM2716.bin)|
|    IC70     |MMI 6330-1J    |  EPROM| [E3405970027001](https://github.com/MattisLind/alfaskop_emu/raw/master/hardware/CPR4101/CPB_E34060_0010_IC70_E3405970027001_MMI_6330-1J.bin)| 


## MRW-A board

The MRW-A board has 32 kbyte expansion memory. There are one 16 16 kbit DRAM memory chips and some logic on this board. There is one PROM.

### Component side

![MRW-A board component side](https://github.com/MattisLind/alfaskop_emu/raw/master/hardware/CPR4101/MRW-A_E34191_0010_ComponentSide.jpg)

### Solder side

![MRW-A board solder side](https://github.com/MattisLind/alfaskop_emu/raw/master/hardware/CPR4101/MRW-A_E34191_0010_SolderSide.jpg)


## SCA board

The SCA board implements the interface to the host. Either this can be using the 6854 ADLC chip or the 6852 SSDA chip. The latter is for implementing the IBM BSC protocols. One port is V.24 the other is X.21.

### Component side

![SCA board component side](https://github.com/MattisLind/alfaskop_emu/raw/master/hardware/CPR4101/SCA_E34194_0000_ComponentSide.jpg)

### Solder side

![SCA board solder side](https://github.com/MattisLind/alfaskop_emu/raw/master/hardware/CPR4101/SCA_E34194_0000_SolderSide.jpg)


## TAB board

### Component side

![TAB board component side](https://github.com/MattisLind/alfaskop_emu/raw/master/hardware/CPR4101/TAB_E34073_0000_ComponentSide.jpg)

### Solder side

![TAB board solder side](https://github.com/MattisLind/alfaskop_emu/raw/master/hardware/CPR4101/TAB_E34073_0000_SolderSide.jpg)


## TUA board

Component side

![TUA board component side](https://github.com/MattisLind/alfaskop_emu/raw/master/hardware/CPR4101/TUA_E34181_0001_ComponentSide.jpg)

Solder side

![TUA board solder side](https://github.com/MattisLind/alfaskop_emu/raw/master/hardware/CPR4101/TUA_E34181_0001_SolderSide.jpg)


## UPB

Component side

![UPB board component side](https://github.com/MattisLind/alfaskop_emu/raw/master/hardware/CPR4101/UPB_E34068_0011_ComponentSide.jpg)

Solder side

![UPB board solder side](https://github.com/MattisLind/alfaskop_emu/raw/master/hardware/CPR4101/UPB_E34068_0011_SolderSide.jpg)