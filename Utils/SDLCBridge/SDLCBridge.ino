/*
 * Set board to Generic STM32F103C form STM32duino.com Variant STM32F103C8, Upload method STLink, 72 MHz
 * 
 */


#include <SPI.h>
#include "ebcdic.h"
#include "RingBuffer.h"
#define DebugSerial Serial1
#define CommSerial Serial
#define DEBUG_LVL 0
//#define DEBUG5
#define RTS PB8 // Input
#define RFS PB7  // Output
#define DTR PB4 // Input 
#define DSR PB6  // Output
#define RI  PB3  // Output
#define DCD PB9  // Output
#define BAUD_INDEX 9
#if DEBUG_LVL > 3
#define DEBUG4
#endif 

#if DEBUG_LVL > 2
#define DEBUG3
#endif

#if DEBUG_LVL > 1
#define DEBUG2
#endif 

#if DEBUG_LVL > 0
#define DEBUG1
#endif


#ifdef DEBUG1
#define BAUD_INDEX 3
#endif

#ifdef DEBUG2
#undef BAUD_INDEX 
#define BAUD_INDEX 2
#endif

#ifdef DEBUG3
#undef BAUD_INDEX 
#define BAUD_INDEX 1
#endif

#ifdef DEBUG4
#undef BAUD_INDEX
#define BAUD_INDEX 2
#endif

#define logOne(s) printMillis(); DebugSerial.print(s); DebugSerial.println(); 
#define logTwo(s,c)  printMillis();DebugSerial.print(s); printTwoDigitHex(c);  DebugSerial.println();
#define logThree(s1, d1, s2, d2, s3) printMillis();DebugSerial.print(s1);DebugSerial.print(d1, HEX);DebugSerial.print(s2);DebugSerial.print(d2, HEX);DebugSerial.println(s3);

struct baudRate {
  int prescaler;
  int divisor;  
};
#if F_CPU == 72000000
struct baudRate baudRates[] = {
  {7200, 10000 }, // 1 bps
  {7200, 1000  }, // 10 bps
  {7200, 200   }, // 50 bps
  {480,  1000  }, // 150 bps
  {480,  500   }, // 300 bps
  {480,  250   }, // 600 bps
  {480,  125   }, // 1200 bps
  {48,   625   }, // 2400 bps
  {15,  1000   }, // 4800 bps
  {15,   500   }, // 9600 bps
  {15,   250   }, // 19200 bps
  {15,   125   }, // 38400 bps
  {125,   10   }, // 57600 bps
  {1,    1125  }, // 64000 bps
  {125,    5   }, // 115200 bps  
  {72,    4    }, // 250000 bps
  {72,    2    }, // 500000 bps
  {36,    2    } // 1000000 bps
};
#endif 

#if CLOCK_SPEED_MHZ == 96
struct baudRate baudRates[] = {
  {9600, 10000 }, // 1 bps
  {9600, 1000  }, // 10 bps
  {9600, 200   }, // 50 bps
  {160,  4000  }, // 150 bps
  {160,  2000   }, // 300 bps
  {160,  1000   }, // 600 bps
  {160,  500   }, // 1200 bps
  {160,  250   }, // 2400 bps
  {160,  125   }, // 4800 bps
  {10,   1000   }, // 9600 bps
  {10,   500   }, // 19200 bps
  {10,   250   }, // 38400 bps
  {1,   1667   }, // 57600 bps
  {1,    1500  }, // 64000 bps
  {1,    833   }, // 115200 bps 
  {96,   4     }, // 250000 bps
  {96,   2     }, // 500000 bps
  {48,   2     } // 1000000 bps 
};
#endif 
#ifdef DEBUG1
void printMillis() {
  unsigned long time = millis();
  if (time < 10L) DebugSerial.print('0');
  if (time < 100L) DebugSerial.print('0');
  if (time < 1000L) DebugSerial.print('0');
  if (time < 10000L) DebugSerial.print('0');
  if (time < 100000L) DebugSerial.print('0');
  if (time < 1000000L) DebugSerial.print('0');
  if (time < 10000000L) DebugSerial.print('0');
  if (time < 100000000L) DebugSerial.print('0');
  if (time < 1000000000L) DebugSerial.print('0');
  if (time < 10000000000L) DebugSerial.print('0');
  DebugSerial.print(time, DEC);
  DebugSerial.print(' ');
}
#endif



SPIClass SPI_2(2); 



HardwareTimer pwmtimer(1);
const int pwmOutPin = PA8; // pin10

class RingBuffer txBuffer;
class RingBuffer rxInBuffer;
unsigned short txCrc=0xffff;
#define HDLC_STATE_IDLE      0
#define HDLC_STATE_FLAG_SENT 1

unsigned char out;
int bitCounter=0;
int oneCounter=0;
int txHDLCState=HDLC_STATE_IDLE;
volatile int txMode = 0;  // There are two modes. Either it receives data from the Serial port, via the buffer or
                 // it transmits data that has been stored previosly in the ringBuffer on SPI interface.

int abortDetected = 1;
int rxBitCounter = 0;
int rxOneCounter = 0;
int rxHDLCState = 0;
unsigned short rxCrc = 0xffff;
unsigned char in = 0;
int nonEmptyFrame = 0;


void setBaudRate (int index) {
  pwmtimer.pause();
  pwmtimer.setPrescaleFactor(baudRates[index].prescaler);
  pwmtimer.setOverflow(baudRates[index].divisor); 
  pwmtimer.refresh();
  pwmtimer.resume();
  pwmWrite(pwmOutPin, baudRates[index].divisor>>1); //50% duty cycle
}

void setup() {
  pinMode(pwmOutPin, PWM);
  CommSerial.begin (2400);
#if DEBUG_LVL > 0  
  DebugSerial.begin (115200);
#endif
#ifdef DEBUG1
  logOne("SDLC Bridge starting up");
#endif
  setBaudRate (BAUD_INDEX);
  SPI_2.beginSlave(); //Initialize the SPI_2 port.
  SPI_2.setBitOrder(LSBFIRST); // Set the SPI_2 bit order
  SPI_2.setDataMode(SPI_MODE0); //Set the  SPI_2 data mode 0
  pinMode(RTS, INPUT);
  pinMode(RFS, OUTPUT);
  pinMode(DTR, INPUT);
  pinMode(DSR, OUTPUT);
  pinMode(DCD, OUTPUT);
  pinMode(RI, OUTPUT);
  rxInBuffer.initBuffer();
  txBuffer.initBuffer();
  oneCounter = 0;
  bitCounter = 0;
  txHDLCState = 0;
  txCrc = 0xffff;
  out = 0;
  rxOneCounter = 0;
  in = 0;
  rxBitCounter=0;
  txMode = 0;
  rxHDLCState = 0;
  nonEmptyFrame = 0;	
  spi_tx_reg(SPI2, 0xff); // dummy write 
  spi_rx_reg(SPI2); // dummy read
  spi_irq_enable(SPI2, SPI_RXNE_INTERRUPT);
}

#ifdef DEBUG1
void printTwoDigitHex (int data) {
  if (data < 16) {
    DebugSerial.print('0');
  } 
  DebugSerial.print(data, HEX);
}
#endif 
#ifdef DEBUG2
void printBufferInEBCDIC (const unsigned char  * buf, int length) {
  int i, j;
  for (i=0;i<length;i+=16) {
    printMillis();
    DebugSerial.print(' ');
    for (j=i; j < (i+16); j++) {
      if (j>=length) {
        DebugSerial.print("   ");
      } else {
        printTwoDigitHex (buf[j]);
      }
    }
    DebugSerial.print("  ");
    for (j=i; j < (i+16); j++) {
      if (j>=length) {
        DebugSerial.print(" ");
      } else {
        if (isprint(buf[j])) {
          DebugSerial.print(buf[j]);
          DebugSerial.print(' ');  
        } else {
          DebugSerial.print(". ");
        }
      }
    }
    DebugSerial.print("  ");
    for (j=i; j < (i+16); j++) {
      if (j>=length) {
        DebugSerial.print(' ');
      } else {
        if (isprint(EBCDICtoASCII(buf[j]))) {
          DebugSerial.print(EBCDICtoASCII(buf[j]));
          DebugSerial.print(' ');
        } else {
          DebugSerial.print(". ");
        }
      }
    }
    DebugSerial.println();
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



unsigned short calculateCrcChar (unsigned short crc, unsigned char data_p) {
  unsigned char i;
  unsigned int data;
  for (i=0, data=(unsigned int)0xff & data_p;
       i < 8; 
       i++, data >>= 1)
    {
      if ((crc & 0x0001) ^ (data & 0x0001))
	crc = (crc >> 1) ^ 0x8408;
      else  crc >>= 1;
    }
  return crc;
}



static inline void shiftInZero() {
#ifdef DEBUG4
  logTwo("ENTRY shiftInZero: bitCounter=", bitCounter);
  logTwo("ENTRY shiftInZero: oneCOunter=", oneCounter);
  logTwo("ENTRY shiftInZero: out=", out);  
#endif  
  oneCounter=0;
  out >>= 1; bitCounter++;  // insert  zero bit.  
  if (bitCounter == 8) {
    spi_irq_disable(SPI2, SPI_RXNE_INTERRUPT); 
    txBuffer.writeBuffer(out); 
    spi_irq_enable(SPI2, SPI_RXNE_INTERRUPT);
    bitCounter = 0;
#ifdef DEBUG4
    logTwo("bitCounter==8 > shiftInZero: out=", out);
#endif
  }
#ifdef DEBUG4
  logTwo("EXIT shiftInZero: bitCounter=", bitCounter);
  logTwo("EXIT shiftInZero: oneCOunter=", oneCounter);
  logTwo("EXIT shiftInZero: out=", out);  
#endif  
}

static inline void shiftInOne() {
#ifdef DEBUG4
  logTwo("ENTRY shiftInOne: bitCounter=", bitCounter);
  logTwo("ENTRY shiftInOne: oneCOunter=", oneCounter);
  logTwo("ENTRY shiftInOne: out=", out);  
#endif  
  out >>= 1; out |= 0b10000000; bitCounter++; oneCounter++;
  if (bitCounter == 8) {
    spi_irq_disable(SPI2, SPI_RXNE_INTERRUPT); 
    txBuffer.writeBuffer(out); 
    spi_irq_enable(SPI2, SPI_RXNE_INTERRUPT);
    bitCounter = 0;
#ifdef DEBUG4
    logTwo("bitCounter==8 > shiftInOne: out=", out);
#endif
 
  }
#ifdef DEBUG4
  logTwo("EXIT shiftInOne: bitCounter=", bitCounter);
  logTwo("EXIT shiftInOne: oneCOunter=", oneCounter);
  logTwo("EXIT shiftInOne: out=", out);  
#endif  
}

void sendAbort() {
#ifdef DEBUG4
  logTwo("ENTRY sendAbort bitCounter=", bitCounter); 
#endif
  if (oneCounter == 5) {
    shiftInZero();
  }
  if (bitCounter == 0) {
    spi_irq_disable(SPI2, SPI_RXNE_INTERRUPT);
    txBuffer.writeBuffer(0x7F);  // Send the flag directly if the bitcounter is indicateing no residual bits.    
    spi_irq_enable(SPI2, SPI_RXNE_INTERRUPT);
  } else {
    shiftInZero();
    shiftInOne();
    shiftInOne();
    shiftInOne();
    shiftInOne();
    shiftInOne();
    shiftInOne();
    shiftInOne();
    for (; bitCounter<8;bitCounter++) { out >>= 1; out |= 0b10000000; }
    spi_irq_disable(SPI2, SPI_RXNE_INTERRUPT);
    txBuffer.writeBuffer(out);   
    spi_irq_enable(SPI2, SPI_RXNE_INTERRUPT);
  }
  bitCounter=0;
  oneCounter=0;
  txHDLCState=HDLC_STATE_IDLE;
  txCrc=0xffff;
}




// This method will end the frame. Since the fram might contain a number of bits that is not divisable by eight we need to handle 
// this. We also need to shift on thge closing frame. If there are uneven, non eight divisable framelength the reamaining bits
// will be filled by one to indicate idle line.

void endHDLCProcessing() {
#ifdef DEBUG4
  logTwo("ENTRY endHDLCProcessing bitCounter=", bitCounter); 
#endif
  if (oneCounter == 5) {
    shiftInZero();
  }
  if (bitCounter == 0) {
    spi_irq_disable(SPI2, SPI_RXNE_INTERRUPT);
    txBuffer.writeBuffer(0x7E);  // Send the flag directly if the bitcounter is indicateing no residual bits.    
    spi_irq_enable(SPI2, SPI_RXNE_INTERRUPT);
  } else {
    shiftInZero();
    shiftInOne();
    shiftInOne();
    shiftInOne();
    shiftInOne();
    shiftInOne();
    shiftInOne();
    shiftInZero();
    for (; bitCounter<8;bitCounter++) { out >>= 1; out |= 0b10000000; }
    spi_irq_disable(SPI2, SPI_RXNE_INTERRUPT);
    txBuffer.writeBuffer(out);   
    spi_irq_enable(SPI2, SPI_RXNE_INTERRUPT);
  }
  bitCounter=0;
  oneCounter=0;
  txHDLCState=HDLC_STATE_IDLE;
  txCrc=0xffff;
}
  
  


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
#ifdef DEBUG4
  logTwo("processHDLCforSending ch=", ch);
  logTwo("processHDLCforSending oneCounter=", oneCounter);
  logTwo("processHDLCforSending bitCunter=", bitCounter);
#endif  
  if (txHDLCState == HDLC_STATE_IDLE) {
    spi_irq_disable(SPI2, SPI_RXNE_INTERRUPT);
    txBuffer.writeBuffer(0x7E); // Send the starting flaga as the first thing to do.
    spi_irq_enable(SPI2, SPI_RXNE_INTERRUPT);
    txHDLCState=HDLC_STATE_FLAG_SENT;
  } 
  // Process each bit of the input character.
#ifdef DEBUG4
    logTwo("bit 00000001 oneCounter=", oneCounter);
#endif    
  if (oneCounter == 5) {
    shiftInZero(); 
  }
  if (0b00000001 & ch) {
    shiftInOne();
  } else {
    shiftInZero();
  }
#ifdef DEBUG4
    logTwo("bit 00000010 oneCounter=", oneCounter);
#endif    
  if (oneCounter == 5) {
    shiftInZero(); 
  }
  if (0b00000010 & ch) {
    shiftInOne();
  } else {
    shiftInZero();
  }
#ifdef DEBUG4
    logTwo("bit 00000100 oneCounter=", oneCounter);
#endif    
  if (oneCounter == 5) {
    shiftInZero(); 
  }
  if (0b00000100 & ch) {
    shiftInOne();     
  } else {
    shiftInZero();
  }
#ifdef DEBUG4
    logTwo("bit 00001000 oneCounter=", oneCounter);
#endif    
  if (oneCounter == 5) {
    shiftInZero(); 
  }
  if (0b00001000 & ch) {
    shiftInOne();      
  } else {
    shiftInZero();
  }
#ifdef DEBUG4
    logTwo("bit 00010000 oneCounter=", oneCounter);
#endif    
  if (oneCounter == 5) {
    shiftInZero(); 
  }
  if (0b00010000 & ch) {
    shiftInOne();
  } else {
    shiftInZero();
  }
#ifdef DEBUG4
    logTwo("bit 00100000 oneCounter=", oneCounter);
#endif    
  if (oneCounter == 5) {
    shiftInZero(); 
  }
  if (0b00100000 & ch) {
    shiftInOne();
  } else {
    shiftInZero();
  }
#ifdef DEBUG4
    logTwo("bit 01000000 oneCounter=", oneCounter);
#endif    
  if (oneCounter == 5) {
    shiftInZero();      
  }
  if (0b01000000 & ch) {
    shiftInOne();
  } else {
    shiftInZero();
  }
#ifdef DEBUG4
    logTwo("bit 10000000 oneCounter=", oneCounter);
#endif    
  if (oneCounter == 5) {
    shiftInZero(); 
  }
  if (0b10000000 & ch) {
    shiftInOne();
  } else {
    shiftInZero();
  }
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
int commandByte;
void processFramedSerialData(unsigned char ch) {
  if (serialFrameState == 0) { // Normal state no ESC has been received
    if (ch == 0xff) {         // Received ESC
      serialFrameState = 1;
    } else {
      txCrc = calculateCrcChar(txCrc, ch); // Calculate the CRC for each character
      processHDLCforSending(ch);   // throw it to HDLC processing
    }
  } else if (serialFrameState == 1) {
    serialFrameState=0;
    commandByte = ch;
    switch (ch) {
      case 0xff: // Just add the 0xff to the data stream
        txCrc = calculateCrcChar(txCrc, ch);  // Calculate the CRC for each character
        processHDLCforSending(ch);    // throw it to HDLC processing
        break;
      case 0xee:
        oneCounter = 0;
        bitCounter = 0;
        txHDLCState = 0;
        txCrc = 0xffff;
        out = 0;
        rxOneCounter = 0;
        in = 0;
        rxBitCounter=0;
        txMode = 0;
        rxHDLCState = 0;
	      nonEmptyFrame = 0; 	    
        rxInBuffer.initBuffer();
        txBuffer.initBuffer();
        break;
      case 0xef: // EOR 
        //processHDLCforSending(~(0xff & txCrc));       // LSB of CRC word 
        //processHDLCforSending(~(0xff & (txCrc >> 8)));  // MSB of CRC word
        endHDLCProcessing();                // Handle non modulo 8 bits and send flags.
        txMode = 1;
        break;
      case 0xfe: // Abort
        sendAbort();
        txMode = 1;
        break;
      case 0xf0: // Two byte commands 
      case 0xf1:
      case 0xf2:
      case 0xf3:
        serialFrameState = 2;
        break;
      default:  // Invalid ESC sequence
        break;
    }
  } else if (serialFrameState == 2) {
    serialFrameState = 0;
    switch (commandByte) {
      case 0xf0: // set baud rate
      if ((ch >= 0) && (ch <= 14)) {
        setBaudRate(ch);
      } 
      break;
      case 0xf1: // set handshake pin
      switch (ch) {
        case 0:
          digitalWrite (RFS, 1); 
          break;
        case 1:
          digitalWrite (DSR, 1);
          break;
        case 2:
          digitalWrite (DCD, 1);
          break;
        case 3:
          digitalWrite (RI, 1);
          break;
      } 
      break;
      case 0xf2: // clear handshake pin
      switch (ch) {
        case 0:
          digitalWrite (RFS, 0); 
          break;
        case 1:
          digitalWrite (DSR, 0);
          break;
        case 2:
          digitalWrite (DCD, 0);
          break;
        case 3:
          digitalWrite (RI, 0);
          break;
      } 
      break;
      case 0xf3:  // report back pin status
      CommSerial.write(0xff);
      CommSerial.write(0xf4);
      if (ch == 0) {
        CommSerial.write(digitalRead (DTR)); 
      } else {
        CommSerial.write(digitalRead (RTS));
      }
      break;
    }
  }
}




void processFrameForSendingToHercules(unsigned char ch) {
}

static inline void processRxZeroHDLCBit() { 
#ifdef DEBUG4
  logTwo("processRxZeroHDLCBit rxOneCounter=", rxOneCounter);
  logTwo("processRxZeroHDLCBit rxBitCunter=", rxBitCounter);
#endif
  if (rxHDLCState) { // We have received a flag - waiting for end flag
    if (rxOneCounter==6) { 
      abortDetected = 0;
#ifdef DEBUG4
      logOne("Flag - while in-sync");
#endif
      if (nonEmptyFrame) { // Flag - still in sync.         
        CommSerial.write((rxCrc>>8) & 0xff);
        CommSerial.write(rxCrc & 0xff);
        rxCrc=0xffff;
        rxBitCounter=0;
        CommSerial.write(0xff);
        CommSerial.write(0xef);
        nonEmptyFrame = 0;
      }
      rxBitCounter = 0; 
    } else if (rxOneCounter != 5) { // This is an ordinary bit that we should store.	      
      in  >>= 1; rxBitCounter++;
      if (rxBitCounter == 8) { 
        rxBitCounter = 0;  
#ifdef DEBUG4
        logTwo("processRxZeroHDLCBit rxBitCounter=8 in=", in);       
#endif
        rxCrc = calculateCrcChar(rxCrc, in);
        if (in==0xff) CommSerial.write(0xff);
        CommSerial.write(in);   
	      nonEmptyFrame = 1;      
      }	      
    } // else we would do nothing since then it is an inserted 0.	    
  } else {  // We are waiting for leading flag
    if (rxOneCounter==6) { // Start flag
#ifdef DEBUG4
      logOne("Flag - Going from out of sync to in sync");
#endif
      rxHDLCState = 1;
      rxBitCounter = 0;
      abortDetected = 0;
    }	    	    
  }
  rxOneCounter=0;	
}

static inline void processRxOneHDLCBit() {
#ifdef DEBUG4
  logTwo("processRxOneHDLCBit rxOneCounter=", rxOneCounter);
  logTwo("processRxOneHDLCBit rxBitCounter=", rxBitCounter);
#endif
  if (rxHDLCState) { // We have received a flag - waiting for end flag    	    
    if (rxOneCounter==6) { // Abort
#ifdef DEBUG2
      logOne("processRxOneHDLCBit Received an Abort");
#endif      
      rxHDLCState = 0;     // This is normal if the line goes to marking state directly after a flag.
      if (nonEmptyFrame) { // But we do have data received in the buffer, then we need to clear out the buffer.
        nonEmptyFrame=0;
        rxCrc=0xffff;      // reset the crc after an abort!
        CommSerial.write(0xff);
        CommSerial.write(0xfe); 
        rxBitCounter = 0;  
        rxOneCounter = 0; 
        abortDetected = 1;
      }	    
    } else {
      in  >>= 1; in |= 0b10000000; rxBitCounter++;
      if (rxBitCounter == 8) { 
        rxBitCounter = 0; 
        nonEmptyFrame=1;
#ifdef DEBUG4
        logTwo("processRxOneHDLCBit rxBitCounter=8 in=", in);
#endif
        rxCrc = calculateCrcChar(rxCrc, in);
        if (in==0xff) CommSerial.write(0xff);
        CommSerial.write(in);   
      } 
    }	      
  } 
  if (rxOneCounter <8) {
    rxOneCounter++; // If we haven't received a flag we just increase the one counter - We always do it we receive a one! But not more than 8 since it would not matter and we don't want to wrap.
  }	  
}


void processRxHDLC(unsigned char ch) {
#ifdef DEBUG4
  logTwo("processRxHDLC: ch=", ch);
#endif
  if (ch == 0xff && rxHDLCState == 0) return; // This is idle line don't spend time procssing it.
#ifdef DEBUG4
  logOne("bit 0");
#endif
  if (0b00000001 & ch) {
    processRxOneHDLCBit();
  } else {
    processRxZeroHDLCBit();	  
  }
#ifdef DEBUG4
  logOne("bit 1");
#endif
  if (0b00000010 & ch) {
    processRxOneHDLCBit();
  } else {
    processRxZeroHDLCBit();	  
  } 	
#ifdef DEBUG4
  logOne("bit 2");
#endif
  if (0b00000100 & ch) {
    processRxOneHDLCBit();
  } else {
    processRxZeroHDLCBit();	  
  } 	
#ifdef DEBUG4
  logOne("bit 3");
#endif
  if (0b00001000 & ch) {
    processRxOneHDLCBit();
  } else {
    processRxZeroHDLCBit();	  
  } 	
#ifdef DEBUG4
  logOne("bit 4");
#endif
  if (0b00010000 & ch) {
    processRxOneHDLCBit();
  } else {
    processRxZeroHDLCBit();	  
  } 	
#ifdef DEBUG4
  logOne("bit 5");
#endif
  if (0b00100000 & ch) {
    processRxOneHDLCBit();
  } else {
    processRxZeroHDLCBit();	  
  } 	
#ifdef DEBUG4
  logOne("bit 6");
#endif
  if (0b01000000 & ch) {
    processRxOneHDLCBit();
  } else {
    processRxZeroHDLCBit();	  
  } 	
#ifdef DEBUG4
  logOne("bit 7");
#endif
  if (0b10000000 & ch) {
    processRxOneHDLCBit();
  } else {
    processRxZeroHDLCBit();	  
  } 		
}


extern "C" void __irq_spi2 (void) {
  unsigned char ch;	   
  if (spi_is_tx_empty(SPI2)){
    if (txMode) {		
      if (txBuffer.isBufferEmpty()) {
        txMode = 0;
        spi_tx_reg(SPI2, 0xff);  
      } else {
        ch = txBuffer.readBuffer();
#ifdef DEBUG5
	logTwo("Sending SPI: ", ch);
#endif            
        spi_tx_reg(SPI2, ch);  
      }    
    } else {
      spi_tx_reg(SPI2, 0xff);		
    }
  }

  if (spi_is_rx_nonempty(SPI2)) {
    ch = spi_rx_reg(SPI2);
    if (ch != 0xff ) {
#ifdef DEBUG5      
      logTwo("Receiving SPI: ", ch);
#endif    
      rxInBuffer.writeBuffer(ch);  		
    } else {
      if (!abortDetected) {
        rxInBuffer.writeBuffer(ch);   
      }
    }
  }
}



void loop() {
unsigned char ch;
  
  if (!txMode) {
    if (CommSerial.available()>0) {
       ch = CommSerial.read();
  #ifdef DEBUG3     
       logTwo("Reciving from Serial port : ", ch);
  #endif   
       processFramedSerialData(ch);
  #ifdef DEBUG3     
       logOne("After rxData");
  #endif     
    }
  }  

  if (!rxInBuffer.isBufferEmpty()) {
    spi_irq_disable(SPI2, SPI_RXNE_INTERRUPT);	
    ch = rxInBuffer.readBuffer();
    spi_irq_enable(SPI2, SPI_RXNE_INTERRUPT);      
#ifdef DEBUG3      
    logTwo("Synced data from buffer to be HDLC processed : ", ch);
#endif
    processRxHDLC(ch);		  
  }
}	
