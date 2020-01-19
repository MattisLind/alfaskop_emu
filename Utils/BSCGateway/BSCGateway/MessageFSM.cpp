
#include "MessageFSM.h"

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
  txDataCb(SYN);
  txDataCb(SYN);
  txDataCb(EOT);
  txDataCb(PAD);
}
void MessageFSM::sendENQ(uint8_t CU, uint8_t DV){
}
void MessageFSM::sendSOHMessage(uint16_t header, uint8_t * msg){
}
void MessageFSM::sendSTXMessage(uint8_t * msg){
}
void MessageFSM::sendACK0(){
}
void MessageFSM::sendACK1(){
}
void MessageFSM::sendWACK(){
}
void MessageFSM::sendRVI(){
}
void MessageFSM::sendNAK(){
  txDataCb(SYN);
  txDataCb(SYN);
  txDataCb(NAK);
  txDataCb(PAD);
}

void MessageFSM::rxData(uint8_t data) {
      msgBuffer[msgBufferCnt++] = data;
      //Serial.print("Buffer");
      //printMsgBuffer();
      //Serial.msgBufferprint("byteCounter:");
      //Serial.print(byteCounter, DEC);
      //Serial.print(" rxState=");
      //Serial.print(rxState, DEC);
      //Serial.print(" data=");
      //Serial.print(data,HEX);
      //Serial.println();
      if (rxState == 0) {
	if (data == SYN) {
	  rxState = 12;
	}
	else {
	}
      } else if (rxState == 12) {
	if (data == SYN) {
	  rxState = 1;
	} else {
	}
      }
      else if (rxState == 1) { // Processing first char efter SYN
        switch (data) {
          case EOT: 
          case NAK:
            rxState = 2;
            break;
          case DLE:  // Two byte sequences
            rxState = 3;
            break;
          case SOH:
            byteCounter=2;
            rxState = 4;
            break;
          case STX:
            rxState = 5;
            break;
          default:  // Enquiry POLL / SELECTION
            rxState = 7;
            byteCounter=3; // 4 with this byte
            break;
        }   
      } else if (rxState == 2) {
        // Data shall be PAD.
        if (data == PAD) {
          // We have all data  - Do a callback
          switch (msgBuffer[2]) {
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
              switch (msgBuffer[3]) {
                case 0x70: // ACK 0
                  //Serial.println("ACK0 received");
                  //printMsgBuffer();
                  break;
                case 0x61: // ACK 1
                  //Serial.println("ACK1 received");
                  //printMsgBuffer();
                  break;
                case 0x6b: // WACK
                  //Serial.println("WACK received");
                  //printMsgBuffer();
                  break;
                case 0x7c: // RVI
                  break;
              }
              break;
            case SOH:
              if (msgBuffer[1] == 0x6c) {
                switch (msgBuffer[2]) {
                  case 0xD9:
                    //Serial.println("Status Message received");
                    //printMsgBuffer();
                    break;  // Status Message                
                  case 0x61:
                    //Serial.println("Test request received");
                    //printMsgBuffer();
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
                //Serial.println("Read or write message received");
                //printMsgBuffer();
              break;
            default:  // Selection and POLL ENQ
                //Serial.println("Selection or POLL message ENQ received");
                //printMsgBuffer();
              break;
          }
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
            rxState = 2;
            break;
          default:
            rxState = 0;
            //Serial.println("State violation - going back to hunt mode when waiting for second byte control code");
            //printMsgBuffer();
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
          byteCounter=2;
          rxState = 9;
        } else {
          //Serial.println("State violation - going back to hunt mode when waiting for ETX or ETB");          
          //printMsgBuffer();          
        }
      } else if (rxState==7) {
          byteCounter--;
          //Serial.print("In state 7 byteCounter=");
          //Serial.print(byteCounter, DEC);
          //Serial.println();
          if (byteCounter == 0) {
            rxState = 10; // Get the ENQ
          }
          
      } else if (rxState == 8) {
          // Check for STX then
        if (data == STX) {
          rxState = 5;
        } else { 
          rxState = 0;
          //Serial.println("State violation - going back to hunt mode when waiting for STX");          
          //printMsgBuffer();
        }
      } else if (rxState ==9) {
        // Two CRC digits to be received
        byteCounter--;
        if (byteCounter = 0) {
            // Check CRC
          rxState = 2; // wait for the PAD
        }
      } else if (rxState == 10) {
        if (data == ENQ) {
          rxState = 2; // There is a PAD to come
        }
        else {
          rxState = 0;
          //Serial.println("State violation - going back to hunt mode when waiting for ENQ");
          //printMsgBuffer();
        }
      }
      else {
        // Error
        //Serial.println("Error unknown state!");
        //printMsgBuffer();
        rxState = 0; // Go back to hunt
      }
    }
 
