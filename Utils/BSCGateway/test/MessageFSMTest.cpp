/*

  Test program for MessageFSM 

  Compile using : c++ MessageFSMTest.cpp ../BSCGateway/MessageFSM.cpp -DDEBUG 

 */

#include <stdio.h>
#include "../BSCGateway/MessageFSM.h"
#include <assert.h>

int testCase;

void txData (unsigned char);
void receivedMessage(unsigned char, unsigned char *);

class MessageFSM messageFSM(txData, receivedMessage);

void txData (unsigned char data) {
  // loop the data back into the receiver to test!
  printf ("Received data %02X\n", data);
  messageFSM.rxData(data);
}


void receivedMessage (unsigned char msgType, unsigned char * msg) {
  switch (testCase) {
  case 0:
    // EOT message sent
    assert (msgType == EOT_MESSAGE);
    assert (msg == NULL);
    testCase++;
    break;
  }
}

int main () {
  testCase = 0;
  messageFSM.sendEOT();
  assert (testCase == 1);
}


