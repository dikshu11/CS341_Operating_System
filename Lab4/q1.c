
/*
Write a C program to create N (MAX_THREADS 50) threads specified
by user in the command line, each of which prints out a message
“I a m  groot ” and its own thread ID. To see how the execution of the threads interleaves, 
make the main thread sleep 1 second for every 5 threads it creates
*/

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <pthread.h> 
typedef void* address_t;

// A normal C function that is executed as a thread 
// when its name is specified in pthread_create() 
void *myThreadFun(address_t args) 
{  
    int iter = *(int* ) args;
	printf("Hello from groot %lu - I was created in iteration %d\n", pthread_self(), iter); 
	return NULL; 
} 

int main() 
{ 
    int n;
    printf("Enter number of threads:\n");
    scanf("%d", &n);

	pthread_t thread_id[n];
    int arg[n];

    for(int i=0; i<n; i++){
        if(i%5 == 0)
            sleep(1);
        arg[i] = i;
	    pthread_create(&thread_id[i], NULL, myThreadFun, (address_t) &arg[i] ); 
        printf("I am groot %lu. Created new groot(%lu) in iteration %d\n", pthread_self(), thread_id[i], i);
    } 

	exit(0); 
}
