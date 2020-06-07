# SDLC bridge

This is an attemmpt to interface a Informer 213, a portable 3178 compatible terminal with integrated 3274 comatible cluster controller, to the Hercules mainframe emulator.
This terminal needs a SDLC compatible interface. This project also discusses how to create the relevnat configuration in the MVS / VTAM environment
to achieve this and what changed is needed to the comm3705 module in Hercules.

![Informer 213](https://i.imgur.com/M9zcy7E.png)

# Links
* [Introdcution to VTAM](http://www.bitsavers.org/pdf/ibm/sna/vtam/GC27-6987-5_Introduction_to_VTAM_Apr76.pdf)
* [SNA Introduction to Sessions Between Logical Units](http://bitsavers.trailing-edge.com/pdf/ibm/sna/GC20-1869-2_SNA_Introduction_to_Sessions_Between_Logical_Units_Dec79.pdf)
* [VTAM Macro Langauge Reference](http://www.bitsavers.org/pdf/ibm/sna/vtam/GC27-6995-2_VTAM_Macro_Language_Reference_Dec74.pdf)
