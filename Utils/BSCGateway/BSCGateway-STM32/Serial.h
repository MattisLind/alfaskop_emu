#ifndef _SERIAL_H_
#define _SERIAL_H_

#define DEC 0
#define HEX 1


class Serial {
  char buffer [1024];
  char * currentBufferPointer;
public:
  Serial ();
  int available ();
  void begin (int);
  void print(char * str);
  void print(char);
  void print(const char * str);
  void print(char, int);
  void print(short, int);
  void print(long, int);
  void print(int, int);
  void println();
  void println(char * str);
  void println(char ch);
  void println(const char * str);
  void write (char);
  int  read();
  void flush();
  void debugPrint();
};

#endif
