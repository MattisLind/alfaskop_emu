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


void messageReceivedCallback(unsigned char msgType, unsigned char * msg) {
     // Serialize and send messgae over serial port
}

void txDataCallback (unsigned char ch) {
     txBuffer.writeBuffer(ch);
}

class SyncFSM syncFSM(receiveCallback);


void enterHuntStateCallback () {
     syncFSM.enterHuntState();     
}

class MessageFSM messageFSM(txDataCallback, messageReceivedCallback, enterHuntStateCallback);

void sendSerializedCharacter (char ch) {
     Serial.write(ch);
}

void processIncomingMessage (MSG * msg) {
     
}

class CommandSerializer commandSerializer(Serial, processIncomingMessage);

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
  if (Serial.available()>0) {
     commandSerializer.processCharacter(Serial.read());
  }
}
