
#ifdef LINUX
/*

  Implement wrapper for Arduino environment for
  Serial and Wifi so we could have the same code in Linux as well as ESP32.


  Compile on Macos: c++ -DLINUX -DMACOS main.cpp Serial.cpp
  Compile on Linux: c++ -DLINUX  main.cpp Serial.cpp

  Run as sudo to be able to open the serial port.

*/
#include "Serial.h"

void setup();
void loop();

class Serial Serial ("/dev/ttyUSB1");

int main (int argc, char ** argv) {

  setup();
  do {
    loop();
  }
  while (1);
  return 0;
}


#include "BSCGateway-ESP32.ino"

#endif
