# Hercules Integration

The intention is to get the Alfaskop terminal up and running with the Hercules IBM mainframe emulator. What was the best way to interface a 3270 terminal to Hercules. The obvious answer would be over TN3270. But is it the best solution. Not necessarily.

Making it TN3270 compatible is a some what over engineered solution. It creates a need to full application layer suppport for the 3270 BSC protocol so that the 3270 data stream can be sent over it. 

Originally an IBM mainframe used a 2703 or possible a 3705 Telecommunication Control Unit (TCU) for communicaating with remote cluster controllers over BSC. Inside Hercules there were already support for emulating the 2703 and also did it support BSC which what is needed here.

The question was then how to make the guest operating system in Hercules, fo example MVS 3.8 aware of the terminal and the cluster controller. It turns out that for getting a 3270 terminal connected to the Time Sharing Option inside the MVS OS one need to configure TCAM. TCAM is handling the processing of BSC messages between TSO and the terminal.

So one need to create a MCP (Message Control Program) targeted for TSO. This program is called TSOMCP. TSOMCP is built using a bunch of macro directives that sets what lines this MCP shall handle. The build file itself is a JCL job file that need to be siubmitted to JES. The output is TSOMCP.


 