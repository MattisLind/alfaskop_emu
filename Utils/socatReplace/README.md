# socatReplace

I had tremendous problems whenever I tried to use socat utilty to bridge between a serial port and a TCP connection. All off them very different from run to run. Sometimes it simply stopped receiving data from ths TCP connection. Although the remote program logged that data has been sent nothing was received. On other instances completely weird data was received on the serial port which mostly looked like the data that was just sent to over the serial port. All this together with the fact that it terms of code this is quite simple caused me to write my own socat replacement.

It takes a set of options to configure which serial port and which baudrate and then what host to connect to and what port to use.


