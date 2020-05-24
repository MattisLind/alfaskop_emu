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

bool telnetNegotiaton;
 
unsigned int transfer(int from, int to)
{
  char buf[BUF_SIZE];
  unsigned int disconnected = 0;
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
      if (telnetNegotation) {
	disconnected = processTelnetNegotation (client);
      } else {
	disconnected = process3270DataFromTerminal(client);
      }
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
