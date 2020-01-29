#include "PollFSM.h"



// This is called from the main loop to do the processing of timers and checking interface signals.


void PollFSM::workerPoll() {
  switch (mode | state) {
  case PROTOCOL_MODE_POLL | PROTOCOL_FSM_WAIT_FOR_RTS:
    if (rtsIsSet()) {
      state = PROTOCOL_FSM_WAIT_FOR_MSG;
      cts(true);
    }
  case PROTOCOL_MODE_POLL | PROTOCOL_FSM_WAIT_FOR_NOT_RTS:
    if (!rtsIsSet()) {
      state = PROTOCOL_FSM_WAIT_FOR_MSG;
      cts(false);
      if (cnt&1) {
	messageFSM.sendACK0();
      } else {
	messageFSM.sendACK1();
      }
    }
    break;
    
  }
}


int PollFSM::sendPoll (unsigned short CU, unsigned short DV) {
  if (state != PROTOCOL_FSM_IDLE) {
    return -1; // We are busy processing another transaction. Wait!
  } else {
    messageFSM.sendENQ(CU, DU);                  // Send the ENQ message
    state = PROTOCOL_FSM_WAIT_FOR_RTS;           // Goto state wait for RTS
    mode = PROTOCOL_MODE_POLL;    
  }
}

void PollFSM::sendWrite (unsigned short CU. unsigned short DV, unsigned char * data) {

}

void PollFSM::sendRead (unsigned short CU. unsigned short DV, unsigned char * data) {

}

// This is called when the MessageFSM has decoded a message to process.
void ProtcolFSM::receivedMessage( unsigned char type, unsigned char * msg ) {
  switch (mode | state) {
  case PROTOCOL_MODE_POLL | PROTOCOL_FSM_WAIT_FOR_MSG:
    switch (type) {
    case STATUS_MESSAGE:
      state = PROTOCOL_FSM_WAIT_FOR_NOT_RTS;
      cnt++;
      break;
    }
    break;
  }
}
  

