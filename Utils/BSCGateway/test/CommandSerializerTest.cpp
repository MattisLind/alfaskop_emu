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
    printf(tmp, "%d", val);
    break;
  case HEX:
    printf(tmp, "%X", val);
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
      /*
  case REP_HAND:
  case EOT_MSG:
  case ENQ_MSG:
  case STAT_MSG:
  case TEST_MSG:
  case TEXT_MSG:
  case ACK0_MSG:
  case ACK1_MSG:
  case WACK_MSG:
  case RVI_MSG:
  case NAK_MSG
  }
      */
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
  
}
