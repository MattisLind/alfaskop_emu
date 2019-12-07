### MC6846 Readout.

Unfortunately it was impossible to read the MC6846 using any of my standard EPROM programmers. I had to resort to hook up a STM32 Blue Pill
and a 74LVC245 level translator.

I wrote a small program on the STM32 that read the entire 2048 bytes ROM memory out as text dumped over the serial / USB port.
Then a small C program on the Linux host converted it to binary.

![Blue pill and MC6846 hookup](../pics/mc6846readout.jpg)
