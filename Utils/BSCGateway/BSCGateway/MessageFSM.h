#ifdef DEBUG
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;
typedef uint32_t uint32;
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

class MessageFSM {
  private:
    uint8_t msgBuffer [300];
    int msgBufferCnt;
    int rxState;
    int byteCounter;
    void (* txDataCb)(unsigned char);
    void (* enterHuntStateCb)();
    void (* receivedMessageCb)(unsigned char, unsigned char *);
  public:
    MessageFSM(void (*)(unsigned char), void (*)(unsigned char, unsigned char *), void (*)());
    void rxData (uint8_t data);
    void sendEOT();
    void sendENQ(uint8_t CU, uint8_t DV);
    void sendSOHMessage(uint16_t header, uint8_t * msg);
    void sendSTXMessage(uint8_t * msg);
    void sendACK0();
    void sendACK1();
    void sendWACK();
    void sendRVI();
    void sendNAK();
};
