/*
 
*/

#include <libmaple/delay.h>

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



void outputAddress (int address) {
  //int tmp = ;
  //GPIOB->regs->ODR &= ~(0b11<<ADDRESS_SHIFT) | (address << ADDRESS_SHIFT);  
  //GPIOB->regs->ODR |= (3<<ADDRESS_SHIFT) & (3 << ADDRESS_SHIFT);
  GPIOB->regs->ODR = (GPIOB->regs->ODR & ~(0x03 << ADDRESS_SHIFT)) |  (address << ADDRESS_SHIFT);
  //tmp = tmp |  (address << ADDRESS_SHIFT); 
  //GPIOB->regs->ODR = tmp;
}

void setIOR () {
  //digitalWrite(IOR, HIGH);
  GPIOB->regs->BSRR = 1 << IOR_SHIFT;
}

void clearIOR () {
  //digitalWrite(IOR, LOW);
  GPIOB->regs->BRR = 1 << IOR_SHIFT;
}

void setIOW () {
  GPIOB->regs->BSRR = 1 << IOW_SHIFT;
}

void clearIOW () {
  GPIOB->regs->BRR = 1 << IOW_SHIFT;
}

void setDirection () {
  GPIOB->regs->BSRR = 1 << DIRECTION_SHIFT;
}

void clearDirection () {
  GPIOB->regs->BRR = 1 << DIRECTION_SHIFT;
}

void setReset () {
  GPIOB->regs->BSRR = 1 << RESET_SHIFT;
}

void clearReset () {
  GPIOB->regs->BRR = 1 << RESET_SHIFT;
}

void outputData(int value) {
  //value = 0xAA;
  GPIOA->regs->CRL = 0x33333333; // set all as outputs 
  GPIOA->regs->ODR = (GPIOA->regs->ODR & ~DATA_MASK) |  (0xff & value);
}

void writeData (int address, int value) {
  setDirection();
  outputData(value);
  outputAddress(address);
  clearIOW();
  delay_us(1);
  setIOW(); /*
  Serial1.print("Write Data Adress: ");
  Serial1.print(address, DEC);
  Serial1.print(" Data: "); 
  Serial1.print(value, HEX);
  Serial1.println(); */
}

int readData (int address) {
  int tmp;
  clearDirection();
  GPIOA->regs->CRL = 0x44444444; // set all as inputs
  outputAddress (address);
  delay_us(1);
  clearIOR();
  delay_us(2);
  tmp = GPIOA->regs->IDR & DATA_MASK;
  delay_us(2);
  setIOR(); /*
  Serial1.print("Read Data Adress: ");
  Serial1.print(address, DEC);
  Serial1.print(" Data: "); 
  Serial1.print(tmp, HEX);
  Serial1.println(); */
  return tmp; 
}

int readStatusRegister (int channel) {
  return 0xff & readData((channel & 0x01) | 0x02);
}

int readStatusRegister (int channel, int regNumber) {
  writeData((channel & 0x01) | 0x02, regNumber);
  delay_us(2);
  return 0xff & readData((channel & 0x01) | 0x02);  
}

void writeControlRegister (int channel, int value) {
  writeData ((channel & 0x01) | 0x02, value);
}

void writeControlRegister (int channel, int regNumber, int value) {
  writeData((channel & 0x01) | 0x02, regNumber);
  delay_us(2);
  writeData((channel & 0x01) | 0x02, value);
}

int readDataRegister (int channel) {
  int tmp=0xff & readData(channel & 0x01);
  //Serial1.print("Read Data Register ");
  //Serial1.print(tmp;, HEX);
  //Serial1.println();
  return tmp;
}

void writeDataRegister (int channel, int value) {
  //Serial1.print("Write Data Register ");
  //Serial1.print(value, HEX);
  //Serial1.println();
  writeData(channel & 0x01, value);
}

void initAsyncMode (int channel, int clockrate, int rxBits, int txBits, int parityType, int stopBits, int parityEnable, int rxEnable, int txEnable, int autoEnable, int brk, int rts, int dtr) {
  writeControlRegister(channel, 0x30); // channel RESET 
  writeControlRegister(channel, 0x14);
  writeControlRegister(channel, clockrate << 6 | stopBits << 2 | parityType << 1 | parityEnable);
  writeControlRegister(channel, 0x13);
  writeControlRegister(channel, rxBits << 6 | rxEnable | autoEnable << 5);
  writeControlRegister(channel, 0x15);
  writeControlRegister(channel, txBits << 5 | txEnable << 3 | dtr << 7 | brk << 4 | rts << 1);  
}

void sendData (int channel, int data) {
  while (!(readStatusRegister(channel) & 0x04));
  writeData (channel, data);
}

bool isTxEmpty (int channel) {
  return ((readStatusRegister(channel) & 0x04) == 0x04);
}

bool isRxAvailable (int channel) {
  return ((readStatusRegister(channel) & 0x01) == 0x01);
}

int receiveData (int channel) {
  while (!(readStatusRegister(channel) & 0x01));
  return readData(channel);
}



// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial1.begin(921600);
  //GPIOA->regs->CRL = 0x44444444; // A is inputs
  //GPIOB->regs->CRH = 0x44441144  // B10 and B11 is outputs;
  //GPIOB->regs->CRL = 0x44444411  //
  setIOR();
  setIOW();
  pinMode (IOR, OUTPUT);
  pinMode (IOW, OUTPUT);
  pinMode (A0,  OUTPUT);
  pinMode (A1,  OUTPUT);
  pinMode (RESET, OUTPUT);
  pinMode (DIRECTION, OUTPUT);
  pinMode (PB5, OUTPUT);
//  setReset();
//  delay(100);
//  clearReset();
//  delay(10);
//  initAsyncMode (0, 3, 3, 3, 1, 1, 0, 1, 1, 0, 0, 1, 1);
  setIOR();
  setIOW();
  setReset();
  delay_us(10);
  clearReset();
  delay_us(10);
  //initAsyncMode (0, 3, 3, 3, 1, 1, 0, 1, 1, 0, 0, 1, 1);
//Serial1.print("Command> ");
// Reset Channel
// init WR4
Serial1.println();
Serial1.print("ALFASKOP COMMANDER> " );
}


  //digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  //digitalWrite(IOR, LOW);
  //digitalWrite(PB5, LOW);
  //clearIOR();
  //clearReset();
  //clearIOW();
  //setDirection();
  //outputData(address);
  //outputAddress(address++);
  //delay(100);                       // wait for a second
  //digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  //digitalWrite(IOR, HIGH);
  //digitalWrite(PB5, HIGH);
  //setIOR();
  //setReset();
  //setIOW();
  //setDirection();
  //outputData(address);
  //outputAddress(address++);
  //delay(100);                       // wait for a second
  //Serial1.write('A');
  //setReset();
  //Serial1.print("Channel:");
  //Serial1.print(address&0x1, DEC);
  //Serial1.println();
  //tmp = readStatusRegister(address, 0);
  //Serial1.print("Status 0:");
  //Serial1.print(tmp, HEX);
  //Serial1.println();
  //tmp = readStatusRegister(address, 1);
  //Serial1.print("Status 2:");
  //Serial1.print(tmp, HEX);
  //Serial1.println();
  //tmp = readStatusRegister(address, 2);
  //Serial1.print("Status 2:");
  //Serial1.print(tmp, HEX);
  //Serial1.println();
  //tmp = readDataRegister(address++);
  //Serial1.print("Data:");
  //Serial1.print(tmp, HEX);
  //Serial1.println();
  //sendData(0,address++);
  //Serial1.print("Data sent");
  //Serial1.println();
  //delay(1000);
  /* Async example 
  if (isRxAvailable(0)) {
    tmp = receiveData(0);
    Serial1.write(tmp);
  }
  if (Serial1.available()> 0) {
    tmp = Serial1.read();
    sendData(0,tmp);
  } */


void initHdlc () {
    setReset();  
    delay_us(10);
    clearReset();
    delay_us(10);
    writeControlRegister(0, 0b00011000); // channel RESET
    //writeControlRegister(0, 0b00110000); // channel RESET
    delay_us(2);
    writeControlRegister(0, 0b00011000); // Error RESET
    writeControlRegister(0, 0x14); // Next write is to WR4 and RESET EXT/STATUS INTERRUPT
    writeControlRegister(0, 0b00100000); // X1 Clock SDLC SYNC MODE 
    writeControlRegister(0, 0x12);  // Next write is to WR2 and RESET EXT/STATUS INTERRUPT
    writeControlRegister(0, 0b00000000);  // No interrupts enabled all should be zero
    writeControlRegister(0, 0x11);  // Next write is to WR1 and RESET EXT/STATUS INTERRUPT
    writeControlRegister(0, 0b00000000);  // No interrupts enabled all should be zero
    writeControlRegister(0, 0x17);  // Next write is to WR7 and RESET EXT/STATUS INTERRUPT
    writeControlRegister(0, 0b01111110);  // Sync byte must be 01111110
    writeControlRegister(0, 0x13);  // Next write is to WR3 and RESET EXT/STATUS INTERRUPT
    writeControlRegister(0, 0b11011001);  // 8 bits Hunt mode Rx CRC enable Rx Enable
    writeControlRegister(0, 0x15);  // Next write is to WR5 and RESET EXT/STATUS INTERRUPT
    //writeControlRegister(0, 0b01100001);  // 8 bits Tx Enable CCITT-CRC RTS Tx CRC enable
    writeControlRegister(0, 0b01100001);  
    writeControlRegister(0, 0b00110000); // Error RESET
    writeControlRegister(0, 0b00110000); // Error RESET
    writeControlRegister(0, 0b00110000); // Error RESET
}


char rxBuf[255];
char txBuf[10] = {0x00, 0xff, 0xc0, 0xa0};
int txLen=4;
int txCnt=0, rxCnt=0;
int txDone=1, rxDone=0;
int cmdState = 0;
int cmd;
int hexValue;
int readLast=0;
uint32_t oldTimerValue, oldTimerRTSValue;
// the loop function runs over and over again forever

void printTwoDigitHex (int data) {
  if (data < 16) {
    Serial1.print('0');
  } 
  Serial1.print(data, HEX);
}


void loop() {
  int tmp, tmp2;
  int i;

  if (txDone == 3) {
    if ((((uint32_t) micros()) - oldTimerRTSValue) > 400) {
      txDone=0;  
      // We have sent all bytes. Now we want to stop the transmitter and set RTS low. But not until all the CRC bytes
      // has been sent. Do we need to do special handling for this?
      // What if we just stop it directly?
      //delay_us(120);
      writeControlRegister(0, 0b00000101);  // Next write is to WR5 
      writeControlRegister(0, 0b01101011);  // 8 bits Tx Enable CCITT-CRC RTS OFF Tx CRC enable 
    }        
  }
  if (txDone == 2) {
    if ((((uint32_t) micros()) - oldTimerValue) > 120) {
      txDone=1;  
      // We have sent all bytes. Now we want to stop the transmitter and set RTS low. But not until all the CRC bytes
      // has been sent. Do we need to do special handling for this?
      // What if we just stop it directly?
      //delay_us(120);
      writeControlRegister(0, 0b00000101);  // Next write is to WR5 
      writeControlRegister(0, 0b01100001);  // 8 bits Tx Enable CCITT-CRC RTS OFF Tx CRC enable 
    }
  }
  if (rxDone == 1) {
    // print out the string and receive enable receiver again
    Serial1.println();
    Serial1.print("RECEIVED FRAME: ");
    for(i=0; i < rxCnt; i++) {
      printTwoDigitHex(rxBuf[i]);
      Serial1.write(' ');
    }
    Serial1.println();
    rxDone = 0;
    rxCnt=0;
    Serial1.print("ALFASKOP COMMANDER> " );
  }
  
  tmp = readStatusRegister(0);
  if (tmp & 0x01) {
    if ((rxDone == 0) || (rxDone == 2)) {
      rxBuf[rxCnt] = readDataRegister(0);
      if (rxDone == 2) {
        rxDone = 1;
      }
    }
    tmp2 = readStatusRegister(0,1);
    if ((tmp2 & 0x80) && (rxDone==0)) { // check if frame is completed
      rxDone=2;
      writeControlRegister(0, 0b00110000);  // Error RESET
    }
    rxCnt++;
  }
  if (tmp & 0x04) {
    if (txDone == 0) {
      if (txCnt < txLen) {
        writeDataRegister(0, txBuf[txCnt]);
        // Reset the EOM by issuing a RESET Tx Underrun / EOM Latch to force CRC generation
        if (txCnt==0) {

          writeControlRegister(0, 0b11000000);  
        }
        txCnt++;
      } else {
        txDone = 2;  
        oldTimerValue = (uint32_t) micros(); 
      }
    } 
  }

  if (Serial1.available()> 0) {
    tmp = Serial1.read();
    if ((tmp >= 'a') && (tmp <= 'z')) {
      tmp &= ~0x20; // to upper case
    }
    switch (cmdState) {
      case 0:
        switch (tmp) {
          case 'R':
            Serial1.write(tmp);
            initHdlc();
            txDone=1;
            Serial1.println();
            Serial1.print("ALFASKOP COMMANDER> " );
            break;
          case 'P':  // send poll
            Serial1.write(tmp);
            Serial1.println();
            if (txDone == 0) {
              Serial1.println("SENDING IN PROGRESS");
            } else {
              oldTimerRTSValue = (uint32_t) micros();
              txDone = 3;  
              txCnt=0;   
              writeControlRegister(0, 0b00010101);  // Next write is to WR5 
              writeControlRegister(0, 0b01100011);  // 8 bits Tx Enable CCITT-CRC RTS ON Tx CRC enable                        
            }
            //initHdlc();
            writeControlRegister(0, 0b00110000);  // Error RESET  
            writeControlRegister(0, 0b10000000);  // Reset Tx CRC Generator
            writeControlRegister(0, 0b01000000);  // Reset Rx CRC Checker
            //writeControlRegister(0, 0b00010101);  // Next write is to WR5 
            //writeControlRegister(0, 0b01101011);  // 8 bits Tx Enable CCITT-CRC RTS ON Tx CRC enable 
            Serial1.print("ALFASKOP COMMANDER> " );
            break;
          case 'T': // set destination address
          case 'D': // set poll status
          case 'F': // set source address
          case 'M': // set destination session
            Serial1.write(tmp);
            Serial1.write(' ');
            cmdState = 1;
            cmd = tmp;
            break;
          case 'X':
            Serial1.println();
            Serial1.print("Current poll buffer: ");
            for(i=0; i < 4; i++) {
              printTwoDigitHex(txBuf[i]);
              Serial1.write(' ');
            }
            Serial1.println();
            Serial1.println("<Todev> <Dsa> <Frdev> <Msgtyp>");
            Serial1.print("ALFASKOP COMMANDER> " );
            break;
          case 'H':
            Serial1.println();
            Serial1.println("ALFASKOP COMMANDER HELP");
            Serial1.println("=======================");
            Serial1.println("H - HELP");
            Serial1.println("P - Send Poll");
            Serial1.println("R - Do a Reset of the 8274 chip");
            Serial1.println("T HH - Set Todev");
            Serial1.println("F HH - Set Frdev");
            Serial1.println("D HH - Set Dsa");
            Serial1.println("M HH - Set Msgtyp");
            Serial1.println("HH is a two digit hex value");
            Serial1.println("X - print current poll buffer");
            Serial1.println();
            Serial1.print("ALFASKOP COMMANDER> " );
            break;
          case '\r': 
            Serial1.println();
            Serial1.print("ALFASKOP COMMANDER> " );
        }
        break;
      case 1: 
        //Serial1.write(tmp);
        // in state 1 we collect hex digits.
        if (((tmp >= '0' ) && (tmp <= '9')) || ((tmp >= 'A') && (tmp <= 'F'))) {
          Serial1.write(tmp); // Echo character
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
          Serial1.write(tmp); // Echo character
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
          case 'T':
            txBuf[0] = hexValue;
            break;
          case 'F':
            txBuf[2] = hexValue;
            break;
          case 'D':
            txBuf[1] = hexValue;
            break;
          case 'M':
            txBuf[3] = hexValue;
            break;;
        }
        Serial1.println();
        Serial1.print("ALFASKOP COMMANDER> " );
      break;      
    }
  } 

} 

