#include "PollFSM.h"



// This is called from the main loop to do the processing of timers and checking interface signals.
// The FSM uses the subState to process the handhaek signal state. Normal state has the SUB_STATE in idle. When the subState is done it goes to idle thus let the main state
// continue processing.

void PollFSM::workerPoll() {
  switch (subState) {
    case PROTOCOL_FSM_SUBSTATE_IDLE:
      break;
    case PROTOCOL_FSM_SUBSTATE_WAIT_FOR_RTS:
      if (rtsIsSet()) {
	state = PROTOCOL_FSM_SUBSTATE_IDLE;
	cts(true);
      }
      break;
    case PROTOCOL_FSM_SUBSTATE_WAIT_FOR_NOT_RTS:
      if (!rtsIsSet()) {
	state = PROTOCOL_FSM_SUBSTATE_IDLE;
	cts(false);
      }
      break;
  }
  switch (mode | state) {
    case PROTOCOL_MODE_POLL | PROTOCOL_FSM_SENDACK | PROTOCOL_FSM_SUBSTATE_IDLE:
      if (cnt&1) {
	messageFSM.sendACK0();
      } else {
	messageFSM.sendACK1();
      }
      subState = PROTOCOL_FSM_SUBSTATE_WAIT_FOR_RTS;
      state = PROTOCOL_FSM_WAIT_FOR_MSG;
  }
}


int PollFSM::sendPoll (unsigned short CU, unsigned short DV) {
  if (state != PROTOCOL_FSM_IDLE) {
    return -1; // We are busy processing another transaction. Wait!
  } else {
    messageFSM.sendENQ(CU, DU);                              // Send the ENQ message
    subState = PROTOCOL_FSM_SUBSTATE_WAIT_FOR_RTS;           // Goto state wait for RTS
    state = PROTOCOL_FSM_WAIT_FOR_MSG; 
    mode = PROTOCOL_MODE_POLL;    
  }
}

void PollFSM::sendWrite (unsigned short CU. unsigned short DV, unsigned char * data) {

}

void PollFSM::sendRead (unsigned short CU. unsigned short DV, unsigned char * data) {

}

// This is called when the MessageFSM has decoded a message to process.
void ProtcolFSM::receivedMessage( unsigned char type, unsigned char * msg ) {
  switch (mode | state | subState) {
  case PROTOCOL_MODE_POLL | PROTOCOL_FSM_WAIT_FOR_MSG | PROTOCOL_FSM_SUBSTATE_IDLE:
    switch (type) {
    case STATUS_MESSAGE:
      subState = PROTOCOL_FSM_SUBSTATE_WAIT_FOR_NOT_RTS;
      state = PROTOCOL_FSM_SENDACK;
      cnt++;
      break;
    }
    break;
  default:

    // protocol violation
    break;
  }
}
  

