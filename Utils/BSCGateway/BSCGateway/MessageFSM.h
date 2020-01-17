

#include "ebcdic.h"

class MessageFSM {
  private:
    uint8_t messageBuffer [300];
    const uint8_t eotBuffer [] = {4, SYN, SYN, EOT, PAD};
    const uint8_t enqBuffer [] = {5, 0x0, 0x0, 0x0, 0x0, ENQ, PAD};
    const uint8_t ack0Buffer [] = {4, SYN, SYN, DLE, 0xb7};
     
  public:
    MessageFSM(void (*)(unsigned char), void (*)(unsigned char));
    rxData ();
    sendEOT();
    sendENQ(uint8_t CU, uint8_t DV);
    sendSOHMessage(uint16_t header, uint8_t * msg);
    sendSTXMessage(uint8_t * msg);
    sendACK0();
    sendACK1();
    sendWACK();
    sendRVI();
    sendNAK();
};
