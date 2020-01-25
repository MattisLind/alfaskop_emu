
#ifndef _COMMANDSERIALIZER_H_
#define _COMMANDSERIALIZER_H_
#include "types.h"
#include "Serial.h"

#define HAND_REQ 0
#define SET_HAND 1
#define REP_HAND 2
#define EOT_MSG 3
#define ENQ_MSG 4
#define STAT_MSG 5
#define TEST_MSG 6
#define TEXT_MSG 7
#define ACK0_MSG 8
#define ACK1_MSG 9
#define WACK_MSG 10
#define RVI_MSG 11
#define NAK_MSG 12

  

union msgData {
  struct ENQData {
    uint8_t CU;
    uint8_t DV;
  } enqData;
  struct TestData {
    int length;
    uint8_t * msg;
    bool thereIsMoreComing;
  } testData;
  struct StatusData {
    uint8_t CU;
    uint8_t DV;
    uint8_t status;
    uint8_t sense;
  } statusData;
  struct TextData {
    int length;
    bool thereIsMoreComing;
    uint8_t * msg;
  } textData;
  struct ErrorData {
    int errorCode;
    char * errorText;
  } errorData;
  struct HandshakeData {
    int dtr;
    int cts;
    int rts;
  } handshakeData;
};

struct msg {
  int type;
  union msgData data;
};

typedef struct msg MSG;


class CommandSerializer {
  char messageBuffer [256];
  char command;
  int bufferPtr;
  int commandState;
  unsigned char hexdigit;
  char rtsVal;
  char ctsVal;
  char dtrVal;
  char handshakeLine;
  unsigned char AsciiHexToChar (char);
  class Serial & Serial;
  void (* processMessageCb) (MSG *);
  void handleHandshakeLines (int, int, int);
  public:
  CommandSerializer (class Serial & serial, void (* processMessage) (MSG *)) : Serial(serial), processMessageCb(processMessage), commandState(0)  {}
  void processCharacter (char);
  void doRequestHandshakeLineState();
  void doSetResetHandshakeLines(int, int, int);
  void doHandshakeLinesChanged(int, int, int);
  void doEOT();
  void doENQ(unsigned char, unsigned char);
  void doStatus();
  void doTestRequestMessage();
  void doTextMessage();
  void doACK0();
  void doACK1();
  void doWACK();
  void doRVI();
  void doNAK();
};


#endif
