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

unsigned char out;
int bitCounter=0;
int oneCounter=0;



// This method will end the frame. Since the fram might contain a number of bits that is not divisable by eight we need to handle 
// this. We also need to shift on thge closing frame. If there are uneven, non eight divisable framelength the reamaining bits
// will be filled by one to indicate idle line.

void endHDLCProcessing() {
  if (bitCounter == 0) {
    txBuffer.writeBuffer(0x7E);  // Send the flag directly if the bitcounter is indicateing no residual bits.    
  } else {
      out << 1; bitCounter++;  // We process the flag one by one and then handle the idle bits.
      if (bitCounter == 8) { txBuffer.writeBuffer(out); bitCounter = 0; }
      out << 1; out |= 1; bitCounter++;
      if (bitCounter == 8) { txBuffer.writeBuffer(out); bitCounter = 0; }
      out << 1; out |= 1; bitCounter++;
      if (bitCounter == 8) { txBuffer.writeBuffer(out); bitCounter = 0; }
      out << 1; out |= 1; bitCounter++;
      if (bitCounter == 8) { txBuffer.writeBuffer(out); bitCounter = 0; }
      out << 1; out |= 1; bitCounter++;
      if (bitCounter == 8) { txBuffer.writeBuffer(out); bitCounter = 0; }
      out << 1; out |= 1; bitCounter++;
      if (bitCounter == 8) { txBuffer.writeBuffer(out); bitCounter = 0; }
      out << 1; out |= 1; bitCounter++;
      if (bitCounter == 8) { txBuffer.writeBuffer(out); bitCounter = 0; }
      out << 1; bitCounter++;
      if (bitCounter == 8) { txBuffer.writeBuffer(out); bitCounter = 0; } 
      for (; bitCounter<8;bitCounter++) { out << 1; out |= 1; }
      txBuffer.writeBuffer(out)
    }
  }
}
  
  

#define HDLC_STATE_IDLE      0
#define HDLC_STATE_FLAG_SENT 1

// Process a character at a time. Processed data is moved onto the txBuffer for sending. 
// In IDLE state when a character is received a FLAG is pused into the buffer before processing the character. State is set to SENT_FLAG
// A chacter is processed from MSB to LSB bits.
// Bits are shifted into the out variable.
// If a bit is a 1 the oneCounter is incremented. If the oneCounter is 5 an extra 0 is shifted in as well before the 1.
// The onecounter is reset to 0.
// If a bit is 0 the out variable is shifted one left only.
// For each bit shifted in the bitCounter is incremented. 
// At every shift the bitCounter is checked. If the bitCounter is 8 then it is reset to 0 and the data is moved to the txBuffer.

void processHDLCforSending(unsigned char ch) {

}

// Process each character.
// The 0xff is the escape character.
// 0xff 0xef is the end of record (EOR) delimiter
// The checksum is accumulated for all bytes up to the EOR marker. 
// The byte prior to the EOR is checksum.
// An proper packet is accepted by writing a 0xff 0xfe in return
// A reject is sent by a 0xff 0xfd
// An 0xff 0xff is the 0xff character
// All bytes execpt for ESC and Checksum is then processed by processHDLCForSending method.
// Every byte is also processed bye the CRC routine to accumulate the CRC digits.
// When a EOR has been seen the the two CRC sigits that has been accumulated during the fram will be sent for processing 
// by processHDLCForSending method.
// Following this it calls endHDLCProcessing method which handles and any residual bits.
int serialFrameState = 0;
unsigned char checkSum = 0;

void processFramedSerialData(unsigned char ch) {
  if (serialFrameState == 0) { // Normal state no ESC has been received
    if (ch == 0xff) {         // Received ESC
      serialFrameState = 1;
    }
  } else if (serialFrameState == 1) {
    switch (ch) {
      case 0xff: // Just add the 0xff to the data stream
        break;
      case 0xfe: // Sent packet was accepted - remove outbound packet
        break;
      case 0xfd: // Sent packet was rejected - resend outboud packet
        break;
      case 0xef: // EOR 
        break;
      default:  // Invalid ESC sequence
        break
    }
  }
}


int txMode = 0;  // There are two modes. Either it receives data from the Serial port, via the buffer or
                 // it transmits data that has been stored previosly in the ringBuffer on SPI interface.


void loop() {
char ch;
if (txMode) {  
  if (spi_is_tx_empty(SPI2)){
    if (txBuffer.isBufferEmpty()) {
      spi_tx_reg(SPI2, 0xff);  
    } else {
      ch = txBuffer.readBuffer();
#ifdef DEBUG3
      printMillis();
      Serial.print("Sending SPI: ");
      printTwoDigitHex(ch);
      Serial.println();
#endif            
      spi_tx_reg(SPI2, ch);  
    }    
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
  
  if (!txMode) {
    if (Serial1.available()>0) {
       ch = Serial1.read();
  #ifdef DEBUG3     
       printMillis();
       Serial.print("Reciving from Hercules : ");
       printTwoDigitHex(ch);
       Serial.println();
  #endif   
       processFramedSerialData(ch);
  #ifdef DEBUG3     
       Serial.println("After rxData");
  #endif     
    }
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
