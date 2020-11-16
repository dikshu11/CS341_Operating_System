
/*
 Write a program in C to create a child process using 
fork system call and convert it zombie process. 
Show that the child process become zombie 
process. 

*/

// Child becomes Zombie as parent is sleeping 
// when child process exits. 
#include <stdlib.h> 
#include <sys/types.h> 
#include <unistd.h> 
int main() 
{ 
    // Fork returns process id 
    // in parent process 
    pid_t child_pid = fork(); 
    
    if (child_pid > 0){
        printf("Parent ID :%d\n", getpid());
        sleep(50);
    }  
    else{
        printf("Child ID :%d\n", getpid());
        exit(0); 
    }        
  
    return 0; 
} 
