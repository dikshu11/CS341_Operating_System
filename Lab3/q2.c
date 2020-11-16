/*
Create a child process and make it orphan process.
What is the significance 
of the orphan process. 
*/

// Parent process finishes execution while the 
// child process is running. The child process 
// becomes orphan. 
#include<stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
  
int main() 
{ 
    int pid = fork(); 
  
    if (pid > 0){
        printf("Parent ID :%d\n", getpid());
        // return 0;
    } 
    else if (pid == 0) 
    { 
        printf("Child ID :%d\n", getpid());
        sleep(30); 
    } 
  
    return 0; 
} 