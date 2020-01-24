#include <SPI.h>
#include "ebcdic.h"
#include "lsbmsb.h"

SPIClass SPI_2(2); 

HardwareTimer pwmtimer(1);
const int pwmOutPin = PA8; // pin10

void setup() {
  int period;
  int maxduty;
  // put your setup code here, to run once:
  pwmtimer.pause();
  period =104; // PWM period in useconds, freq 300 Hz
  maxduty = pwmtimer.setPeriod(period);
  pinMode(pwmOutPin, PWM);
  pwmtimer.refresh();
  pwmtimer.resume();
  pwmWrite(pwmOutPin, maxduty/2); //50% duty cycle
  Serial1.begin (2400);
  Serial.begin (9600);
  SPI_2.beginSlave(); //Initialize the SPI_2 port.
  SPI_2.setBitOrder(MSBFIRST); // Set the SPI_2 bit order
  SPI_2.setDataMode(SPI_MODE0); //Set the  SPI_2 data mode 0
}

/*
int count;
int cmdState=0;
int txDone=1;
int txCnt=8;
char txBuf[] = {SYN, SYN, 0x40, 0x40, 0x40, 0x40, ENQ, PAD};
int txLen = sizeof txBuf;
char cmd;
int hexValue;
uint32 dataWord;
int syncPoint;
uint8_t msgBuffer [300];
int msgBufferCnt = 0;
int byteCounter;
int rxState=0;
*/

void printTwoDigitHex (int data) {
  if (data < 16) {
    Serial.print('0');
  } 
  Serial.print(data, HEX);
}

void printEightHexDigits (uint32 data) {
  printTwoDigitHex((data >> 24) & 0xff);  
  printTwoDigitHex((data >> 16) & 0xff);  
  printTwoDigitHex((data >> 8) & 0xff);  
  printTwoDigitHex(data & 0xff);  
}


class RingBuffer rxBuffer;
class RingBuffer txBuffer;

void receiveCallback(unsigned char ch) {
  rxBuffer.writeBuffer(ch);
}
class SyncFSM syncFSM(receiveCallback);

void loop() {
spi_dev * spi_d = SPI2;
//  uint16 read;
//  uint8_t data;
//  uint8_t msg;
//  char tmp;
//  int i;
  if (spi_is_tx_empty(spi_d)){
    if (txBuffer.isBufferEmpty()) {
      spi_tx_reg(spi_d, 0xff);  
    } else {
      spi_tx_reg(spi_d, translationArray[txBuffer.readBuffer()]);  
    }    
  }
           
  if (spi_is_rx_nonempty(spi_d)) {
    syncFSM.receivedData(spi_rx_reg(spi_d));  
  }
}
