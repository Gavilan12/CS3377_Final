#include <signal.h> 
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h> 
#include <string.h>
#include <gsl/gsl_rng.h>
#include <sys/types.h>

gsl_rng * r;
void childHandler(int signal);void parentHandler(int signal);
pid_t pid;

int main(){
  struct timespec Time;
  Time.tv_nsec= 500000000;

  struct timeval milliSec;
  gettimeofday(&milliSec, NULL);
  gsl_rng_env_setup();
  
  extern unsigned long int gsl_rng_default_seed;
  gsl_rng_default_seed = (milliSec.tv_usec);
  
  const gsl_rng_type * T;
  T = gsl_rng_default;
  r = gsl_rng_alloc(T);
  
  pid= fork();
  if (pid==0){
  int signalNumber = 1;
  for(signalNumber; signalNumber < 32; signalNumber++){
  signal(signalNumber, childHandler);
  }
  for (;;){
  printf("Child is waiting\n");
  nanosleep(&Time, (struct timespec*)NULL);
  }
  }
  else{
  int signalNumber=1;
  for(signalNumber; signalNumber < 32; signalNumber++){
  signal(signalNumber, parentHandler);
  }
  gsl_rng_default_seed = (milliSec.tv_usec);
  sleep(1);
  unsigned long int N = 31;
  
  for (;;){
    unsigned long int randomSignal = gsl_rng_uniform_int(r,N);
    randomSignal++;
    printf("Parent sending signal %lu\n",randomSignal);
    kill(pid, randomSignal);
    nanosleep(&Time, (struct timespec*)NULL);
}
}
}








void childHandler(int signal)
{
  printf("Signal received by child %d\n", signal);
}

void parentHandler(int signal)
{
  printf("Parent recieved signal %d\n", signal);
  kill(pid,9);
  int waitStatus;
  wait(&waitStatus);
  printf("Parent will exit now\n"); 
  exit(0);
}

