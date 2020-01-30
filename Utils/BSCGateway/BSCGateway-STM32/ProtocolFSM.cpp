#include "ProtocolFSM.h"



// This is called from the main loop to do the processing of timers and checking interface signals.
// The FSM uses the subState to process the handhaek signal state. Normal state has the SUB_STATE in idle. When the subState is done it goes to idle thus let the main state
// continue processing.

void ProtocolFSM::workerPoll() {
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


int ProtocolFSM::sendPoll (unsigned short CU, unsigned short DV) {
  if (state != PROTOCOL_FSM_IDLE) {
    return -1; // We are busy processing another transaction. Wait!
  } else {
    messageFSM.sendENQ(CU, DV);                              // Send the ENQ message
    subState = PROTOCOL_FSM_SUBSTATE_WAIT_FOR_RTS;           // Goto state wait for RTS
    state = PROTOCOL_FSM_WAIT_FOR_MSG; 
    mode = PROTOCOL_MODE_POLL;
    thereIsMoreComing=true;    
  }
}

int ProtocolFSM::sendWrite (unsigned short CU, unsigned short DV, unsigned char * data) {
  if (state != PROTOCOL_FSM_IDLE) {
    return -1; // We are busy processing another transaction. Wait!
  } else {
    messageFSM.sendENQ(CU, DV);                              // Send the ENQ message
    subState = PROTOCOL_FSM_SUBSTATE_WAIT_FOR_RTS;           // Goto state wait for RTS
    state = PROTOCOL_FSM_WAIT_FOR_MSG; 
    mode = PROTOCOL_MODE_WRITE;
    thereIsMoreComing=true;    
  }

}

int ProtocolFSM::sendRead (unsigned short CU, unsigned short DV, unsigned char * data) {
  if (state != PROTOCOL_FSM_IDLE) {
    return -1; // We are busy processing another transaction. Wait!
  } else {
    messageFSM.sendENQ(CU, DV);                              // Send the ENQ message
    subState = PROTOCOL_FSM_SUBSTATE_WAIT_FOR_RTS;           // Goto state wait for RTS
    state = PROTOCOL_FSM_WAIT_FOR_MSG; 
    mode = PROTOCOL_MODE_READ;
    thereIsMoreComing=true;    
  }

}

// This is called when the MessageFSM has decoded a message to process.
void ProtocolFSM::receivedMessage( unsigned char type, MSG * msg ) {
  switch (mode | state | subState) {
  case PROTOCOL_MODE_POLL | PROTOCOL_FSM_WAIT_FOR_MSG | PROTOCOL_FSM_SUBSTATE_IDLE:
    if (thereIsMoreComing) {
      switch (type) {
        case TEXT_MESSAGE:
	  thereIsMoreComing = msg->testData.thereIsMoreComing;
        case TEST_MESSAGE:
	  thereIsMoreComing = msg->textData.thereIsMoreComing;
        case STATUS_MESSAGE:
	  thereIsMoreComing = false;
	  break;
        }
      subState = PROTOCOL_FSM_SUBSTATE_WAIT_FOR_NOT_RTS;
      state = PROTOCOL_FSM_SENDACK;
      cnt++;	  
    } else {
      // Now we should get a EOT if the last message had an ETX
      if (type == EOT_MESSAGE) {
	// do the callback. We have aggregated all data into the receive buffer and sends it to initiator
      } else {
	// protocol violation
      }
    }
    break;
  case PROTOCOL_MODE_WRITE | PROTOCOL_FSM_WAIT_FOR_MSG | PROTOCOL_FSM_SUBSTATE_IDLE:
    switch (type) {
    case ACK0_MESSAGE:
      subState = PROTOCOL_FSM_SUBSTATE_WAIT_FOR_NOT_RTS;
      state = PROTOCOL_SEND_FSM_DATA;
      break;
    case RVI_MESSAGE:
    case WACK_MESSAGE:
      subState = PROTOCOL_FSM_SUBSTATE_WAIT_FOR_NOT_RTS;
      state = PROTOCOL_FSM_SEND_EOT;
      // This is some kind of error condition that need to be handled. We store the message and call a callback when we receive the EOT.
      break;

    }
  default:

    // protocol violation
    break;
  }
}
  

