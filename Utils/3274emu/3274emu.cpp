/* 
 *  A simple TCP proxy
 *  by Martin Broadhurst (www.martinbroadhurst.com)
 *  Usage: tcpproxy local_host local_port remote_host remote_port
 */
 
#include <stdio.h>
#include <string.h> /* memset() */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <signal.h>
 
#define BACKLOG  10      /* Passed to listen() */
#define BUF_SIZE 4096    /* Buffer for  transfers */

unsigned int transfer(int from, int to)
{
  char buf[BUF_SIZE]
;  unsigned int disconnected = 0;
  size_t bytes_read, bytes_written;
  bytes_read = read(from, buf, BUF_SIZE);
  if (bytes_read == 0) {
    disconnected = 1;
  }
  else {
    bytes_written = write(to, buf, bytes_read);
    if (bytes_written == -1) {
      disconnected = 1;
    }
  }
  return disconnected;
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



void process3270Data(unsigned char ch) {
  if (testTelnetOptionsDone()) {
    // process TN3270 data!
  } else {
    // We are not ready for procssing TN3270 data yet. No point in forwarding data
    printf("Not yet negotaited options done\n");
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

unsigned char subParamsBuf [BUF_SIZE];
int subParamPtr = 0; 

void storeSubParam (unsigned char ch) {
  subParamsBuf[subParamPtr++] = ch;
}

void endOfSubParam () {
  subParamsBuf[subParamPtr++] = 0;
}

unsigned int  processBSCDataFromHercules(int server, int client) {
  unsigned int disconnected = 0;
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
      switch (state) {
      case STATE_NORMAL:
	if (buf[i] == IAC) {
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
	  break;
	case SB:
	  state = STATE_NORMAL;
	  subState = true;
	  break;
	case SE:
	  state = STATE_NORMAL;
	  endOfSubParam();
	  printf ("Terminal param received: %s\n", subParamsBuf);
	  subState = false;
	  break;
	}
      case STATE_PROCESS_OPTION:
	switch (buf[i]) {
	case TERMTYPE:
	  if (code == WILL) {
	    sendTelnetSubnegotationParams(client, terminalTypeRequest, 2);
	    doTerminalTypeDone = true;
	  }
	  break;
	case EOR:
	  if (code == WILL) {
	    willEORDone = true;
	  } else if (code == DO) {
	    doEORDone = true;
	  }
	case BINARY: 
	  if (code == WILL) {
	    willBinaryDone = true;
	  } else if (code == DO) {
	    doBinaryDone = true;
	  }
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
  char buf[] = {0xFF, 0xFB, 0x00};
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
  char buf[] = {0xFF, 0xFE, 0x00};
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
  char buf[] = {0xFF, 0xFC, 0x00};
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
  int server = -1;
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
    FD_ZERO(&set);
    FD_SET(client, &set);
    FD_SET(server, &set);
    if (select(max_sock + 1, &set, NULL, NULL, NULL) == -1) {
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
  if (argc < 5) {
    fprintf(stderr, "Usage: tcpproxy local_host local_port remote_host remote_port\n");
    return 1;
  }
  local_host = argv[1];
  local_port = argv[2];
  remote_host = argv[3];
  remote_port = argv[4];
 
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
 
    if (newsock == -1) {
      perror("accept");
    }
    else {
      printf("Got a connection from %s on port %d\n",
	     inet_ntoa(their_addr.sin_addr), htons(their_addr.sin_port));
      handle(newsock, remote_host, remote_port);
    }
  }
 
  close(sock);
 
  return 0;
}
