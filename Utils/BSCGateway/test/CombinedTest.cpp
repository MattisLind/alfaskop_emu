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



void setup();
void loop();

class Serial Serial ("/dev/ttyUSB0");

main (int argc, char ** argv) {

  setup();
  do {
    loop();
  }
  while (1);
}


#include "../BSCGateway-STM32/BSCGateway-STM32.ino"

#endif


