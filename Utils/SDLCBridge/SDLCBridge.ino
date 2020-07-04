/*
 * Set board to Generic STM32F103C form STM32duino.com Variant STM32F103C8, Upload method STLink, 72 MHz
 * 
 */


#include <SPI.h>
#include "ebcdic.h"
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
#undef BAUD 
#define BAUD 1000
#endif

#ifdef DEBUG2
#undef BAUD 
#define BAUD 10000
#endif

#ifdef DEBUG3
#undef BAUD 
#define BAUD 20000
#endif

#ifdef DEBUG4
#undef BAUD 
#define BAUD 60000
#endif

#define logOne(s) printMillis(); Serial.print(s); Serial.println(); 
#define logTwo(s,c)  printMillis();Serial.print(s); printTwoDigitHex(c);  Serial.println();
#define logThree(s1, d1, s2, d2, s3) printMillis();Serial.print(s1);Serial.print(d1, HEX);Serial.print(s2);Serial.print(d2, HEX);Serial.println(s3);



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
  Serial.print(time, DEC);
  Serial.print(' ');
}
#endif



SPIClass SPI_2(2); 



HardwareTimer pwmtimer(1);
const int pwmOutPin = PA8; // pin10

class RingBuffer rxOutBuffer;
class RingBuffer txBuffer;
class RingBuffer rxInBuffer;
unsigned short txCrc=0;
#define HDLC_STATE_IDLE      0
#define HDLC_STATE_FLAG_SENT 1

unsigned char out;
int bitCounter=0;
int oneCounter=0;
int txHDLCState=HDLC_STATE_IDLE;
volatile int txMode = 0;  // There are two modes. Either it receives data from the Serial port, via the buffer or
                 // it transmits data that has been stored previosly in the ringBuffer on SPI interface.


int rxMode=0;
int rxBitCounter = 0;
int rxOneCounter = 0;
int rxHDLCState = 0;
unsigned short rxCrc = 0;
unsigned char in = 0;
int nonEmptyFrame = 0;

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
  SPI_2.setBitOrder(LSBFIRST); // Set the SPI_2 bit order
  SPI_2.setDataMode(SPI_MODE0); //Set the  SPI_2 data mode 0
  pinMode(RTS, INPUT);
  pinMode(RFS, OUTPUT);
  pinMode(DTR, INPUT);
#ifdef DEBUG1
  logOne("SDLC Bridge starting up");
#endif
  rxInBuffer.initBuffer();
  rxOutBuffer.initBuffer();
  txBuffer.initBuffer();
  oneCounter = 0;
  bitCounter = 0;
  txHDLCState = 0;
  txCrc = 0;
  out = 0;
  rxOneCounter = 0;
  in = 0;
  rxBitCounter=0;
  rxMode = 0;
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

// This method will end the frame. Since the fram might contain a number of bits that is not divisable by eight we need to handle 
// this. We also need to shift on thge closing frame. If there are uneven, non eight divisable framelength the reamaining bits
// will be filled by one to indicate idle line.

void endHDLCProcessing() {
  logTwo("ENTRY endHDLCProcessing bitCounter=", bitCounter); 
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
  txCrc=0;
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
    switch (ch) {
      case 0xff: // Just add the 0xff to the data stream
        txCrc = calculateCrcChar(txCrc, ch);  // Calculate the CRC for each character
        processHDLCforSending(ch);    // throw it to HDLC processing
        break;
      case 0xee:
        oneCounter = 0;
        bitCounter = 0;
        txHDLCState = 0;
        txCrc = 0;
        out = 0;
        rxOneCounter = 0;
        in = 0;
        rxBitCounter=0;
        rxMode = 0;
        txMode = 0;
        rxHDLCState = 0;
	nonEmptyFrame = 0; 	    
        rxInBuffer.initBuffer();
        rxOutBuffer.initBuffer();
        txBuffer.initBuffer();
        break;
      case 0xef: // EOR 
        processHDLCforSending(0xff & txCrc);       // LSB of CRC word 
        processHDLCforSending(0xff & (txCrc >> 8));  // MSB of CRC word
        endHDLCProcessing();                // Handle non modulo 8 bits and send flags.
        txMode = 1;
        break;
      default:  // Invalid ESC sequence
        break;
    }
  }
}




void processFrameForSendingToHercules(unsigned char ch) {
}

static inline void processRxZeroHDLCBit() { 
  if (rxHDLCState) { // We have received a flag - waiting for end flag
    if (rxOneCounter==6 && nonEmptyFrame) { // Flag - still in sync. 
      rxMode = 1; 
      nonEmptyFrame = 0; 
    } else if (rxOneCounter != 5) { // This is an ordinary bit that we should store.	      
      in  >>= 1; rxBitCounter++;
      if (rxBitCounter == 8) { 
        rxBitCounter = 0;         
        rxOutBuffer.writeBuffer(in);
	nonEmptyFrame = 1;      
      }	      
    } // else we would do nothing since then it is an inserted 0.	    
  } else {  // We are waiting for leading flag
    if (rxOneCounter==6) { // Start flag
      rxHDLCState = 1;
    }	    	    
  }
  rxOneCounter=0;	
}

static inline void processRxOneHDLCBit() {
  if (rxHDLCState) { // We have received a flag - waiting for end flag    	    
    if (rxOneCounter==6) { // Abort
      rxHDLCState = 0;     // This is normal if the line goes to marking state directly after a flag.
      if (nonEmptyFrame) { // But we do have data received in the buffer, then we need to clear out the buffer.
        nonEmptyFrame=0;
	rxOutBuffer.initBuffer();  // re-init the buffer would do it for us. 
      }	    
    } else {
      in  >>= 1; in |= 0b10000000; rxBitCounter++;
      if (rxBitCounter == 8) { 
        rxBitCounter = 0; 
        rxOutBuffer.writeBuffer(in); 
      } 
    }	      
  } 
  if (rxOneCounter <8) {
    rxOneCounter++; // If we haven't received a flag we just increase the one counter - We always do it we receive a one! But not more than 8 since it would not matter and we don't want to wrap.
  }	  
}


void processRxHDLC(unsigned char ch) {
  if (ch == 0xff && rxHDLCState == 0) return; // This is idle line don't spend time procssing it.
  if (0b00000001 & ch) {
    processRxOneHDLCBit();
  } else {
    processRxZeroHDLCBit();	  
  }
  if (0b00000010 & ch) {
    processRxOneHDLCBit();
  } else {
    processRxZeroHDLCBit();	  
  } 	
  if (0b00000100 & ch) {
    processRxOneHDLCBit();
  } else {
    processRxZeroHDLCBit();	  
  } 	
  if (0b00001000 & ch) {
    processRxOneHDLCBit();
  } else {
    processRxZeroHDLCBit();	  
  } 	
  if (0b00010000 & ch) {
    processRxOneHDLCBit();
  } else {
    processRxZeroHDLCBit();	  
  } 	
  if (0b00100000 & ch) {
    processRxOneHDLCBit();
  } else {
    processRxZeroHDLCBit();	  
  } 	
  if (0b01000000 & ch) {
    processRxOneHDLCBit();
  } else {
    processRxZeroHDLCBit();	  
  } 	
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
    } 
  }
}



void loop() {
unsigned char ch;
  
  if (!txMode) {
    if (Serial1.available()>0) {
       ch = Serial1.read();
  #ifdef DEBUG3     
       logTwo("Reciving from Serial port : ", ch);
  #endif   
       processFramedSerialData(ch);
  #ifdef DEBUG3     
       logOne("After rxData");
  #endif     
    }
  }  

  if (!rxMode && !rxInBuffer.isBufferEmpty()) {
    spi_irq_disable(SPI2, SPI_RXNE_INTERRUPT);	
    ch = rxInBuffer.readBuffer();
    spi_irq_enable(SPI2, SPI_RXNE_INTERRUPT);      
#ifdef DEBUG3      
    logTwo("Synced data from buffer to be HDLC processed : ", ch);
#endif
    processRxHDLC(ch);		  
  }
  if (rxMode) {
    if (!rxOutBuffer.isBufferEmpty()) {
      ch = rxOutBuffer.readBuffer();
#ifdef DEBUG3
     logTwo("Read from rxOutBuffer for sending to serial port: ", ch);
#endif 
      rxCrc = calculateCrcChar(rxCrc, ch);
      if (ch==0xff) Serial1.write(0xff);
      Serial1.write(ch);	  
    } else {
#ifdef DEBUG3
      logOne("Buffer empty sending the CRCs and the EOR");
#endif
      rxMode = 0;
      rxCrc = calculateCrcChar(rxCrc, 0);
      rxCrc = calculateCrcChar(rxCrc, 0);
      Serial1.write((rxCrc>>8) & 0xff);
      Serial1.write(rxCrc & 0xff);
      rxCrc=0;
      rxBitCounter=0;
      rxOneCounter=0;
      Serial1.write(0xff);
      Serial1.write(0xef);
    }
  }
}	
