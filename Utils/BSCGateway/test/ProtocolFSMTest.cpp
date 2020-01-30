/*

  Test code for ProtocolFSM

  compile using c++ ProtocolFSMTest.cpp ../BSCGateway-STM32/ProtocolFSM.cpp ../BSCGateway-STM32/MessageFSM.cpp ../BSCGateway-STM32/crc-16.c -DDEBUG

 */
#include "../BSCGateway-STM32/ProtocolFSM.h"

void txData (unsigned char);
void receivedMessage(unsigned char, unsigned char *);
void enterHuntState();
void protocolResponse (ProtocolMsg * pMsg);

class MessageFSM messageFSM(txData, receivedMessage, enterHuntState);
class ProtocolFSM protocolFSM(messageFSM, protocolResponse );


void receivedMessage(unsigned char type, unsigned char * msg) {
  protocolFSM.receivedMessage(type, (MSG *) msg);
}

void txData (unsigned char ch) {
}
void enterHuntState() {
}
void protocolResponse (ProtocolMsg * pMsg) {
}


int rts;


int main () {
  // First send the poll.
  protocolFSM.sendPoll(0x40,0x40);
  // Now we need to do a poll to have the worker inside to the work.
  rts = 0;
  protocolFSM.workerPoll();
  rts = 1;
  protocolFSM.workerPoll();
  
}
