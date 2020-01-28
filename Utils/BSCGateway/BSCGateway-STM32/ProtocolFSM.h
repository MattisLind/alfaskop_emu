#ifndef _POLLFSM_H_
#define _POLLFSM_H

#include "MessageFSM.h"


struct ProtocolMsg {
  short type;
  union protocolData {
    struct TestData {
      int length;
      uint8_t * msg;
    } test;
    struct StatusData {
      uint8_t CU;
      uint8_t DV;
      uint8_t status;
      uint8_t sense;
    } status;
    struct TextData {
      int length;
      uint8_t * msg;
    } textData;
    struct ErrorData {
      int errorCode;
      char * errorText;
    } error;
  } data;
};

typedef struct ProtocolMsg ProtocolMsg ;


#define PROTOCOL_TYPE_STATUS  0
#define PROTOCOL_TYPE_TEXT    1
#define PROTOCOL_TYPE_TEST    2
#define PROTOCOL_TYPE_ERROR   3

#define PROTOCOL_FSM_IDLE 0
#define PROTOCOL_FSM_WAIT_FOR_RTS 1
#define PROTOCOL_FSM_WAIT_FOR_MSG 2
#define PROTOCOL_FSM_WAIT_FOR_NOT_RTS 4

class ProtocolFSM {
  receiveBuffer [2048];
  void (*  receivedMessage ) ( ProtocolMsg * );
  class MessageFSM & messageFSM;
  int state;
  bool rtsIsSet();
  void cts (bool value);
 public:
 PollFSM(class MessageFSM & mFSM, void (* pRCB) (ProtocolMsg *) ) : messageFSM(mFSM), pollResponseCb(pRCB);
  void doPoll (unsigned short CU, unsigned short DV);
  void doWrite (unsigned short CU, unsigned short DV, unsigned char * data);
  void doRead (unsigned short CU, unsigned short DV, unsigned char * data);
  // Called when receiving a message. A callback in the MessageFSM class
  void rxMessage (unsigned char, unsigned char *);
  void workerPoll ();
};




#endif
