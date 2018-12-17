#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_rng.h>

gsl_rng * r;

int main(int argc, char* argv[]) 
{   
  float PointsInQuarterCircle = 0.0;
  int chance, opt;
  extern char *optarg;
  extern int optind, opterr, optopt;
  int NumberOfTrials = atoi(argv[1]);
  int i;
  
  
  struct timeval milliSec;
  gettimeofday(&milliSec, NULL);
  gsl_rng_env_setup();
  
  extern unsigned long int gsl_rng_default_seed;
  gsl_rng_default_seed = (milliSec.tv_usec);
  
  const gsl_rng_type * T;
  T = gsl_rng_default;
  r = gsl_rng_alloc(T);
  // set to have number between 0-1
  
  for (i=0;i<NumberOfTrials;i++){
  double x = gsl_rng_uniform(r);
  double y = gsl_rng_uniform(r);
  double X = x*x;
  double Y = y*y;
  double XY = X+Y;
  if (XY <= 1.000){
  PointsInQuarterCircle++;
  }
  
  
  }
  float MyPi = ((PointsInQuarterCircle / NumberOfTrials) * 4 );

  float Pi = 3.141592654;
  float deviation = (MyPi - Pi);
  float error = ((deviation / Pi)*100);
  printf("Pi = %f Dev = %f Error = %f \n",MyPi, deviation, error);
  
  
  exit(0);
  }