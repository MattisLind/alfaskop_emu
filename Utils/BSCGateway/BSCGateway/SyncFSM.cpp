/*

SyncFSM.cpp 

Handles finding the sync position. When in sync it will dispatch the receivedSyncData for each character received. Typically
used by the message FSM.
 
The Sync FSM has two states, Hunt state and Sync state. When in Hunt state it will search for the BSC SYNC characters, SYN SYN, 0x32 0x32.

*/


#include "SyncFSM.h"

// Construtcor taks as argument a callback to call when sync is established and valid data is received

SyncFSM::syncFSM(void (*recivedSyncData)(unsigned char)) {

}

// Is called by the data receiver 

SyncFSM::receivedData(unsigned char) {

}

// Routine to tell the Sync FSM to enter Hunt state

SyncFSM::enterHuntState() {

}
