/*
 MC6846 Reader program. Based on a STM32 Blue pill connected to the MC6846. The databus is level converted usinga 74LVC245.
 
*/

#include <libmaple/delay.h>

#define E PB0
#define CS1 PA8
#define CS0 PB1
#define RESET PC14


void setupAdressOutputAndDataInput () {
  GPIOB->regs->CRL |= 0x33300000; // set  B5, B6, B7 as outputs
  GPIOB->regs->CRL &= 0x333FFFFF;  // but don't affect the other bots
  GPIOB->regs->CRH =  0x33333333; // Set the B15, B14, B13, B12, B11, B10, B9 and B8 as outputs
  GPIOA->regs->CRL = 0x44444444; // set all as inputs 
}

void outputAddress (int address) {
  GPIOB->regs->ODR = (GPIOB->regs->ODR & 0b0000000000011111) |  (0b1111111111100000 & (address << 5));
}


// E is PB0
void inline setE () {
  //digitalWrite(IOR, HIGH);
  GPIOB->regs->BSRR = 1 << 0;
}

void inline clearE () {
  //digitalWrite(IOR, LOW);
  GPIOB->regs->BRR = 1 << 0;
}
// CS0 is PB1
void inline setCS0 () {
  GPIOB->regs->BSRR = 1 << 1;
  digitalWrite(CS0, HIGH);
}

void inline clearCS0 () {
  GPIOB->regs->BRR = 1 << 1;
  //digitalWrite(CS0, LOW);
}
// CS1 is PA8
void inline setCS1 () {
  GPIOA->regs->BSRR = 1 << 8;
}

void inline clearCS1 () {
  GPIOA->regs->BRR = 1 << 8;
}

// Reset is PC14
void inline setReset () {
  GPIOC->regs->BSRR = 1 << 14;
}

void inline clearReset () {
  GPIOC->regs->BRR = 1 << 14;
}


int readData (int address) {
  int tmp;
  outputAddress (address);
  delay_us(1);
  clearE();
  delay_us(1);
  setE(); 
  delay_us(1);
  tmp = GPIOA->regs->IDR & 0xff;
  return tmp; 
}



// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  setupAdressOutputAndDataInput();
  Serial.begin(921600);
  pinMode (E, OUTPUT);
  pinMode (CS1, OUTPUT);
  pinMode (CS0,  OUTPUT);
  pinMode (RESET, OUTPUT);
  clearReset();
  delay_us(10);
  setReset();
  Serial.print("MC6846 READER> " );
}


void printNZeros(int n) {
  int i;
  if (n<=0) return;
  for (i=0;i<n; i++) {
    Serial.print('0');
  }
}

void printZeroPrePaddedHex (int data, int n) {
  if (data < 16) {
    printNZeros(n-1);
  } else if (data < 256) {
    printNZeros(n-2);
  } else if (data < 4096) {
    printNZeros(n-3);
  }
  Serial.print(data, HEX);
}

int a=2040;
int cs=0;

void loop() {
  int tmp, i, j;
  if (Serial.available()> 0) {
    tmp = Serial.read();
    if ((tmp >= 'a') && (tmp <= 'z')) {
      tmp &= ~0x20; // to upper case
    }
      switch (tmp) {
        case 'R':
          printZeroPrePaddedHex(a,4);
          Serial.print(":");
          printZeroPrePaddedHex(readData(a++),2);
          Serial.println();
          break;
        case 'P': 
          clearReset();
          delay_us(10);
          setReset();
          delay_us(10);
          clearCS1();
          clearCS0();
          cs=0;
          a=2040;
          break;
        case 'C': // set CS
          a=2040;
          Serial.print("CS:");
          Serial.print(cs, DEC);
          Serial.println();
          switch (cs) {
            case 0:
              clearCS1();
              clearCS0();
              cs++;
              break;
            case 1:
              cs++;
              clearCS1();
              setCS0();
              break;
            case 2:
              cs++;
              clearCS0();
              setCS1();
              break;
            case 3:
              cs=0;
              setCS1();
              setCS0();
              break;
          }
          break;
        case 'X':
          for (i=0; i<128;i++) {
            printZeroPrePaddedHex((i<<4),4);           
            for (j=0; j<16; j++) {
              Serial.print(" ");
              printZeroPrePaddedHex(readData( (i << 4) | j ),2);  
            }
            Serial.println();
          }
          break;        
        case 'H':
          Serial.println();
          Serial.println("MC6846 READER HELP");
          Serial.println("=======================");
          Serial.println("H - HELP");
          Serial.println("P - Reset");
          Serial.println("R - Read byte and increment address"););
          Serial.println("X - Read entire memory");
          Serial.println();
          Serial.print("MC6846 READER> " );
          break;
        case '\r': 
          Serial.println();
          Serial.print("MC6846 READER> " );
      }
  } 

} 

