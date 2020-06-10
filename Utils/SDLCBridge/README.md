# SDLC bridge

This is an attemmpt to interface a Informer 213, a portable 3178 compatible terminal with integrated 3274 comatible cluster controller, to the Hercules mainframe emulator.
This terminal needs a SDLC compatible interface. This project also discusses how to create the relevnat configuration in the MVS / VTAM environment
to achieve this and what changed is needed to the comm3705 module in Hercules.

![Informer 213](https://i.imgur.com/M9zcy7E.png)

## Links

### SNA

* [SNA Introduction to Sessions Between Logical Units](http://bitsavers.trailing-edge.com/pdf/ibm/sna/GC20-1869-2_SNA_Introduction_to_Sessions_Between_Logical_Units_Dec79.pdf)
* [Systems Network Architecture Reference Summary](http://www.bitsavers.org/pdf/ibm/sna/GA27-3136-2_Systems_Network_Architecture_Reference_Summary_Oct78.pdf)
### VTAM
* [Introduction to VTAM](http://www.bitsavers.org/pdf/ibm/sna/vtam/GC27-6987-5_Introduction_to_VTAM_Apr76.pdf)
* [VTAM Macro Langauge Reference](http://www.bitsavers.org/pdf/ibm/sna/vtam/GC27-6995-2_VTAM_Macro_Language_Reference_Dec74.pdf)
* [System Programming Library: VTAM](http://www.prycroft6.com.au/misc/download/GC28-0688-2_SPL_VTAM_Level2_Dec77OCR.pdf)
* [VTAM Concepts and Planning](http://bitsavers.informatik.uni-stuttgart.de/pdf/ibm/sna/vtam/GC27-6998-2_VTAM_Concepts_and_Planning_Aug75.pdf)
### SDLC
* [SDLC General Information](http://bitsavers.informatik.uni-stuttgart.de/pdf/ibm/datacomm/GA27-3093-2_SDLC_General_Information_Mar79.pdf)
* [SDLC Concepts](http://bitsavers.informatik.uni-stuttgart.de/pdf/ibm/datacomm/GA27-3093-3_SDLC_Concepts_Jun86.pdf)

### Other
* [Matt Burke's work on DSLw to interconnect SNA / SDLC](https://www.9track.net/hercules/dlsw/)
* [SNA / SDLC quick guide by Clif Anderson](https://www.cliffa1994.com/snasteps.htm)
* [SDLC overview](https://www.euclideanspace.com/coms/protocol/sdlc/index.htm)
* [VTAM/NCP Node Definition Example](http://ps-2.kev009.com/tl/techlib/manuals/adoclib/3270hcon/hconugd/definvta.htm)
* [Course on SNA / VTAM](http://bitsavers.informatik.uni-stuttgart.de/pdf/ibm/sna/Kaptronix_SNA.pdf)
