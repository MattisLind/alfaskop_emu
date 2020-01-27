#include <stdio.h>

#define POLY 0xa001

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
    unsigned char buf[] = {0x40,0x40,0x40,0x70,0x03,0x26,0x88};
    //{0x01, 0x6c, 0xd9, 0x02, 0x40, 0x40, 0x40, 0x70, 0x03, 0x26, 0x88};

    crc = crc16(0x0000, buf, 7);
    printf("%04x\n", crc);
    return 0;
}
