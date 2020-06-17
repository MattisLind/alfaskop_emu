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

HardwareTimer timer(2);

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
  GPIOA->regs->CRL = 0x33333333; // set all as outputs 
  GPIOA->regs->ODR = (GPIOA->regs->ODR & ~DATA_MASK) |  (0xff & value);
}

void writeData (int address, int value) {
  setDirection();
  outputData(value);
  outputAddress(address);
  clearIOW();
  delay_us(1);
  setIOW(); 
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
  setIOR(); 
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
  return tmp;
}

void writeDataRegister (int channel, int value) {
  writeData(channel & 0x01, value);
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

void handler_led(void){ // Toggle pin. 
  digitalWrite(PB1, !digitalRead(PB1));
}



// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.


      // Pause the timer while we're configuring it
    timer.pause();

    // Set up period
    timer.setPeriod(1000); // in microseconds

    // Set up an interrupt on channel 1
    timer.setChannel1Mode(TIMER_OUTPUT_COMPARE);
    timer.setCompare(TIMER_CH1, 1);  // Interrupt 1 count after each update
    timer.attachCompare1Interrupt(handler_led);

    // Refresh the timer's count, prescale, and overflow
    timer.refresh();

    // Start the timer counting
    timer.resume();  

  pinMode(PB1, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial1.begin(921600);
  setIOR();
  setIOW();
  pinMode (IOR, OUTPUT);
  pinMode (IOW, OUTPUT);
  pinMode (A0,  OUTPUT);
  pinMode (A1,  OUTPUT);
  pinMode (RESET, OUTPUT);
  pinMode (DIRECTION, OUTPUT);
  pinMode (PB5, OUTPUT);
  setIOR();
  setIOW();
  setReset();
  delay_us(10);
  clearReset();
  delay_us(10);
  Serial1.println();
  Serial1.print("IBM BSC COMMANDER> " );
}



void initBSC () {
    setReset();  
    delay_us(10);
    clearReset();
    delay_us(10);
    writeControlRegister(1, 0b00011000); // channel RESET
    delay_us(2);
    writeControlRegister(1, 0b00011000); // Error RESET
    writeControlRegister(1, 0x14); // Next write is to WR4 and RESET EXT/STATUS INTERRUPT
    writeControlRegister(1, 0b00010000); // X1 Clock 16 BIT SYNC CHAR SYNC MODE NO PARITY
    writeControlRegister(1, 0x12);  // Next write is to WR2 and RESET EXT/STATUS INTERRUPT
    writeControlRegister(1, 0b00000000);  // No interrupts enabled all should be zero
    writeControlRegister(1, 0x11);  // Next write is to WR1 and RESET EXT/STATUS INTERRUPT
    writeControlRegister(1, 0b00000000);  // No interrupts enabled all should be zero
    writeControlRegister(1, 0x17);  // Next write is to WR7 and RESET EXT/STATUS INTERRUPT
    writeControlRegister(1, 0b00110010);  // SYN Character
    //writeControlRegister(1, 0b11111111);  // SYN Character
    writeControlRegister(1, 0x16);  // Next write is to WR7 and RESET EXT/STATUS INTERRUPT
    writeControlRegister(1, 0b00110010);  // SYN Character
    //writeControlRegister(1, 0b11111111);  // SYN Character
    writeControlRegister(1, 0x13);  // Next write is to WR3 and RESET EXT/STATUS INTERRUPT
    writeControlRegister(1, 0b11010001);  // 8 bit RX, NO AUTO ENABLES, Rx CRC Not enabled , Rx Enable, HUNT MODE
    writeControlRegister(1, 0x15);  // Next write is to WR5 and RESET EXT/STATUS INTERRUPT
    writeControlRegister(1, 0b11100110); //  DTR active, 8 bit Tx, Tx Enable Tx CRC not enabled 
    writeControlRegister(1, 0b00110000); // Error RESET
    writeControlRegister(1, 0b00110000); // Error RESET
    writeControlRegister(1, 0b00110000); // Error RESET
}


char rxBuf[255];
char * txBuf;
char txBufPoll[5]= {0x40, 0x40, 0x40, 0x40, 0x2D};
char txBufStatus[9] = {0x01, 0x6C, 0xD9, 0x02, 0x40, 0x40, 0x40, 0x70, 0x03};
int txLen;
int txCnt=0, rxCnt=0;
int txState=0, rxDone=0, txDone=1;
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
  int data;
  tmp = readStatusRegister(1);
  if (tmp & 0x01) {
    data = readDataRegister(1);
    printTwoDigitHex(data);
    switch (data) {
      case 0x37:
      case 0x2d:
      writeControlRegister(1, 3, 0b11010001);  // 8 bit RX, NO AUTO ENABLES, Rx CRC Not enabled , Rx Enable, HUNT MODE
      break;
    }
  }
  if (tmp & 0x04) {
    if (txDone > 0) {
      if (txCnt < txLen) {
        writeDataRegister(1, txBuf[txCnt]);
        // Reset the EOM by issuing a RESET Tx Underrun / EOM Latch to force CRC generation
        txCnt++;
      } else {
        txDone = 0; 
        writeControlRegister(1, 5, 0b11100110);  // Next write is to WR5 - Disable Tx   
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
            initBSC();
            txDone=1;
            Serial1.println();
            Serial1.print("IBM BSC COMMANDER> ");
            break;
          case 'P':  // send poll
            Serial1.write(tmp);
            Serial1.println();
            txBuf = txBufPoll;
            txLen = 5;
            if (txDone > 0) {
              Serial1.println("SENDING IN PROGRESS");
            } else {
              txDone = 2;  
              txCnt=0;   
              writeControlRegister(1, 5, 0b11101110);  // Next write is to WR5 - Enable Tx                        
            } 
            Serial1.print("IBM BSC COMMANDER> " );
            break;
          case 'S':
            Serial1.write(tmp);
            Serial1.println();
            txLen = 9;
            txBuf = txBufStatus;
            if (txDone > 0) {
              Serial1.println("SENDING IN PROGRESS");
            } else {
              txDone = 1;  
              txCnt=0;   
              writeControlRegister(1, 5, 0b11101110);  // Next write is to WR5 - Enable Tx                        
            } 
            Serial1.print("IBM BSC COMMANDER> " );
            break;
          case 'C': // set destination address
          case 'D': // set poll status
            Serial1.write(tmp);
            Serial1.write(' ');
            cmdState = 1;
            cmd = tmp;
            break;
          case 'X':
            Serial1.println();
            Serial1.print("Current poll buffer: ");
            for(i=0; i < txLen; i++) {
              printTwoDigitHex(txBuf[i]);
              Serial1.write(' ');
            }
            Serial1.println();
            Serial1.print("IBM BSC COMMANDER> " );
            break;
          case 'H':
            Serial1.println();
            Serial1.println("IBM BSC COMMANDER HELP");
            Serial1.println("=======================");
            Serial1.println("H - HELP");
            Serial1.println("P - Send BSC Poll");
            Serial1.println("R - Do a Reset of the 8274 chip");
            Serial1.println("C HH - Set CU");
            Serial1.println("D HH - Set DV");
            Serial1.println("HH is a two digit hex value");
            Serial1.println("X - print current poll buffer");
            Serial1.println();
            Serial1.print("IBM BSC COMMANDER> " );
            break;
          case '\r': 
            Serial1.println();
            Serial1.print("IBM BSC COMMANDER> " );
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
          case 'C':
            txBuf[12] = hexValue;
            txBuf[13] = hexValue;
            break;
          case 'D':
            txBuf[14] = hexValue;
            txBuf[15] = hexValue;
            break;
        }
        Serial1.println();
        Serial1.print("IBM BSC COMMANDER> " );
      break;      
    }
  } 

}
