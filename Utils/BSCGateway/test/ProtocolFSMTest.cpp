/*

  Test code for ProtocolFSM

  compile using c++ ProtocolFSMTest.cpp ../BSCGateway-STM32/ProtocolFSM.cpp ../BSCGateway-STM32/MessageFSM.cpp ../BSCGateway-STM32/crc-16.c -DDEBUG

 */
#include "../BSCGateway-STM32/ProtocolFSM.h"
#include <assert.h>
#include <stdio.h>


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
  return digitalRead(RTS)==1;
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
}
void enterHuntState() {
}
void protocolResponse (ProtocolMsg * pMsg) {
}



int main () {
  // First send the poll.
  protocolFSM.sendPoll(0x40,0x40);
  // Now we need to do a poll to have the worker inside to the work.
  rtsValue = 0;
  protocolFSM.workerPoll();
  rtsValue = 1;
  protocolFSM.workerPoll();
  assert (ctsValue == 1);
}
