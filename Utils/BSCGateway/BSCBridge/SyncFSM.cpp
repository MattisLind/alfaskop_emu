/*

SyncFSM.cpp 

Handles finding the sync position. When in sync it will dispatch the receivedSyncData for each character received. Typically
used by the message FSM.
 
The Sync FSM has two states, Hunt state and Sync state. When in Hunt state it will search for the BSC SYNC characters, SYN SYN, 0x32 0x32.

*/

  // Reception is a bit strange since we are not getting the bits on proper byte bounderies we need shift the bits to get them right.
  // In hardware there are a 16 bit shift register that in which the data are clocked in from the line and then matched with the sync sequence.
  // While in software we need to handle it a bit differentlty since we get bits in chunks of bytes.
  // On the serial line the LSB of the byte is transmitted first and thus received first in the receiver. If we use the LSBFIRST setting
  // for the SPI transmitting works great but not reception. The order of the bits on the line would not line up well when the bytes are concatenated in a 16 or 32 bit word
  //
  //  Sequence 0x32 0x32  / SYN SYN
  // 
  //  Bits   0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
  //
  //               0  1  2  3  4  5  6  7   0  1  2  3  4  5  6  7  0  1  2  3  4  5  6  7
  //              
  //         1  1  0  1  0  0  1  1  0  0   0  1  0  0  1  1  0  0  1  1  1  1  1  1  1  1 
  //        First byte shifted in with LSBFIRST   11001011 0xcb
  //        Second Byte                           11001000 0xc8
  //        Third  Byte                           11111100 0xfc
  //        Bits in word is then 
  //        0xcbcafc  = 1 1 0 0 1 0 1 1 1 1 0 0 1 0 0 0 1 1 1 1 1 1 0 0 
  //        The same number of 0 indicate the same pattern, but scrambled. We will never be able to find a matching sequence
  //        And we cannot shift the bits in the processor to find our bits belonging to one byte
  // 
  // This all boils down is to use MSBFIRST since it will fit better with how the shifting takes place in the processor
  //        First Byte shifted with MSB first     11010011 0xb3
  //        Second byte                           00010011 0x13
  //        Third byte                            00111111 0x3f
  //        0xb3133f  = 110100110001001100111111
  // If we then use the LSB converted bit pattern for the sync char (0x3232)  0x4c4c we can easily use shift operations
  // to find the bit in the word where sync is matching.
  //        110100110001001100111111 0xb3133f
  //        111010011000100110011111 0xe9899f
  //        111101001100010011001111 0xf4c4cf
  //        111110100110001001100111 0xfa6267
  //        111111010011000100110011 0xfd3133
  //        111111101001100010011001 0xfe9899
  //        111111110100110001001100 0xff4c4c < MATCH!


#include "SyncFSM.h"

// Construtcor taks as argument a callback to call when sync is established and valid data is received

SyncFSM::SyncFSM(void (*recivedSyncData)(unsigned char)) {
  cb = recivedSyncData;
  dataWord = 0xffffffff;
  syncState = HUNT; 
}

// Is called by the data receiver 

void SyncFSM::receivedData(unsigned char read) {
  int i;
  dataWord = dataWord << 8;  
  dataWord = (0xffffff00 & dataWord) | (0xff & read);
  if (syncState==HUNT) { // Hunting for SYNC
    // Try to find sync
    for (i=0; i<8; i++) {
      if (((dataWord >> i) & 0xffff) == 0x4c4c) {
        syncPoint = i;
        break;
      }
    }
    if (i!= 8) {
      syncState = SYNC; // We have found sync
      cb(SYN);
      cb(SYN);
    }
  }
  else {
    cb(translationArray[0xff & (dataWord >> syncPoint)]);
  } 
} 

// Routine to tell the Sync FSM to enter Hunt state

void SyncFSM::enterHuntState() {
  syncState = HUNT;
}
