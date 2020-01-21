/* 

   Test program for SyncFSM

   Compile using:  c++ SyncFSMTest.cpp ../BSCGateway-STM32/SyncFSM.cpp -DDEBUG

*/
#include <assert.h>
#include "../BSCGateway-STM32/SyncFSM.h"
#include <stdio.h>
#include "../BSCGateway-STM32/ebcdic.h"
// Testdata MSBFIRST from the SPI.
// 11010011 00010011 00111011 00111111 11111111 11111010 01100010 01100111 01100111 11111111 11111111 
// 0xd3,0x13,0x3b,0x3f,0xff,0xfa,0x62, 0x67, 0x67, 0xff, 0xff 
// Test message is SYN, SYN, EOT, PAD
// 11010011 00010011 00111011
// 11101001 10001001 10011101
// 11110100 11000100 11001110
// 11111010 01100010 01100111
// 11111101 00110001 00110011
// 11111110 10011000 10011001
// 11111111 01001100 01001100
// 11111111 10100110 00100110
int cnt=0;

void receivedChar (unsigned char);

class SyncFSM syncFSM (receivedChar);

void receivedChar (unsigned char data) {
  printf ("%02X", data);
  switch (cnt) {
  case 0:
    assert (data == SYN);
    break;
  case 1:
    assert (data == SYN);
    break;
  case 2:
    assert (data == EOT);
    break;
  case 3:
    assert (data == PAD);
    syncFSM.enterHuntState();
    break;
  case 4:
    assert (data == SYN);
    break;
  case 5:
    assert (data == SYN);
    break;
  case 6:
    assert (data == EOT);
    break;
  case 7:
    assert (data == PAD);
    syncFSM.enterHuntState();
    break;
  default:
    assert(0);
    break;
  }
  cnt++;
}



unsigned char testData [] = {0xd3,0x13,0x3b,0x3f,0xff,0xfa,0x62, 0x67, 0x67, 0xff, 0xff};

int main () {
  int i;
  printf("Trying to send two messages slightly out of sync, SYN, SYN, EOT, PAD\n");
  printf("Received:");
  for (i=0; i< sizeof testData; i++) {
    syncFSM.receivedData(testData[i]);
  }
  assert(cnt == 8);
  printf ("\nTest done OK!\n");
}
