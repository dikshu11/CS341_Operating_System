/*
 Write a program in C to show 
‘Parent process and child process run in parallel’ 
using a for loop. 
Also show Parent and Child id with their respective update. 


*/

#include <stdio.h>
#include <unistd.h>

int main(){
  int c = 0;
  printf("Starting process: c = 0\n");

  int process_id = fork();
  
  if(process_id == 0)
  {
    printf("child: pid=%d, ppid=%d\n", getpid(), getppid());
    for(int i=0; i<200; i++)
    {
      printf("child: pid=%d, c=%d\n", getpid(), ++c);
    }
  }
  else
  {
    printf("parent: pid=%d\n", getpid());
    for(int i=0; i<200; i++)
    {
      printf("parent: pid=%d, c=%d\n", getpid(), ++c);
    }
    wait(NULL);
  }
  printf("End of pid=%d\n", getpid());
  return 0;

}