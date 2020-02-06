/*

  Test code for ProtocolFSM

  compile using c++ ProtocolFSMTest.cpp ../BSCGateway-STM32/ProtocolFSM.cpp ../BSCGateway-STM32/MessageFSM.cpp ../BSCGateway-STM32/crc-16.c -DDEBUG

 */
#include "../BSCGateway-STM32/ProtocolFSM.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

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
  //printf ("\nrtsIsSet is returing %d\n", tmp);
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

unsigned char receivedBuffer [300];
int receivedBufferPtr;


void txData (unsigned char ch) {
  //printf ("%02X", ch);
  receivedBuffer[receivedBufferPtr++]=ch;
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

char testString1[] = "ABCDEFGHIJKLMNOPQRSTUVXYZ";

void clearBuffer () {
  receivedBufferPtr=0;
}

void assertReceivedMessage(int len, unsigned char * data) {
  int i;
  for (i=0; i<len; i++) {
    //printf ("%02X %02X\n", receivedBuffer[i], data[i]);
    assert(receivedBuffer[i] == data[i]);
  }
  printf("Message received OK!\n");
}

unsigned char ENQmessage [] = {0x32, 0x32, 0x40, 0x40, 0x40, 0x40, 0x2d, 0xff};
unsigned char SelectENQmessage [] = {0x32, 0x32, 0x60, 0x60, 0x40, 0x40, 0x2d, 0xff};
unsigned char ACK1message [] = {0x32, 0x32, 0x10, 0x61, 0xff};

/*
  
  Did a try to refactor test case so that they would be more compact. Moving the assert into function. It turned out to be a bad idea since it
  is hard to track down which line aborts. Better to let the abort stay in the main test flow. Is there a possibility to track which line it was called from and 
  thus get traceability? Create a macro instead of function? A macro was much better since it didn't obscure the causing line. At least not entirely. You at least now what line the expansion took place..

 */

#define assertRTSTransaction(MODE, STATE) {\
  printf ("========================================================\n");\
  printf ("Verifying RTS tranaction going from RTS low to RTS high.\n");\
  printf ("Verifying STATE=%d\n", STATE);assert(protocolFSM.state == (STATE)); \
  printf ("Verifying MODE=%d\n", MODE);assert(protocolFSM.mode == (MODE)); \
  printf ("verifying Substate=PROTOCOL_FSM_SUBSTATE_WAIT_FOR_RTS\n"); assert(protocolFSM.subState == PROTOCOL_FSM_SUBSTATE_WAIT_FOR_RTS); \
  rtsValue = 0; printf("Setting RTS LOW expecting a CTS LOW.\n");  \
  protocolFSM.workerPoll(); assert(ctsValue==0); \
  rtsValue = 1; printf ("Setting RTS HIGH expecting a CTS HIGH.\n");	\
  protocolFSM.workerPoll(); \
  assert (ctsValue == 1); \
  assert(protocolFSM.mode == (MODE)); \
  assert(protocolFSM.state == (STATE));			      \
  assert(protocolFSM.subState == PROTOCOL_FSM_SUBSTATE_IDLE); \
  printf ("========================================================\n"); \
}


void test1 () {
  // First send the poll.
  printf("Testing Poll\n");
  printf("============\n");
  printf ("Now we should get a ENQ message:");
  clearBuffer();
  assert(protocolFSM.state == PROTOCOL_FSM_IDLE);
  protocolFSM.sendPoll(0x40,0x40);
  assertReceivedMessage(8, ENQmessage);
  assertRTSTransaction((PROTOCOL_MODE_POLL), (PROTOCOL_FSM_WAIT_FOR_MSG))
  /*
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
  */


  sendStatusMessage(0x40, 0x40,  0x40, 0x50);
  printf ("Sent the status message in\n");
  assert(protocolFSM.mode == PROTOCOL_MODE_POLL);
  assert(protocolFSM.state == PROTOCOL_FSM_SENDACK);
  assert(protocolFSM.subState == PROTOCOL_FSM_SUBSTATE_WAIT_FOR_NOT_RTS);
  clearBuffer();
  protocolFSM.workerPoll();
  assert(protocolFSM.mode == PROTOCOL_MODE_POLL);
  assert(protocolFSM.state == PROTOCOL_FSM_SENDACK);
  assert(protocolFSM.subState == PROTOCOL_FSM_SUBSTATE_WAIT_FOR_NOT_RTS);
  rtsValue = 0;
  printf("Now we should get a ACK1 message:");
  protocolFSM.workerPoll();
  assertReceivedMessage(5, ACK1message);
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
  printf("Now we send in the EOT message.\n");
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

}

unsigned char Textmessage [] = {0x32, 0x32, 0x02, 0x41, 0x42, 0x43, 0x44, 0x45,
				0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D,
				0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55,
				0x56, 0x58, 0x59, 0x5A, 0x03, 0x75, 0x06, 0xFF};
unsigned char EOTmessage [] = {0x32, 0x32, 0x37, 0xFF};

void test2 () {
  printf ("Testing Write\n");
  printf ("=============\n");
  printf ("Now we should get a ENQ message:");
  assert(protocolFSM.state == PROTOCOL_FSM_IDLE);
  clearBuffer();
  protocolFSM.sendWrite(0x40,0x40, strlen(testString1), (unsigned char *) testString1);
  assertReceivedMessage(8, SelectENQmessage);
  assert(protocolFSM.state == PROTOCOL_FSM_WAIT_FOR_ACK);
  assert(protocolFSM.mode == PROTOCOL_MODE_WRITE);
  assert(protocolFSM.subState == PROTOCOL_FSM_SUBSTATE_WAIT_FOR_RTS);

  
  rtsValue = 0;
  protocolFSM.workerPoll();
  rtsValue = 1;
  protocolFSM.workerPoll();
  assert (ctsValue == 1);
  assert(protocolFSM.mode == PROTOCOL_MODE_WRITE);
  assert(protocolFSM.state == PROTOCOL_FSM_WAIT_FOR_ACK);
  assert(protocolFSM.subState == PROTOCOL_FSM_SUBSTATE_IDLE);
  printf("Sending ACK message\n");
  sendACK0();
  assert(protocolFSM.mode == PROTOCOL_MODE_WRITE);
  assert(protocolFSM.state == PROTOCOL_FSM_SEND_DATA);
  assert(protocolFSM.subState == PROTOCOL_FSM_SUBSTATE_WAIT_FOR_NOT_RTS);
  protocolFSM.workerPoll();
  assert(protocolFSM.mode == PROTOCOL_MODE_WRITE);
  assert(protocolFSM.state == PROTOCOL_FSM_SEND_DATA);
  assert(protocolFSM.subState == PROTOCOL_FSM_SUBSTATE_WAIT_FOR_NOT_RTS);
  rtsValue = 0;
  clearBuffer();
  printf ("Now we should get a Text message:");
  protocolFSM.workerPoll();
  assertReceivedMessage(32, Textmessage);

  
  assert (ctsValue == 0);
  assert(protocolFSM.mode == PROTOCOL_MODE_WRITE);
  assert(protocolFSM.state == PROTOCOL_FSM_WAIT_FOR_ACK);
  assert(protocolFSM.subState == PROTOCOL_FSM_SUBSTATE_WAIT_FOR_RTS);
  protocolFSM.workerPoll();
  assert(protocolFSM.mode == PROTOCOL_MODE_WRITE);
  assert(protocolFSM.state == PROTOCOL_FSM_WAIT_FOR_ACK);
  assert(protocolFSM.subState == PROTOCOL_FSM_SUBSTATE_WAIT_FOR_RTS);
  rtsValue = 1;
  protocolFSM.workerPoll();
  assert (ctsValue == 1);
  assert(protocolFSM.mode == PROTOCOL_MODE_WRITE);
  assert(protocolFSM.state == PROTOCOL_FSM_WAIT_FOR_ACK);
  assert(protocolFSM.subState == PROTOCOL_FSM_SUBSTATE_IDLE);
  printf("Sending ACK message\n");
  sendACK1();
  assert(protocolFSM.mode == PROTOCOL_MODE_WRITE);
  assert(protocolFSM.state == PROTOCOL_FSM_SEND_DATA);
  assert(protocolFSM.subState == PROTOCOL_FSM_SUBSTATE_WAIT_FOR_NOT_RTS);
  rtsValue=0;
  printf("Now we should get a EOT message:");
  clearBuffer();
  protocolFSM.workerPoll();
  assertReceivedMessage(4, EOTmessage);
  
  assert (ctsValue == 0);
  assert(protocolFSM.mode == PROTOCOL_MODE_WRITE);
  assert(protocolFSM.state == PROTOCOL_FSM_IDLE);
  assert(protocolFSM.subState == PROTOCOL_FSM_SUBSTATE_IDLE);

}

int main () {
  test1();
  printf("\n");
  test2();
  printf("\n");
  return 0;
}
