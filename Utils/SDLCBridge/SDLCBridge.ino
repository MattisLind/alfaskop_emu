/*
 * Set board to Generic STM32F103C form STM32duino.com Variant STM32F103C8, Upload method STLink, 72 MHz
 *
 */


#include <SPI.h>
#include "ebcdic.h"
#include "lsbmsb.h" 
#include "RingBuffer.h"
#define DEBUG_LEVEL 4 
#define RTS PB11 // Input
#define RFS PB1  // Output
#define DTR PB10 // Input 

#define BAUD 104

#if DEBUG_LEVEL > 3
#define DEBUG4
#endif 

#if DEBUG_LEVEL > 2
#define DEBUG3
#endif

#if DEBUG_LEVEL > 1
#define DEBUG2
#endif 

#if DEBUG_LEVEL > 0
#define DEBUG1
#endif


#ifdef DEBUG1 
#define BAUD 1000
#endif

#ifdef DEBUG2
#define BAUD 10000
#endif

#ifdef DEBUG3
#define BAUD 20000
#endif

#ifdef DEBUG4
#define BAUD 30000
#endif

SPIClass SPI_2(2); 



HardwareTimer pwmtimer(1);
const int pwmOutPin = PA8; // pin10

class RingBuffer rxBuffer;
class RingBuffer txBuffer;



void setup() {
  int period;
  int maxduty;
  // put your setup code here, to run once:
  pwmtimer.pause();
  period = BAUD; // PWM period in useconds, freq 300 Hz
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
  pinMode(RTS, INPUT);
  pinMode(RFS, OUTPUT);
  pinMode(DTR, INPUT);
#ifdef DEBUG1
  printMillis(); 
  Serial.print("BSC Bridge starting up");
  Serial.println();
#endif
  rxBuffer.initBuffer();
  txBuffer.initBuffer();
}

#ifdef DEBUG1
void printMillis() {
  unsigned long time = millis();
  if (time < 10L) Serial.print('0');
  if (time < 100L) Serial.print('0');
  if (time < 1000L) Serial.print('0');
  if (time < 10000L) Serial.print('0');
  if (time < 100000L) Serial.print('0');
  if (time < 1000000L) Serial.print('0');
  if (time < 10000000L) Serial.print('0');
  if (time < 100000000L) Serial.print('0');
  if (time < 1000000000L) Serial.print('0');
  if (time < 10000000000L) Serial.print('0');
  Serial.print(time);
  Serial.print(' ');
}

void printTwoDigitHex (int data) {
  if (data < 16) {
    Serial.print('0');
  } 
  Serial.print(data, HEX);
}
#endif 
#ifdef DEBUG2
void printBufferInEBCDIC (const unsigned char  * buf, int length) {
  int i, j;
  for (i=0;i<length;i+=16) {
    printMillis();
    Serial.print(' ');
    for (j=i; j < (i+16); j++) {
      if (j>=length) {
        Serial.print("   ");
      } else {
        printTwoDigitHex (buf[j]);
      }
    }
    Serial.print("  ");
    for (j=i; j < (i+16); j++) {
      if (j>=length) {
        Serial.print(" ");
      } else {
        if (isprint(buf[j])) {
          Serial.print(buf[j]);
          Serial.print(' ');  
        } else {
          Serial.print(". ");
        }
      }
    }
    Serial.print("  ");
    for (j=i; j < (i+16); j++) {
      if (j>=length) {
        Serial.print(' ');
      } else {
        if (isprint(EBCDICtoASCII(buf[j]))) {
          Serial.print(EBCDICtoASCII(buf[j]));
          Serial.print(' ');
        } else {
          Serial.print(". ");
        }
      }
    }
    Serial.println();
  }
}
#endif
#ifdef DEBUG5
void printEightHexDigits (uint32 data) {
  printTwoDigitHex((data >> 24) & 0xff);  
  printTwoDigitHex((data >> 16) & 0xff);  
  printTwoDigitHex((data >> 8) & 0xff);  
  printTwoDigitHex(data & 0xff);  
}

#endif






void loop() {
char ch;
if (spi_is_tx_empty(SPI2)){
    if (txBuffer.isBufferEmpty()) {
      spi_tx_reg(SPI2, 0xff);  
    } else {
      ch = translationArray[txBuffer.readBuffer()];
#ifdef DEBUG3
      printMillis();
      Serial.print("Sending SPI: ");
      printTwoDigitHex(ch);
      Serial.println();
#endif            
      spi_tx_reg(SPI2, ch);  
    }    
  }
           
  if (spi_is_rx_nonempty(SPI2)) {
    ch = spi_rx_reg(SPI2);
#ifdef DEBUG3     
    if (ch != 0xff ) {
      printMillis();
      Serial.print("Receiving SPI: ");
      printTwoDigitHex(ch);
      Serial.println();        
    } 
#endif    
  }
  if (Serial1.available()>0) {
     ch = Serial1.read();
#ifdef DEBUG3     
     printMillis();
     Serial.print("Reciving from Hercules : ");
     printTwoDigitHex(ch);
     Serial.println();
#endif     
#ifdef DEBUG3     
     Serial.println("After rxData");
#endif     
  }
  if (!rxBuffer.isBufferEmpty()) {
      ch = rxBuffer.readBuffer();
#ifdef DEBUG3      
      printMillis();
      Serial.print("Synced data from buffer to Hercules : ");
      printTwoDigitHex(ch);
      Serial.println(); 
#endif      
  }
}
