/*

  Combined test program for MessageFSM, SyncFSM, RingBuffer. To simulate the full implementation 
  at the serial port interface to upper level host and SPI level to sync line
   

  Compile using : c++ MessageFSMTest.cpp ../BSCGateway-STM32/MessageFSM.cpp ../BSCGateway-STM32/SyncFSM.cpp ../BSCGateway-STM32/RingBuffer.cpp  -DDEBUG 

 */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../BSCGateway-STM32/lsbmsb.h"
#include "../BSCGateway-STM32/SyncFSM.h"
#include "../BSCGateway-STM32/ebcdic.h"
#include "../BSCGateway-STM32/MessageFSM.h"
#include "../BSCGateway-STM32/RingBuffer.h"
#include "SPI.h"


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
  void print(int, int);
  void println();
  void println(char * str);
  void println(const char * str);
  void write (char);
  int  read();
};


Serial::Serial() {};
int Serial::available() {};
void Serial::begin(int speed) {};
void Serial::print(char * str) {};
void Serial::print(char ch) {};
void Serial::print(const char * str) {};
void Serial::print(char, int) {};
void Serial::print(short, int) {};
void Serial::print(long, int) {};
void Serial::print(int, int) {};
void Serial::println() {};
void Serial::println(char * str) {};
void Serial::println(const char * str) {};
void Serial::write(char ch) {};
int Serial::read() {};


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
uint16 spi_rx_reg(spi_dev *) {
} 
bool spi_is_rx_nonempty(spi_dev *) {
}
bool spi_is_tx_empty(spi_dev *) {
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



