
/*
 * Set board to Generic STM32F103C form STM32duino.com Variant STM32F103C8, Upload method STLink, 72 MHz
 *
 */


#include <SPI.h>
#include "ebcdic.h"
#include "lsbmsb.h" 
#include "RingBuffer.h"
#include "SyncFSM.h"
#include "MessageFSM.h"
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


void txDataCallback (unsigned char);
void enterHuntStateCallback ();
void messageReceivedCallback (unsigned char, unsigned char *);
void txToHercules (unsigned char);
void messageReceivedFromHerculesCallback (unsigned char, unsigned char *);
void enterHuntHercules ();
class MessageFSM messageFSM(txDataCallback, messageReceivedCallback, enterHuntStateCallback);
class MessageFSM herculesMessageFSM(txToHercules, messageReceivedFromHerculesCallback, enterHuntHercules, true);


HardwareTimer pwmtimer(1);
const int pwmOutPin = PA8; // pin10

class RingBuffer rxBuffer;
class RingBuffer txBuffer;

#define logOne(s) printMillis(); Serial.print(s); Serial.println(); 
#define logTwo(s,c)  printMillis();Serial.print(s); printTwoDigitHex(c);  Serial.println();
#define logThree(s1, d1, s2, d2, s3) printMillis();Serial.print(s1);Serial.print(d1, HEX);Serial.print(s2);Serial.print(d2, HEX);Serial.println(s3);


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
  logOne("BSC Bridge Starting up");
#endif
  rxBuffer.initBuffer();
  txBuffer.initBuffer();
  spi_tx_reg(SPI2, 0xff); // dummy write 
  spi_rx_reg(SPI2); // dummy read
  spi_irq_enable(SPI2, SPI_RXNE_INTERRUPT);
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



void receiveCallback(unsigned char ch) {
#ifdef DEBUG2
  logTwo("Synced data: ",ch);
#endif     
  messageFSM.rxData(ch);   
}


void messageReceivedCallback(unsigned char msgType, unsigned char * msg) {
  // Dispatch message coming from terminal based on msgType and let the hercules facing take on.
  switch (msgType) {
    case EOT_MESSAGE:
#ifdef DEBUG1
      logOne("Received EOT from Cluster controller");
#endif      
      herculesMessageFSM.setTextMode(false);	
      messageFSM.setTextMode(false);	
      herculesMessageFSM.sendEOT();
      break;
    case ENQ_MESSAGE:
#ifdef DEBUG1    
      logOne("Received ENQ from Cluster controller");
#endif      
      herculesMessageFSM.sendENQ();
      break;
    case POLL_MESSAGE:
#ifdef DEBUG1        
      logThree("Received POLL/SELECT for CU=", ((MSG *) msg)->enqData.CU," DV=", ((MSG *) (msg))->enqData.DV, " from Cluster controller");
#endif
      herculesMessageFSM.setTextMode(true);	
      messageFSM.setTextMode(true);	      
      herculesMessageFSM.sendPollSelect(((MSG *) msg)->enqData.CU, ((MSG *) (msg))->enqData.DV ); 
      break;
    case NAK_MESSAGE:
#ifdef DEBUG1    
      logOne("Received NAK from Cluster controller");
#endif      
      herculesMessageFSM.sendNAK();
      break;
    case ACK0_MESSAGE:
#ifdef DEBUG1    
      logOne("Received ACK0 from Cluster controller");
#endif      
      herculesMessageFSM.sendACK0();
      break;
    case ACK1_MESSAGE:
#ifdef DEBUG1    
      logOne("Received ACK1 from Cluster controller");
#endif      
      herculesMessageFSM.sendACK1();
      break;
    case WACK_MESSAGE:
#ifdef DEBUG1    
      logOne("Received WACK from Cluster controller");
#endif      
      herculesMessageFSM.sendWACK();
      break;
    case RVI_MESSAGE:
#ifdef DEBUG1    
      logOne("Received RVI from Cluster controller");
#endif      
      herculesMessageFSM.sendRVI();
      break;               
    case STATUS_MESSAGE:
#ifdef DEBUG1    
      logThree("Received STATUS for CU=",((MSG *) msg)->statusData.CU," DV=",((MSG *) (msg))->statusData.DV," from Cluster controller");
#endif            
      herculesMessageFSM.sendStatusMessage(((MSG *) msg)->statusData.CU, ((MSG *) msg)->statusData.DV, ((MSG *) msg)->statusData.status, ((MSG *) msg)->statusData.sense);
      break;               
    case TEXT_MESSAGE:
#ifdef DEBUG1    
      logOne("Received TEXT from Cluster controller");
#endif
#ifdef DEBUG2      
      printBufferInEBCDIC (((MSG *) msg)->textData.msg, ((MSG *) msg)->textData.length);
#endif      
      herculesMessageFSM.sendTextMessage(((MSG *) msg)->textData.length, ((MSG *) msg)->textData.msg, ((MSG *) msg)->textData.thereIsMoreComing);
      break;               
    case TEST_MESSAGE:
#ifdef DEBUG1    
      logOne("Received TEST from Cluster controller");
#endif 
#ifdef DEBUG2     
      printBufferInEBCDIC (((MSG *) msg)->testData.msg, ((MSG *) msg)->testData.length);
#endif      
      herculesMessageFSM.sendTestRequestMessage(((MSG *) msg)->testData.length, ((MSG *) msg)->testData.msg, ((MSG *) msg)->testData.thereIsMoreComing);
      break;               
    case ERROR_MESSAGE:
      break;               
                 
  }
}

void messageReceivedFromHerculesCallback(unsigned char msgType, unsigned char * msg) {
  // Dispatch message coming from terminal based on msgType and let the hercules facing take on.
  switch (msgType) {
    case EOT_MESSAGE:
#ifdef DEBUG1    
      logOne("Received EOT from Hercules"); 
#endif
      herculesMessageFSM.setTextMode(false);	
      messageFSM.setTextMode(false);	      
      messageFSM.sendEOT();
      break;
    case ENQ_MESSAGE:
#ifdef DEBUG1    
      logOne("Received ENQ from Hercules"); 
#endif
      messageFSM.sendENQ();
      break;
    case POLL_MESSAGE:
#ifdef DEBUG1    
      logThree("Received POLL/SELECT for CU=",((MSG *) msg)->enqData.CU," DV=",((MSG *) (msg))->enqData.DV," from Hercules");
#endif 
      herculesMessageFSM.setTextMode(true);	
      messageFSM.setTextMode(true);	               
      messageFSM.sendPollSelect(((MSG *) msg)->enqData.CU, ((MSG *) (msg))->enqData.DV );
#ifdef DEBUG4       
      logOne("After sendPollSelect.");
#endif      
      break;
    case NAK_MESSAGE:
#ifdef DEBUG1    
      logOne("Received NAK from Hercules.");
#endif          
      messageFSM.sendNAK();
      break;
    case ACK0_MESSAGE:
#ifdef DEBUG1    
      logOne("Received ACK0 from Hercules.");
#endif      
      messageFSM.sendACK0();
      break;
    case ACK1_MESSAGE:
#ifdef DEBUG1    
      logOne("Received ACK1 from Hercules.");
#endif      
      messageFSM.sendACK1();
      break;
    case WACK_MESSAGE:
#ifdef DEBUG1    
      logOne("Received WACK from Hercules.");
#endif      
      messageFSM.sendWACK();
      break;
    case RVI_MESSAGE:
#ifdef DEBUG1    
      logOne("Received RVI from Hercules.");
#endif      
      messageFSM.sendRVI();
      break;               
    case STATUS_MESSAGE:
#ifdef DEBUG1    
      logThree("Received STATUS for CU=",((MSG *) msg)->statusData.CU, " DV=",((MSG *) (msg))->statusData.DV," from Hercules.");
#endif      
      messageFSM.sendStatusMessage(((MSG *) msg)->statusData.CU, ((MSG *) msg)->statusData.DV, ((MSG *) msg)->statusData.status, ((MSG *) msg)->statusData.sense);
      break;               
    case TEXT_MESSAGE:
#ifdef DEBUG1    
      logOne("Received TEXT from Hercules");
#endif
#ifdef DEBUG2      
      printBufferInEBCDIC (((MSG *) msg)->textData.msg, ((MSG *) msg)->textData.length);
#endif      
      messageFSM.sendTextMessage(((MSG *) msg)->textData.length, ((MSG *) msg)->textData.msg, ((MSG *) msg)->textData.thereIsMoreComing);
      break;               
    case TEST_MESSAGE:
#ifdef DEBUG1
      logOne("Received TEST from Hercules");
#endif
#ifdef DEBUG2      
      printBufferInEBCDIC (((MSG *) msg)->testData.msg, ((MSG *) msg)->testData.length);
#endif
      messageFSM.sendTestRequestMessage(((MSG *) msg)->testData.length, ((MSG *) msg)->testData.msg, ((MSG *) msg)->testData.thereIsMoreComing);
      break;               
    case ERROR_MESSAGE:
#ifdef DEBUG1    
      logOne("Received an ERROR from Hercules");
#endif
      break;                                
  }
}

void txDataCallback (unsigned char ch) {
#ifdef DEBUG2  
     logTwo("txDataCallback From Hercules to Line: ",ch);
#endif     
    spi_irq_disable(SPI2, SPI_RXNE_INTERRUPT);	
    txBuffer.writeBuffer(ch);
    spi_irq_enable(SPI2, SPI_RXNE_INTERRUPT);
}

void txToHercules (unsigned char ch) {
#ifdef DEBUG2  
  logTwo("Sending to Hercules : ", ch);
#endif  
  Serial1.write(ch); 
}

class SyncFSM syncFSM(receiveCallback);


void enterHuntStateCallback () {
     syncFSM.enterHuntState();     
}

void enterHuntHercules() {
#ifdef DEBUG4  
  logOne("Enter Hunt state - Hercules");
#endif  
}


extern "C" void __irq_spi2 (void) {
  if (spi_is_tx_empty(SPI2)){
    if (txBuffer.isBufferEmpty()) {
      spi_tx_reg(SPI2, 0xff);  
    } else {
      spi_tx_reg(SPI2, translationArray[txBuffer.readBuffer()]);  
    }    
  }

  if (spi_is_rx_nonempty(SPI2)) {
    syncFSM.receivedData(spi_rx_reg(SPI2));
  }
}


void loop() {
  char ch;
  if (!rxBuffer.isBufferEmpty()) {
    spi_irq_disable(SPI2, SPI_RXNE_INTERRUPT);	
    ch = rxBuffer.readBuffer();
    spi_irq_enable(SPI2, SPI_RXNE_INTERRUPT);
#ifdef DEBUG3      
    logTwo("Data from SyncFSM buffer to Hercules : ", ch);
#endif      
    syncFSM.receivedData(ch);
  }
  if (Serial1.available()>0) {
     ch = Serial1.read();
#ifdef DEBUG3     
     logTwo("Reciving from Hercules : ", ch);
#endif     
     herculesMessageFSM.rxData(ch);
#ifdef DEBUG3     
     logOne("After rxData");
#endif     
  }
}
