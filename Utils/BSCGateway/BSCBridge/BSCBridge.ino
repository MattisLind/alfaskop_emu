
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

#define RTS PB11 // Input
#define RFS PB1  // Output
#define DTR PB10 // Input 

SPIClass SPI_2(2); 


void txDataCallback (unsigned char);
void enterHuntStateCallback ();
void messageReceivedCallback (unsigned char, unsigned char *);
void txToHercules (unsigned char);
void messageReceivedFromHerculesCallback (unsigned char, unsigned char *);

class MessageFSM messageFSM(txDataCallback, messageReceivedCallback, enterHuntStateCallback);
class MessageFSM herculesMessageFSM(txToHercules, messageReceivedFromHerculesCallback, NULL, true);


HardwareTimer pwmtimer(1);
const int pwmOutPin = PA8; // pin10


void setup() {
  int period;
  int maxduty;
  // put your setup code here, to run once:
  pwmtimer.pause();
  period =13; // PWM period in useconds, freq 300 Hz
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
}


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
          Serial.print(buf[j])
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


void messageReceivedCallback(unsigned char msgType, unsigned char * msg) {
  // Dispatch message coming from terminal based on msgType and let the hercules facing take on.
  switch (msgType) {
    case EOT_MESSAGE:
      printMillis();
      Serial.println("Received EOT from Cluster controller");
      herculesMessageFSM.sendEOT();
      break;
    case ENQ_MESSAGE:
      printMillis();
      Serial.print("Received ENQ for CU=");
      Serial.print(((MSG *) msg)->enqData.CU, HEX);
      Serial.print(" DV=");
      Serial.print(((MSG *) (msg))->enqData.DV, HEX);
      Serial.println( "from Cluster controller");
      herculesMessageFSM.sendENQ(((MSG *) msg)->enqData.CU, ((MSG *) (msg))->enqData.DV ); 
      break;
    case NAK_MESSAGE:
      printMillis();
      Serial.print("Received NAK from Cluster controller");
      herculesMessageFSM.sendNAK();
      break;
    case ACK0_MESSAGE:
      printMillis();
      Serial.print("Received ACK0 from Cluster controller");
      herculesMessageFSM.sendACK0();
      break;
    case ACK1_MESSAGE:
      printMillis();
      Serial.print("Received ACK1 from Cluster controller");
      herculesMessageFSM.sendACK1();
      break;
    case WACK_MESSAGE:
      printMillis();
      Serial.print("Received WACK from Cluster controller");
      herculesMessageFSM.sendWACK();
      break;
    case RVI_MESSAGE:
      printMillis();
      Serial.print("Received RVI from Cluster controller");
      herculesMessageFSM.sendRVI();
      break;               
    case STATUS_MESSAGE:
      printMillis();
      Serial.print("Received STATUS for CU=");
      Serial.print(((MSG *) msg)->statusData.CU, HEX);
      Serial.print(" DV=");
      Serial.print(((MSG *) (msg))->statusData.DV, HEX);
      Serial.println( "from Cluster controller");      
      herculesMessageFSM.sendStatusMessage(((MSG *) msg)->statusData.CU, ((MSG *) msg)->statusData.DV, ((MSG *) msg)->statusData.status, ((MSG *) msg)->statusData.sense);
      break;               
    case TEXT_MESSAGE:
      printMillis();
      Serial.print("Received TEXT from Cluster controller");
      herculesMessageFSM.sendTextMessage(((MSG *) msg)->textData.length, ((MSG *) msg)->textData.msg, ((MSG *) msg)->textData.thereIsMoreComing);
      break;               
    case TEST_MESSAGE:
      printMillis();
      Serial.print("Received TEST from Cluster controller");
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
      printMillis();
      Serial.println("Received EOT from Hercules"); 
      messageFSM.sendEOT();
      break;
    case ENQ_MESSAGE:
      printMillis();
      Serial.print("Received ENQ for CU=");
      Serial.print(((MSG *) msg)->enqData.CU, HEX);
      Serial.print(" DV=");
      Serial.print(((MSG *) (msg))->enqData.DV, HEX);
      Serial.println( "from Hercules");    
      messageFSM.sendENQ(((MSG *) msg)->enqData.CU, ((MSG *) (msg))->enqData.DV ); 
      break;
    case NAK_MESSAGE:
      printMillis();
      Serial.print("Received NAK from Hercules");    
      messageFSM.sendNAK();
      break;
    case ACK0_MESSAGE:
      printMillis();
      Serial.print("Received ACK0 from Hercules");
      messageFSM.sendACK0();
      break;
    case ACK1_MESSAGE:
      printMillis();
      Serial.print("Received ACK1 from Hercules");
      messageFSM.sendACK1();
      break;
    case WACK_MESSAGE:
      printMillis();
      Serial.print("Received WACK from Hercules");
      messageFSM.sendWACK();
      break;
    case RVI_MESSAGE:
      printMillis();
      Serial.print("Received RVI from Hercules");
      messageFSM.sendRVI();
      break;               
    case STATUS_MESSAGE:
      printMillis();
      Serial.print("Received STATUS for CU=");
      Serial.print(((MSG *) msg)->statusData.CU, HEX);
      Serial.print(" DV=");
      Serial.print(((MSG *) (msg))->statusData.DV, HEX);
      Serial.println( "from Hercules");
      messageFSM.sendStatusMessage(((MSG *) msg)->statusData.CU, ((MSG *) msg)->statusData.DV, ((MSG *) msg)->statusData.status, ((MSG *) msg)->statusData.sense);
      break;               
    case TEXT_MESSAGE:
      printMillis();
      Serial.print("Received TEXT from Hercules");
      messageFSM.sendTextMessage(((MSG *) msg)->textData.length, ((MSG *) msg)->textData.msg, ((MSG *) msg)->textData.thereIsMoreComing);
      break;               
    case TEST_MESSAGE:
      printMillis();
      Serial.print("Received TEST from Hercules");
      messageFSM.sendTestRequestMessage(((MSG *) msg)->testData.length, ((MSG *) msg)->testData.msg, ((MSG *) msg)->testData.thereIsMoreComing);
      break;               
    case ERROR_MESSAGE:
      break;                                
  }
}

void txDataCallback (unsigned char ch) {
     txBuffer.writeBuffer(ch);
}

void txToHercules (unsigned char ch) {
  printMillis();
  Serial.print("Sending to Hercules : ");
  printTwoDigitHex(ch);
  Serial.println();
  Serial1.write(ch); 
}

class SyncFSM syncFSM(receiveCallback);


void enterHuntStateCallback () {
     syncFSM.enterHuntState();     
}



void loop() {
char ch;
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
  if (Serial1.available()>0) {
     ch = Serial1.read();
     printMillis();
     Serial.print("Reciving from Hercules : ");
     printTwoDigitHex(ch);
     Serial.println();
     herculesMessageFSM.rxData(ch);
  }
}
