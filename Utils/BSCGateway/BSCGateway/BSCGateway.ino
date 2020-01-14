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
uint32 dataWord;
int syncPoint;
uint8_t msgBuffer [300];
int msgBufferCnt = 0;

void printTwoDigitHex (int data) {
  if (data < 16) {
    Serial.print('0');
  } 
  Serial.print(data, HEX);
}


void loop() {
  spi_dev * spi_d = SPI2;
  uint16 read;
  uint8_t data;
  uint8_t msg;
  int rxState=0;
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
    dataWord = dataWord << 8;  
    dataWord = dataWord | (0xff & read);
    if (state==0) { // Hunting for SYNC
      // Try to find sync
      for (i=0; i<8; i++) {
        if (((dataWord >> i) & 0xffff) == 0x3232) {
          syncPoint = i;
          break;
        }
      }
      if (i!= 8) {
        rxState = 1; // We have found sync
      }
    }
    else {
      data = 0xff & (dataWord >> syncPoint);
      msgBuffer[msgBufferCnt++] = data;
      if (rxState == 1) { // Processing first char efter SYN
        switch (data) {
          case EOT: 
          case NAK:
            rxState = 2;
            break;
          case DLE:  // Two byte sequences
            rxState = 3;
            break;
          case SOH:
            rxState = 4;
            break;
          case STX:
            rxState = 5;
            break;
        }   
      } else if (rxState == 2) {
        // Data shall be PAD.
        if (data == PAD) {
          // Do a callback 
          if (msgBuffer[0] == EOT) {
          } else if (msgBuffer[0] == NAK) {
          } else {
            // Error callback
          }
        } else {
          // Error do something - call error callback
        }
        rxState = 0; // Go back to hunt for sync.
      } else if (rxState == 3) {
        switch (data) {
          case 0x70: // ACK 0
          case 0x61: // ACK 1
          case 0x6b: // WACK
          case 0x7c: // RVI
            rxState = 6;
            break;
          default:
            break;
        }
      } else if (rxState == 4) {
      } else if (rxState == 5) {
      } else if (rxState == 6) {
        // Two byte sequence
        if (data == PAD) {
          switch (msgBuffer[1]) {
            case 0x70: // ACK 0
              break;
            case 0x61: // ACK 1
              break;
            case 0x6b: // WACK
              break;
            case 0x7c: // RVI
              break;
          }
        } else {
          // Error
        }
        rxState = 0; // Go back to hunt
      }
    }
  }
}
