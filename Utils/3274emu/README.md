# 3274 emulator

The 3274 emulator is a quick project to try to make a software replica of the 3274 cluster controller. It connects using the Hercules BSC over TCP protocol to the Hercules host in one end, and in the other end up to 32 TN3270 clients can connect to one port each. Each port maps on to a certain station ID. 

Mostly this is to learn more about av Hecules handles BSC and also learn some things about the 3270 Data Stream.

## Telnet negotiation

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
