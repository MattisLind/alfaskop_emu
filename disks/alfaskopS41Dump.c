#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#pragma pack(1)

struct VOLLAB {
  char DTYPE;
  char DVOLNR[8];
  char DNAME[8];
  char DVERS[2];
  char DREVDT[10];
  char DUSER[20];
  char DFLAG;
  unsigned short DSTAT;
  unsigned short DVPTR;
  unsigned short DVSIZE;
  char DFDBOT[8];
  char DNAT[24];
  char DRPQ[10];
};


struct VTOC {
  char DSTYPE;
  char DSNAME[8];
  char DSAUTH;
  char DSPROT;
  char DSFBSZ;
  unsigned short DS1STA;
  char DSDOVH;
  char DSFUUS;
  unsigned short DSPADR;
  unsigned short DSSIZE;
  unsigned short DSBSIZ;
  unsigned short DSRSIZ;
  unsigned short DSFNUB;
  unsigned short DSLUSE;
  unsigned short DSENPT;
  unsigned short DSLPDT;
};

void trimTrailingSpaces (char * str) {
  printf ("%c", *str);
  while (*str != 0) {
    printf ("%c", *str);
     if (*str == 0x20) {
       *str=0;
       break;
     }
    str++;
    }
}

static int do_mkdir(const char *path, mode_t mode)
{
  struct stat     st;
  int             status = 0;

  if (stat(path, &st) != 0)
    {
      /* Directory does not exist. EEXIST for race condition */
      if (mkdir(path, mode) != 0 && errno != EEXIST)
	status = -1;
    }
  else if (!S_ISDIR(st.st_mode))
    {
      errno = ENOTDIR;
      status = -1;
    }

  return(status);
}

int calculateOffset(unsigned short address) {
  return ((address & 0xff) * 26 + ((address & 0xff00) >> 8)) * 128;
}

int fixByteOrder (unsigned int in) {
  return ((in >> 8) & 0xff)  | ((in << 8) & 0xff00);  
}


void printVtoc (unsigned char * buffer, int address, int size) 
{
  struct VTOC * vtoc_ptr;
  char dummy [256];
  int i;
  printf ("                            D I S P L A Y   V T O C               \n");
  printf ("UNUSED AREA %04d SECTORS    STARTS AT CUL %02X  SECTOR %02X  UNUSED FDE %02X\n", 0, 0, 0, 0);
  printf ("TYPE   NAME  AUTH FBSZ 1STA  CYL SEC SIZE  BSIZE RSIZE FNUB  LUSE  ENPT LDPT\n");
  for (i=0; i< size; i++) {
    // printf ("Offset : %d size : %d\n", calculateOffset(vollab_ptr->DVPTR), fixByteOrder(vollab_ptr->DVSIZE));
    vtoc_ptr = (struct VTOC * ) (buffer + address + 32*i);
    printf ("  %c ", vtoc_ptr->DSTYPE);

    strncpy(dummy, vtoc_ptr->DSNAME, sizeof( vtoc_ptr->DSNAME));
    dummy[sizeof( vtoc_ptr->DSNAME)]=0;
    printf (" %8s", dummy);

    printf (" %02X ", vtoc_ptr->DSAUTH);

    printf (" %02X ", vtoc_ptr->DSFBSZ);

    printf ("  %04X ", fixByteOrder(vtoc_ptr->DS1STA));

    printf (" %02X ", 0xff & vtoc_ptr->DSPADR);

    printf (" %02X ", 0xff & (vtoc_ptr->DSPADR>>8));

    printf (" %04X ", fixByteOrder(vtoc_ptr->DSSIZE));

    printf (" %04X ", fixByteOrder(vtoc_ptr->DSBSIZ));

    printf (" %04X ", fixByteOrder(vtoc_ptr->DSRSIZ));

    printf (" %04X ", fixByteOrder(vtoc_ptr->DSFNUB));

    printf (" %04X ", fixByteOrder(vtoc_ptr->DSLUSE));

    printf (" %04X ", fixByteOrder(vtoc_ptr->DSENPT));

    printf (" %04X\n", fixByteOrder(vtoc_ptr->DSLPDT));


    
  }

}


int main (int argc, char ** argv) {
  int i,j;
  FILE * in, * out;
  char dummy [256];
  char dir [256];
  char path[256];
  struct VOLLAB *  vollab_ptr;
  struct VTOC * vtoc_ptr, * vtoc_ptr2;
  unsigned char buffer [256256];
  if (argc!=2) exit(1);
  in = fopen (argv[1], "r");
  if (in==NULL) exit(2);
  fread(buffer, 1, 256256, in);
  vollab_ptr = (struct VOLLAB *) buffer;

  printf ("DTYPE: %c\n", vollab_ptr->DTYPE);
  strncpy(dummy, vollab_ptr->DVOLNR, sizeof( vollab_ptr->DVOLNR));
  dummy[sizeof( vollab_ptr->DVOLNR)]=0;
  printf ("DVOLNR: %s\n", dummy);
  strncpy(dummy, vollab_ptr->DNAME, sizeof( vollab_ptr->DNAME));
  dummy[sizeof( vollab_ptr->DNAME)]=0;
  printf ("DNAME: %s\n", dummy);
  strncpy(dummy, vollab_ptr->DVERS, sizeof( vollab_ptr->DVERS));
  dummy[sizeof( vollab_ptr->DVERS)]=0;
  printf ("DVERS: %s\n", dummy);

  strncpy(dummy, vollab_ptr->DREVDT, sizeof( vollab_ptr->DREVDT));
  dummy[sizeof( vollab_ptr->DREVDT)]=0;
  printf ("DREVDT: %s\n", dummy);

  strncpy(dummy, vollab_ptr->DUSER, sizeof( vollab_ptr->DUSER));
  dummy[sizeof( vollab_ptr->DUSER)]=0;
  printf ("DUSER: %s\n", dummy);

  printf ("DFLAG: %02X\n", vollab_ptr->DFLAG);

  printf ("DSTAT: %04X\n", vollab_ptr->DSTAT);

  printf ("DVPTR: %04X\n", vollab_ptr->DVPTR);

  printf ("DVSIZE: %04X\n", vollab_ptr->DVSIZE);

  strncpy(dummy, vollab_ptr->DFDBOT, sizeof( vollab_ptr->DFDBOT));
  dummy[sizeof( vollab_ptr->DFDBOT)]=0;
  printf ("DFDBOT: %s\n", dummy);

  strncpy(dummy, vollab_ptr->DNAT, sizeof( vollab_ptr->DNAT));
  dummy[sizeof( vollab_ptr->DNAT)]=0;
  printf ("DNAT: %s\n", dummy);

  strncpy(dummy, vollab_ptr->DRPQ, sizeof( vollab_ptr->DRPQ));
  dummy[sizeof( vollab_ptr->DRPQ)]=0;
  printf ("DRPQ: %s\n", dummy);

  // get VTOC 

  printVtoc (buffer, calculateOffset(vollab_ptr->DVPTR), fixByteOrder(vollab_ptr->DVSIZE));

  for (i=0; i< fixByteOrder(vollab_ptr->DVSIZE); i++) {

    vtoc_ptr = (struct VTOC * ) (buffer + calculateOffset(vollab_ptr->DVPTR) + fixByteOrder(vollab_ptr->DVSIZE)*i);
    if (vtoc_ptr->DSTYPE=='D') {
      strncpy(dummy, vtoc_ptr->DSNAME, sizeof( vtoc_ptr->DSNAME));
      dummy[sizeof( vtoc_ptr->DSNAME)]=0;
      trimTrailingSpaces(dummy);
      do_mkdir(dummy, 0775);
      strcpy(dir,dummy);
      strcat(dir,"/");
      printf ("Offset : %04X size : %04X\n", calculateOffset(vtoc_ptr->DSPADR), (vtoc_ptr->DSRSIZ >> 8) & 0xff);
      printVtoc (buffer, calculateOffset(vtoc_ptr->DSPADR), (vtoc_ptr->DSRSIZ >> 8) & 0x0FF);
      for (j=0; j< ((vtoc_ptr->DSRSIZ >> 8) & 0x00FF); j++) {
	vtoc_ptr2 = (struct VTOC * ) (buffer + calculateOffset(vtoc_ptr->DSPADR) + 32*j);
	printf ("Offset : %04X size : %04X\n", calculateOffset(vtoc_ptr2->DSPADR), (vtoc_ptr2->DSRSIZ >> 8) & 0xff);
	if ((vtoc_ptr2->DSTYPE=='F') || (vtoc_ptr2->DSTYPE=='A')) {
	  strncpy(dummy, vtoc_ptr2->DSNAME, sizeof( vtoc_ptr2->DSNAME));
	  dummy[sizeof( vtoc_ptr2->DSNAME)]=0;
	  trimTrailingSpaces(dummy);
	  strcat (dummy,".");
	  if (vtoc_ptr2->DSTYPE=='F') {
	    strcat (dummy,"F");
	  } else {
	    strcat (dummy,"A");
	  }  
	  strcpy(path, dir);
	  strcat(path, dummy);
	  out = fopen (path, "w");
	  fwrite (buffer+calculateOffset(vtoc_ptr2->DSPADR), 1, (fixByteOrder(vtoc_ptr2->DSSIZE)-1)*fixByteOrder(vtoc_ptr2->DSBSIZ)+fixByteOrder(vtoc_ptr2->DSLUSE), out);
	}

      }
    }
    if ((vtoc_ptr->DSTYPE=='F') || (vtoc_ptr->DSTYPE=='A')) {
       strncpy(dummy, vtoc_ptr->DSNAME, sizeof( vtoc_ptr->DSNAME));
       dummy[sizeof( vtoc_ptr->DSNAME)]=0;
       trimTrailingSpaces(dummy);
       strcat (dummy,".");
       if (vtoc_ptr->DSTYPE=='F') {
	 strcat (dummy,"F");
       } else {
	 strcat (dummy,"A");
	 }  
       out = fopen (dummy, "w");
       fwrite (buffer+calculateOffset(vtoc_ptr->DSPADR), 1, (fixByteOrder(vtoc_ptr->DSSIZE)-1)*fixByteOrder(vtoc_ptr->DSBSIZ)+fixByteOrder(vtoc_ptr->DSLUSE), out);
    }
  }
}
