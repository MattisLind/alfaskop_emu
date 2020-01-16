#include <SPI.h>
#include "ebcdic.h"
#include "lsbmsb.h"

SPIClass SPI_2(2); //Create an instance of the SPI Class called SPI_2 that uses the 2nd SPI Port

HardwareTimer pwmtimer(1);
const int pwmOutPin = PA8; // pin10

void setup() {
  int period;
  int maxduty;
  // put your setup code here, to run once:
  pwmtimer.pause();
  period =333333; // PWM period in useconds, freq 300 Hz
  maxduty = pwmtimer.setPeriod(period);
  pinMode(pwmOutPin, PWM);
  pwmtimer.refresh();
  pwmtimer.resume();
  pwmWrite(pwmOutPin, maxduty/2); //50% duty cycle
  Serial1.begin (2400);
  Serial.begin (9600);
    // Setup SPI 2
  SPI_2.beginSlave(); //Initialize the SPI_2 port.
  SPI_2.setBitOrder(MSBFIRST); // Set the SPI_2 bit order
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
int byteCounter;
int rxState=0;


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

void printMsgBuffer () {
  for (int i=0; i<msgBufferCnt;i++) {
    printTwoDigitHex (msgBuffer[i]);
    Serial.print(" ");
  }  
  Serial.println();
}


void loop() {
  spi_dev * spi_d = SPI2;
  uint16 read;
  uint8_t data;
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
        spi_tx_reg(spi_d, translationArray[txBuf[txCnt++]]);  
      } else {
        txDone = 1;
      }
    }    
  }
  // Reception is a bit strange since we are not getting the bits on proper byte bounderies we need shift the bits to get them right.
  // In hardware there are a 16 bit shift register that in which the data are clocked in from the line and then matched with the sync sequence.
  // While in software we need to handle it a bit differentlty since we get bits in chunks of bytes.
  // On the serial line the LSB of the byte is transmitted first and thus received first in the receiver. If we use the LSBFIRST setting
  // for the SPI transmitting works great but not reception. The order of the bits on the line would not line up well when the bytes are concatenated in a 16 or 32 bit word
  //
  //  Sequence 0x32 0x32  / SYN SYN
  // 
  //  Bits   0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
  //
  //               0  1  2  3  4  5  6  7   0  1  2  3  4  5  6  7  0  1  2  3  4  5  6  7
  //              
  //         1  1  0  1  0  0  1  1  0  0   0  1  0  0  1  1  0  0  1  1  1  1  1  1  1  1 
  //        First byte shifted in with LSBFIRST   11001011 0xcb
  //        Second Byte                           11001000 0xc8
  //        Third  Byte                           11111100 0xfc
  //        Bits in word is then 
  //        0xcbcafc  = 1 1 0 0 1 0 1 1 1 1 0 0 1 0 0 0 1 1 1 1 1 1 0 0 
  //        The same number of 0 indicate the same pattern, but scrambled. We will never be able to find a matching sequence
  //        And we cannot shift the bits in the processor to find our bits belonging to one byte
  // 
  // This all boils down is to use MSBFIRST since it will fit better with how the shifting takes place in the processor
  //        First Byte shifted with MSB first     11010011 0xb3
  //        Second byte                           00010011 0x13
  //        Third byte                            00111111 0x3f
  //        0xb3133f  = 110100110001001100111111
  // If we then use the LSB converted bit pattern for the sync char (0x3232)  0x4c4c we can easily use shift operations
  // to find the bit in the word where sync is matching.
  //        110100110001001100111111 0xb3133f
  //        111010011000100110011111 0xe9899f
  //        111101001100010011001111 0xf4c4cf
  //        111110100110001001100111 0xfa6267
  //        111111010011000100110011 0xfd3133
  //        111111101001100010011001 0xfe9899
  //        111111110100110001001100 0xff4c4c < MATCH!
          
 
  if (spi_is_rx_nonempty(spi_d)) {
    read = spi_rx_reg(spi_d); // "... and read the last received data."  
    dataWord = dataWord << 8;  
    dataWord = (0xffffff00 & dataWord) | (0xff & read);
    printEightHexDigits(dataWord);
    Serial.println();
    if (rxState==0) { // Hunting for SYNC
      // Try to find sync
      for (i=0; i<8; i++) {
        if (((dataWord >> i) & 0xffff) == 0x4c4c) {
          syncPoint = i;
          Serial.print("Found syncpoint:");
          Serial.print(syncPoint, DEC);
          Serial.println();
          break;
        }
      }
      if (i!= 8) {
        rxState = 1; // We have found sync
        Serial.print("Found syncpoint:");
        Serial.print(syncPoint, DEC);
        Serial.println();
        msgBufferCnt = 0;
      }
    }
    else {
      data = translationArray[0xff & (dataWord >> syncPoint)];      
      msgBuffer[msgBufferCnt++] = data;
      Serial.print("Buffer");
      printMsgBuffer();
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
            byteCounter=2;
            rxState = 4;
            break;
          case STX:
            rxState = 5;
            break;
          default:  // Enquiry POLL / SELECTION
            rxState = 7;
            byteCounter=4;
            break;
        }   
      } else if (rxState == 2) {
        // Data shall be PAD.
        if (data == PAD) {
          // We have all data  - Do a callback
          switch (msgBuffer[0]) {
            case EOT:
              Serial.println("EOT received");
              printMsgBuffer();
              break;
            case NAK:
              Serial.println("NAK received");
              printMsgBuffer();
              break;
            case DLE:
              switch (msgBuffer[1]) {
                case 0x70: // ACK 0
                  Serial.println("ACK0 received");
                  printMsgBuffer();
                  break;
                case 0x61: // ACK 1
                  Serial.println("ACK1 received");
                  printMsgBuffer();
                  break;
                case 0x6b: // WACK
                  Serial.println("WACK received");
                  printMsgBuffer();
                  break;
                case 0x7c: // RVI
                  break;
              }
              break;
            case SOH:
              if (msgBuffer[1] == 0x6c) {
                switch (msgBuffer[2]) {
                  case 0xD9:
                    Serial.println("Status Message received");
                    printMsgBuffer();
                    break;  // Status Message                
                  case 0x61:
                    Serial.println("Test request received");
                    printMsgBuffer();
                    break;  // Test request message
                  default:
                    Serial.println("Error SOH with wrong header code");
                    printMsgBuffer();
                    break;
                }
              } else {
                Serial.println("Error SOH with wrong header code");
                printMsgBuffer();
              }
              break;
            case STX:
                Serial.println("Read or write message received");
                printMsgBuffer();
              break;
            default:  // Selection and POLL ENQ
                Serial.println("Selection or POLL message ENQ received");
                printMsgBuffer();
              break;
          }
        } else {
          Serial.println("Last byte was not a PAD - go back to hunt mode!");
          printMsgBuffer();       
        }
        rxState = 0; // Go back to hunt for sync.
      } else if (rxState == 3) {
        switch (data) {
          case 0x70: // ACK 0
          case 0x61: // ACK 1
          case 0x6b: // WACK
          case 0x7c: // RVI
            rxState = 2;
            break;
          default:
            rxState = 0;
            Serial.println("State violation - going back to hunt mode when waiting for second byte control code");
            printMsgBuffer();
            break;
        }
      } else if (rxState == 4) { // SOH is followed by two byte header
        byteCounter--;
        if (byteCounter = 0) {
          rxState = 8; // Now watch for the STX
        }
      } else if (rxState == 5) {
        // Waiting for ETB or ETX to come
        if ((data == ETB) || (data == ETX)) {
          byteCounter=2;
          rxState = 9;
        } else {
          Serial.println("State violation - going back to hunt mode when waiting for ETX or ETB");          
          printMsgBuffer();          
        }
      } else if (rxState==7) {
          byteCounter--;
          if (byteCounter > 0) {
            rxState = 10; // Get the ENQ
          }
          
      } else if (rxState == 8) {
          // Check for STX then
        if (data == STX) {
          rxState = 5;
        } else { 
          rxState = 0;
          Serial.println("State violation - going back to hunt mode when waiting for STX");          
          printMsgBuffer();
        }
      } else if (rxState ==9) {
        // Two CRC digits to be received
        byteCounter--;
        if (byteCounter > 0) {
            // Check CRC
          rxState = 2; // wait for the PAD
        }
      } else if (rxState == 10) {
        if (data == ENQ) {
          rxState = 2; // There is a PAD to come
        }
        else {
          rxState = 0;
          Serial.println("State violation - going back to hunt mode when waiting for ENQ");
          printMsgBuffer();
        }
      }
      else {
        // Error
        Serial.println("Error unknown state!");
        printMsgBuffer();
        rxState = 0; // Go back to hunt
      }
    }
  }
}
