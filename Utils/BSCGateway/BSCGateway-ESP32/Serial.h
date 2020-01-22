#include <termios.h>
#define SERIAL_5N1 CS5  
#define SERIAL_6N1 CS6
#define SERIAL_5N2 CS5 | CSTOPB
#define SERIAL_6N2 CS6 | CSTOPB
#define SERIAL_7N1 CS7 
#define SERIAL_8N1 CS8
#define SERIAL_7N2 CS7 | CSTOPB
#define SERIAL_8N2 CS8 | CSTOPB
#define SERIAL_5E1 CS5 | PARENB
#define SERIAL_6E1 CS6 | PARENB
#define SERIAL_7E1 CS7 | PARENB
#define SERIAL_8E1 CS8 | PARENB
#define SERIAL_5E2 CS5 | CSTOPB | PARENB
#define SERIAL_6E2 CS6 | CSTOPB | PARENB
#define SERIAL_7E2 CS7 | CSTOPB | PARENB
#define SERIAL_8E2 CS8 | CSTOPB | PARENB
#define SERIAL_5O1 CS5 | PARENB | PARODD
#define SERIAL_6O1 CS6 | PARENB | PARODD
#define SERIAL_7O1 CS7 | PARENB | PARODD
#define SERIAL_8O1 CS8 | PARENB | PARODD
#define SERIAL_5O2 CS5 | PARENB | PARODD | CSTOPB
#define SERIAL_6O2 CS6 | PARENB | PARODD | CSTOPB
#define SERIAL_7O2 CS7 | PARENB | PARODD | CSTOPB
#define SERIAL_8O2 CS8 | PARENB | PARODD | CSTOPB

class Serial {
  speed_t translateSpeed(int);
  char devStr[256];
  int  fd;
 public:
  Serial(const char *);
  int available ();
  int read ();
  int write(char);
  int write(char *);
  int write(unsigned char *, int);
  void begin (int, int);
};

