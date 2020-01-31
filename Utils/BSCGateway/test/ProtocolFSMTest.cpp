/*

  Test code for ProtocolFSM

  compile using c++ ProtocolFSMTest.cpp ../BSCGateway-STM32/ProtocolFSM.cpp ../BSCGateway-STM32/MessageFSM.cpp ../BSCGateway-STM32/crc-16.c -DDEBUG

 */
#include "../BSCGateway-STM32/ProtocolFSM.h"
#include <assert.h>
#include <stdio.h>

unsigned short calculateCrcChar (unsigned short crc, unsigned char data_p);
void txData (unsigned char);
void receivedMessage(unsigned char, unsigned char *);
void enterHuntState();
void protocolResponse (ProtocolMsg * pMsg);

int ctsValue;

void digitalWrite(int pin, int value) {
  ctsValue  = value;
}


int rtsValue;

int digitalRead (int pin) {
  return rtsValue;
}


#define RTS 1  
#define CTS 2

bool rtsIsSet() {
  bool tmp = (digitalRead(RTS)==1);
  printf ("\nrtsIsSet is returing %d\n", tmp);
  return tmp;
}

void cts(bool value) {
  digitalWrite(CTS, value?1:0);
}




class MessageFSM messageFSM(txData, receivedMessage, enterHuntState);
class ProtocolFSM protocolFSM(messageFSM, protocolResponse, rtsIsSet, cts );


void receivedMessage(unsigned char type, unsigned char * msg) {
  protocolFSM.receivedMessage(type, (MSG *) msg);
}

void txData (unsigned char ch) {
  printf ("%02X", ch);
}
void enterHuntState() {
}
void protocolResponse (ProtocolMsg * pMsg) {
}


void sendEOT(){
  messageFSM.rxData(SYN);
  messageFSM.rxData(SYN);
  messageFSM.rxData(EOT);
  messageFSM.rxData(PAD);
}
void sendENQ(uint8_t CU, uint8_t DV){
  messageFSM.rxData(SYN);
  messageFSM.rxData(SYN);
  messageFSM.rxData(CU);
  messageFSM.rxData(CU);
  messageFSM.rxData(DV);
  messageFSM.rxData(DV);
  messageFSM.rxData(ENQ);
  messageFSM.rxData(PAD);  
}
void sendStatusMessage(uint8_t CU, uint8_t DV,  uint8_t status, uint8_t sense) {
  int crc=0;
  messageFSM.rxData(SYN);
  messageFSM.rxData(SYN);
  messageFSM.rxData(SOH);
  messageFSM.rxData(0x6c);
  crc = calculateCrcChar (crc, 0x6c);
  messageFSM.rxData(0xd9);
  crc = calculateCrcChar (crc, 0xd9);
  messageFSM.rxData(STX);
  crc = calculateCrcChar (crc, STX);
  messageFSM.rxData(CU);
  crc = calculateCrcChar (crc, CU);
  messageFSM.rxData(DV);
  crc = calculateCrcChar (crc, DV);
  messageFSM.rxData(status);
  crc = calculateCrcChar (crc, status);
  messageFSM.rxData(sense);  
  crc = calculateCrcChar (crc, sense);
  messageFSM.rxData(ETX);
  crc = calculateCrcChar (crc, ETX);
  messageFSM.rxData(crc & 0xff);
  messageFSM.rxData((crc >> 8) & 0xff);
  messageFSM.rxData(PAD);
}

void sendTestRequestMessage(int messageLength, uint8_t * msg, bool thereIsMoreComing) {
  int i;
  int crc=0;
  messageFSM.rxData(SYN);
  messageFSM.rxData(SYN);
  messageFSM.rxData(SOH);
  messageFSM.rxData(0x6c);
  crc = calculateCrcChar (crc, 0x6c);
  messageFSM.rxData(0x61);
  crc = calculateCrcChar (crc, 0x61);
  messageFSM.rxData(STX);
  crc = calculateCrcChar (crc, STX);
  for (i=0; i<messageLength; i++) {
    messageFSM.rxData(msg[i]);
    crc = calculateCrcChar (crc, msg[i]);
  }
  if (thereIsMoreComing) {
    messageFSM.rxData(ETB);
    crc = calculateCrcChar (crc, ETB);
  } else {
    messageFSM.rxData(ETX);
    crc = calculateCrcChar (crc, ETX);
  }
  messageFSM.rxData(crc & 0xff);
  messageFSM.rxData((crc >> 8) & 0xff);
  messageFSM.rxData(PAD);
}

void sendTextMessage(int messageLength, uint8_t * msg, bool thereIsMoreComing) {
  int i;
  int crc=0;
  messageFSM.rxData(SYN);
  messageFSM.rxData(SYN);
  messageFSM.rxData(STX);
  for (i=0; i<messageLength; i++) {
    messageFSM.rxData(msg[i]);
    crc = calculateCrcChar (crc, msg[i]);
  }
  if (thereIsMoreComing) {
    messageFSM.rxData(ETB);
    crc = calculateCrcChar (crc, ETB);
  } else {
    messageFSM.rxData(ETX);
    crc = calculateCrcChar (crc, ETX);
  }
  messageFSM.rxData(crc & 0xff);
  messageFSM.rxData((crc >> 8) & 0xff);
  messageFSM.rxData(PAD);
}
void sendACK0(){
  messageFSM.rxData(SYN);
  messageFSM.rxData(SYN);
  messageFSM.rxData(DLE);
  messageFSM.rxData(0x70);
  messageFSM.rxData(PAD);
}
void sendACK1(){
  messageFSM.rxData(SYN);
  messageFSM.rxData(SYN);
  messageFSM.rxData(DLE);
  messageFSM.rxData(0x61);
  messageFSM.rxData(PAD);
}
void sendWACK(){
  messageFSM.rxData(SYN);
  messageFSM.rxData(SYN);
  messageFSM.rxData(DLE);
  messageFSM.rxData(0x6b);
  messageFSM.rxData(PAD);
}
void sendRVI(){
 messageFSM.rxData(SYN);
  messageFSM.rxData(SYN);
  messageFSM.rxData(DLE);
  messageFSM.rxData(0x7c);
  messageFSM.rxData(PAD);
}
void sendNAK(){
  messageFSM.rxData(SYN);
  messageFSM.rxData(SYN);
  messageFSM.rxData(NAK);
  messageFSM.rxData(PAD);
}





int main () {
  // First send the poll.
  printf ("\nNow we should get a ENQ message:");
  assert(protocolFSM.state == PROTOCOL_FSM_IDLE);
  protocolFSM.sendPoll(0x40,0x40);
  assert(protocolFSM.state == PROTOCOL_FSM_WAIT_FOR_MSG);
  assert(protocolFSM.mode == PROTOCOL_MODE_POLL);
  assert(protocolFSM.subState == PROTOCOL_FSM_SUBSTATE_WAIT_FOR_RTS);
  // Now we need to do a poll to have the worker inside to the work.
  rtsValue = 0;
  protocolFSM.workerPoll();
  rtsValue = 1;
  protocolFSM.workerPoll();
  assert (ctsValue == 1);
  assert(protocolFSM.mode == PROTOCOL_MODE_POLL);
  assert(protocolFSM.state == PROTOCOL_FSM_WAIT_FOR_MSG);
  assert(protocolFSM.subState == PROTOCOL_FSM_SUBSTATE_IDLE);
  sendStatusMessage(0x40, 0x40,  0x40, 0x50);
  printf ("Sent the status message in\n");
  assert(protocolFSM.mode == PROTOCOL_MODE_POLL);
  assert(protocolFSM.state == PROTOCOL_FSM_SENDACK);
  assert(protocolFSM.subState == PROTOCOL_FSM_SUBSTATE_WAIT_FOR_NOT_RTS);
  protocolFSM.workerPoll();
  assert(protocolFSM.mode == PROTOCOL_MODE_POLL);
  assert(protocolFSM.state == PROTOCOL_FSM_SENDACK);
  assert(protocolFSM.subState == PROTOCOL_FSM_SUBSTATE_WAIT_FOR_NOT_RTS);
  rtsValue = 0;
  printf("\nNow we should get a ACK1 message:");
  protocolFSM.workerPoll();
  assert (ctsValue == 0);
  assert(protocolFSM.mode == PROTOCOL_MODE_POLL);
  assert(protocolFSM.state == PROTOCOL_FSM_WAIT_FOR_MSG);
  assert(protocolFSM.subState == PROTOCOL_FSM_SUBSTATE_WAIT_FOR_RTS);
  protocolFSM.workerPoll();
  assert(protocolFSM.mode == PROTOCOL_MODE_POLL);
  assert(protocolFSM.state == PROTOCOL_FSM_WAIT_FOR_MSG);
  assert(protocolFSM.subState == PROTOCOL_FSM_SUBSTATE_WAIT_FOR_RTS);
  rtsValue = 1;
  protocolFSM.workerPoll();
  assert(protocolFSM.mode == PROTOCOL_MODE_POLL);
  assert(protocolFSM.state == PROTOCOL_FSM_WAIT_FOR_MSG);
  assert(protocolFSM.subState == PROTOCOL_FSM_SUBSTATE_IDLE);
  assert (ctsValue == 1);
  printf("\nNow we send in the EOT message.\n");
  sendEOT();
  assert(protocolFSM.mode == PROTOCOL_MODE_POLL);
  assert(protocolFSM.state == PROTOCOL_FSM_IDLE);
  assert(protocolFSM.subState == PROTOCOL_FSM_SUBSTATE_WAIT_FOR_NOT_RTS);  
  protocolFSM.workerPoll();
  assert(protocolFSM.mode == PROTOCOL_MODE_POLL);
  assert(protocolFSM.state == PROTOCOL_FSM_IDLE);
  assert(protocolFSM.subState == PROTOCOL_FSM_SUBSTATE_WAIT_FOR_NOT_RTS);
  rtsValue = 0;
  protocolFSM.workerPoll();
  assert(ctsValue == 0);
  assert(protocolFSM.mode == PROTOCOL_MODE_POLL);
  assert(protocolFSM.state == PROTOCOL_FSM_IDLE);
  assert(protocolFSM.subState == PROTOCOL_FSM_SUBSTATE_IDLE);
  printf ("Test done\n");

  printf ("Testing Write\n");

  printf ("\nNow we should get a ENQ message:");
  assert(protocolFSM.state == PROTOCOL_FSM_IDLE);
  protocolFSM.sendWrite(0x40,0x40, (unsigned char *) "ABCDEFGHIJKLMNOPQRSTUVXYZ");
  assert(protocolFSM.state == PROTOCOL_FSM_WAIT_FOR_MSG);
  assert(protocolFSM.mode == PROTOCOL_MODE_WRITE);
  assert(protocolFSM.subState == PROTOCOL_FSM_SUBSTATE_WAIT_FOR_RTS);
  // Now we need to do a poll to have the worker inside to the work.
  rtsValue = 0;
  protocolFSM.workerPoll();
  rtsValue = 1;
  protocolFSM.workerPoll();
  assert (ctsValue == 1);
  assert(protocolFSM.mode == PROTOCOL_MODE_WRITE);
  assert(protocolFSM.state == PROTOCOL_FSM_WAIT_FOR_MSG);
  assert(protocolFSM.subState == PROTOCOL_FSM_SUBSTATE_IDLE);
  printf("Sending ACK message\n");
  sendACK0();
  assert(protocolFSM.mode == PROTOCOL_MODE_WRITE);
  assert(protocolFSM.state == PROTOCOL_SEND_FSM_DATA);
  assert(protocolFSM.subState == PROTOCOL_FSM_SUBSTATE_WAIT_FOR_NOT_RTS);
  protocolFSM.workerPoll();
  assert(protocolFSM.mode == PROTOCOL_MODE_WRITE);
  assert(protocolFSM.state == PROTOCOL_SEND_FSM_DATA);
  assert(protocolFSM.subState == PROTOCOL_FSM_SUBSTATE_WAIT_FOR_NOT_RTS);
  rtsValue = 0;
  protocolFSM.workerPoll();
  assert (ctsValue == 0);
  assert(protocolFSM.mode == PROTOCOL_MODE_WRITE);
  assert(protocolFSM.state == PROTOCOL_FSM_WAIT_FOR_MSG);
  assert(protocolFSM.subState == PROTOCOL_FSM_SUBSTATE_IDLE);

}
