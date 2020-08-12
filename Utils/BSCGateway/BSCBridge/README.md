# BSCBridge

Some more detailed resarch into this has given that it should be possible to interface towards Hercules and allow a TSO login using the older access method called TCAM and using the 2703 emulation inside Hercules. This emulation has support for BSC and tests has been done using a test client to prove it might be a path to be pursued. See [herculesIntegration](https://github.com/MattisLind/alfaskop_emu/tree/master/Utils/HerculesIntegration) for more info.

## Proposed architecture 

![Architecture](https://github.com/MattisLind/alfaskop_emu/raw/master/pics/Architecture.jpg)

The SyncFSM has two states. Either HUNT state or SYNC state. When in SYNC state it continuously searches for a valid sync pattern which is SYN SYN, 0x32 0x32. When it finds this pattern it will enter the SYNC state and forward all received characters (including the received SYN characters) to the upper layer. The upper layer is the MessageFSM class which receives the characters from SyncFSM and tries to decode the various valid BSC messages. As soon as a it received a valid message it will forward it to its upper layer and also request the SyncFSM to reenter HUNT mode so that it is prepared to get the next message.

The main module or glue logic is the mediator between the MessageFSM towards the terminal cluster and the MessageFSM connected to the host. These two MessageFSM hare essentially the same but instatiated differently, one in Hercules mode and one in normal mode.
The difference is that in Hercules mode no SYN characters are sent and required when receiving, neither is any PAD characters required or sent. The CRC bytes are sent and received but the CRC calculation is dsiregareded from.

Whenever a message comes from the hercules facing MessageFSM main glue logic will make sure to negate the CTS signal and then wait for the remote end to negate the CTS signal. When a negated CTS is seen the message will be forwarded to the cluster controller facing MessageFSM for transmissions. Now the remote end will assert RTS and the glue code will assert CTS as soon as it sees the RTS. When the cluster controller facing SyncFSM and MessagesFSM receives the message it will be syncronized and moved to the Hercules facing MessageFSM for transmission.

## Implementation

The BSCBridge is implemented in a STM32F103 Blue Pill.

![BSCBridge in a STM32F103 Blue Pill](https://github.com/MattisLind/alfaskop_emu/raw/master/pics/BSCGateway.jpg)

The board has one DB-25 for connecting to the BSC Synchronous line to the cluster controller and a DE-09 for connecting to the host.
On board there are two MAX 202CPE level translators so that the proper EIA RS-232-C / CCITT V.24/V.28 levels are maintained.

![Schematic](https://github.com/MattisLind/alfaskop_emu/raw/master/pics/BSCGateway-schematic.png)

DE-09 connectin to host

| Signal | Pin |
|--------|-----|
| TXD    | PA9 |
| RXD    | PA10|

DB-25 connecting to cluster controller

| Signal |Pin DB-25| Pin STM32 |
|--------|---------|-----------|
| TD     | 2       |       PB15|
| RD     | 3       |       PB14|
| RTS    | 4       |       PB11|
| RFS    | 5       |       PB1 |
| DTR    | 20      |       PB10|
| TSET/RSET| 15/17  |  PA8/PB13|


To properly handle the case where a real modem is connected pins 15 and 17 should be inputs. Since the design only have one clock signal input which is used for bothRx and Tx there should be a jumper selecting which input to use. 

Pin 24 can then be jumpered to provide a clock signal. If a null-modem is used this can the jumper from one of the inputs on pin 24 to pin 15 and 17.  

## SOCAT

A proper socat command for
```
sudo socat  TCP:localhost:32701 OPEN:/dev/ttyUSB0,b2400,raw
```

## Installation
This software uses the Arduino development environment and the Arduino_STM32 framework by Roger Clark which can be found here: [Arduino_STM32](https://github.com/rogerclarkmelbourne/Arduino_STM32). Make sure to [install](https://github.com/rogerclarkmelbourne/Arduino_STM32/wiki/Installation) this framwork in the correct place and select the Generic STM32F103 board as the target. I always use a ST-LINK JTAG dongle for download and have not tried any other download mechanism or bootloader although there is one for Serial port builtin in which might be used.
