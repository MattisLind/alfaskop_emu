#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include "../BSCGateway/BSCGateway-STM32/MessageFSM.h"

/*
  Compile using c++ herculesConnect.cpp ../BSCGateway/BSCGateway-STM32/MessageFSM.cpp ../BSCGateway/BSCGateway-STM32/crc-16.c   -DHERCULES -DDEBUG  -o herculesConnect

 */

int sock = 0;

void txData (unsigned char);
void receivedMessage(unsigned char, unsigned char *);
void enterHuntState();

class MessageFSM messageFSM(txData, receivedMessage, enterHuntState);

void txData (unsigned char data) {
  int ret = write( sock , &data, 1); 
  printf ("Sent %02X got back ret=%d\n", data, ret);
}


void receivedMessage (unsigned char msgType, unsigned char * msg) {
  MSG * m;
  m = (MSG *) msg;
  printf ("msgType = %d\n", msgType);
  switch (msgType) {
  case ENQ_MESSAGE:
    printf ("CU=%02X DV=%02X\n",msg[0],msg[2]);
    switch (msg[2]) {
    case 0x40:
      messageFSM.sendEOT();
      break;
    case 0xc1:
      messageFSM.sendStatusMessage(0x40,0xc1,0xc2,0x40);
      break;
    case 0xc2:
      messageFSM.sendStatusMessage(0x40,0xc2,0xc4,0x40);
      break;
    case 0xc3:
      messageFSM.sendStatusMessage(0x40,0xc3,0xc8,0x40);
      break;
    case 0xc4:
      messageFSM.sendStatusMessage(0x40,0xc4,0x40,0x50);
      break;
    case 0xc5:
      messageFSM.sendStatusMessage(0x40,0xc5,0x40,0x60);
      break;
    case 0xc6:
      messageFSM.sendStatusMessage(0x40,0xc6,0x40,0xc1);
      break;
    case 0xc7:
      messageFSM.sendStatusMessage(0x40,0xc7,0xc2,0x40);
      break;
    default:
      break;
    }
    break;
  default:
    break;
  }
}

void enterHuntState () {
}

   
int main(int argc, char const *argv[]) 
{ 
  int ret, run=1; 
  struct sockaddr_in serv_addr; 
  char ch;
  
  if (argc!= 3) {
    fprintf(stderr, "Too few arguments: Usage: herculesConnect <ip-address> <port>\n");
    return -1;
  }
 
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
      printf("\n Socket creation error \n"); 
      return -1; 
    } 
   
  serv_addr.sin_family = AF_INET; 
  serv_addr.sin_port = htons(atoi(argv[2])); 
       
  // Convert IPv4 and IPv6 addresses from text to binary form 
  if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)  
    { 
      printf("\nInvalid address/ Address not supported \n"); 
      return -1; 
    } 
   
  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
      printf("\nConnection Failed \n"); 
      return -1; 
    } 
  do {
  ret = read( sock , &ch, 1); 
  messageFSM.rxData(ch);
  } while (run);
} 
