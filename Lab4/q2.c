/*
Write a simple C program to creates 10 threads
(each thread increments the variable by one).
Define two variables,
global(shared among all threads)and 
local static and wait for all threads to complete its execution, 
then show the final value of each variable.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int global_var = 5;

void *my_thread(void *vargp)
{

    static int static_var = 0;
    int local_var = 6;
    ++static_var; ++global_var; ++local_var;
    pthread_t tid = pthread_self();
    printf("Thread ID: %lu, Static var: %d, Global var: %d, Local var: %d\n", tid, static_var, global_var, local_var);
    pthread_exit(NULL);		//terminating thread

}
int main(){

	pthread_t tid[10];
	int i;
	for(i=0;i<10;i++)
	{
		pthread_create(&tid[i],NULL,my_thread,NULL);
	}
	pthread_exit(NULL);	

	return 0;
}
