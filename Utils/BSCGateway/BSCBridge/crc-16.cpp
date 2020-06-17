/*

  CRC-16 algorithm taken from Internet.
  Made by Isak Johansson
  https://people.cs.umu.se/isak/snippets/crc-16.c

 */
//#define POLY 0x8408
//#define POLY 0xA001
/*
//                                      16   12   5
// this is the CCITT CRC 16 polynomial X  + X  + X  + 1.
// This works out to be 0x1021, but the way the algorithm works
// lets us use 0x8408 (the reverse of the bit pattern).  The high
// bit is always assumed to be set, thus we only use 16 bits to
// represent the 17 bit value.
*/
//            16   15   2
// CRC-16 is X  + X  + X  + 1 is 8005 and a001 reversed.
//


unsigned short calculateCrcChar (unsigned short crc, unsigned char data_p) {
  unsigned char i;
  unsigned int data;
  for (i=0, data=(unsigned int)0xff & data_p;
       i < 8; 
       i++, data >>= 1)
    {
      if ((crc & 0x0001) ^ (data & 0x0001))
	crc = (crc >> 1) ^ 0xa001;
      else  crc >>= 1;
    }
  return crc;
}
