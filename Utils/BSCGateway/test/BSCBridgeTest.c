#include <termios.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>

int main () {
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
  ch = 0x37;
  ret = write(fd,&ch,1);
  ret = read (fd,&ch,1);
  assert (ch == 0x37);
  ch = 0x40;
  ret = write(fd,&ch,1);
  ch = 0x40;
  ret = write(fd,&ch,1);
  ch = 0x40;
  ret = write(fd,&ch,1);
  ch = 0x40;
  ret = write(fd,&ch,1);
  ch = 0x2d;
  ret = write(fd,&ch,1);
  ret = read (fd,&ch,1);
  assert (ch == 0x40);
  ret = read (fd,&ch,1);
  assert (ch == 0x40);
  ret = read (fd,&ch,1);
  assert (ch == 0x40);
  ret = read (fd,&ch,1);
  assert (ch == 0x40);
  ret = read (fd,&ch,1);
  assert (ch == 0x2D);
  ch = 0x2D;
  ret = write(fd,&ch,1);
  ret = read (fd,&ch,1);
  assert (ch == 0x2D);

}
