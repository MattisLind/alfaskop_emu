#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../BSCGateway-STM32/types.h"
#include "../BSCGateway-STM32/Serial.h"
//typedef unsigned char uint8_t;


#include "../BSCGateway-STM32/CommandSerializer.h"


char buffer [1024];
int bufferPtr=0;


Serial::Serial() {}
int Serial::available() {
  return strlen(buffer);
}
void Serial::begin(int speed) {}
void Serial::print(char * str) {
  printf("%s", str);
}
void Serial::print(char ch) {
  printf("%c", ch);
}
void Serial::print(const char * str) {
  printf("%s", str);
};
void Serial::print(char val, int type) {
  switch (type) {
  case DEC:
    printf("%d", val);
    break;
  case HEX:
    printf("%X", val);
  }
}
void Serial::print(short val, int type) {
  switch (type) {
  case DEC:
    printf("%d", val);
    break;
  case HEX:
    printf("%X", val);
  }
}
void Serial::print(long val, int type) {
  switch (type) {
  case DEC:
    printf("%ld", val);
    break;
  case HEX:
    printf("%lX", val);
  }
}
void Serial::print(int val, int type) {
  switch (type) {
  case DEC:
    printf("%d", val);
    break;
  case HEX:
    printf("%X", val);
  }
}
void Serial::println() {
  printf("\n");
};
void Serial::println(char * str) {
  printf("%s\n", str);
};
void Serial::println(char ch) {
  printf("%c\n", ch);
};
void Serial::println(const char * str) {
  printf("%s\n", str);
};
void Serial::write(char ch) {
  printf("%c", ch);
}
int Serial::read() {
  return buffer[bufferPtr++];
}

int testCase;

class Serial Serial;

void processMessage (MSG * msg) {
  switch (testCase) {
  case 0:
    assert(msg->msgType == HAND_REQ);
    testCase = 1;
    break;
      /*
  switch (msg->msgType) {
  case :
    break;
  case SET_HAND:
    break;
    
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

int main () {
  testCase=0;
  //commandSerializer->doRequestHandshakeLineState();
  assert (testCase==1);
}
