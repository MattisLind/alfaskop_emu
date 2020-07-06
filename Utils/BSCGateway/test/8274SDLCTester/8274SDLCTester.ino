/*
 
*/

#include <libmaple/delay.h>
#include "RingBuffer.h"

#define IOR PB6
#define IOW PB7
#define IOW_SHIFT 7
#define IOR_SHIFT 6
#define A0 PB10
#define A1 PB11
#define RESET PB9
#define RESET_SHIFT 9
#define DIRECTION PB0
#define DIRECTION_SHIFT 0
#define ADDRESS_MASK 0x00000C00
#define ADDRESS_SHIFT 10
#define DATA_MASK 0x000000FF

HardwareTimer timer(2);

class RingBuffer txBuffer;
class RingBuffer rxBuffer;

inline void outputAddress (int address) {
  //int tmp = ;
  //GPIOB->regs->ODR &= ~(0b11<<ADDRESS_SHIFT) | (address << ADDRESS_SHIFT);  
  //GPIOB->regs->ODR |= (3<<ADDRESS_SHIFT) & (3 << ADDRESS_SHIFT);
  GPIOB->regs->ODR = (GPIOB->regs->ODR & ~(0x03 << ADDRESS_SHIFT)) |  (address << ADDRESS_SHIFT);
  //tmp = tmp |  (address << ADDRESS_SHIFT); 
  //GPIOB->regs->ODR = tmp;
}

inline void setIOR () {
  //digitalWrite(IOR, HIGH);
  GPIOB->regs->BSRR = 1 << IOR_SHIFT;
}

inline void clearIOR () {
  //digitalWrite(IOR, LOW);
  GPIOB->regs->BRR = 1 << IOR_SHIFT;
}

inline void setIOW () {
  GPIOB->regs->BSRR = 1 << IOW_SHIFT;
}

inline void clearIOW () {
  GPIOB->regs->BRR = 1 << IOW_SHIFT;
}

inline void setDirection () {
  GPIOB->regs->BSRR = 1 << DIRECTION_SHIFT;
}

inline void clearDirection () {
  GPIOB->regs->BRR = 1 << DIRECTION_SHIFT;
}

inline void setReset () {
  GPIOB->regs->BSRR = 1 << RESET_SHIFT;
}

inline void clearReset () {
  GPIOB->regs->BRR = 1 << RESET_SHIFT;
}

inline void outputData(int value) {
  GPIOA->regs->CRL = 0x33333333; // set all as outputs 
  GPIOA->regs->ODR = (GPIOA->regs->ODR & ~DATA_MASK) |  (0xff & value);
}

inline void writeData (int address, int value) {
  setDirection();
  outputData(value);
  outputAddress(address);
  clearIOW();
  delay_us(1);
  setIOW(); 
}

inline int readData (int address) {
  int tmp;
  clearDirection();
  GPIOA->regs->CRL = 0x44444444; // set all as inputs
  outputAddress (address);
  delay_us(1);
  clearIOR();
  delay_us(2);
  tmp = GPIOA->regs->IDR & DATA_MASK;
  delay_us(2);
  setIOR(); 
  return tmp; 
}

inline int readStatusRegister (int channel) {
  return 0xff & readData((channel & 0x01) | 0x02);
}

inline int readStatusRegister (int channel, int regNumber) {
  writeData((channel & 0x01) | 0x02, regNumber);
  delay_us(2);
  return 0xff & readData((channel & 0x01) | 0x02);  
}

inline void writeControlRegister (int channel, int value) {
  writeData ((channel & 0x01) | 0x02, value);
}

inline void writeControlRegister (int channel, int regNumber, int value) {
  writeData((channel & 0x01) | 0x02, regNumber);
  delay_us(2);
  writeData((channel & 0x01) | 0x02, value);
}

inline int readDataRegister (int channel) {
  return (0xff & readData(channel & 0x01));
}

inline void writeDataRegister (int channel, int value) {
  writeData(channel & 0x01, value);
}


inline void sendData (int channel, int data) {
  while (!(readStatusRegister(channel) & 0x04));
  writeData (channel, data);
}

inline bool isTxEmpty (int channel) {
  return ((readStatusRegister(channel) & 0b00000100) == 0b00000100);
}

inline bool isRxAvailable (int channel) {
  return ((readStatusRegister(channel) & 0b00000001) == 0b00000001);
}

inline bool isFrameAborted(int channel) {
 return ((readStatusRegister(channel) & 0b10000000) == 0b10000000);
}

inline bool isEndOfFrame (int channel) {
  return ((readStatusRegister (channel, 1) & 0b10000000) == 0b10000000); 
}

inline bool isCrcError (int channel) {
  return ((readStatusRegister (channel, 1) & 0b01000000) == 0b01000000); 
}


inline int receiveData (int channel) {
  while (!(readStatusRegister(channel) & 0x01));
  return readData(channel);
}


// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(921600);
  setIOR();
  setIOW();
  pinMode (IOR, OUTPUT);
  pinMode (IOW, OUTPUT);
  pinMode (A0,  OUTPUT);
  pinMode (A1,  OUTPUT);
  pinMode (RESET, OUTPUT);
  pinMode (DIRECTION, OUTPUT);
  setIOR();
  setIOW();
  setReset();
  delay_us(10);
  clearReset();
  delay_us(10);
  Serial.println();
  Serial.print("8274 SDLC TESTER> " );
}

inline void channelReset(int channel) {
 writeControlRegister(channel, 0b00011000); // channel RESET
}

inline void errorReset (int channel) {
   writeControlRegister(channel, 0b00110000); // Error RESET
}

inline void sendAbort (int channel) {
  writeControlRegister(channel, 0b00001000);
}

inline void resetExtStatus (int channel) {
  writeControlRegister(channel, 0b00010000);
}
 
inline void enterHuntMode (int channel) {
    writeControlRegister(channel, 0x03);  // Next write is to WR3 and RESET EXT/STATUS INTERRUPT
    writeControlRegister(channel, 0b11011001);  // 8 bits Hunt mode Rx CRC enable Rx Enable
}

inline void hardwareReset() {
    setReset();  
    delay_us(10);
    clearReset();
    delay_us(10);
}

void initHdlc (int channel) {
    channelReset(channel);
    delay_us(2);
    writeControlRegister(channel, 0x14); // Next write is to WR4 and RESET EXT/STATUS INTERRUPT
    writeControlRegister(channel, 0b00100000); // X1 Clock SDLC SYNC MODE 
    writeControlRegister(channel, 0x12);  // Next write is to WR2 and RESET EXT/STATUS INTERRUPT
    writeControlRegister(channel, 0b00000000);  // No interrupts enabled all should be zero
    writeControlRegister(channel, 0x11);  // Next write is to WR1 and RESET EXT/STATUS INTERRUPT
    writeControlRegister(channel, 0b00000000);  // No interrupts enabled all should be zero
    writeControlRegister(channel, 0x17);  // Next write is to WR7 and RESET EXT/STATUS INTERRUPT
    writeControlRegister(channel, 0b01111110);  // Sync byte must be 01111110
    writeControlRegister(channel, 0x13);  // Next write is to WR3 and RESET EXT/STATUS INTERRUPT
    writeControlRegister(channel, 0b11011001);  // 8 bits Hunt mode Rx CRC enable Rx Enable
    writeControlRegister(channel, 0x15);  // Next write is to WR5 and RESET EXT/STATUS INTERRUPT
    writeControlRegister(channel, 0b01101001);  // 8 bits Tx Enable CCITT-CRC RTS Tx CRC enable
    errorReset (channel); 
    errorReset (channel);
    errorReset (channel);    
}

inline void resetRxCrc (int channel) {
  writeControlRegister(channel, 0b01000000);
}

inline void resetTxCrc (int channel) {
  writeControlRegister(channel, 0b10000000);
}
inline void resetTxUnderrun (int channel) {
  writeControlRegister(channel, 0b11000000);
}


void printTwoDigitHex (int data) {
  if (data < 16) {
    Serial.print('0');
  } 
  Serial.print(data, HEX);
}

void printPrompt() {
  Serial.println();
  Serial.print("8274 SDLC TESTER> " );
}

bool messagePrinted = false;
bool firstTxChar = true;
bool sendingInProgress = false;
void loop() {
  int data, tmp;
  if (isRxAvailable(1)) {
    tmp = readDataRegister(1);
    //printTwoDigitHex(tmp);
    //if (isCrcError(1)) {
    //  Serial.println("CRC ERROR"); 
    //}
    rxBuffer.writeBuffer(tmp);
  }
  if (sendingInProgress && isTxEmpty(1)) {
    if (!txBuffer.isBufferEmpty()) {
      writeDataRegister(1, txBuffer.readBuffer());
      if (firstTxChar) {
        firstTxChar = false;
        resetTxUnderrun(1);
      }
    } else {
      sendingInProgress = false;
    }
  }   
  if (isEndOfFrame(1)) {
    Serial.println();
    Serial.print("Message received: ");      
    while (!rxBuffer.isBufferEmpty()) {
      printTwoDigitHex(rxBuffer.readBuffer()); 
    }
    Serial.println();
    if (isCrcError(1)) {
      Serial.println("CRC ERROR"); 
    } else {
      Serial.println("CRC OK");
    }
    errorReset(1);
    printPrompt();
  } 
  if (isFrameAborted(1)) {
    resetRxCrc(1);
    enterHuntMode(1);
    resetExtStatus(1);
    //Serial.println();
    //Serial.print("Frame aborted!");
    //printPrompt();
  }
  if (Serial.available()> 0) {
    tmp = Serial.read();
    if ((tmp >= 'a') && (tmp <= 'z')) {
      tmp &= ~0x20; // to upper case
    }
    switch (tmp) {
      case 'R':
        Serial.write(tmp);           
        hardwareReset();
        initHdlc(1);
        printPrompt();
        break;
      case 'S':
        if (sendingInProgress) {
          Serial.write(tmp);
          Serial.println();
          Serial.print("Sending already in progress!");
          printPrompt();
        } else {
          txBuffer.writeBuffer(0x40);
          txBuffer.writeBuffer(0x93);
          sendingInProgress = true;
          firstTxChar=true;
          Serial.write(tmp);
          printPrompt();
        }
        break;
      case 'T':
        if (sendingInProgress) {
          Serial.write(tmp);
          Serial.println();
          Serial.print("Sending already in progress!");
          printPrompt();
        } else {
          txBuffer.writeBuffer(0x21);
          txBuffer.writeBuffer(0x43);
          sendingInProgress = true;
          firstTxChar=true;
          Serial.write(tmp);
          printPrompt();
        }
        break;
      case 'U':
        if (sendingInProgress) {
          Serial.write(tmp);
          Serial.println();
          Serial.print("Sending already in progress!");
          printPrompt();
        } else {
          txBuffer.writeBuffer(0x66);
          txBuffer.writeBuffer(0x64);
          sendingInProgress = true;
          firstTxChar=true;
          Serial.write(tmp);
          printPrompt();
        }
        break;
      case 'V':
        if (sendingInProgress) {
          Serial.write(tmp);
          Serial.println();
          Serial.print("Sending already in progress!");
          printPrompt();
        } else {
          txBuffer.writeBuffer(0xcc);
          txBuffer.writeBuffer(0x19);
          sendingInProgress = true;
          firstTxChar=true;
          Serial.write(tmp);
          printPrompt();
        }
        break;
      case 'H':
        Serial.println();
        Serial.println("8274 SDLC TESTER HELP");
        Serial.println("=======================");
        Serial.println("H - HELP");
        Serial.println("S - Send SNRM message");
        Serial.println("A - Send ACTPU message");
        Serial.println("R - Do a Reset of the 8274 chip");
        printPrompt();
        break;
      case '\r': 
        printPrompt();
        break;
    }
  } 
}
