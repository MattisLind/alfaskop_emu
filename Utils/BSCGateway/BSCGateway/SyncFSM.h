/*
SyncFSM.h 
Handles finding the sync position. When in sync it will dispatch the receivedSyncData for each character received. Typically
used by the message FSM.
 
The Sync FSM has two states, Hunt state and Sync state. When in Hunt state it will search for the BSC SYNC characters, SYN SYN, 0x32 0x32.
*/


#include "ebcdic.h"
#include "lsbmsb.h"
#define  HUNT 0
#define  SYNC 1

Class SyncFSM {
  private:
    void (* cb )(unsigned char);
    int syncState;
    uint32 dataWord;
  public:
    syncFSM(void (*)(unsigned char));
    receiveData(unsigned char);
    enterHuntState();
}
