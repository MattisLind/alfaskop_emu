
#include "libmaple/libmaple_types.h"
#include "ebcdic.h"

class MessageFSM {
  private:
    uint8_t msgBuffer [300];
    int msgBufferCnt;
    int rxState;
    int byteCounter;
    const uint8_t eotBuffer [5] = {4, SYN, SYN, EOT, PAD};
    const uint8_t enqBuffer [7] = {6, 0x0, 0x0, 0x0, 0x0, ENQ, PAD};
    const uint8_t ack0Buffer [5] = {4, SYN, SYN, DLE, 0xb7};
     
  public:
    MessageFSM(void (*)(unsigned char), void (*)(unsigned char));
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
