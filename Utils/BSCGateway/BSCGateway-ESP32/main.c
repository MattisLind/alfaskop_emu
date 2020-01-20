#ifdef LINUX
// Implement wrapper from Arduino environment for
// Serial

class Serial {
  const char * quickMsg;
  int cnt;
  int            fd;
  void open (char * device)
 public:
  Serial();
  int available ();
  char read ();
  void write(char ch);
  void reset() { cnt = 0; }; 
} Serial ();


void Serial::open(char * devStr) {

  struct termios options;

  /* open the port */
  fd = open(devStr, O_RDWR | O_NOCTTY | O_NDELAY);
  fcntl(fd, F_SETFL, 0);
  
  /* get the current options */
  tcgetattr(fd, &options);
  
  /* set raw input, 1 second timeout */
  options.c_cflag     |= (CLOCAL | CREAD);
  options.c_lflag     &= ~(ICANON | ECHO | ECHOE | ISIG);
  options.c_oflag     &= ~OPOST;
  options.c_cc[VMIN]  = 0;
  options.c_cc[VTIME] = 10;
  
  /* set the options */
  tcsetattr(fd, TCSANOW, &options);
}
  


#include "BSCGateway-ESP32.ino"

main () {
  Serial Serial (deviceString);
  setup();
  do {
    loop();
  }
  while (1);
}


#endif
