

#include "ebcdic.h"

Class MessageFSM {
  private:
    messageBuffer []
  public:
    MessageFSM();
    rxData ();
    sendEOT();
    sendPOLL();
    sendWrite();
    sendRead();
};
