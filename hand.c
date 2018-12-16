#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h> 
#include <string.h>
#include <gsl/gsl_rng.h>

gsl_rng * r;
  
int main(int argc, char** argv) 
{ 

  int chance, opt;
  extern char *optarg;
  extern int optind, opterr, optopt;
  
  // get time in milliseconds
  struct timeval milliSec;
  gettimeofday(&milliSec, NULL);
  gsl_rng_env_setup();
  
  extern unsigned long int gsl_rng_default_seed;
  gsl_rng_default_seed = (milliSec.tv_usec);
  
  const gsl_rng_type * T;
  T = gsl_rng_default;
  r = gsl_rng_alloc(T);
  // set to have number between 0-1
  double uniform = gsl_rng_uniform(r);


  opt = getopt(argc, argv, "");
  if (opt == -1){
      chance = atoi(argv[optind]);
  }
  else{
      fprintf(stderr, "usuage is ./hand <successPercentage> ");
     }
    
    bool Successful = ((uniform*100) < chance);
 
    // if successful, print success, else print failure
   
    if (Successful==true){

      exit(10);
    }
    else{

      exit(0);
    }
   
   return 0; 
} 