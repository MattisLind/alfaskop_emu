# BSCBridge

Some more detailed resarch into this has given that it should be possible to interface towards Hercules and allow a TSO login using the older access method called TCAM and using the 2703 emulation inside Hercules. This emulation has support for BSC and tests has been done using a test client to prove it might be a path to be pursued. See [herculesIntegration](https://github.com/MattisLind/alfaskop_emu/tree/master/Utils/HerculesIntegration) for more info.

Please note that transparent mode is currently NOT supported.

## Proposed architecture 

![Architecture](https://github.com/MattisLind/alfaskop_emu/raw/master/pics/Architecture.jpg)

The SyncFSM has two states. Either HUNT state or SYNC state. When in SYNC state it continuously searches for a valid sync pattern which is SYN SYN, 0x32 0x32. When it finds this pattern it will enter the SYNC state and forward all received characters (including the received SYN characters) to the upper layer. The upper layer is the MessageFSM class which receives the characters from SyncFSM and tries to decode the various valid BSC messages. As soon as a it received a valid message it will forward it to its upper layer and also request the SyncFSM to reenter HUNT mode so that it is prepared to get the next message.

The main module or glue logic is the mediator between the MessageFSM towards the terminal cluster and the MessageFSM connected to the host. These two MessageFSM hare essentially the same but instatiated differently, one in Hercules mode and one in normal mode.
The difference is that in Hercules mode no SYN characters are sent and required when receiving, neither is any PAD characters required or sent. The CRC bytes are sent and received but the CRC calculation is dsiregareded from.

~~Whenever a message comes from the hercules facing MessageFSM main glue logic will make sure to negate the CTS signal and then wait for the remote end to negate the CTS signal. When a negated CTS is seen the message will be forwarded to the cluster controller facing MessageFSM for transmissions. Now the remote end will assert RTS and the glue code will assert CTS as soon as it sees the RTS.~~ The previous statement has been deemed unecessary and will not be implemented for now.

When the cluster controller facing SyncFSM and MessagesFSM receives the message it will be syncronized and moved to the Hercules facing MessageFSM for transmission.

Transmission is taking place as a polled state machine. Whenever there is space on the output buffers the transmission state machine is polled. Depending if there is a stored message it will then step by step process the outbound message. Each poll will result in that at most one byte is transfered to the output buffer. The reason for this polling approach is that there were evidence that the output buffer were overwhelmed when the transmission burst was occuring and it was not feasible to increase buffers to cope with this.

## Perfomance measurements

It is important to understand how much time each of the processing tasks take when processing messages. There are four tasks in the main loop. 

1. Process Rx byte from BSC line.
2. Poll Tx state machine for data going to BSC line.
3. Process Rx byte from host.
4. Poll Tx state machine for data going to host.

As BSC is half duplex by design and then that a message is recived, buffered and then transmitted means that at most one task can be active at a time. At other times very little processing is spent in the task. As there are certain buffering  som jitter in terms of processing time is allowed, but it is important to make sure that the speed is not making the buffers grow over time.

It would be interesting to pin-point if there is a task that takes substantially much more of CPU processing and if optimizations can be done to lower this.

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

I had some problems when dealing with socat which I initially attributed to be due to socat itself. It resulted in that I created a socat replacement, socatReplace in the utils folder in this project. It turned out that I could run into exactly the same problem using my new socatReplace and that I got problems with two FTDI dongles simultaneously even using minicom! The problem is solved by pulling the USB plug out and reinsert it. It seems that the driver ends up in a strange state if the system is booted with the FTDI dongles inserted while booting.

## Testing with 3274emu and x3270
A test of the system would be to connect two SyncDongles together with a null modem and have them exchange some data. I created a quick test suite in the test folder that did exactly this and since this was successful I continued to use the same link to connect the 3274emu.

This means that the chain looks like this:
```
x3270 (TN3270 client)   <=> 3274emu (TN3270 to BSC) <=> socatReplace (in server mode) <=> SyncDongle <=> null modem <=> SyncDongle <=> socatReplace (client) <=> Hercules
```

![Testing with 3274emu](https://i.imgur.com/BN3FohD.jpg)

At least that it is possible to start the REVIEW editor and it looks ok. I now consider the BSCBridge in BETA state. There are probably things lurking there but it can be made working. Remember that the RTO paramter of the 2703 device must be set to a higher value since the baudrate is quite low. I have tried 20000 (20 seconds) and it seems ok.

I also use a 10 seconds poll interval right now and just one terminal configured in TCAM since it is much easier to debug things then.



## Installation

![Arduino Env](https://i.imgur.com/gjirQPa.png)

This software uses the Arduino development environment and the Arduino_STM32 framework by Roger Clark which can be found here: [Arduino_STM32](https://github.com/rogerclarkmelbourne/Arduino_STM32). Make sure to [install](https://github.com/rogerclarkmelbourne/Arduino_STM32/wiki/Installation) this framwork in the correct place and select the Generic STM32F103 board as the target. I always use a ST-LINK JTAG dongle for download and have not tried any other download mechanism or bootloader although there is one for Serial port builtin in which might be used.

