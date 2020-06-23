/*

  Combined test program for MessageFSM, SyncFSM, RingBuffer. To simulate the full implementation 
  at the serial port interface to upper level host and SPI level to sync line
   

  Compile using : compile: c++ -DDEBUG SDLCBridgeTest.cpp -I. -o SDLCBridgeTest ../../SDLCBridge/RingBuffer.cpp ../../SDLCBridge/ebcdic.cpp

 */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "SPI.h"
#include <ctype.h>


#define PB11 5
#define PB1 6
#define PB10 7
#define INPUT 1
#define OUTPUT 2

unsigned long millis() {
  return 0L;
}

class HardwareTimer {

public:
  HardwareTimer(int);
  void pause();
  int setPeriod (int);
  void refresh ();
  void resume ();
  
};




class DebugConsoleSerial {
public:
  void begin (int);
  void print(char);
  void print(const char *);
  void print(int, int);
  void println();
  void println(const char * str);
};


// DebugConsoleSerial::DebugConsoleSerial() {};
void DebugConsoleSerial::begin(int speed) {}
void DebugConsoleSerial::print(char ch) {}
void DebugConsoleSerial::print(const char * str) {}
void DebugConsoleSerial::print(int, int) {}
void DebugConsoleSerial::println() {}
void DebugConsoleSerial::println(const char * str) {}


class DebugHardwareSerial {
public:
  int available ();
  void begin (int);
  void write (char);
  int  read();

};

//DebugHardwareSerial::DebugHardwareSerial() {};
int DebugHardwareSerial::available() {return false;};
void DebugHardwareSerial::begin(int speed) {};
void DebugHardwareSerial::write(char ch) {};
int DebugHardwareSerial::read() { return 0; };



HardwareTimer::HardwareTimer(int timerId) {
}
void HardwareTimer::pause() {
}
void HardwareTimer::refresh() {
}
void HardwareTimer::resume() {
}
int HardwareTimer::setPeriod(int period) {
  return 0;
}

void SPIClass::beginSlave () {
}

void SPIClass::setBitOrder (int bitOrder) {
}
void SPIClass::setDataMode (int dataMode) {
}

SPIClass::SPIClass(int id) {
}

#define PA8 1
#define DEC 0
#define HEX 2
#define PWM 2

void pinMode(int, int) {
};

void pwmWrite (int, int) {
}


void spi_tx_reg(spi_dev *, int) {
}
uint16_t spi_rx_reg(spi_dev *) {
  return 0;
} 
bool spi_is_rx_nonempty(spi_dev *) {
  return true;
}
bool spi_is_tx_empty(spi_dev *) {
  return true;
}

void setup();
void loop();

class DebugConsoleSerial Serial;
class DebugHardwareSerial Serial1;

int main (int argc, char ** argv) {

  setup();
  do {
    loop();
  }
  while (1);
}


#include "../../SDLCBridge/SDLCBridge.ino"



