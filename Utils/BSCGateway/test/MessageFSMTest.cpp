/*

  Test program for MessageFSM 

  Compile using : c++ MessageFSMTest.cpp ../BSCGateway/MessageFSM.cpp -DDEBUG 

 */

#include <stdio.h>
#include "../BSCGateway/MessageFSM.h"
#include <assert.h>

int testCase=0;
int huntState=0;
void txData (unsigned char);
void receivedMessage(unsigned char, unsigned char *);
void enterHuntState();

class MessageFSM messageFSM(txData, receivedMessage, enterHuntState);

void txData (unsigned char data) {
  // loop the data back into the receiver to test!
  printf ("Received data %02X\n", data);
  messageFSM.rxData(data);
}


void receivedMessage (unsigned char msgType, unsigned char * msg) {
  printf ("msgType = %d\n", msgType);
  switch (testCase) {
  case 0:
    // EOT message sent
    assert (msgType == EOT_MESSAGE);
    assert (msg == NULL);
    testCase = 1;
    break;
  case 1:
    assert (msgType == NAK_MESSAGE);
    assert (msg == NULL);
    testCase = 2;
    break;
  case 2:
    assert (msgType == ACK0_MESSAGE);
    assert (msg == NULL);
    testCase = 3;
    break;
  case 3:
    assert (msgType == ACK1_MESSAGE);
    assert (msg == NULL);
    testCase = 4;
    break;
  }
}

void enterHuntState () {
  huntState = 1;
}

int main () {
  // Testing sending and receiving EOT
  huntState = 0;
  testCase = 0;
  messageFSM.sendEOT();
  assert (testCase == 1);
  assert (huntState == 1);
  // Testing sending and receiving NAK
  huntState = 0;
  testCase = 1;
  messageFSM.sendNAK();
  assert (testCase == 2);
  assert (huntState == 1);
  // Testing sending and receiving ACK0
  huntState = 0;
  testCase = 2;
  messageFSM.sendACK0();
  assert (testCase == 3);
  assert (huntState == 1);
  // Testing sending and receiving ACK1
  huntState = 0;
  testCase = 3;
  messageFSM.sendACK1();
  assert (testCase == 4);
  assert (huntState == 1);

}


