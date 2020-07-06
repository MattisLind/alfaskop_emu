#include <stdio.h>

#define POLY 0x8408

unsigned crc16(unsigned crc, unsigned char *buf, size_t len)
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

int main(void)
{
    unsigned crc;
    // actual message is 0x40, 0x93, 0x33, 0xef - if we invert the last two bytes the resulting sum will be zero 
    unsigned char buf1[] = {0x40,0x93, 0xCC, 0x10};
    unsigned char buf2[] = {0x02,0xC9, 0xcc, 0xF7};
    unsigned char buf3[] = {0xFD,0x36, 0x33, 0x08};
    //{0x01, 0x6c, 0xd9, 0x02, 0x40, 0x40, 0x40, 0x70, 0x03, 0x26, 0x88};

    crc = crc16(0xffff, buf1, 4);
    printf("%04x\n", crc);
    crc = crc16(0xffff, buf2, 4);
    printf("%04x\n", crc);
    crc = crc16(0xffff, buf3, 4);
    printf("%04x\n", crc);
    crc = crc16(0x0000, buf1, 4);
    printf("%04x\n", crc);
    crc = crc16(0x0000, buf2, 4);
    printf("%04x\n", crc);
    crc = crc16(0x0000, buf3, 4);
    printf("%04x\n", crc);
    return 0;
}
