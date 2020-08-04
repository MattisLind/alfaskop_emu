#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <netdb.h>

 #include <sys/types.h>
 #include <sys/stat.h>
 #include <fcntl.h>

extern int h_errno;
FILE * logfile = stderr;

speed_t translateSpeed (int speed) {
  switch (speed) {
    case 50: return B50;
    case 75: return B75;
    case 110: return B110;
    case 134: return B134;
    case 150: return B150;
    case 300: return B300;
    case 600: return B600;
    case 1200: return B1200;
    case 2400: return B2400;
    case 4800: return B4800;
    case 9600: return B9600;
    case 19200: return B19200;
    case 38400: return B38400;
    case 57600: return B57600;
    case 115200: return B115200;
    case 230400: return B230400;
#ifndef MACOS
    case 460800: return B460800;
    case 500000: return B500000;
    case 576000: return B576000;
    case 921600: return B921600;
    case 1152000: return B1152000;
    case 2000000: return B2000000;
    case 2500000: return B2500000;
    case 3000000: return B3000000;
    case 3500000: return B3500000;
    case 4000000: return B4000000;
#endif
    default: return B9600;
  }

}



int openSerial (int fd, int baudrate) {
  int ret;
  struct termios options;
  unsigned char ch;

  ret = fcntl(fd, F_SETFL, 0);
  if (ret == -1) {
    perror("Error:");
    abort();
  }


/* get the current options */
  ret = tcgetattr(fd, &options);
  
  options.c_cflag &= ~CSIZE;
  options.c_cflag &= ~CSTOPB;
  options.c_cflag &= ~PARENB;
  options.c_cflag &= ~PARODD;
  
  cfsetispeed(&options, translateSpeed(baudrate));
  cfsetospeed(&options, translateSpeed(baudrate));
  
  /* set raw input, 1 second timeout */
  options.c_cflag     |= (CLOCAL | CREAD);
  options.c_lflag     &= ~(ICANON | ECHO | ECHOE | ISIG);
  options.c_oflag     &= ~OPOST;
  options.c_cc[VMIN]  = 1;
  options.c_cc[VTIME] = 1;
  
  /* set the options */
  ret=tcsetattr(fd, TCSANOW, &options);
}



int main (int argc, char **argv) {
  int c;
  int remotePort=0;
  struct hostent * remoteHost;
  struct sockaddr_in serveraddr;
  int serialFd=-1;
  int serialBaudrate=0;
  FILE * logfile;
  int hostSocket;
  while (1) {
    static struct option long_options[] = {
      {"host",    required_argument, 0, 'h'},
      {"port",    required_argument, 0, 'p'},
      {"device",  required_argument, 0, 'd'},
      {"baudrate",required_argument, 0, 'b'},
      {"logfile", required_argument, 0, 'l'},
      {0, 0, 0, 0}
    };
    /* getopt_long stores the option index here. */
    int option_index = 0;
    
    c = getopt_long (argc, argv, "h:p:d:b:l:", long_options, &option_index);
    
    /* Detect the end of the options. */
    if (c == -1)
      break;
    
    switch (c) {
    case 0:
      /* If this option set a flag, do nothing else now. */
      if (long_options[option_index].flag != 0)
	break;
      printf ("option %s", long_options[option_index].name);
      if (optarg)
	printf (" with arg %s", optarg);
      printf ("\n");
      break;
      
    case 'h':  // hostname
      remoteHost = gethostbyname(optarg);
      break;
      
    case 'p':
      remotePort = atoi(optarg);
      if (remotePort == 0) {
	fprintf(stderr, "Invalid port: %s.\n", optarg);
	abort();
      }
      break;
      
    case 'd':
      serialFd = open (optarg,O_RDWR | O_NOCTTY | O_NDELAY);
      if (serialFd == -1) {
	perror("Failed to open serial port.");
	abort();
      }
      break;
      
    case 'b':
      serialBaudrate = atoi(optarg);
      if (serialBaudrate == 0) {
	fprintf(stderr, "Baudrate invalid: %s. \n", optarg);
	abort();
      }
      break;
      
    case 'l':
      logfile = fopen (optarg, "w+");
      if (logfile == NULL) {
	fprintf(stderr, "Invalid logfile: %s.\n",optarg);
	abort();
      }
      break;
      
    case '?':
      break;
      
    default:
      abort ();
    }
  }
  if (serialBaudrate == 0) {
    fprintf(stderr, "No baudrate specified.\n");
    abort();
  }
  if (hostPort == 0) {
    fprintf(stderr, "No host port specified.\n");
    abort();
  }
  if (serialFd==-1) {
    fprintf(stderr, "No serial device specified.\n");
    abort();
  }

  openSerial(serialFd);
  hostSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (conn_fd == -1) {
    perror("socket");
    return -1;
  }
  /* build the server's Internet address */
  bzero((char *) &serveraddr, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  bcopy((char *)remoteHost->h_addr, 
	(char *)&serveraddr.sin_addr.s_addr, remoteHost->h_length);
  serveraddr.sin_port = htons(remotePort);

  if (connect(sockfd, &serveraddr, sizeof(serveraddr)) < 0) 
      error("ERROR connecting");


  while (1) {

    build_fd_sets(&server, &read_fds, &write_fds, &except_fds);
        
    int activity = select(maxfd + 1, &read_fds, &write_fds, &except_fds, NULL);
    
    switch (activity) {
    case -1:
      perror("select()");
      shutdown_properly(EXIT_FAILURE);
      
    case 0:
      // you should never get here
      printf("select() returns 0.\n");
      shutdown_properly(EXIT_FAILURE);
      
    default:
      /* All fd_set's should be checked. */
      if (FD_ISSET(STDIN_FILENO, &read_fds)) {
	if (handle_read_from_stdin(&server, client_name) != 0)
	  shutdown_properly(EXIT_FAILURE);
      }
      
      if (FD_ISSET(STDIN_FILENO, &except_fds)) {
	printf("except_fds for stdin.\n");
	shutdown_properly(EXIT_FAILURE);
      }
      
      if (FD_ISSET(server.socket, &read_fds)) {
	if (receive_from_peer(&server, &handle_received_message) != 0)
	  shutdown_properly(EXIT_FAILURE);
      }
      
      if (FD_ISSET(server.socket, &write_fds)) {
	if (send_to_peer(&server) != 0)
	  shutdown_properly(EXIT_FAILURE);
      }
      
      if (FD_ISSET(server.socket, &except_fds)) {
	printf("except_fds for server.\n");
	shutdown_properly(EXIT_FAILURE);
      }
    }
    
  exit (0);
}
