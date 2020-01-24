#ifdef DEBUG
#include "../test/types.h"
#else
#include "libmaple/libmaple_types.h"
#endif

#include <stdlib.h>
#include "ebcdic.h"
// Message types
#define EOT_MESSAGE 0
#define ENQ_MESSAGE 1
#define ACK_MESSAGE 2
#define NAK_MESSAGE 3
#define ACK0_MESSAGE 4
#define ACK1_MESSAGE 5
#define WACK_MESSAGE 6
#define RVI_MESSAGE 7
#define STATUS_MESSAGE 8
#define TEXT_MESSAGE 9
#define TEST_MESSAGE 10
#define ERROR_MESSAGE 11


union msg {
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
};

typedef union msg MSG; 

class MessageFSM {
  private:
    uint8_t msgBuffer [300];
    int msgBufferCnt;
    int rxState;
    int byteCounter;
    bool thereIsMoreComing;
    int length;
    void (* txDataCb)(unsigned char);
    void (* enterHuntStateCb)();
    void (* receivedMessageCb)(unsigned char, unsigned char *);
  public:
    MessageFSM(void (*)(unsigned char), void (*)(unsigned char, unsigned char *), void (*)());
    void rxData (uint8_t data);
    void sendEOT();
    void sendENQ(uint8_t CU, uint8_t DV);
    void sendStatusMessage(uint8_t CU, uint8_t DV,  uint8_t status, uint8_t sense);
    void sendTestRequestMessage(int messageLength, uint8_t * msg, bool thereIsMoreComing);
    void sendTextMessage(int messageLength, uint8_t * msg, bool thereIsMoreComing);
    void sendACK0();
    void sendACK1();
    void sendWACK();
    void sendRVI();
    void sendNAK();
};
