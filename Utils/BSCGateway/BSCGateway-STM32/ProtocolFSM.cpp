#include "ProtocolFSM.h"



// This is called from the main loop to do the processing of timers and checking interface signals.
// The FSM uses the subState to process the handhaek signal state. Normal state has the SUB_STATE in idle. When the subState is done it goes to idle thus let the main state
// continue processing.

void ProtocolFSM::workerPoll() {
  int bytesLeftToCopy=256, i;
  ProtocolMsg * pMsg;
  switch (subState) {
    case PROTOCOL_FSM_SUBSTATE_IDLE:
      break;
    case PROTOCOL_FSM_SUBSTATE_WAIT_FOR_RTS:
      if (rtsIsSet()) {
	subState = PROTOCOL_FSM_SUBSTATE_IDLE;
	cts(true);
      }
      break;
    case PROTOCOL_FSM_SUBSTATE_WAIT_FOR_NOT_RTS:
      if (!rtsIsSet()) {
	subState = PROTOCOL_FSM_SUBSTATE_IDLE;
	cts(false);
      }
      break;
  }
  switch (mode | state | subState) {
    case PROTOCOL_MODE_POLL | PROTOCOL_FSM_SENDACK | PROTOCOL_FSM_SUBSTATE_IDLE:
      if (cnt&1) {
	messageFSM.sendACK1();
      } else {
	messageFSM.sendACK0();
      }
      subState = PROTOCOL_FSM_SUBSTATE_WAIT_FOR_RTS;
      state = PROTOCOL_FSM_WAIT_FOR_MSG;
      break;
    case PROTOCOL_MODE_WRITE | PROTOCOL_FSM_SEND_DATA | PROTOCOL_FSM_SUBSTATE_IDLE:
      // We need to slice the incoming data so that we get right amount of data in each message
      // and decide if the thereIsMoreComing flag is to be set or not. Copy data character by character. 
      // If in transparent mode we do the escaping at this time.
      if (txMessageLength == 0) {
	messageFSM.sendEOT();
	subState = PROTOCOL_FSM_SUBSTATE_IDLE;
	state = PROTOCOL_FSM_IDLE;
	pMsg->type = PROTOCOL_TYPE_DONE;
	protocolResponseCb(pMsg);
      } else {
	subState = PROTOCOL_FSM_SUBSTATE_WAIT_FOR_RTS;
	state = PROTOCOL_FSM_WAIT_FOR_ACK;
	i=0;
	do {
	  if (*incomingTransmitBufP==DLE) {
	    if (bytesLeftToCopy == 1) {
	      // We have no space for this esacpe
	      break;
	    } else {
	      transmitBuffer[i++] = DLE;
	      transmitBuffer[i++] = DLE;
	      bytesLeftToCopy--;
	    }	
	  } else {
	    transmitBuffer[i++] = *incomingTransmitBufP;
	  }
	  incomingTransmitBufP++;
	  bytesLeftToCopy--;
	  txMessageLength--;
	} while(bytesLeftToCopy>0 && txMessageLength > 0);
	if (txMessageLength > 0) {
	  thereIsMoreComing = true;
	}      
	messageFSM.sendTextMessage(256-bytesLeftToCopy, transmitBuffer,thereIsMoreComing);
      }
      break;
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
  return 0;
}

int ProtocolFSM::sendWrite (unsigned short CU, unsigned short DV, int length, unsigned char * data) {
  int i;


  if (state != PROTOCOL_FSM_IDLE) {
    return -1; // We are busy processing another transaction. Wait!
  } else {
    messageFSM.sendENQ(CU+0x20, DV);                              // Send the ENQ message
    subState = PROTOCOL_FSM_SUBSTATE_WAIT_FOR_RTS;           // Goto state wait for RTS
    state = PROTOCOL_FSM_WAIT_FOR_ACK; 
    mode = PROTOCOL_MODE_WRITE;
    transparentMode = false;
    thereIsMoreComing=false;    
    incomingTransmitBufP = data;
    txMessageLength = length;
    // We need to figure out if we need to use transparent mode or not.
    // That can be done iterating through the inbound buffer and find if there are any character 
    // that has to be escaped.
    for (i=0; i<length; i++) {
      if (isLinkControlChar(*(data+i))) {
	transparentMode=true;
	break;
      }
    }    
  } 
  return 0;
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
  return 0;
}

// This is called when the MessageFSM has decoded a message to process.
void ProtocolFSM::receivedMessage( unsigned char type, MSG * msg ) {
  ProtocolMsg * pMsg;
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
	subState = PROTOCOL_FSM_SUBSTATE_WAIT_FOR_NOT_RTS;
	state = PROTOCOL_FSM_IDLE;
	pMsg->type = PROTOCOL_TYPE_DONE;
	protocolResponseCb(pMsg)	;
	// do the callback. We have aggregated all data into the receive buffer and sends it to initiator
      } else {
	// protocol violation
      }
    }
    break;
  case PROTOCOL_MODE_WRITE | PROTOCOL_FSM_WAIT_FOR_ACK | PROTOCOL_FSM_SUBSTATE_IDLE:
    switch (type) {
    case ACK0_MESSAGE: // Check odd / even also!
      subState = PROTOCOL_FSM_SUBSTATE_WAIT_FOR_NOT_RTS;
      state = PROTOCOL_FSM_SEND_DATA;
      break;
    case ACK1_MESSAGE:
      subState = PROTOCOL_FSM_SUBSTATE_WAIT_FOR_NOT_RTS;
      state = PROTOCOL_FSM_SEND_DATA;
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

// These pins shall have a proper definitions. And the functions should really be callbacks so that theu can be implemented in the code instatiating the ProtocolFSM class.

