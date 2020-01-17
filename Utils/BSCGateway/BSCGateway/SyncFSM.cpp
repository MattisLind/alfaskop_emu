/*

SyncFSM.cpp 

Handles finding the sync position. When in sync it will dispatch the receivedSyncData for each character received. Typically
used by the message FSM.
 
The Sync FSM has two states, Hunt state and Sync state. When in Hunt state it will search for the BSC SYNC characters, SYN SYN, 0x32 0x32.

*/


#include "SyncFSM.h"

// Construtcor taks as argument a callback to call when sync is established and valid data is received

SyncFSM::SyncFSM(void (*recivedSyncData)(unsigned char)) {
  cb = receivedSyncData;
  dataWord = 0xffffffff;
  syncState = HUNT; 
}

// Is called by the data receiver 

SyncFSM::receivedData(unsigned char read) {
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
      rxState = SYNC; // We have found sync
    }
  }
  else {
    data = translationArray[0xff & (dataWord >> syncPoint)];
    cb (data);
  } 
} 

// Routine to tell the Sync FSM to enter Hunt state

SyncFSM::enterHuntState() {
  syncState = HUNT;
}
