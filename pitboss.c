#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <string.h>

struct rollStat
{
  char statementTrials[45];
  int numOfTrials;
  char statementSuccess[45];
  float percentageSuccess;
  char statementFailure[45];
  float percentageFailure;

};


int main(int argc, char** argv)
{
  // setting up variables for get opt
  int chance, opt;
  extern char *optarg;
  extern int optind, opterr, optopt;
  int verbose=0;
  int openFile = 0;
  char *fileName;
  long int offset=0;
  struct rollStat stat;
  // loop for getopt to parse cmd line args
  while ((opt = getopt (argc, argv, "p:")) != -1)
    {
      switch (opt)
	{
	// percentage chance is found, record the percentage
	case 'p':
	  chance = atoi(optarg);
	  break;

	}
    }
    if (opt == -1){
    fileName = argv[optind];
    }
    
    offset = ((chance/10)-1) * sizeof(stat);
    // 156 is the byte size for the struct from dealer
   
  FILE *BinFile;
  BinFile = fopen(fileName,"rb");
  printf("\nReading results from %s \n", fileName);
  
  fseek( BinFile, offset, SEEK_SET );
  
  fread(&stat, sizeof(stat), 1, BinFile );
  printf("\nChecking results for -p = %d \n", chance);
  printf("\nFound %d trials.\n",stat.numOfTrials  ); 
  printf(stat.statementSuccess, stat.percentageSuccess );
  printf(stat.statementFailure, stat.percentageFailure );
  
  fclose(BinFile);
  
  
  
  
    exit(0);
}
