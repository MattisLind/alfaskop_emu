# BSCgateway

Some more detailed resarch into this has given that it should be possible to interface towards Hercules and allow a TSO login using the older access method called TCAM and using the 2703 emulation inside Hercules. This emulation has support for BSC and tests has been done using a test client to prove it might be a path to be pursued. See [herculesIntegration](https://github.com/MattisLind/alfaskop_emu/tree/master/Utils/HerculesIntegration) for more info.

## Proposed architecture 

![Architecture](https://github.com/MattisLind/alfaskop_emu/raw/master/pics/Architecture.jpg)

The SyncFSM has two states. Either HUNT state or SYNC state. When in SYNC state it continuously searches for a valid sync pattern which is SYN SYN, 0x32 0x32. When it finds this pattern it will enter the SYNC state and forward all received characters (including the received SYN characters) to the upper layer. The upper layer is the MessageFSM class which receives the characters from SyncFSM and tries to decode the various valid BSC messages. As soon as a it received a valid message it will forward it to its upper layer and also request the SyncFSM to reenter HUNT mode so that it is prepared to get the next message.

The main module or glue logic is the mediator between the MessageFSM towards the terminal cluster and the MessageFSM connected to the host. These two MessageFSM hare essentially the same but instatiated differently, one in Hercules mode and one in normal mode.
The difference is that in Hercules mode no SYN characters are sent and required when receiving, neither is any PAD characters required or sent. The CRC bytes are sent and received but the CRC calculation is dsiregareded from.

Whenever a message comes from the hercules facing MessageFSM main glue logic will make sure to negate the CTS signal and then wait for the remote end to negate the CTS signal. When a negated CTS is seen the message will be forwarded to the cluster controller facing MessageFSM for transmissions. Now the remote end will assert RTS and the glue code will assert CTS as soon as it sees the RTS. When the cluster controller facing SyncFSM and MessagesFSM receives the message it will be syncronized and moved to the Hercules facing MessageFSM for transmission.


##  Deprecated and informational only - TN3270 protocol

The TN3270 protocol carry the 3270 Data stream over a standard telnet connection. To be able to do this it negotaites a couple of capabilitites 
at startup.

## Wireshark dumps.

Two Wireshark traces were taken. The pictures below is from the standard data stream. The traces are stored in the dumps folder.

![Data from host](https://raw.githubusercontent.com/MattisLind/alfaskop_emu/master/pics/TN3270_Extended_data_stream_from_host.png)

![Data from host](https://raw.githubusercontent.com/MattisLind/alfaskop_emu/master/pics/TN3270_Extended_data_to_host.png)

## Telnet handshake

Terminal type : IBM-3278-2
End of record 
Binary transmission


End of record used is 0xFF 0xEF

