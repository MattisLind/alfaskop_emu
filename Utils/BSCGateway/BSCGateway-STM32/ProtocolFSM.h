#ifndef _PROTOCOLFSM_H_
#define _PROTOCOLFSM_H_

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
#define PROTOCOL_FSM_WAIT_FOR_MSG 1
#define PROTOCOL_FSM_SENDACK 2
#define PROTOCOL_SEND_FSM_DATA 3
#define PROTOCOL_FSM_SEND_EOT 4

#define PROTOCOL_FSM_SUBSTATE_IDLE 0
#define PROTOCOL_FSM_SUBSTATE_WAIT_FOR_RTS 16
#define PROTOCOL_FSM_SUBSTATE_WAIT_FOR_NOT_RTS 32


#define PROTOCOL_MODE_POLL   64
#define PROTOCOL_MODE_WRITE  128
#define PROTOCOL_MODE_READ   192

class ProtocolFSM {
  unsigned char receiveBuffer [2048];
  class MessageFSM & messageFSM;
  int state;
  int subState;
  int cnt;
  int mode; // POLL, WRITE or READ
  unsigned char thereIsMoreComing;
  bool rtsIsSet();
  void cts (bool value);
  void ( * protocolResponseCb ) (ProtocolMsg *);
 public:
 ProtocolFSM(class MessageFSM & mFSM, void (* pRCB) (ProtocolMsg *) ) : messageFSM(mFSM), protocolResponseCb(pRCB), cnt(0) {}
  int sendPoll (unsigned short CU, unsigned short DV);
  int sendWrite (unsigned short CU, unsigned short DV, unsigned char * data);
  int sendRead (unsigned short CU, unsigned short DV, unsigned char * data);
  // Called when receiving a message. A callback in the MessageFSM class
  void receivedMessage( unsigned char, MSG *);
  void workerPoll ();
};




#endif
