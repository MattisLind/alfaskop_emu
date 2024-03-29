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
#include <stdlib.h>
#include <sys/time.h>
#include "../../SDLCBridge/RingBuffer.h"

#define PB11 5
#define PB1 6
#define PB10 7
#define INPUT 1
#define OUTPUT 2
#define PA8 1
#define DEC 0
#define HEX 2
#define PWM 2



unsigned long millis() {
  struct timeval  tv;
  gettimeofday(&tv, NULL);

  long time_in_mill =  (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 ; // convert tv_sec & tv_usec to millisecond
  // printf("millis() called returning %lU\n", time_in_mill);
  return time_in_mill;
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
  //void print(unsigned long);
  void println();
  void println(const char * str);
};


// DebugConsoleSerial::DebugConsoleSerial() {};
void DebugConsoleSerial::begin(int speed) {}
void DebugConsoleSerial::print(char ch) {
  putchar(ch);
}
/*
void DebugConsoleSerial::print(unsigned long number) {
  printf("%lU", number);
  }*/
void DebugConsoleSerial::print(const char * str) {
  puts(str);
}
void DebugConsoleSerial::print(int number, int type) {
  char buf[32];
  switch (type) {
  case HEX:
    printf("%X",number);
    break;
  case DEC:
    printf("%d",number);
    break;
  }
}
void DebugConsoleSerial::println() {
  putchar('\n');
}
void DebugConsoleSerial::println(const char * str) {
  puts(str);
  putchar('\n');
}


class DebugHardwareSerial {
  char * readBuffer;
  int readBufferLength;
  int readPtr;
public:
  int available ();
  void begin (int);
  void write (char);
  int  read();
  void setReadBuffer(int, char *);
};

//DebugHardwareSerial::DebugHardwareSerial() {};
int DebugHardwareSerial::available() { 
  printf ("Calling available() \n");
  return readBufferLength-readPtr;  
};
void DebugHardwareSerial::begin(int speed) {};
void DebugHardwareSerial::write(char ch) {
  printf("Wrote %02X\n", ch&0xff);
};
int DebugHardwareSerial::read() { 
  printf("Calling read() \n");
  return readBuffer[readPtr++]; 
};
void  DebugHardwareSerial::setReadBuffer(int length, char * buffer) {  
  readBuffer = buffer;
  readBufferLength = length;
  readPtr=0;
};



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


void pinMode(int, int) {
};

void pwmWrite (int, int) {
}


unsigned int spibuf;
bool spi_empty = true;

void spi_tx_reg(spi_dev *, int ch) {
  printf("SPI tx %02X\n", ch & 0xff);
  spibuf = ch;
  spi_empty = false;
}
uint16_t spi_rx_reg(spi_dev *) {
  spi_empty=true;
  printf ("SPI rx %02X\n", spibuf & 0xff);
  return spibuf; 
} 
bool spi_is_rx_nonempty(spi_dev *) {
  printf("spi_is_rx_nonempty: %d\n", !spi_empty);
  return !spi_empty;
}
bool spi_is_tx_empty(spi_dev *) {
  printf("spi_is_tx_empty: %d\n", spi_empty);
  return spi_empty;
}

void setup();
void loop();

class DebugConsoleSerial Serial;
class DebugHardwareSerial Serial1;

char test1[] = {0x01, 0x02, 0xff, 0xef};
char test2[] = {0xfc, 0x02, 0xff, 0xef};
char test3[] = {0x01, 0xff, 0xef};
char test4[] = {0xff, 0xff, 0x01, 0xfe, 0x02, 0x7C, 0x00, 0x3e, 0x1c, 0xff, 0xef};
char test5[] = {0x40, 0x93, 0xff, 0xef};
#include "../../SDLCBridge/SDLCBridge.ino"

int main (int argc, char ** argv) {
  int i;
  setup();
  Serial1.setReadBuffer(4, test2);
  for (i=0;i<30;i++) {
    loop();
    __irq_spi2();
  }
  Serial1.setReadBuffer(11, test4);
  for (i=0;i<60;i++) {
    loop();
    __irq_spi2();
  }
  Serial1.setReadBuffer(4, test5);
  for (i=0;i<30;i++) {
    loop();
    __irq_spi2();
  }
}






