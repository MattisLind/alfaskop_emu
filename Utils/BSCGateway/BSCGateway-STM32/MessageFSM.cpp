
#include "MessageFSM.h"
#ifdef DEBUG
#include <stdio.h>
#endif

unsigned short calculateCrcChar (unsigned short crc, unsigned char data_p);

// The constructor have a number of callbacks for the various received messages and for the txByte. txByte is called each time 
// the Message FSM has a byte to send. Typically these bytes are put in the ringbuffer for transmission by the interrupt routine




MessageFSM::MessageFSM(void (*txData)(unsigned char), void (*recivedMessage)(unsigned char, unsigned char *),void (*enterHuntState)()) {
  txDataCb = txData;
  receivedMessageCb = recivedMessage;
  enterHuntStateCb = enterHuntState;
  rxState = 0;
}


// Method to send the EOT message

void MessageFSM::sendEOT(){
  #ifndef HERCULES
  txDataCb(SYN);
  txDataCb(SYN);
  #endif 
  txDataCb(EOT);
  #ifndef HERCULES
  txDataCb(PAD);
  #endif
}
void MessageFSM::sendENQ(uint8_t CU, uint8_t DV){
  #ifndef HERCULES
  txDataCb(SYN);
  txDataCb(SYN);
  #endif 
  txDataCb(CU);
  txDataCb(CU);
  txDataCb(DV);
  txDataCb(DV);
  txDataCb(ENQ);
  #ifndef HERCULES
  txDataCb(PAD);
  #endif
}
void MessageFSM::sendStatusMessage(uint8_t CU, uint8_t DV,  uint8_t status, uint8_t sense) {
  int crc=0;
  #ifndef HERCULES
  txDataCb(SYN);
  txDataCb(SYN);
  #endif 
  txDataCb(SOH);
  txDataCb(0x6c);
  crc = calculateCrcChar (crc, 0x6c);
  txDataCb(0xd9);
  crc = calculateCrcChar (crc, 0xd9);
  txDataCb(STX);
  crc = calculateCrcChar (crc, STX);
  txDataCb(CU);
  crc = calculateCrcChar (crc, CU);
  txDataCb(DV);
  crc = calculateCrcChar (crc, DV);
  txDataCb(status);
  crc = calculateCrcChar (crc, status);
  txDataCb(sense);  
  crc = calculateCrcChar (crc, sense);
  txDataCb(ETX);
  crc = calculateCrcChar (crc, ETX);
  txDataCb(crc & 0xff);
  txDataCb((crc >> 8) & 0xff);
  #ifndef HERCULES
  txDataCb(PAD);
  #endif
}

void MessageFSM::sendTestRequestMessage(int messageLength, uint8_t * msg, bool thereIsMoreComing) {
  int i;
  int crc=0;
  #ifndef HERCULES
  txDataCb(SYN);
  txDataCb(SYN);
  #endif 
  txDataCb(SOH);
  txDataCb(0x6c);
  crc = calculateCrcChar (crc, 0x6c);
  txDataCb(0x61);
  crc = calculateCrcChar (crc, 0x61);
  txDataCb(STX);
  crc = calculateCrcChar (crc, STX);
  for (i=0; i<messageLength; i++) {
    txDataCb(msg[i]);
    crc = calculateCrcChar (crc, msg[i]);
  }
  if (thereIsMoreComing) {
    txDataCb(ETB);
    crc = calculateCrcChar (crc, ETB);
  } else {
    txDataCb(ETX);
    crc = calculateCrcChar (crc, ETX);
  }
  txDataCb(crc & 0xff);
  txDataCb((crc >> 8) & 0xff);
  #ifndef HERCULES
  txDataCb(PAD);
  #endif
}

void MessageFSM::sendTextMessage(int messageLength, uint8_t * msg, bool thereIsMoreComing) {
  int i;
  int crc=0;
  #ifndef HERCULES
  txDataCb(SYN);
  txDataCb(SYN);
  #endif 
  txDataCb(STX);
  for (i=0; i<messageLength; i++) {
    txDataCb(msg[i]);
    crc = calculateCrcChar (crc, msg[i]);
  }
  if (thereIsMoreComing) {
    txDataCb(ETB);
    crc = calculateCrcChar (crc, ETB);
  } else {
    txDataCb(ETX);
    crc = calculateCrcChar (crc, ETX);
  }
  txDataCb(crc & 0xff);
  txDataCb((crc >> 8) & 0xff);
  #ifndef HERCULES
  txDataCb(PAD);
  #endif
}

void MessageFSM::sendACK0(){
  #ifndef HERCULES
  txDataCb(SYN);
  txDataCb(SYN);
  #endif 
  txDataCb(DLE);
  txDataCb(0x70);
  #ifndef HERCULES
  txDataCb(PAD);
  #endif
}

void MessageFSM::sendACK1(){
  #ifndef HERCULES
  txDataCb(SYN);
  txDataCb(SYN);
  #endif 
  txDataCb(DLE);
  txDataCb(0x61);
  #ifndef HERCULES
  txDataCb(PAD);
  #endif
}

void MessageFSM::sendWACK(){
  #ifndef HERCULES
  txDataCb(SYN);
  txDataCb(SYN);
  #endif 
  txDataCb(DLE);
  txDataCb(0x6b);
  #ifndef HERCULES
  txDataCb(PAD);
  #endif
}

void MessageFSM::sendRVI(){
  #ifndef HERCULES
  txDataCb(SYN);
  txDataCb(SYN);
  #endif 
  txDataCb(DLE);
  txDataCb(0x7c);
  #ifndef HERCULES
  txDataCb(PAD);
  #endif
}
void MessageFSM::sendNAK(){
  #ifndef HERCULES
  txDataCb(SYN);
  txDataCb(SYN);
  #endif 
  txDataCb(NAK);
  #ifndef HERCULES
  txDataCb(PAD);
  #endif
}

void MessageFSM::messageDone() {
  MSG msg;
      // We have all data  - Do a callback
      switch (msgBuffer[0]) {
      case EOT:
	receivedMessageCb(EOT_MESSAGE, NULL);
	enterHuntStateCb();
	msgBufferCnt=0;
	break;
      case NAK:
	receivedMessageCb(NAK_MESSAGE, NULL);
	enterHuntStateCb();
	msgBufferCnt=0;
	break;
      case DLE:
	switch (msgBuffer[1]) {
	case 0x70: // ACK 0
	  receivedMessageCb(ACK0_MESSAGE, NULL);
	  enterHuntStateCb();
	  msgBufferCnt=0;
	  break;
	case 0x61: // ACK 1
	  receivedMessageCb(ACK1_MESSAGE, NULL);
	  enterHuntStateCb();
	  msgBufferCnt=0;
	  break;
	case 0x6b: // WACK
	  receivedMessageCb(WACK_MESSAGE, NULL);
	  enterHuntStateCb();
	  msgBufferCnt=0;
	  break;
	case 0x7c: // RVI
	  receivedMessageCb(RVI_MESSAGE, NULL);
	  enterHuntStateCb();
	  msgBufferCnt=0;
	  break;
	}
	break;
      case SOH:
	if (msgBuffer[1] == 0x6c) {
	  switch (msgBuffer[2]) {
	  case 0xd9:
	    msg.statusData.CU = msgBuffer[4];
	    msg.statusData.DV = msgBuffer[5];
	    msg.statusData.status = msgBuffer[6];
	    msg.statusData.sense = msgBuffer[7];
	    msg.statusData.crcOk = crcOk;
	    receivedMessageCb(STATUS_MESSAGE, (uint8_t *) &msg);
	    enterHuntStateCb();
	    msgBufferCnt=0;
	    break;  // Status Message                
	  case 0x61:
	    msg.testData.length = length; 
	    msg.testData.msg = msgBuffer+4;
	    msg.testData.thereIsMoreComing = thereIsMoreComing;
	    msg.testData.crcOk = crcOk;
	    receivedMessageCb(TEST_MESSAGE, (uint8_t *) &msg);
	    enterHuntStateCb();
	    msgBufferCnt=0;
	    break;  // Test request message
	  default:
	    //Serial.println("Error SOH with wrong header code");
	    //printMsgBuffer();
	    break;
	  }
	} else {
	  //Serial.println("Error SOH with wrong header code");
	  //printMsgBuffer();
	}
	break;
      case STX:
	msg.textData.length = length; 
	msg.textData.msg = msgBuffer+1;
	msg.textData.thereIsMoreComing = thereIsMoreComing;
	msg.textData.crcOk = crcOk;
	receivedMessageCb(TEXT_MESSAGE, (uint8_t *) &msg);
	enterHuntStateCb();
	msgBufferCnt=0;
	break;
      default:  // Selection and POLL ENQ
	receivedMessageCb(ENQ_MESSAGE, msgBuffer);
	enterHuntStateCb();
	msgBufferCnt=0;
	break;
      }
}

void MessageFSM::rxData(uint8_t data) {
  #ifdef DEBUG
  printf ("Received %02X in state %d\n", data, rxState);
  #endif

  if (data == SYN) {
    return;
  }
  crc = calculateCrcChar (crc, data);
  msgBuffer[msgBufferCnt++] = data;
  if (rxState == 0) { 
    switch (data) {
    case EOT: 
    case NAK:
#ifdef HERCULES  
      messageDone();
      rxState = 0;
#else
      rxState = 2;
#endif
      break;
    case DLE:  // Two byte sequences
      rxState = 3;
      break;
    case SOH:
      byteCounter=2;
      rxState = 4;
      crc = 0;
      break;
    case STX:
      byteCounter=4096;
      rxState = 5;
      crc = 0;
      break;
#ifdef HERCULES
    case PAD:
      break;
#endif
    default:  // Enquiry POLL / SELECTION
      rxState = 7;
      byteCounter=3; // 4 with this byte
      break;
    }   
  } else if (rxState == 2) {
    // Data shall be PAD.
    if (data == PAD) {
      messageDone();
    } else {
      //Serial.println("Last byte was not a PAD - go back to hunt mode!");
      //printMsgBuffer();       
    }
    rxState = 0; // Go back to hunt for sync.
  } else if (rxState == 3) {
    switch (data) {
    case 0x70: // ACK 0
    case 0x61: // ACK 1
    case 0x6b: // WACK
    case 0x7c: // RVI
#ifdef HERCULES
      messageDone();
      rxState = 0;
#else
      rxState = 2;
#endif
      break;
    default:
      rxState = 0;
      rxState = 0;
      receivedMessageCb(ERROR_MESSAGE, (unsigned char *)  "State violation - going back to hunt mode when waiting for second byte control code");
      enterHuntStateCb();
      msgBufferCnt=0;
      break;
    }
  } else if (rxState == 4) { // SOH is followed by two byte header
    byteCounter--;
    if (byteCounter == 0) {
      rxState = 8; // Now watch for the STX
    }
  } else if (rxState == 5) {
    // Waiting for ETB or ETX to come
    if ((data == ETB) || (data == ETX)) {
      length = 4096-byteCounter;
      byteCounter=2;
      rxState = 9;
      if (data == ETB) {
	thereIsMoreComing = true;
      }
      else {
	thereIsMoreComing = false;
      }
    } else { // Here comes the data. Up to 4096 bytes of EBCDIC data
      if (byteCounter == 0) {
	rxState = 0;
	receivedMessageCb(ERROR_MESSAGE, (unsigned char *)  "Message to long");
	enterHuntStateCb();
	msgBufferCnt=0;
      }
      byteCounter--;
    }
  } else if (rxState==7) {
    byteCounter--;
    if (byteCounter == 0) {
      rxState = 10; // Get the ENQ
    }
    
  } else if (rxState == 8) {
    // Check for STX then
    if (data == STX) {
      rxState = 5;
      byteCounter=4096;
    } else { 
      rxState = 0;
      receivedMessageCb(ERROR_MESSAGE, (unsigned char *)  "State violation - going back to hunt mode when waiting for STX");
      enterHuntStateCb();
      msgBufferCnt=0;
    }
  } else if (rxState ==9) {
    // Two CRC digits to be received
    byteCounter--;
    //printf("crc=%04X\n", crc);
    if (byteCounter == 0) {
      if (crc == 0) {
	crcOk=true;
      } else {
	crcOk=false;
      }
#ifdef HERCULES
      messageDone();
      rxState = 0;
#else
      rxState = 2; // wait for the PAD
#endif
    }
  } else if (rxState == 10) {
    if (data == ENQ) {
#ifdef HERCULES
      messageDone();
      rxState = 0;
#else
      rxState = 2; // There is a PAD to come
#endif
    }
    else {
      rxState = 0;
      receivedMessageCb(ERROR_MESSAGE, (unsigned char *) "State violation - going back to hunt mode when waiting for ENQ");
      enterHuntStateCb();
      msgBufferCnt=0;
    }
  }
  else {
    receivedMessageCb(ERROR_MESSAGE, (unsigned char *) "Error unknown state!");
    enterHuntStateCb();
    msgBufferCnt=0;
    rxState = 0; // Go back to hunt
  }
}
 
