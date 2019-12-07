/*
This stupid little program converts a file with an address and 16 hex numbers 
into a binary file.
The file has 128 lines which gives an output of 2048 bytes.
Each line has this format
0000 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F
*/
#include <stdio.h>
int main () {
  char buf[2048];
  int tmp, i, j, address;
  for (i=0;i<128; i++) {
    scanf ("%04X", &address);
    for (j=0; j<16; j++) {
      scanf("%02X", &tmp);
      buf[i<<4 | j] = 0xff & tmp;
    }
  }
  fwrite (buf, 2048, 1, stdout);
}
