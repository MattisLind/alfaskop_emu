
#ifndef _COMMANDSERIALIZER_H_
#define _COMMANDSERIALIZER_H_


class CommandSerializer {
  char messageBuffer [256];
  char command;
  int bufferPtr;
  int commandState=0;
  unsigned char hexdigit;
  char rtsVal;
  char ctsVal;
  char dtrVal;
  char handshakeLine;
  inline unsigned char AsciiHexToChar (char);
  class Serial & Serial;
  void (processMessage *) (MSG *);
  public:
  CommandSerializer (class Serial &, void (processMessage *) (MSG *));
  void processCharacter (char);
  void doRequestHandshakeLineState();
  void doSetResetHandshakeLines();
  void doHandshakeLinesChanged();
  void doEOT();
  void doENQ();
  void doStatus();
  void doTestRequestMessage();
  void doTextMessage();
  void doACK0();
  void doACK1();
  void doWACK();
  void doRVI();
  void doNAK();
}


#endif
