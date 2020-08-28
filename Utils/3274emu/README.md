# 3274 emulator

The 3274 emulator is a quick project to try to make a software replica of the 3274 cluster controller. It connects using the Hercules BSC over TCP protocol to the Hercules host in one end, and in the other end up to 32 TN3270 clients can connect to one port each. Each port maps on to a certain station ID. 

Mostly this is to learn more about av Hecules handles BSC and also learn some things about the 3270 Data Stream.

## Telnet negotiation

The TN3270 client will start off the telnet session by negotiating a couple of parameters, Binary transmission, Use of EOR and terminal type. I recorded the startup phase when a a client is connecting to Hercules just to hav as a reference. This client sends one or two options at time. But it would work equally well to send all om them in one go as it appears. I assume though that the termtype subnegotiation where the client sends the terminal type string has to happen after the client has responded that it will do terminal type.

|   From      |   Data   | Meaning |
|-------------|----------|---------|
|  Server     | FFFD18   |
|  Client     | FFFB18   |
|  Server     | FFFA1801FFF0 |
|  Client     | FFFA180049424D2D333237382D32FFF0|
|  Server     | FFFD19FFFB19 |
|  Client     | FFFB19|
|  Client     | FFFD19 |
|  Server     | FFFD00FFFB00 |
|  Client     | FFFB00 |
|  Client     | FFFD00 |

## BSC
I mostly reused code from the herculesIntegration test project for creating the interface towards Hercules. Some code was needed to move data back and forth and to add certain things that was needed for the client to accept the data. A very simple BSC machine that sent correct type of ACK is in the code as well.

After some debugging it actually started to work so well that I was able to log into the system and be greeted with a TSO prompt. I still have some ABENDs which are likely to be due to some bugs in the code. I noticed for example that TCAM is sending more than 660 bytes even though some documents speicfy that the maximum size of a packet is 254 bytes. Perhaps there is some kind of option when TCAM is built that specify the maximum message size.

Login in progress with messages:
![Login in progress](https://github.com/MattisLind/alfaskop_emu/raw/master/pics/LoginInProgress.png)

TSO greeting screen:
![TSO greeting screen](https://github.com/MattisLind/alfaskop_emu/raw/master/pics/TSO.png)

## Debuging...

Yet more time spent on reading manuals and asking (stuipd) questions on Hercules mailing list. First issue that caused trouble was that the BSC implementation in 2703 and TCAM was not sending CRC and not anticipating it to be sent to it. I sort of know this but had disregaeded from the issus since I thought it worked the way it was. It wasn't. Disabling of CRC in both directions got me much further.

Then I was able to log in, but as soon as I type commands on other lines the the top line of the screen they were misinterpreted by the system. Quite weird. Until I got back and read the 3274 manual again. It clearly stated tha the first text block sent back on the system should include the CU / DV address as the two top bytes. Included that in the response and all worked much, much better.

![REVIEW start screen](https://github.com/MattisLind/alfaskop_emu/raw/master/pics/REVIEW-start.png)
![REVIEW editing screen](https://github.com/MattisLind/alfaskop_emu/raw/master/pics/REVIEW-editing-COBOL.png)

## Hercules bugfixing

As I had been off working on other things I got back to this and found it suddenly failed to work. Strange errors that made communication to break down completely. I re-read various documents and discussed the issu on the H390-hercules mailing list. It looked like the channel program tried to write more than one text block to the line without waiting for an ACK inbetween. Protocol violation? Maybe, but it is hard to be sure so long time later on. Where there specifcation changes that has been introduced in the documentation?

The problem occured when a SELECT operation was initiated by the host, the receiving end responded with an ACK0 to confirm the SELECT. Then the channel program did two separate write operations. The first one did not include a full message, but the sencod write concluded the first text message, but also included a second text message and an EOT at the end. All these data was then transfered to the line. The receiving end would then issue an ACK1 for the first message and then an ACK0 for the second message. Now the channel program sent another text message which looked identical to the last text message in the first transmission, including the trailing EOT. Some sort of re-transmission? Since the receiving end had seen three text message it sent an ACK1 back. Now the channel program became most unhappy and replied with a ENQ message indicating a wrong ACK has been sent! It was expecting an ACK0 instead of an ACK1?

Re-reading the [manual for the 2703 TCU](http://bitsavers.trailing-edge.com/pdf/ibm/2703/GA27-2703-1_2703_Transmission_Ctl_Component_Descr_May67.pdf) again revealed that on page 58 there were a section on how Write operations takes place from the channel program:

```
All data or control characters
that are transmitted to the communications line must
be originated in main storage (except DLE and SYN
when used as time-fill). The Write command will
end as a result of any of the following conditions:
a. An ETX or ETB control character is detected
in the data stream (except in transparent
mode).
b. The 2703 detects common-carrier-equipment
malfunction.
c. Count field in Write CCW is decremented to
zero.
At the end of the Write command, a single pad
character is automatically sent after the last
character of block-check character (bcc) to ensure
that the data set will have time to transmit the last
character before data-set turnaround. 
```

It was quite clear the commadpt.c code inside Hercules did someting wrong since it was not just forwarding the first text message but also the second text message as well as the trailing EOT. It should not do that! It should have stopped at the ETB of the first text block, then waiting for the proper ACK1 to be received.

That also meant that what was looking like a re-transmission was just the actual transmission of text block 2. The one prior was only sent by mistake.

A very simple patch was introduced in the write logic of the commadpt.c to force to stop write as soon as it saw an ETX or ETB when in non transparent mode. The code was tested an indeed solved the problem!

An PR was created towards the Hercules repo: [PR](https://github.com/rbowler/spinhawk/pull/93)

### Running 3274emu

```./3274emu 127.0.0.1 37252 127.0.0.1 32701```

3274emu takes five arguments, four mandatory and one optional. The first two specify the IP address and port of the local server that the 3274emu creats internally to where the TN3274 client attaches. The following two arguments specify the IP address and port for server to which 3274emu connects. That is the Hercules process. The hercules config should include a 2703 device configured using this port.

```0604    2703    lport=32701 lnctl=BSC dial=IN```

This specifies a 2703 in BSC mode at port 32701. If low baudrates are used it can happen that there will be resening taking place in MVS because of lack of response from the remote end. This is beause the 2703 has no knowledge about when the actual bytes has been sent to the remote destination. It just know that data has been sent on the socket which take no time at all. With a read timeout of 20 seconds this problem can be circumvented. Read timeout is specified using the rto option. FOr example rto=20000.


