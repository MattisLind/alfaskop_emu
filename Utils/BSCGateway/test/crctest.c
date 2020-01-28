#include <stdio.h>
#include <assert.h>
#include "../BSCGateway-STM32/lsbmsb.h"

unsigned short crc16(unsigned char *data_p, unsigned short length, unsigned short crc, unsigned short poly);

unsigned char testMessage1 [8] = {0x6c,0xd9,0x02,0x40,0x40,0x40,0x70,0x03};
unsigned char testMessage2 [10] = {0x6c,0xd9,0x02,0x40,0xc8,0x40,0x50,0x03, 0x0d, 0x28};
unsigned char testMessage1lsb [8];
unsigned char testMessage2lsb [8];

#include <stdio.h>

int crc163(unsigned char *ptr, int count)
{
    unsigned int crc;
    char i;

    crc = 0x0000;
    while (--count >= 0)
    {
        crc = crc ^ (unsigned int) *ptr++;
        i = 8;
        do
        {
            if (crc & 0x0001)
                crc = (crc >> 1) ^ 0xA001;  /* 0x8005 bit reversed */
            else
                crc = (crc >> 1);
        } while(--i);
    }
    return (crc);
}




unsigned crc162(unsigned char *buf, size_t len, unsigned short crc, unsigned short POLY)
{
    while (len--) {
        crc ^= *buf++;
        crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
        crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
        crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
        crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
        crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
        crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
        crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
        crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
    }
    return crc;
}



void printmessage (unsigned char * str, int length) {
  int i;
  for (i=0;i<length;i++) {
    printf("%02X", str[i] & 0xff); 
  }
    printf("\n");
}

int main () {
  int i;
  unsigned short crc;
  for (i=0; i<8; i++) {
    testMessage1lsb[i] = translationArray[testMessage1[i]];
    testMessage2lsb[i] = translationArray[testMessage2[i]];
  }
  printmessage(testMessage1,8);
  printmessage(testMessage2,8);
  printmessage(testMessage1lsb,8);
  printmessage(testMessage2lsb,8);
  crc = crc16(testMessage1, 8, 0x0000, 0xA001);
  printf ("%04X\n", crc);
  //assert (crc == 0x0000);
  crc = crc16(testMessage2, 10, 0x0000, 0xA001);
  printf ("%04X\n", crc);
  //assert (crc == 0x0000);
  crc = crc16(testMessage1lsb, 8, 0x0000, 0xA001);
  printf ("%04X\n", crc);
  //assert (crc == 0x0000);
  crc = crc16(testMessage2lsb, 8, 0x0000, 0xA001);
  printf ("%04X\n", crc);
  //assert (crc == 0x0000);
  crc = crc16(testMessage1, 8, 0xffff, 0xA001);
  printf ("%04X\n", crc);
  //assert (crc == 0x0000);
  crc = crc16(testMessage2, 10, 0xffff, 0xA001);
  printf ("%04X\n", crc);
  //assert (crc == 0x0000);
  crc = crc16(testMessage1lsb, 8, 0xffff, 0xA001);
  printf ("%04X\n", crc);
  //assert (crc == 0x0000);
  crc = crc16(testMessage2lsb, 8, 0xffff, 0xA001);
  printf ("%04X\n", crc);
  crc = crc162(testMessage1, 8, 0x0000, 0xA001);
  printf ("%04X\n", crc);
  crc = crc162(testMessage2, 10, 0x0000, 0xA001);
  printf ("%04X\n", crc);
  crc = crc162(testMessage1, 8, 0xffff, 0xA001);
  printf ("%04X\n", crc);
  crc = crc162(testMessage2, 10, 0xffff, 0xA001);
  printf ("%04X\n", crc);
  crc = crc163(testMessage1, 8);
  printf ("%04X\n", crc);
  crc = crc163(testMessage2, 10);
  printf ("%04X\n", crc);
  crc = crc163(testMessage1, 8);
  printf ("%04X\n", crc);
  crc = crc163(testMessage2, 10);
  printf ("%04X\n", crc);
}
