/* CpSc 852 Hw 3 Q 3: Master program module */

#include <stdio.h>
#include <stdlib.h>


/* GLOBALS */
char binaryFileNameBuffer[32];
/*-------------------------------------------------------*/

/* PROGRAM */
/*-------------------------------------------------------*/
int main(int argc, char** argv) {

  int dataSize=0;
  int fileID=0;
  int i=0;
  int rc = 0;  //0 no error, -1 on error
  FILE *binaryFile;

  char *bFile = binaryFileNameBuffer;

  
  /* Make sure the poor user has a clue. */
  if (argc <3 ) 
  {
      printf("usage: ./createDataFiles size fileID\n");
      rc = 1;
  }
  
  if (rc == 0) {

    dataSize = atoi(argv[1]);
    fileID = atoi(argv[2]);
    sprintf(bFile,"DataFile%d.dat",fileID);
  
    binaryFile = fopen(bFile, "w+");

    unsigned char  myByte = 0x00;
    for (i=0;i<dataSize;i++) {

       fwrite(&myByte,sizeof(unsigned char),1,binaryFile);

    }

    fclose(binaryFile);
  
  }
  exit(rc);
}



