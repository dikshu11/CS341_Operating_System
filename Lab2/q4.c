/* 
Write a C program to generate 3 child processes 
from the same parent process. Once a process gets generated 
it ask the user for maximum wait time and 
it waits for that specified duration and then dies. 
Parent process checks for the status of all the child processes, 
if all child processes are dead then parent also dies. 
You are also supposed to display the lifetime of each and every 
process along with its process id. 
*/


#include <stdio.h>
#include <unistd.h>


void fork1(){
	int child_status;
	if(fork() == 0){
		int wait_time;
		printf("Child ID :%d ", getpid());
		printf("ID Parent of child: %d\n", getppid());
		printf("Enter wait time for process %d\n", getpid());
		scanf("%d", &wait_time);
		printf("Waiting for time:%d ..................\n", wait_time);
		sleep(wait_time);
		printf("Finished waiting..................\n\n");
		exit(0);
	}
	else{
		wait(&child_status);
	}
}

int main()
{

	printf("Creating first child for process %d\n\n", getpid());
	fork1();
	printf("Creating second child for process %d\n\n", getpid());
	fork1();
	printf("Creating third child for process %d\n\n", getpid());
	fork1();
	return 0;
}
