#ifndef _EBCDIC_H_
#define _EBCDIC_H_

#define NUL 0x00
#define SOH 0x01
#define STX 0x02
#define ETX 0x03
#define PF  0x04
#define HT  0x05
#define LC  0x06
#define DEL 0x07
#define RLF 0x09
#define SMM 0x0a
#define VT  0x0b
#define FF  0x0c
#define CR  0x0d
#define SO  0x0e
#define SI  0x0f
#define DLE 0x10
#define DC1 0x11
#define DC2 0x12
#define DC3 0x13
#define RES 0x14
#define NL  0x15
#define BS  0x16
#define IL  0x17
#define CAN 0x18
#define EM  0x19
#define CC  0x1a
#define IFS 0x1c
#define IGS 0x1d
#define IRS 0x1e
#define ITB 0x1f
#define DS  0x20
#define SOS 0x21
#define FS  0x22
#define BYP 0x24
#define LF  0x25
#define ETB 0x26
#define ESC 0x27
#define SM  0x2a
#define ENQ 0x2d
#define ACK 0x2e
#define BEL 0x2f
#define SYN 0x32
#define PN  0x34
#define RS  0x35
#define UC  0x36
#define EOT 0x37
#define DC4 0x3a
#define NAK 0x3d
#define SUB 0x3f
#define PAD 0xff

#define isLinkControlChar(ch) ((ch==STX) || (ch==ETX) || (ch==DLE) || (ch==ETB) || (ch==ENQ) || (ch==SYN) || (ch==ITB) || (ch==EOT) || (ch==NAK)) 

char ASCIItoEBCDIC(const unsigned char);
char EBCDICtoASCII(const unsigned char);


#endif 
