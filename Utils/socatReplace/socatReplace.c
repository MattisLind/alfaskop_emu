#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <netdb.h>

 #include <sys/types.h>
 #include <sys/stat.h>
 #include <fcntl.h>

extern int h_errno;

int main (int argc, char **argv) {
  int c;
  int remotePort;
  struct hostent * remoteHost;
  int serialFd;
  int serialBaudrate;
  FILE * logfile;
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
      break;
      
    case 'd':
      serialFd = open (optarg,O_RDWR | O_NOCTTY | O_NDELAY);
      break;
      
    case 'b':
      serialBaudrate = atoi(optarg);
      break;
      
    case 'l':
      logfile = fopen (optarg, "w+");
      if (logfile == NULL) {
	fprintf(stderr, "Invalid logfile: %s.\n",optarg);
      }
      break;
      
    case '?':
      break;
      
    default:
      abort ();
    }
  }  
  exit (0);
}
