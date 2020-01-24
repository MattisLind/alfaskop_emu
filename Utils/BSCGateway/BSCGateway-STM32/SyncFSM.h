/*
SyncFSM.h 
Handles finding the sync position. When in sync it will dispatch the receivedSyncData for each character received. Typically
used by the message FSM.
 
The Sync FSM has two states, Hunt state and Sync state. When in Hunt state it will search for the BSC SYNC characters, SYN SYN, 0x32 0x32.
*/
#ifndef DEBUG
#include "libmaple/libmaple_types.h"
#else
#include <stdio.h>
#include "../test/types.h"
#endif
#include "ebcdic.h"
#include "lsbmsb.h"
#define  HUNT 0
#define  SYNC 1

class SyncFSM {
  private:
    void (* cb )(unsigned char);
    int syncState;
    uint32_t dataWord;
    int syncPoint;
  public:
    SyncFSM(void (*)(unsigned char));
    void receivedData(unsigned char);
    void enterHuntState();
};
