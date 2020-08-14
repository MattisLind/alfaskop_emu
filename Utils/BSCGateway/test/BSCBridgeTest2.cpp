/*
< SELECT 6040

16:57:23 HHCCA300D 0604:Writing 1 byte in socket : 60
16:57:23 HHCCA300D 0604:Writing 1 byte in socket : 60
16:57:23 HHCCA300D 0604:Writing 1 byte in socket : 40
16:57:23 HHCCA300D 0604:Writing 1 byte in socket : 40
16:57:23 HHCCA300D 0604:Writing 1 byte in socket : 2D
> ACK0
16:57:23 HHCCA300D 0604:RECV : 0000: 1070
< TEXT
0227F1C1 11C1501D C8C8D4E5 E2F0F140
D3D6C7D6 D540C9D5 40D7D9D6 C7D9C5E2
E240C1E3 40F0F97A F5F77AF2 F340D6D5
40C1E4C7 E4E2E340 F76B40F2 F0F2F01D
4011C260 1DC8404D E3E2E4F0 F0F0F0F9
5D40C8D4 E5E2F0F1 404061C9 D2D1C5C6
E3F0F161 E260F6F2 F261F0F0 7AF0F07A
F0F04BF1 F661F0F0 7AF0F17A F2F86140
40404040 40404061 1D4011C3 F01DC840
4DE3E2E4 F0F0F0F0 F95D40C8 D4E5E2F0
F1404061 C9D2D1C5 C6E3F0F1 61E260F6
F2F261F0 F07AF0F0 7AF0F04B F1F661F0
F07AF0F1 7AF2F861 40404040 40404040
611D4011 C5401DC8 D3D6C7C7 C9D5C740
D6
D540E3D6 40E3E2D6 40C1E340 F0F97AF5
F77AF2F3 40E4E2C9 D5C740C9 D2D1C1C3
C3D5E31D 4011C650 1DC8D3D6 C7C7C9D5
C740D6D5 40E4E2C9 D5C740D7 D9C9E5C1
E3C540D3 D6C7D6D5 40D7D9D6 C3C5C4E4
D9C51D40 11C76013 03
> ACK1

< EOT
*/

#include <termios.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>



void sendEOT (int fd) {
  unsigned char ch = 0x37;
  int ret;
  ret = write(fd,&ch,1);
}

void receiveEOT (int fd) {
  unsigned char ch;
  int ret;
  ret = read (fd,&ch,1);
  printf ("Rx %02X\n", ch);
  assert (ret == 1);
  assert (ch == 0x37);
}



void sendSelect (int fd) {
  int ret;
  unsigned char ch = 0x60;
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0x60;
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
  assert (ret == 1);
}

void receiveSelect(int fd) {
  int ret;
  unsigned char ch;
  ret = read (fd,&ch,1);
  printf ("Rx %02X\n", ch);
  assert (ret == 1);
  assert (ch == 0x60);
  ret = read (fd,&ch,1);
  printf ("Rx %02X\n", ch);
  assert (ret == 1);
  assert (ch == 0x60);
  ret = read (fd,&ch,1);
  printf ("Rx %02X\n", ch);
  assert (ret == 1);
  assert (ch == 0x40);
  ret = read (fd,&ch,1);
  printf ("Rx %02X\n", ch);
  assert (ret == 1);
  assert (ch == 0x40);
  ret = read (fd,&ch,1);
  printf ("Rx %02X\n", ch);
  assert (ret == 1);
  assert (ch == 0x2D);
}



void sendText (int fd, unsigned char * buffer, int length) {
  int ret;

  ret = write(fd,buffer,length);
  assert (ret == length);
  
}

void receiveText (int fd, unsigned char * buffer, int length) {
  int ret;
  unsigned char ch;
  int l = length;
  unsigned char testbuffer [1024];
  unsigned char * bufp = testbuffer;
  while (l > 0) {
    printf ("Trying to read %d bytes from serial port.\n", l);
    ret = read (fd,bufp,length);
    printf ("Read returned %d.\n", ret);
    for (int i=0; i<ret; i++) {
      printf ("Rx %02X\n", bufp[i]);
    }
    l-=ret;
    bufp+=ret;
  }
  assert (0 == l);
  for (int i=0; i<length; i++) {
    printf ("Comparing Rx %02X with actual: %02X\n", testbuffer[i], buffer[i]); 
    assert(buffer[i] == testbuffer[i]);  // STX
  }


  
}


void sendACK0 (int fd) {
  unsigned char ch = 0x10;
  int ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0x70;
  ret = write(fd,&ch,1);
  assert (ret == 1);
}

void receiveACK0 (int fd) {
  unsigned char ch;
  int ret;
  ret = read (fd,&ch,1);
  printf ("Rx %02X\n", ch);
  assert (ret == 1);
  assert (ch == 0x10);
  ret = read (fd,&ch,1);
  printf ("Rx %02X\n", ch);
  assert (ret == 1);
  assert (ch == 0x70);

} 

void sendACK1 (int fd) {
  unsigned char ch = 0x10;
  int ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0x61;
  ret = write(fd,&ch,1);
  assert (ret == 1);
}

void receiveACK1 (int fd) {
  unsigned char ch;
  int ret;
  ret = read (fd,&ch,1);
  printf ("Rx %02X\n", ch);
  assert (ret == 1);
  assert (ch == 0x10);
  ret = read (fd,&ch,1);
  printf ("Rx %02X\n", ch);
  assert (ret == 1);
  assert (ch == 0x61);
} 


int openSerial (const char * devStr) {
  int ret;
  int fd;
  struct termios options;
  unsigned char ch;
  int flags;
  /* open the port */
  fprintf(stderr, "devStr=%s\n", devStr);
  fd = open(devStr, O_RDWR | O_NOCTTY | O_NDELAY);
  fprintf(stderr, "open fd=%d", fd);
  flags = fcntl(fd, F_GETFL, 0);
  fprintf(stderr, "fcntl flags =%08X\n", flags);
  ret = fcntl(fd, F_SETFL, flags & ~O_NDELAY);
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
  options.c_cc[VMIN]  = 1;
  options.c_cc[VTIME] = 5;
  
  /* set the options */
  ret=tcsetattr(fd, TCSANOW, &options);
  fprintf(stderr, "tcsetattr ret=%d\n", ret);
  sleep(2); //required to make flush work, for some reason
  tcflush(fd,TCIOFLUSH);
  return fd;
}

unsigned char buffer [] = {
  0x02, 0x27, 0xF1, 0xC1, 0x11, 0xC1, 0x50, 0x1D, 0xC8, 0xC8, 0xD4, 0xE5, 0xE2, 0xF0, 0xF1, 0x40,
  0xD3, 0xD6, 0xC7, 0xD6, 0xD5, 0x40, 0xC9, 0xD5, 0x40, 0xD7, 0xD9, 0xD6, 0xC7, 0xD9, 0xC5, 0xE2,
  0xE2, 0x40, 0xC1, 0xE3, 0x40, 0xF0, 0xF9, 0x7A, 0xF5, 0xF7, 0x7A, 0xF2, 0xF3, 0x40, 0xD6, 0xD5,
  0x40, 0xC1, 0xE4, 0xC7, 0xE4, 0xE2, 0xE3, 0x40, 0xF7, 0x6B, 0x40, 0xF2, 0xF0, 0xF2, 0xF0, 0x1D,
  0x40, 0x11, 0xC2, 0x60, 0x1D, 0xC8, 0x40, 0x4D, 0xE3, 0xE2, 0xE4, 0xF0, 0xF0, 0xF0, 0xF0, 0xF9,
  0x5D, 0x40, 0xC8, 0xD4, 0xE5, 0xE2, 0xF0, 0xF1, 0x40, 0x40, 0x61, 0xC9, 0xD2, 0xD1, 0xC5, 0xC6,
  0xE3, 0xF0, 0xF1, 0x61, 0xE2, 0x60, 0xF6, 0xF2, 0xF2, 0x61, 0xF0, 0xF0, 0x7A, 0xF0, 0xF0, 0x7A,
  0xF0, 0xF0, 0x4B, 0xF1, 0xF6, 0x61, 0xF0, 0xF0, 0x7A, 0xF0, 0xF1, 0x7A, 0xF2, 0xF8, 0x61, 0x40,
  0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x61, 0x1D, 0x40, 0x11, 0xC3, 0xF0, 0x1D, 0xC8, 0x40,
  0x4D, 0xE3, 0xE2, 0xE4, 0xF0, 0xF0, 0xF0, 0xF0, 0xF9, 0x5D, 0x40, 0xC8, 0xD4, 0xE5, 0xE2, 0xF0,
  0xF1, 0x40, 0x40, 0x61, 0xC9, 0xD2, 0xD1, 0xC5, 0xC6, 0xE3, 0xF0, 0xF1, 0x61, 0xE2, 0x60, 0xF6,
  0xF2, 0xF2, 0x61, 0xF0, 0xF0, 0x7A, 0xF0, 0xF0, 0x7A, 0xF0, 0xF0, 0x4B, 0xF1, 0xF6, 0x61, 0xF0,
  0xF0, 0x7A, 0xF0, 0xF1, 0x7A, 0xF2, 0xF8, 0x61, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
  0x61, 0x1D, 0x40, 0x11, 0xC5, 0x40, 0x1D, 0xC8, 0xD3, 0xD6, 0xC7, 0xC7, 0xC9, 0xD5, 0xC7, 0x40,
  0xD6, 0xD5, 0x40, 0xE3, 0xD6, 0x40, 0xE3, 0xE2, 0xD6, 0x40, 0xC1, 0xE3, 0x40, 0xF0, 0xF9, 0x7A,
  0xF5, 0xF7, 0x7A, 0xF2, 0xF3, 0x40, 0xE4, 0xE2, 0xC9, 0xD5, 0xC7, 0x40, 0xC9, 0xD2, 0xD1, 0xC1,
  0xC3, 0xC3, 0xD5, 0xE3, 0x1D, 0x40, 0x11, 0xC6, 0x50, 0x1D, 0xC8, 0xD3, 0xD6, 0xC7, 0xC7, 0xC9,
  0xD5, 0xC7, 0x40, 0xD6, 0xD5, 0x40, 0xE4, 0xE2, 0xC9, 0xD5, 0xC7, 0x40, 0xD7, 0xD9, 0xC9, 0xE5,
  0xC1, 0xE3, 0xC5, 0x40, 0xD3, 0xD6, 0xC7, 0xD6, 0xD5, 0x40, 0xD7, 0xD9, 0xD6, 0xC3, 0xC5, 0xC4,
  0xE4, 0xD9, 0xC5, 0x1D, 0x40, 0x11, 0xC7, 0x60, 0x13, 0x03
};


int main () {
  int fd1, fd2;
  fd1 = openSerial("/dev/ttyACM0");
  fd2 = openSerial("/dev/ttyACM1");
  sendEOT(fd1);
  receiveEOT(fd2);
  sendSelect(fd1);
  receiveSelect(fd2);
  sendACK0(fd2);
  receiveACK0(fd1);
  sendText(fd1, buffer, sizeof (buffer));
  receiveText(fd2, buffer, sizeof (buffer));
  sendACK1(fd2);
  receiveACK1(fd1);
  sendEOT(fd1);
  receiveEOT(fd2);
}
