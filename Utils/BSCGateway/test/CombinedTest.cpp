/*

  Combined test program for MessageFSM, SyncFSM, RingBuffer. To simulate the full implementation 
  at the serial port interface to upper level host and SPI level to sync line
   

  Compile using : c++ MessageFSMTest.cpp ../BSCGateway-STM32/MessageFSM.cpp ../BSCGateway-STM32/SyncFSM.cpp ../BSCGateway-STM32/RingBuffer.cpp  -DDEBUG 

 */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../BSCGateway-STM32/SyncFSM.h"
#include "../BSCGateway-STM32/ebcdic.h"
#include "../BSCGateway-STM32/MessageFSM.h"
#include "../BSCGateway-STM32/RingBuffer.h"

class HardwareTimer {

public:
  HardwareTimer(int);
  void pause();
  int setPeriod (int);
  void refresh ();
  void resume ();
  
};


class Serial {

public:
  Serial ();
  int available ();
  void begin (int);
  void print(char * str);
  void print(char);
  void print(const char * str);
  void print(char, int);
  void print(short, int);
  void print(long, int);
  void println();
  void println(char * str);
  void println(const char * str);
  void write (char);
};


#define PA8 1
#define DEC 0
#define HEX 2
#define PWM 2

void pinMode(int, int) {
};

void pwmWrite (int, int) {
}


void setup();
void loop();

class Serial Serial;
class Serial Serial1;

int main (int argc, char ** argv) {

  setup();
  do {
    loop();
  }
  while (1);
}


#include "../BSCGateway-STM32/BSCGateway-STM32.ino"

#endif


