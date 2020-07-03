#include <termios.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>


void testSNRM (int fd) {
  unsigned char ch = 0x40; // Address
  int ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0x93; // SNRM
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0xFF; // ESACPE
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ch = 0xEF; // EOR
  ret = write(fd,&ch,1);
  assert (ret == 1);
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert (ch == 0x40);  // Assert Address back
  ret = read (fd,&ch,1);
  assert (ret == 1);
  assert (ch == 0x93);  // Assert SNRM back
  ret = read (fd,&ch,1);
  assert (ret == 1);
  ret = read (fd,&ch,1); // Read Crc bytes but don't assert it
  assert (ret == 1);
  ret = read (fd,&ch,1); // CRC
  assert (ret == 1);
  assert (ch == 0x00);   // But the sum should be 0
  ret = read (fd,&ch,1);
  assert (ret == 1);     // Second byte sum
  assert (ch == 0x00);
  ret = read (fd,&ch,1);
  assert (ret == 1);     // ESACAPE
  assert (ch == 0xFF);
  ret = read (fd,&ch,1);
  assert (ret == 1);     // EOR
  assert (ch == 0xEF);
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
  sleep(2); //required to make flush work, for some reason
  tcflush(fd,TCIOFLUSH);
  fprintf(stderr, "tcsetattr ret=%d\n", ret);
  return fd;
}

int main () {
  int fd;
  fd = openSerial();
  testSNRM(fd);
}
