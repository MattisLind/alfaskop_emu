
#include "MessageFSM.h"
#ifdef DEBUG
#include <stdio.h>
#endif

unsigned short calculateCrcChar (unsigned short crc, unsigned char data_p);

// The constructor have a number of callbacks for the various received messages and for the txByte. txByte is called each time 
// the Message FSM has a byte to send. Typically these bytes are put in the ringbuffer for transmission by the interrupt routine




MessageFSM::MessageFSM(void (*txData)(unsigned char), void (*recivedMessage)(unsigned char, unsigned char *),void (*enterHuntState)(), bool hMode) {
  txDataCb = txData;
  receivedMessageCb = recivedMessage;
  enterHuntStateCb = enterHuntState;
  rxState = 0; txState=0;
  herculesMode = hMode;  
}

MessageFSM::MessageFSM(void (*txData)(unsigned char), void (*recivedMessage)(unsigned char, unsigned char *),void (*enterHuntState)()) {
  txDataCb = txData;
  receivedMessageCb = recivedMessage;
  enterHuntStateCb = enterHuntState;
  rxState = 0; txState=0;
  herculesMode = false;  
}


// The Tx FSM
// Called every time there is at least one byte space in transmitting buffer.
// txDataCb is used to send one character. Or no character is sent if there is nothing to send.


#define TX_IDLE 0
#define TX_FIRST_SYN 1
#define TX_SECOND_SYN 2
#define TX_EOT 3
#define TX_ENQ 4
#define TX_PAD 5
#define TX_POLL 6
#define TX_POLL2 7
#define TX_POLL3 8
#define TX_POLL4 9
#define TX_STATUS 10
#define TX_STATUS2 11
#define TX_STATUS3 12
#define TX_STATUS4 13
#define TX_STATUS5 14
#define TX_STATUS6 15
#define TX_STATUS7 16
#define TX_STATUS8 17
#define TX_STATUS9 18
#define TX_CRC1 19
#define TX_CRC2 20
#define TX_TEST 21
#define TX_TEST2 22
#define TX_TEST3 23
#define TX_TEST4 24
#define TX_TEST5 25
#define TX_TEST6 26
#define TX_TEXT 27
#define TX_TEXT2 28
#define TX_TEXT3 29
#define TX_ACK0 30
#define TX_ACK0_2 31
#define TX_ACK1 32
#define TX_ACK1_2 33
#define TX_WACK 34
#define TX_WACK2 35
#define TX_RVI 36
#define TX_RVI2 37
#define TX_NAK 38

bool MessageFSM::isTxIdle() {
  return (txState == TX_IDLE);
}


void MessageFSM::txPoll() {
  switch (txState) {
  case TX_IDLE:
    break;
  case TX_FIRST_SYN:
    txState = TX_SECOND_SYN;
    txDataCb(SYN);
    break;
  case TX_SECOND_SYN:
    txState = txStateAfterSYN;
    txDataCb(SYN);
    break;
  case TX_EOT:
    if (herculesMode) {
      txState = TX_IDLE;     
    } else {
      txState = TX_PAD;
    }
    txDataCb(EOT);
    break;
  case TX_ENQ:
    if (herculesMode) {
      txState = TX_IDLE;     
    } else {
      txState = TX_PAD;
    }
    txDataCb(ENQ);
    break;
  case TX_POLL:
    txState = TX_POLL2;
    txDataCb(txCU);
    break;
  case TX_POLL2:
    txState = TX_POLL3;
    txDataCb(txCU);
    break;
  case TX_POLL3:
    txState = TX_POLL4;
    txDataCb(txDV);
    break;
  case TX_POLL4:
    txState = TX_ENQ;
    txDataCb(txDV);
    break;
  case TX_STATUS:
    txState = TX_STATUS2;
    txDataCb(SOH);
    break;
  case TX_STATUS2:
    txCrc = 0;
    txState = TX_STATUS3;
    txDataCb(0x6C);
    txCrc = calculateCrcChar (txCrc, 0x6c);
  case TX_STATUS3:
    txState = TX_STATUS4;
    txDataCb(0xd9);
    txCrc = calculateCrcChar (txCrc, 0xd9);
    break;
  case TX_STATUS4:
    txState = TX_STATUS5;
    txDataCb(STX);
    txCrc = calculateCrcChar (txCrc, STX);
    break;
  case TX_STATUS5:
    txState = TX_STATUS6;
    txDataCb(txCU);
    txCrc = calculateCrcChar (txCrc, txCU);
    break;
  case TX_STATUS6:
    txState = TX_STATUS7;
    txDataCb(txDV);
    txCrc = calculateCrcChar (txCrc, txDV);
    break;
  case TX_STATUS7:
    txState = TX_STATUS8;
    txDataCb(txStatus);
    txCrc = calculateCrcChar (txCrc, txStatus);
    break;
  case TX_STATUS8:
    txState = TX_STATUS9;
    txDataCb(txSense);  
    txCrc = calculateCrcChar (txCrc, txSense);
    break;
  case TX_STATUS9:
    if (herculesMode) {
      txState = TX_IDLE;
    } else {
      txState = TX_CRC1;
    }
    txDataCb(ETX);
    txCrc = calculateCrcChar (txCrc, ETX);
    break;
  case TX_TEST:
    txState = TX_TEST2;
    txDataCb(SOH);
    break;
  case TX_TEST2:
    txCrc = 0;
    txState = TX_TEST3;
    txDataCb(0x6C);
    txCrc = calculateCrcChar (txCrc, 0x6c);
  case TX_TEST3:
    txState = TX_TEST4;
    txDataCb(0x61);
    txCrc = calculateCrcChar (txCrc, 0x61);
    break;
  case TX_TEST4:
    if (txMsgLength > 0) {
      txState = TX_TEST5;
    } else {
      txState = TX_TEST6;
    }
    txDataCb(STX);
    txCrc = calculateCrcChar (txCrc, STX);
    break;
  case TX_TEST5:
    txMsgLength--;
    if (txMsgLength == 0) {
      txState = TX_TEST6;
    }
    txDataCb(*txMsg);
    txCrc = calculateCrcChar (txCrc, *txMsg);
    txMsg++;
    break;
  case TX_TEST6:
    if (herculesMode) {
      txState = TX_IDLE;
    } else {
      txState = TX_CRC1;
    }
    if (txThereIsMoreComing) {
      txDataCb(ETB);
      txCrc = calculateCrcChar (txCrc, ETB);
    } else {
      txDataCb(ETX);
      txCrc = calculateCrcChar (txCrc, ETX);
    }
    break;
  case TX_TEXT:
    txCrc = 0;
    if (txMsgLength > 0) {
      txState = TX_TEXT2;
    } else {
      txState = TX_TEXT3;
    }
    txDataCb(STX);
    break;
  case TX_TEXT2:
    txMsgLength--;
    if (txMsgLength == 0) {
      txState = TX_TEXT3;
    }
    txDataCb(*txMsg);
    txCrc = calculateCrcChar (txCrc, *txMsg++);
    break;
  case TX_TEXT3:
    if (herculesMode) {
      txState = TX_IDLE;
    } else {
      txState = TX_CRC1;
    }
    if (txThereIsMoreComing) {
      txDataCb(ETB);
      txCrc = calculateCrcChar (txCrc, ETB);
    } else {
      txDataCb(ETX);
      txCrc = calculateCrcChar (txCrc, ETX);
    }
    break;
  case TX_ACK0:
    txState = TX_ACK0_2;
    txDataCb(DLE);
    break;
  case TX_ACK0_2:
    if (herculesMode) {
      txState = TX_IDLE;     
    } else {
      txState = TX_PAD;
    }
    txDataCb(0x70);
    break;
  case TX_ACK1:
    txState = TX_ACK1_2;
    txDataCb(DLE);
    break;
  case TX_ACK1_2:
    if (herculesMode) {
      txState = TX_IDLE;     
    } else {
      txState = TX_PAD;
    }
    txDataCb(0x61);
    break;
  case TX_WACK:
    txState = TX_WACK2;
    txDataCb(DLE);
    break;
  case TX_WACK2:
    if (herculesMode) {
      txState = TX_IDLE;     
    } else {
      txState = TX_PAD;
    }
    txDataCb(0x6b);
    break;
  case TX_RVI:
    txState = TX_RVI2;
    txDataCb(DLE);
    break;
  case TX_RVI2:
    if (herculesMode) {
      txState = TX_IDLE;     
    } else {
      txState = TX_PAD;
    }
    txDataCb(0x7C);
    break;
  case TX_NAK:
    if (herculesMode) {
      txState = TX_IDLE;     
    } else {
      txState = TX_PAD;
    }
    txDataCb(NAK);
    break;  
  case TX_CRC1:
    txState = TX_CRC2;
    txDataCb(txCrc & 0xff);
    break;
  case TX_CRC2:
    txState = TX_PAD;
    txDataCb((txCrc >> 8) & 0xff);
    break;
  case TX_PAD:
    txState = TX_IDLE;
    txDataCb(PAD);
    break;
  }
}


// Method to send the EOT message

void MessageFSM::sendEOT(){
  if (herculesMode) {
    txState = TX_EOT;
  } else {
    txState = TX_FIRST_SYN;
    txStateAfterSYN = TX_EOT;
  }
}

void MessageFSM::sendENQ(){
  if (herculesMode) {
    txState = TX_ENQ;
  } else {
    txState = TX_FIRST_SYN;
    txStateAfterSYN = TX_ENQ;
  }
}

void MessageFSM::sendPollSelect(uint8_t CU, uint8_t DV){
  if (herculesMode) {
    txState = TX_POLL;
  } else {
    txState = TX_FIRST_SYN;
    txStateAfterSYN = TX_POLL;
  }
  txCU = CU;
  txDV = DV;
}

void MessageFSM::sendStatusMessage(uint8_t CU, uint8_t DV,  uint8_t status, uint8_t sense) {
  if (herculesMode) {
    txState = TX_STATUS;
  } else {
    txState = TX_FIRST_SYN;
    txStateAfterSYN = TX_STATUS;
  }
  txCU = CU;
  txDV = DV;
  txStatus = status;
  txSense = sense;
}

void MessageFSM::sendTestRequestMessage(int messageLength, uint8_t * msg, bool thereIsMoreComing) {
  if (herculesMode) {
    txState = TX_TEST;
  } else {
    txState = TX_FIRST_SYN;
    txStateAfterSYN = TX_TEST;
  }
  txMsg = msg;
  txMsgLength = messageLength;
  txThereIsMoreComing = thereIsMoreComing;
}

void MessageFSM::sendTextMessage(int messageLength, uint8_t * msg, bool thereIsMoreComing) {
  if (herculesMode) {
    txState = TX_TEXT;
  } else {
    txState = TX_FIRST_SYN;
    txStateAfterSYN = TX_TEXT;
  }
  txMsg = msg;
  txMsgLength = messageLength;
  txThereIsMoreComing = thereIsMoreComing; 
}

void MessageFSM::sendACK0(){
  if (herculesMode) {
    txState = TX_ACK0;
  } else {
    txState = TX_FIRST_SYN;
    txStateAfterSYN = TX_ACK0;
  }
}

void MessageFSM::sendACK1(){
  if (herculesMode) {
    txState = TX_ACK1;
  } else {
    txState = TX_FIRST_SYN;
    txStateAfterSYN = TX_ACK1;
  }
}

void MessageFSM::sendWACK(){
  if (herculesMode) {
    txState = TX_WACK;
  } else {
    txState = TX_FIRST_SYN;
    txStateAfterSYN = TX_WACK;
  }
}

void MessageFSM::sendRVI(){
    if (herculesMode) {
    txState = TX_RVI;
  } else {
    txState = TX_FIRST_SYN;
    txStateAfterSYN = TX_RVI;
  }
}

void MessageFSM::sendNAK(){
  if (herculesMode) {
    txState = TX_NAK;
  } else {
    txState = TX_FIRST_SYN;
    txStateAfterSYN = TX_NAK;
  }
}

void MessageFSM::setTextMode(bool mode) {
  textMode=mode; 
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
  case ENQ:
	  receivedMessageCb(ENQ_MESSAGE, NULL);
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
	  msg.enqData.CU = msgBuffer[0];
	  msg.enqData.DV = msgBuffer[2];
	  receivedMessageCb(POLL_MESSAGE, (uint8_t *) &msg);
	  enterHuntStateCb();
	  msgBufferCnt=0;
	  break;
  }
}

void MessageFSM::rxData(uint8_t data) {
  #ifdef DEBUG
  //printf ("Received %02X in state %d\n", data, rxState);
  #endif

  if (data == SYN) {
    return;
  }
  crc = calculateCrcChar (crc, data);
  msgBuffer[msgBufferCnt++] = data;
  if (rxState == 0) { 
handleLinkChars:	  
    switch (data) {
    case EOT: 
    case NAK:
      if (herculesMode) {  
	      messageDone();
	      rxState = 0;
      } else {
	      rxState = 2;
      }
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
    case ENQ:
      if (textMode) {
	      if (herculesMode) {  
	        messageDone();
	        rxState = 0;
	      } else {
	        rxState = 2;
	      }
      }
      break;
    case PAD:
      break;
    default:  // Enquiry POLL / SELECTION
      if (!textMode) {
	      rxState = 7;
	      byteCounter=3; // 4 with this byte
      }
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
      if (herculesMode) {
        messageDone();
        rxState = 0;
      } else {
        rxState = 2;
      }
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
      if (herculesMode) {
	      messageDone();
	      rxState = 0;
      } else {
	      rxState = 9; 
      }
      if (data == ETB) {
	      thereIsMoreComing = true;
      }
      else {
	      thereIsMoreComing = false;
      }
    } else if (isLinkControlCharacter(data)) {
	// This is some kind of error. In non transparent data we have received link control characters!
	// return to state 0. Issue an error message.
      rxState = 0;
      receivedMessageCb(ERROR_MESSAGE, (unsigned char *)  "Link characters in data");
      enterHuntStateCb();
      msgBufferCnt=0;
      goto handleLinkChars; // OK. goto is really not what I wanted. But it fits its purpose here. We are back in state 0 because of some error. 
                            // We need to deal with it to get on track!
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
      rxState = 2; // wait for the PAD
    }
  } else if (rxState == 10) {
    if (data == ENQ) {
      if (herculesMode) {
        messageDone();
        rxState = 0;
      } else {
	      rxState = 2; // There is a PAD to come
      }
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
 
