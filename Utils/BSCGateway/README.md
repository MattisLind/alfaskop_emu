# BSCGateway

Here is several experiments for interfacing a BSC cluster to Hercules. Much of the code is informational only or work in progress.

## BSCBridge

This is the the taregt solution for the interfacing the Alfaskop cluster using IBM BSC to the 2703 emulation in Hercules.


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

