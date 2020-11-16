#include <stdio.h>
#include <unistd.h>

int num;
void fork1(){
	int child_status;
	if(fork() == 0){
		num+=3;
		printf("Child ID :%d num: %d ", getpid(), num);
		printf("ID Parent of child: %d\n", getppid());
		// exit(0);
	}
	else{
		wait(&child_status);
		printf("Parent ID: %d num: %d\n\n", getpid(), num);
	}
}

int main()
{
	num = 0;
	printf("Creating first fork for process %d\n", getpid());
	fork1();
	printf("Creating second fork for process %d\n", getpid());
	fork1();
}

