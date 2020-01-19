/*

  Test program for MessageFSM 

  Compile using : c++ MessageFSMTest.cpp ../BSCGateway/MessageFSM.cpp -DDEBUG 

 */

#include <stdio.h>
#include "../BSCGateway/MessageFSM.h"
#include <assert.h>
#include <string.h>

int testCase=0;
int huntState=0;
bool errorOverride = false;
void txData (unsigned char);
void receivedMessage(unsigned char, unsigned char *);
void enterHuntState();
const char * testRequestString = "This is a test message";

class MessageFSM messageFSM(txData, receivedMessage, enterHuntState);

void txData (unsigned char data) {
  // loop the data back into the receiver to test!
  //printf ("Received data %02X\n", data);
  messageFSM.rxData(data);
}


void receivedMessage (unsigned char msgType, unsigned char * msg) {
  MSG * m;
  m = (MSG *) msg;
  if (msgType == ERROR_MESSAGE && !errorOverride) {
    printf("%s\n", msg);
    assert (0);
  }
  //printf ("msgType = %d\n", msgType);
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
  case 4:
    assert (msgType == WACK_MESSAGE);
    assert (msg == NULL);
    testCase = 5;
    break;
  case 5:
    assert (msgType == RVI_MESSAGE);
    assert (msg == NULL);
    testCase = 6;
    break;
  case 6:
    assert (msgType == ENQ_MESSAGE);
    assert (msg[0] == 0x40);
    assert (msg[1] == 0x40);
    assert (msg[2] == 0x41);
    assert (msg[3] == 0x41);
    testCase = 7;
    break;
  case 7:
    assert (msgType == STATUS_MESSAGE);

    assert (m->statusData.CU == 0x40); // CU
    assert (m->statusData.DV == 0x41); // DV
    assert (m->statusData.status == 0x42); // Status
    assert (m->statusData.sense == 0x43); // Sense
    testCase = 8;
    break;
  case 8:
    assert (msgType == TEST_MESSAGE);
    assert (m->testData.thereIsMoreComing == false);
    assert (m->testData.length == strlen(testRequestString));
    assert ((strncmp ((char *) m->testData.msg,testRequestString ,m->testData.length) == 0));
    testCase = 9;
    break;
  case 9:
    assert (msgType == TEXT_MESSAGE);
    assert (m->testData.thereIsMoreComing == false);
    assert (m->testData.length == strlen(testRequestString));
    assert ((strncmp ((char *) m->testData.msg,testRequestString ,m->testData.length) == 0));
    testCase = 10;
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
  printf("Test passed -  sending and receiving EOT\n");
  // Testing sending and receiving NAK
  huntState = 0;
  testCase = 1;
  messageFSM.sendNAK();
  assert (testCase == 2);
  assert (huntState == 1);
  printf("Test passed -  sending and receiving NAK\n");
  // Testing sending and receiving ACK0
  huntState = 0;
  testCase = 2;
  messageFSM.sendACK0();
  assert (testCase == 3);
  assert (huntState == 1);
  printf("Test passed -  sending and receiving ACK0\n");  
  // Testing sending and receiving ACK1
  huntState = 0;
  testCase = 3;
  messageFSM.sendACK1();
  assert (testCase == 4);
  assert (huntState == 1);
  printf("Test passed -  sending and receiving ACK1\n");  
  // Testing sending and receiving WACK
  huntState = 0;
  testCase = 4;
  messageFSM.sendWACK();
  assert (testCase == 5);
  assert (huntState == 1);
  printf("Test passed -  sending and receiving WACK\n");  
  // Testing sending and receiving RVI
  huntState = 0;
  testCase = 5;
  messageFSM.sendRVI();
  assert (testCase == 6);
  assert (huntState == 1);
  printf("Test passed -  sending and receiving RVI\n");  
  // Testing sending and receiving ENQ
  huntState = 0;
  testCase = 6;
  messageFSM.sendENQ(0x40,0x41);
  assert (testCase == 7);
  assert (huntState == 1);
  printf("Test passed -  sending and receiving ENQ\n");
  // Testing sending and receiving Status Message
  huntState = 0;
  testCase = 7;
  messageFSM.sendStatusMessage(0x40,0x41,0x42,0x43);
  assert (testCase == 8);
  assert (huntState == 1);
  printf("Test passed -  sending and receiving Status Message\n");
  // Testing sending and receiving Test Message
  huntState = 0;
  testCase = 8;
  messageFSM.sendTestRequestMessage(strlen (testRequestString), (unsigned char *) testRequestString, false);
  assert (testCase == 9);
  assert (huntState == 1);
  printf("Test passed -  sending and receiving Test Message\n");
  // Testing sending and receiving Text Message
  huntState = 0;
  testCase = 9;
  messageFSM.sendTextMessage(strlen (testRequestString), (unsigned char *) testRequestString, false);
  assert (testCase == 10);
  assert (huntState == 1);
  printf("Test passed -  sending and receiving Text Message\n");

}


