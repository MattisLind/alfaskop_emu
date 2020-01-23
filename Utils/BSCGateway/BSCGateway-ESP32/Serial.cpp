#ifdef LINUX

#include "Serial.h"

Serial::Serial(const char * devStr) {
  devStr = Serial::devStr;
}

speed_t Serial::translateSpeed(int speed) {
  switch (speed) {
    case 50: return B50;
    case 75: return B75;
    case 110: return B110;
    case 134: return B134;
    case 150: return B150;
    case 300: return B300;
    case 600: return B600;
    case 1200: return B1200;
    case 2400: return B2400;
    case 4800: return B4800;
    case 9600: return B9600;
    case 19200: return B19200;
    case 38400: return B38400;
    case 57600: return B57600;
    case 115200: return B115200;
    case 230400: return B230400;
#ifndef MACOS
    case 460800: return B460800;
    case 500000: return B500000;
    case 576000: return B576000;
    case 921600: return B921600;
    case 1152000: return B1152000;
    case 2000000: return B2000000;
    case 2500000: return B2500000;
    case 3000000: return B3000000;
    case 3500000: return B3500000;
    case 4000000: return B4000000;
#endif
    default: return B9600;
  }

}

void Serial::begin(int speed, int config) {

  speed_t speedSetting = translateSpeed(speed);
  
	      
  struct termios options;

  /* open the port */
  fd = open(devStr, O_RDWR | O_NOCTTY | O_NDELAY);
  fcntl(fd, F_SETFL, 0);
  



/* get the current options */
  tcgetattr(fd, &options);

  
  options.c_cflag &= ~CSIZE;
  options.c_cflag &= ~CSTOPB;
  options.c_cflag &= ~PARENB;
  options.c_cflag &= ~PARODD;
  options.c_cflag |= config;
  
  cfsetispeed(&options, speedSetting);
  cfsetospeed(&options, speedSetting);
  
  /* set raw input, 1 second timeout */
  options.c_cflag     |= (CLOCAL | CREAD);
  options.c_lflag     &= ~(ICANON | ECHO | ECHOE | ISIG);
  options.c_oflag     &= ~OPOST;
  options.c_cc[VMIN]  = 0;
  options.c_cc[VTIME] = 10;
  
  /* set the options */
  tcsetattr(fd, TCSANOW, &options);
}

int Serial::available () {
  int ret;
  struct pollfd pollfd;
  pollfd.fd = fd;
  pollfd.events = POLLIN;
  ret = poll(&pollfd, 1 , 10);
  return ret; 
}

//extern "C" ssize_t read (int, void *, size_t);

int Serial::read () {
  char ch;
  if (::read (fd, &ch, 1) != 1) {
    return -1;
  }
  return (int) ch;
}
int Serial::write(char ch) {
  return ::write(fd, &ch, 1);
}
int Serial::write(char * str) {
  return ::write(fd, str, strlen(str));
}
int Serial::write(unsigned char * buf, int len) {
  return ::write(fd, buf, len);
}

#endif
