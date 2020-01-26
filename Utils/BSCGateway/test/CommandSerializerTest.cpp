/*

  Tests for the CommandSerializer class

  Compile using c++ ../BSCGateway-STM32/CommandSerializer.cpp CommandSerializerTest.cpp

*/




#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../BSCGateway-STM32/types.h"
#include "../BSCGateway-STM32/Serial.h"
//typedef unsigned char uint8_t;


#include "../BSCGateway-STM32/CommandSerializer.h"


  

Serial::Serial() {}

void Serial::flush() {
  currentBufferPointer=buffer;
}

int Serial::available() {
  return strlen(currentBufferPointer);
}
void Serial::begin(int speed) {}
void Serial::print(char * str) {
  sprintf(currentBufferPointer, "%s", str);
  currentBufferPointer+=strlen(str);  
}
void Serial::print(char ch) {
  sprintf(currentBufferPointer,"%c", ch);
  *(++currentBufferPointer) = '\0';
}
void Serial::print(const char * str) {
  sprintf(currentBufferPointer, "%s", str);
  currentBufferPointer+=strlen(str);
  *currentBufferPointer = '\0';
};

void Serial::print(char val, int type) {
  char tmp [16];
  switch (type) {
  case DEC:
    sprintf(tmp,"%d", val);
    break;
  case HEX:
    sprintf(tmp,"%X", val);
  }
  strcpy(currentBufferPointer, tmp);
  currentBufferPointer+= strlen(tmp);
  *currentBufferPointer = '\0';
}

void Serial::print(short val, int type) {
  char tmp [16];
  switch (type) {
  case DEC:
    sprintf(tmp,"%d", val);
    break;
  case HEX:
    sprintf(tmp,"%X", val);
  }
  strcpy(currentBufferPointer, tmp);
  currentBufferPointer+= strlen(tmp);
  *currentBufferPointer = '\0';
}
void Serial::print(long val, int type) {
  char tmp [16];
  switch (type) {
  case DEC:
    sprintf(tmp,"%ld", val);
    break;
  case HEX:
    sprintf(tmp,"%lX", val);
  }
  strcpy(currentBufferPointer, tmp);
  currentBufferPointer+= strlen(tmp);
  *currentBufferPointer = '\0';
}
void Serial::print(int val, int type) {
  char tmp [16];
  switch (type) {
  case DEC:
    sprintf(tmp, "%d", val);
    break;
  case HEX:
    sprintf(tmp, "%X", val);
  }
  strcpy(currentBufferPointer, tmp);
  currentBufferPointer+= strlen(tmp);
  *currentBufferPointer = '\0';
}
void Serial::println() {
  sprintf(currentBufferPointer, "\n");
  *(++currentBufferPointer) = '\0';
};
void Serial::println(char * str) {
  sprintf(currentBufferPointer, "%s\n", str);
  currentBufferPointer+=strlen(str);
  *(++currentBufferPointer) = '\0';
};
void Serial::println(char ch) {
  sprintf(currentBufferPointer, "%c\n", ch);
  currentBufferPointer+=2;
  *currentBufferPointer = '\0';
};
void Serial::println(const char * str) {
  sprintf(currentBufferPointer, "%s\n", str);
  currentBufferPointer+=strlen(str);
  *(++currentBufferPointer) = '\0';

};
void Serial::write(char ch) {
  sprintf(currentBufferPointer,"%c", ch);
  *(++currentBufferPointer) = '\0';
}
int Serial::read() {
  return *(currentBufferPointer++) ;
}

void Serial::debugPrint() {
  printf ("%s", buffer);
}

char testString [] = "This is a test message ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890+-.,#$%&/()=";

  

int testCase;

class Serial Serial;

void processMessage (MSG * msg) {
  switch (testCase) {
  case 0:
    assert(msg->type == HAND_REQ);
    printf ("Test case 0: G command DONE!\n");    
    testCase = 1;
    break;
  case 1:
    assert(msg->type == SET_HAND);
    assert(msg->data.handshakeData.rts == 1);
    assert(msg->data.handshakeData.cts == 0);
    assert(msg->data.handshakeData.dtr == -1);
    printf ("Test case 1 H: command DONE!\n");    
    testCase = 2;
    break;
  case 2:
    assert(msg->type == REP_HAND);
    assert(msg->data.handshakeData.rts == -1);
    assert(msg->data.handshakeData.cts == 1);
    assert(msg->data.handshakeData.dtr == 0);
    printf ("Test case 2 I: command DONE!\n");    
    testCase = 3;
    break;
  case 3:
    assert(msg->type == EOT_MSG);
    printf ("Test case 3 Q: command DONE!\n");    
    testCase = 4;
    break;
  case 4:
    assert(msg->type == ENQ_MSG);
    assert(msg->data.enqData.CU == 0x40);
    assert(msg->data.enqData.DV == 0x41);
    printf ("Test case 4 P: command DONE!\n");    
    testCase = 5;
    break;
  case 5:
    assert(msg->type == STAT_MSG);
    assert(msg->data.statusData.CU == 0x42);
    assert(msg->data.statusData.DV == 0x43);
    assert(msg->data.statusData.status == 0x44);
    assert(msg->data.statusData.sense == 0x45);
    printf ("Test case 6 S: command DONE!\n");    
    testCase = 6;
    break;
  case 6:
    assert(msg->type == TEST_MSG);
    assert(msg->data.testData.length == (strlen(testString)+1));
    printf ("testString::%s::\n", msg->data.testData.msg);
    assert(strncmp((const char *) msg->data.testData.msg, testString, msg->data.testData.length) == 0);
    assert(msg->data.testData.thereIsMoreComing == false);
    printf ("Test case 7 X: command DONE!\n");    
    testCase = 7;
    break;
  case 7:
    assert(msg->type == TEXT_MSG);
    assert(msg->data.textData.length == (strlen(testString)+1));
    printf ("testString::%s::\n", msg->data.textData.msg);
    assert(strncmp((const char *) msg->data.textData.msg, testString, msg->data.textData.length) == 0);
    assert(msg->data.textData.thereIsMoreComing == false);
    printf ("Test case 7 X: command DONE!\n");    
    testCase = 8;
    break;
  case 8:
    assert(msg->type == ACK0_MSG);
    printf ("Test case 8 L: command DONE!\n");    
    testCase = 9;
    break;
  case 9:
    assert(msg->type == ACK1_MSG);
    printf ("Test case 9 M: command DONE!\n");    
    testCase = 10;
    break;
  case 10:
    assert(msg->type == WACK_MSG);
    printf ("Test case 10 W: command DONE!\n");    
    testCase = 11;
    break;
  case 11:
    assert(msg->type == RVI_MSG);
    printf ("Test case 11 R: command DONE!\n");    
    testCase = 12;
    break;
  case 12:
    assert(msg->type == NAK_MSG);
    printf ("Test case 12 N: command DONE!\n");    
    testCase = 13;
    break;
  }
  
}


#include "../BSCGateway-STM32/CommandSerializer.h"

class CommandSerializer commandSerializer (Serial, processMessage);



void doTest() {
  char tmp;
  int ret;
  Serial.debugPrint();
  Serial.flush();
  while ((ret = Serial.available())>0) {
    tmp = Serial.read();
    printf ("available=%d ch=%c ch=%02X\n", ret, tmp, tmp);
    commandSerializer.processCharacter(/* Serial.read()*/ tmp);
  }       
}


int main () {
  testCase=0;
  Serial.flush();
  commandSerializer.doRequestHandshakeLineState();
  doTest();
  assert (testCase==1);
  Serial.flush();
  commandSerializer.doSetResetHandshakeLines(1, 0, -1);
  doTest();
  assert (testCase==2);
  Serial.flush();
  commandSerializer.doHandshakeLinesChanged(-1, 1, 0);
  doTest();
  assert (testCase==3);
  Serial.flush();
  commandSerializer.doEOT();
  doTest();
  assert (testCase==4);  
  Serial.flush();
  commandSerializer.doENQ(0x40, 0x41);
  doTest();
  assert (testCase==5);  
  Serial.flush();
  commandSerializer.doStatus(0x42, 0x43, 0x44, 0x45);
  doTest();
  assert (testCase==6);  
  Serial.flush();
  commandSerializer.doTestRequestMessage(testString, strlen(testString)+1, false);
  doTest();
  assert (testCase==7);  
  Serial.flush();
  commandSerializer.doTextMessage(testString, strlen(testString)+1, false);
  doTest();
  assert (testCase==8);  
  Serial.flush();
  commandSerializer.doACK0();
  doTest();
  assert (testCase==9);  
  Serial.flush();
  commandSerializer.doACK1();
  doTest();
  assert (testCase==10);  
  Serial.flush();
  commandSerializer.doWACK();
  doTest();
  assert (testCase==11);  
  Serial.flush();
  commandSerializer.doRVI();
  doTest();
  assert (testCase==12);  
  Serial.flush();
  commandSerializer.doNAK();
  doTest();
  assert (testCase==13);  
}
