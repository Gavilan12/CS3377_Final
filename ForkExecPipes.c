#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char** argv)
{
  int pipeFD[2];
  int pid;
  int i;
  
  int file1Check = open(argv[1],O_RDONLY);
  if (file1Check < 0){
  printf("Unable to open file %s \n", argv[1]);
  return 1;
  }
  int file2Check = open(argv[2], O_WRONLY | O_APPEND);
  if (file2Check < 0){
  printf("Unable to open file %s \n", argv[2]);
  return 1;
  }
  pipe(pipeFD);
  pid = fork();
  if (pid==0){
  dup2(pipeFD[1],1);
  close(pipeFD[0]);
  execl("/bin/cat","cat","-b",argv[1], (char *)0 );
  }
  else{
  int waitForChild;
  wait(&waitForChild);
  i = WEXITSTATUS(waitForChild);
  
  int fileDes = open(argv[2], O_WRONLY);
  dup2(pipeFD[0],0);
  close(pipeFD[1]);
  
  size_t BufferSize = 1;
  char Ch;
  while(read(0, &Ch, BufferSize) > 0){
  printf("%c",Ch);
  write(fileDes,&Ch, BufferSize);
  }
  
  }

exit(0);
}

