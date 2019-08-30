# alfaskop_emu
This project aims to make a Alfaskop 4110 running towards the Hercules IBM emulator and run the MEMO SW.

The Alfaskop terminal was a big success for the early Swedishg IT industry. In total 900 000 units were delivered world wide.
More information about the Alfaskop Series 41, marketing material and technical documents can be found [here.](http://www.datormuseum.se/peripherals/terminals/alfaskop)

There are today not one single Alfaskop Series 41 terminal that is able to run and show what is was like. The root cause
is that the system as a whole  is quite complex. The system 41 terminal of Diaplay Unit (DU) requires a communication processor 
and a floppy drive (FD) to be able to run. It also has no software built in but loads this from the cluster.

The system software diskette 4016 has been found at Dansk Datahistorisk Förening. This disk has origninally been with SAS. People there will make an image dump of this disk
and provide it to use.

The basic idea is to use MAME to emulate the CP and the FD. All technical documentation and schematics are available and is scanned.

![Alfaskop in MAME](https://i.imgur.com/yO6jXmll.png)

Lacking is the IPL BOOT ROM of the real hardware unless DDHF happens to have a CP4101 and FD4120 in their possession.

To communicate between the various entities of the cluster a TCP variant of the two wire bus will be created eumlating the 32 ports of the 
CP. To interface to the real Alfaskop DU 4110 a two-wire bus to TCP bridge will be created. In the first implementation it will
use an Ericsson TWIB PC board connected to a small uController and a Raspberry Pi Zero W.

![Two wire connector](https://i.imgur.com/YzAfB2gl.png)


