#include <SPI.h>
#include "ebcdic.h"

SPIClass SPI_2(2); //Create an instance of the SPI Class called SPI_2 that uses the 2nd SPI Port

HardwareTimer pwmtimer(1);
const int pwmOutPin = PA8; // pin10

void setup() {
  int period;
  int maxduty;
  // put your setup code here, to run once:
  pwmtimer.pause();
  period = 104; // PWM period in useconds, freq 9600 Hz
  maxduty = pwmtimer.setPeriod(period);
  pinMode(pwmOutPin, PWM);
  pwmtimer.refresh();
  pwmtimer.resume();
  pwmWrite(pwmOutPin,3600); //50% duty cycle
  Serial1.begin (2400);
  Serial.begin (9600);
    // Setup SPI 2
  SPI_2.beginSlave(); //Initialize the SPI_2 port.
  SPI_2.setBitOrder(LSBFIRST); // Set the SPI_2 bit order
  SPI_2.setDataMode(SPI_MODE0); //Set the  SPI_2 data mode 0
  //SPI_2.setDataSize(SPI_CR1_DFF_16_BIT);
}
int count;
int cmdState=0;
int txDone=1;
int txCnt=8;
char txBuf[] = {SYN, SYN, 0x40, 0x40, 0x40, 0x40, ENQ, PAD};
int txLen = sizeof txBuf;
char cmd;
int hexValue;


void printTwoDigitHex (int data) {
  if (data < 16) {
    Serial.print('0');
  } 
  Serial.print(data, HEX);
}


void loop() {
  spi_dev * spi_d = SPI2;
  uint16 read;
  uint8_t msg;
  char tmp;
  int i;
  // put your main code here, to run repeatedly:
    if (Serial.available()> 0) {
    tmp = Serial.read();
    if ((tmp >= 'a') && (tmp <= 'z')) {
      tmp &= ~0x20; // to upper case
    }
    switch (cmdState) {
      case 0:
        switch (tmp) {
          case 'P':  // send poll
            Serial.write(tmp);
            Serial.println();
            if (txDone == 0) {
              Serial.println("SENDING IN PROGRESS");
            } else {
              txDone = 0;  
              txCnt=0;   
            } 
            Serial.print("IBM BSC COMMANDER> " );
            break;
          case 'C': // set destination address
          case 'D': // set poll status
            Serial.write(tmp);
            Serial.write(' ');
            cmdState = 1;
            cmd = tmp;
            break;
          case 'X':
            Serial.println();
            Serial.print("Current poll buffer: ");
            for(i=0; i < txLen; i++) {
              printTwoDigitHex(txBuf[i]);
              Serial.write(' ');
            }
            Serial.println();
            Serial.print("IBM BSC COMMANDER> " );
            break;
          case 'H':
            Serial.println();
            Serial.println("IBM BSC COMMANDER HELP");
            Serial.println("=======================");
            Serial.println("H - HELP");
            Serial.println("P - Send BSC Poll");
            Serial.println("C HH - Set CU");
            Serial.println("D HH - Set DV");
            Serial.println("HH is a two digit hex value");
            Serial.println("X - print current poll buffer");
            Serial.println();
            Serial.print("IBM BSC COMMANDER> " );
            break;
          case '\r': 
            Serial.println();
            Serial.print("IBM BSC COMMANDER> " );
        }
        break;
      case 1: 
        //Serial1.write(tmp);
        // in state 1 we collect hex digits.
        if (((tmp >= '0' ) && (tmp <= '9')) || ((tmp >= 'A') && (tmp <= 'F'))) {
          Serial.write(tmp); // Echo character
          if (tmp > '9') {
            tmp -= 'A';
            tmp += 10;
          } else {
            tmp -= '0';
          }
          hexValue = tmp << 4;
          cmdState = 2;
        }
        break;        
      case 2:
        if (((tmp >= '0' ) && (tmp <= '9')) || ((tmp >= 'A') && (tmp <= 'F'))) {
          Serial.write(tmp); // Echo character
          if (tmp > '9') {
            tmp -= 'A';
            tmp += 10;
          } else {
            tmp -= '0';
          }
          hexValue |= tmp;
        }
        cmdState = 0;
        switch (cmd) {
          case 'C':
            txBuf[2] = hexValue;
            txBuf[3] = hexValue;
            break;
          case 'D':
            txBuf[4] = hexValue;
            txBuf[5] = hexValue;
            break;
        }
        Serial.println();
        Serial.print("IBM BSC COMMANDER> " );
      break;      
    }
  } 
  //spi_rx_reg(spi_d); // read any previous data
  if (spi_is_tx_empty(spi_d)){
    if (txDone==1) {
      spi_tx_reg(spi_d, 0xff); // Write the data item to be transmitted into the SPI_DR register    
    } else {
      if (txCnt < txLen) {
        spi_tx_reg(spi_d, txBuf[txCnt++]);  
      } else {
        txDone = 1;
      }
    }
    
  }
  if (spi_is_rx_nonempty(spi_d)) {
    read = spi_rx_reg(spi_d); // "... and read the last received data."  
  }
}
