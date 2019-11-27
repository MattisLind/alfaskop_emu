#Firmware and picture of the boards

Here are all the dumped EPROMS, bipolar PROMS for character generator, Bipolar PROMs for decoding and other uses, 82S100 FPLA and 14H4 PAL.

The dumps of the programmable logic is a bit strange since they are binry files. Essentially they consist of an 8 byte header and then the fuse data and finally a one byte trailer.

For the 82S100 the layout of the fuses are as follows.
The first 1280 fuses are grouped in 48 lines of 40 fuses each. Each row is corresponding to each of the product terms of the PLA. First there are 
32 fuses corresponding to the non-inverted and inverted inputs pairs. 16 inputs. The following 8 bits are the 8 or-terms corresponding to the 
8 outputs.

Finally there is one single byte for the output XOR gates of the 82S100.

