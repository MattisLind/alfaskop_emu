#include <termios.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>


void testStatusMessage (int fd) {
  int ch, ret
  ch = 0x01;
  ret = write(fd,&ch,1);
  ch = 0x6C;
  ret = write(fd,&ch,1);
  ch = 0xD9;
  ret = write(fd,&ch,1);
  ch = 0x02;
  ret = write(fd,&ch,1);
  ch = 0x40;
  ret = write(fd,&ch,1);
  ch = 0x40;
  ret = write(fd,&ch,1);
  ch = 0xC2;
  ret = write(fd,&ch,1);
  ch = 0x40;
  ret = write(fd,&ch,1);
  ch = 0x03;
  ret = write(fd,&ch,1);
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert (ch == 0x01);
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert (ch == 0x6C);
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert (ch == 0xD9);
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert (ch == 0x02);
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert (ch == 0x40);
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert (ch == 0x40);
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert (ch == 0xC2);
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert (ch == 0x40);
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert (ch == 0x03);
}

void testEOT (int fd) {
  ch = 0x37;
  ret = write(fd,&ch,1);
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert (ch == 0x37);
}

void testPOLL (int fd) {
  ch = 0x40;
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0x40;
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0x40;
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0x40;
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0x2d;
  ret = write(fd,&ch,1);
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert (ch == 0x40);
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert (ch == 0x40);
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert (ch == 0x40);
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert (ch == 0x40);
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert (ch == 0x2D);
}

void testENQ (int fd) {
  ch = 0x2D;
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert (ch == 0x2D);
}

void testTextMessage (int fd) {
  ch = 0x02;  // STX
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0x27;  // ESC
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0xF1;  // 1
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0xC3;  // C
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0x11;  // VT
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0x40;  // SPACE
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0x40;  // SPACE
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0xC9;  // I
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0xD2;  // K
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0xD1;  // J
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0xF5;  // 5
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0xF4;  // 4
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0xF0;  // 0
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0xF1;  // 1
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0xF1;  // 1
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0xC9;  // I
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0x40;  // SPACE
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0xE3;  // T
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0xE2;  // S
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0xD6;  // O
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0x40;  // SPACE
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0xC9;  // I
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0xE2;  // S
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0x40;  // SPACE
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0xD5;  // N
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0xD6;  // O
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0xE3;  // T
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0x40;  // SPACE
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0xC1;  // A
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0xC3;  // C
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0xE3;  // T
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0xC9;  // I
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0xE5;  // V
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0xC5;  // E
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0x11;
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0x40;
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0x40;
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0x13;
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0x03;
  ret = write(fd,&ch,1);
  assert (ret == 1);
  
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert(ch == 0x02);  // STX
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert(ch == 0x27);  // ESC
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert(ch == 0xF1);  // 1
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert(ch == 0xC3);  // C
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert(ch == 0x11);  // 
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert(ch == 0x40);  // SPACE
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert(ch == 0x40);  // SPACE
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert(ch == 0xC9);  // I
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert(ch == 0xD2);  // K
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert(ch == 0xD1);  // J
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert(ch == 0xF5);  // 5
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert(ch == 0xF4);  // 4
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert(ch == 0xF0);  // 0
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert(ch == 0xF1);  // 1
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert(ch == 0xF1);  // 1
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert(ch == 0xC9);  // I
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert(ch == 0x40);  // SPACE
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert(ch == 0xE3);  // T
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert(ch == 0xE2);  // S
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert(ch == 0xD6);  // O
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert(ch == 0x40);  // SPACE
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert(ch == 0xC9);  // I
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert(ch == 0xE2);  // S
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert(ch == 0x40);  // SPACE
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert(ch == 0xD5);  // N
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert(ch == 0xD6);  // O
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert(ch == 0xE3);  // T
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert(ch == 0x40);  // SPACE
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert(ch == 0xC1);  // A
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert(ch == 0xC3);  // C
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert(ch == 0xE3);  // T
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert(ch == 0xC9);  // I
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert(ch == 0xE5);  // V
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert(ch == 0xC5);  // E
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert(ch == 0x11);  // 
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert(ch == 0x40);  // SPACE
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert(ch == 0x40);  // SPACE 
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert(ch == 0x13);
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert(ch == 0x03);  // ETX
}

void testNAK (int fd) {
  ch = 0x3D;
  ret = write(fd,&ch,1);
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert (ch == 0x3D);
} 

void testACK0 (int fd) {
  ch = 0x10;
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0x70;
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert (ch == 0x10);
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert (ch == 0x70);

} 
void testACK1 (int fd) {
  ch = 0x10;
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0x61;
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert (ch == 0x10);
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert (ch == 0x61);

} 
void testWACK (int fd) {
  ch = 0x10;
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0x6b;
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert (ch == 0x10);
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert (ch == 0x6b);

} 


int openSerial () {
  int ret;
  int fd;
  const char * devStr = "/dev/ttyUSB0";
  struct termios options;
  unsigned char ch;
  /* open the port */
  fprintf(stderr, "devStr=%s\n", devStr);
  fd = open(devStr, O_RDWR | O_NOCTTY | O_NDELAY);
  fprintf(stderr, "open fd=%d", fd);
  ret = fcntl(fd, F_SETFL, 0);
  if (ret == -1) {
    perror("Error:");
  }
  fprintf(stderr, "fcntl ret=%d",ret);



/* get the current options */
  ret = tcgetattr(fd, &options);
  fprintf(stderr, "tcgetattr ret=%d",ret);
  
  options.c_cflag &= ~CSIZE;
  options.c_cflag &= ~CSTOPB;
  options.c_cflag &= ~PARENB;
  options.c_cflag &= ~PARODD;
  //options.c_cflag |= config;
  
  cfsetispeed(&options, B2400);
  cfsetospeed(&options, B2400);
  
  /* set raw input, 1 second timeout */
  options.c_cflag     |= (CLOCAL | CREAD);
  options.c_lflag     &= ~(ICANON | ECHO | ECHOE | ISIG);
  options.c_oflag     &= ~OPOST;
  options.c_cc[VMIN]  = 0;
  options.c_cc[VTIME] = 255;
  
  /* set the options */
  ret=tcsetattr(fd, TCSANOW, &options);
  fprintf(stderr, "tcsetattr ret=%d\n", ret);
  return fd;
}

int main () {
  int fd;
  fd = openSerial();
  testEOT(fd);
  testStatusMessage(fd);
  testTextMessage(fd);
  testNAK(fd);
  testACK0(fd);
  testACK1(fd);
  testWACK(fd);
}
