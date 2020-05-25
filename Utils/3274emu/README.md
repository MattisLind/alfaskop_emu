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
![](https://github.com/MattisLind/alfaskop_emu/raw/master/pics/LoginInProgress.png)

TSO greeting screen:
![](https://github.com/MattisLind/alfaskop_emu/raw/master/pics/TSO.png)
