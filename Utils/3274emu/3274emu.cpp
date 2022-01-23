/* 
 *  A simple TN3270 to BSC ovr TCP hercules style gateway
 *  by Mattis Lind
 *
 *  TCP proxy skeleton by Martin Broadhurst (www.martinbroadhurst.com)
 *  Usage: tcpproxy local_host local_port remote_host remote_port
 */

/*
  Compile using c++ 3274emu.cpp ../BSCGateway/BSCBridge/MessageFSM.cpp ../BSCGateway/BSCBridge/crc-16.cpp   -DHERCULES -DDEBUG  -o 3274emu

 Run: ./3274emu 127.0.01 37051 127.0.0.1 32701 3274emu2.log

 */

 
#include <stdio.h>
#include <stdarg.h>
#include <string.h> /* memset() */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <signal.h>
#include <sys/time.h>
#include "../BSCGateway/BSCBridge/MessageFSM.h"

 
#define BACKLOG  10      /* Passed to listen() */
#define BUF_SIZE 4096    /* Buffer for  transfers */

int client;
int server;
FILE * logfile;


void printLog (const char * format, ...) {
  struct timeval t;
  gettimeofday(&t, NULL);
  va_list(args);
  fprintf(logfile, "%lu.%06lu: ",t.tv_sec, t.tv_usec );
  va_start(args, format);
  vfprintf(logfile, format, args);
  fflush (logfile);
}


int state;
unsigned char code;
bool doTerminalTypeDone;
bool doBinaryDone;
bool doEORDone;
bool willBinaryDone;
bool willEORDone;


void clearTelnetOptions() {
  doTerminalTypeDone =false;
  doBinaryDone =false;
  doEORDone = false;
  willBinaryDone = false;
  willEORDone = false;
} 

bool testTelnetOptionsDone() {
  if (doTerminalTypeDone && doBinaryDone && doEORDone && willBinaryDone && willEORDone) {
    return true;
  }
  return false;
}

#define BINARY 0x00
#define TERMTYPE 0x18
#define EOR 0x19

#define SE 240
#define NOP 241
#define DATA_MARK 242
#define BREAK 243
#define INTERRUPT_PROCESS 244
#define ABORT_OUTPUT 246
#define ARE_YOU_THERE 247
#define ERASE_CHAR 247
#define ERASELINE 248
#define GOAHEAD 249
#define SB   250
#define WILL 251
#define WONT 252
#define DO   253
#define DONT 254
#define IAC 255


int sock = 0;

void txData (unsigned char);
void receivedMessage(unsigned char, unsigned char *);
void enterHuntState();

class MessageFSM messageFSM(txData, receivedMessage, enterHuntState, true);

void txData (unsigned char data) {
  int ret = write( server , &data, 1); 
  printLog("Sent %02X got back ret=%d\n", data, ret);
}

int ack;


unsigned int writeTextToClient(unsigned char * msg, int length) {
  unsigned char buf[BUF_SIZE];
  size_t bytes_written;
  unsigned int disconnected = 0;
  int i;
  printLog("Writing Text To client length=%d\n", length);
  // We need to remove the  0x27 / ESC that is prepended to the actual data stream.
  // Then copy in the data from he msg.
  memcpy(buf, msg+1, length-1);
  buf[length-1] = IAC;
  buf[length] = 0xef; // End Of Record
  bytes_written = write (client, buf, length+1);
  printLog("Buffer to write:");
  //for (i=0;i<length+1;i++) {
  //  printLog("%02X ", 0xff & buf[i]);
  //}
  //printLog("\n");
  printLog("bytes_written=%lu to client socket.\n", bytes_written);
  if (bytes_written == -1) {
    disconnected = 1;
  }  
  return disconnected;
}

unsigned char sendBuffer[BUF_SIZE];
int bufferLength=2;
int dataToSend = 0;
int firstThingToDoCnt=0;

void receivedMessage (unsigned char msgType, unsigned char * msg) {
  MSG * m;
  m = (MSG *) msg;
  unsigned char aid[0];
  printLog("msgType = %d\n", msgType);
  switch (msgType) {
  case POLL_MESSAGE:
    printLog("POLL CU=%02X DV=%02X\n",((MSG *) msg)->enqData.CU, ((MSG *) (msg))->enqData.DV);
    messageFSM.setTextMode(true);
    ack=1;
    if (((MSG *) msg)->enqData.CU == 0x40) {
    switch (((MSG *) msg)->enqData.DV) {
      case 0x40:
        if (dataToSend==1) {
	  messageFSM.sendTextMessage(bufferLength, sendBuffer, false);
	  dataToSend=0;
  	  bufferLength=2;
        } else {
	  messageFSM.sendEOT();
        }
        break;
      default:
        messageFSM.sendEOT();
        break;
      }
    } else {
      messageFSM.sendACK0();
      ack=1;
    }
    break;
  case EOT_MESSAGE:
    printLog("Got EOT\n");
    messageFSM.setTextMode(false);
    break;
  case ENQ_MESSAGE:
    printLog("Got ENQ\n");
    if (((ack-1)&1)==1) messageFSM.sendACK1();
    else messageFSM.sendACK0();
    messageFSM.sendACK0();
    break;
  case NAK_MESSAGE:
    printLog("Got NAK\n");
    break;
  case ACK0_MESSAGE:
    printLog("Got ACK0\n");
    messageFSM.sendEOT();
    break;
  case ACK1_MESSAGE:
    printLog("Got ACK1\n");
    messageFSM.sendEOT();
    break;
  case WACK_MESSAGE:
    printLog("Got WACK\n");
    break;
  case RVI_MESSAGE:
    printLog("Got RVI\n");
    break;
  case STATUS_MESSAGE:
    printLog("Got STATUS\n");
    break;
  case TEXT_MESSAGE:
    printLog("Got TEXT\n");
    printLog("Got crcOK = %d\n", m->textData.crcOk);
    if ((ack&1)==1) {
      printLog("Sending ACK1\n");
      messageFSM.sendACK1();
    }
    else {
      printLog("Sending ACK0\n");
      messageFSM.sendACK0();
    }
    ack++;
    writeTextToClient(m->textData.msg, m->textData.length);
    break;
  case TEST_MESSAGE:
    printLog("Got TEST\n");
    break;
  case ERROR_MESSAGE:
    printLog("Got ERROR\n");
    break;
  default:
    break;
  }
}

void enterHuntState () {
}


void process3270Data(unsigned char ch) {
  int i;
  if (testTelnetOptionsDone()) {
    // process TN3270 data!
    sendBuffer[bufferLength++] = ch;
    printLog("Stored ch=%02x into buffer. Now bufferLength=%d buffer is=", 0xff&ch, bufferLength);
    for (i=0;i<bufferLength;i++) printLog("%02x ", 0xff & sendBuffer[i]);
    printLog("\n");
  } else {
    // We are not ready for procssing TN3270 data yet. No point in forwarding data
    printLog("Not yet negotaited options done\n");
  }
  
}

unsigned int sendTelnetSubnegotationParams (int socket, const unsigned char * paramString, int length) {
  size_t bytes_written;
  unsigned int disconnected = 0;
  unsigned char sb[] = {0xFF, 0xFA};
  unsigned char sbEnd[] = {0xFF, 0xF0};
  bytes_written = write(socket, sb, 2);
  bytes_written = write(socket, paramString, length);
  bytes_written = write(socket, sbEnd, 2);
  if (bytes_written == -1) {
    disconnected = 1;
  }  
  return disconnected;
}


#define STATE_NORMAL 0
#define STATE_IAC_RECEIVED 1
#define STATE_PROCESS_OPTION 2
#define STATE_SUBPARAM_TYPE 3
#define STATE_SUBPARAM_OPCODE 4

const char *  printStateName (int state) {
  switch (state) {
  case STATE_NORMAL:
    return "STATE_NORMAL";
  case STATE_IAC_RECEIVED:
    return "STATE_IAC_RECEIVED";
  case STATE_PROCESS_OPTION:
    return "STATE_PROCESS_OPTION";
  case STATE_SUBPARAM_TYPE:
    return "STATE_SUBPARAM_TYPE";
  case STATE_SUBPARAM_OPCODE:
    return "STATE_SUBPARAM_OPCODE";
  default:
    return "STATE_UNKNOWN";
  }
} 

unsigned char subParamsBuf [BUF_SIZE];
int subParamPtr = 0; 

void storeSubParam (unsigned char ch) {
  printLog("storing %c at ptr=%d\n", ch, subParamPtr);
  subParamsBuf[subParamPtr++] = ch;
}

void endOfSubParam () {
  subParamsBuf[subParamPtr++] = 0;
}

unsigned int  processBSCDataFromHercules(int server, int client) {
  int i;
  unsigned char buf[BUF_SIZE];
  unsigned int disconnected = 0;
  size_t bytes_read, bytes_written;
  bytes_read = read(server, buf,BUF_SIZE);
  if (bytes_read == 0) {
    disconnected = 1; 
  } else {
    for (i=0; i<bytes_read; i++) {
      printLog("read %02x : %c from BSC line\n", buf[i] & 0xff, buf[i] & 0xff);
      messageFSM.rxData(buf[i]);
      while (messageFSM.isTxIdle() != true) {
	messageFSM.txPoll();
      }
    }
  }
  return disconnected;
}


bool subState;

unsigned int processDataFromTerminal (int client) {
  unsigned char buf[BUF_SIZE];
  const unsigned char terminalTypeRequest [] = {0x18, 0x01};
  int i;
  unsigned int disconnected = 0; 
  size_t bytes_read, bytes_written;
  bytes_read = read(client, buf,BUF_SIZE);
  if (bytes_read == 0) {
    disconnected = 1;
  } else {
    for (i=0; i<bytes_read; i++) {
      printLog("read %02x : %c from terminal in state=%s substate=%s\n", buf[i] & 0xff, buf[i] & 0xff, printStateName(state), subState?"TRUE":"FALSE");
      switch (state) {
      case STATE_NORMAL:
	if (buf[i] == IAC) {
	  printLog("IAC received\n");
	  state = STATE_IAC_RECEIVED;
	} else {
	  // Normal character - do normal processing according to 3270 Data stream
	  if (subState) {
	    storeSubParam(buf[i]);
	  } else {
	    process3270Data (buf[i]);
	  }
	}
	break;
      case STATE_IAC_RECEIVED:

	switch (buf[i]) {
	case 0xef:
	  // EOR
	  dataToSend=1;
	  state = STATE_NORMAL;
	  break;
	case IAC:
	  // We got another IAC which means that normal processing of a 255 byte should take place
	  state = STATE_NORMAL;
	  if (subState) {
	    storeSubParam(255);
	  } else {
	    process3270Data(255);
	  }
	  break;
	case DONT:
	case DO:
	case WONT:
	case WILL:
	  state = STATE_PROCESS_OPTION;
	  code = buf[i];
	  printLog("received DONT, DO, WONT or WILL: %02x\n", code);
	  break;
	case SB:
	  printLog("Received SB\n");
	  state = STATE_SUBPARAM_TYPE;
	  break;
	case SE:
	  if (subState) {
	    printLog("Received SE\n");
	    state = STATE_NORMAL;
	    endOfSubParam();
	    doTerminalTypeDone = true;
	    printLog("Terminal param received: %s\n", subParamsBuf);
	    //write(client, peer1_5, sizeof (peer1_5));
	    //write(client, peer1_6, sizeof (peer1_6));
	    subState = false;
	  } else {
	    state = STATE_NORMAL;
	  }
	  break;
	default:
	  state = STATE_NORMAL;
	  break;
	}
	break;
      case STATE_SUBPARAM_TYPE:
	printLog("Received SUVPARAM TYPE = %02x\n", buf[i]);
	state = STATE_SUBPARAM_OPCODE;
	break;
      case STATE_SUBPARAM_OPCODE:
	printLog("Received SUBPARAM OPCODE = %02x\n", buf[i]);
	state = STATE_NORMAL;
	subState = true;
	break;
      case STATE_PROCESS_OPTION:
	state = STATE_NORMAL;
	switch (buf[i]) {
	case TERMTYPE:
	  printLog("Received TERMTYPE\n");
	  if (code == WILL) {
	    sendTelnetSubnegotationParams(client, terminalTypeRequest, 2);	    
	  }
	  break;
	case EOR:
	  printLog("Received EOR\n");
	  if (code == WILL) {
	    willEORDone = true;
	  } else if (code == DO) {
	    doEORDone = true;
	  }
	  break;
	case BINARY: 
	  printLog("Recieved BINARY\n");
	  if (code == WILL) {
	    willBinaryDone = true;
	  } else if (code == DO) {
	    doBinaryDone = true;
	  }
	  break;
	}
	break;	  
      }
    }
  }
  return disconnected;
}

unsigned int sendTelnetDo(int socket, unsigned char option) {
  unsigned int disconnected = 0;
  unsigned char buf[] = {0xFF, 0xFD, 0x00};
  size_t bytes_written;
  buf[2] = option;
  // Write Telnet negotation to client
  bytes_written = write(socket, buf, 3); 
  if (bytes_written == -1) {
    disconnected = 1;
  }  
  return disconnected;
}

unsigned int sendTelnetWill(int socket, unsigned char option) {
  unsigned int disconnected = 0;
  unsigned char buf[] = {0xFF, 0xFB, 0x00};
  size_t bytes_written;
  buf[2] = option;
  // Write Telnet negotation to client
  bytes_written = write(socket, buf, 3); 
  if (bytes_written == -1) {
    disconnected = 1;
  }  
  return disconnected;
}

unsigned int sendTelnetDont(int socket, unsigned char option) {
  unsigned int disconnected = 0;
  unsigned char buf[] = {0xFF, 0xFE, 0x00};
  size_t bytes_written;
  buf[2] = option;
  // Write Telnet negotation to client
  bytes_written = write(socket, buf, 3); 
  if (bytes_written == -1) {
    disconnected = 1;
  }  
  return disconnected;
}

unsigned int sendTelnetWont(int socket, unsigned char option) {
  unsigned int disconnected = 0;
  unsigned char buf[] = {0xFF, 0xFC, 0x00};
  size_t bytes_written;
  buf[2] = option;
  // Write Telnet negotation to client
  bytes_written = write(socket, buf, 3); 
  if (bytes_written == -1) {
    disconnected = 1;
  }  
  return disconnected;
}


void handle(int client, const char *remote_host, const char *remote_port)
{
  struct addrinfo hints, *res;
  unsigned int disconnected = 0;
  fd_set set;
  unsigned int max_sock;


  /* Get the address info */
  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  if (getaddrinfo(remote_host, remote_port, &hints, &res) != 0) {
    perror("getaddrinfo");
    close(client);
    return;
  }
 
  /* Create the socket */
  server = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if (server == -1) {
    perror("socket");
    close(client);
    return;
  }
 
  /* Connect to the host */
  
  if (connect(server, res->ai_addr, res->ai_addrlen) == -1) {
    perror("connect");
    close(client);
    return;
  }
  

  if (client > server) {
    max_sock = client;
  }
  else {
    max_sock = server;
  }
  clearTelnetOptions();
  sendTelnetWill(client, 0x00);
  sendTelnetDo(client, 0x00);
  sendTelnetWill(client, 0x19);
  sendTelnetDo(client, 0x19);
  sendTelnetDo(client, 0x18);

  /* Main transfer loop */
  while (!disconnected) {
    struct timeval t;
    t.tv_sec = 0;
    t.tv_usec = 1000;
    FD_ZERO(&set);
    FD_SET(client, &set);
    FD_SET(server, &set);
    if (select(max_sock + 1, &set, NULL, NULL, &t) == -1) {
      perror("select");
      break;
    }
    if (FD_ISSET(client, &set)) {
      // Here is where we take care of input from the TN3270 terminal client.
      disconnected = processDataFromTerminal(client);
    }
    if (FD_ISSET(server, &set)) {
      disconnected = processBSCDataFromHercules(server, client);
    }
    messageFSM.txPoll();
  }
  close(server);
  close(client);
}
 
int main(int argc, char **argv)
{
  int sock;
  struct addrinfo hints, *res;
  int reuseaddr = 1; /* True */
  const char *local_host, *local_port, *remote_host, *remote_port;
  /* Get the local and remote hosts and ports from the command line */
  sendBuffer[0]=0x40;
  sendBuffer[1]=0x40;
 
  if (argc < 5) {
    fprintf(stderr, "Usage: tcpproxy local_host local_port remote_host remote_port\n");
    return 1;
  }
  local_host = argv[1];
  local_port = argv[2];
  remote_host = argv[3];
  remote_port = argv[4];
  
  if (argc==6) {
    // logfile
    logfile = fopen(argv[5], "a");
    if (logfile == NULL) {
      fprintf(stderr, "Failed to open log file.\n");
      exit(1);
    }
  } else {
    logfile = stderr;
  }

  /* Get the address info */
  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  if (getaddrinfo(local_host, local_port, &hints, &res) != 0) {
    perror("getaddrinfo");
    return 1;
  }
 
  /* Create the socket */
  sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if (sock == -1) {
    perror("socket");
    freeaddrinfo(res);
    return 1;
  }
 
  /* Enable the socket to reuse the address */
  if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(int)) == -1) {
    perror("setsockopt");
    freeaddrinfo(res);
    return 1;
  }
 
  /* Bind to the address */
  if (bind(sock, res->ai_addr, res->ai_addrlen) == -1) {
    perror("bind");
    freeaddrinfo(res);
    return 1;
  }
 
  /* Listen */
  if (listen(sock, BACKLOG) == -1) {
    perror("listen");
    freeaddrinfo(res);
    return 1;
  }
 
  freeaddrinfo(res);
 
  /* Ignore broken pipe signal */
  signal(SIGPIPE, SIG_IGN);
  
  /* Main loop */
  while (1) {
    socklen_t size = sizeof(struct sockaddr_in);
    struct sockaddr_in their_addr;
    int newsock = accept(sock, (struct sockaddr*)&their_addr, &size);
    client = newsock;
    if (newsock == -1) {
      perror("accept");
    }
    else {
      printLog("Got a connection from %s on port %d\n",
	     inet_ntoa(their_addr.sin_addr), htons(their_addr.sin_port));
      handle(newsock, remote_host, remote_port);
    }
  }
 
  close(sock);
 
  return 0;
}
