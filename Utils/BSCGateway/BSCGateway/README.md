# STM32 BSC interface

## Overall design

The code consists of a main .ino sketch and three C++ classes SyncFSM, MessageFSM and RingBuffer. 

The .ino files has an interrrupt driven SPI routine that continously receives and transmits data. The SPI is configured to act in slave mode
and is clocked bye a PWM output at 9600 bps. The configuration is that MSB bit is sent first on the line. Mor on that later.

### Rx path

When a interrupt occur the receving part will read byte of the SPI and forward it to the SyncFSM. The Sync FSM class put the byte
into a software shiftregister. It will loop through trying to shift the contents 0 to 7 steps to see if it can get a match with
the sync pattern. If it gets a match then the FSM will enter SYNC mode starting to forward characters until a the method enterHuntState is called.

The MessageFSM will then receive the characters and process them so understand what kind of message was received. A callback is called
with a message type and a paramter if applicable.

The The callback will then serialize data into messages sent over a standard async serial line to the host which can be a PC
or a ESP32 board.


### Protocol

The protocol on this line is specified below:

All commands start with a command letter which are in the range G to Z. A command is terminated with a single newline.


|  Command      |  Description                            |  Parameters                             |
|---------------|-----------------------------------------|-----------------------------------------|
|    G          |  Request handshake line status report   |                                         |
|    H          |  Set or reset specifiec hand shake line |  R0 RFS=0, R1 RFS=1                     |
|    I          |  Handshake signals changed              |  C0 CTS=0  C1 CTS=1, D0 DTR=0, D1 DTR=1 |
|    Q          |  EOT message                            |                                         |
|    P          |  ENQ message                            |  Two hex digits CU, DV. e.g P4040       |
|    S          |  Status message                         |  Four hex digits CU, DV, Status, sense  |
|    X          |  Test request message                   |  Hex digits                             |
|    T          |  Text message                           |  Hex digits                             |
|    L          |  ACK0 message                           |                                         |
|    M          |  ACK1 message                           |                                         |
|    W          |  WACK message                           |                                         |
|    R          |  RVI message                            |                                         |
|    N          |  NAK message                            |                                         |
