/*
Write a program that computes the cube roots of the integers 
from 0 to 999 in a separate thread and 
returns an array of doubles containing the results. 
In the meantime the main thread should display a short message
“Computation under process. Please wait...”to the user 
and then display the results of the computation when they are ready.
For example :cbrt(0) = 0.000000
*/


//	 NOTE : When using math.h library functions we need to compile the code with -lm flag.
// 	because library which contains functions of math.h is not linked by default.

#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h> 		//	required for cbrt() function.


void * thread_function(void *param)
{
	int i;
	double *result = malloc(sizeof(double)*100);	// create array to store results.
	for(i=0; i < 100; i++){
		result[i] = cbrt((double)i);	//	compute the answer using cbrt() library function.
	}
	
	return (void *)result;	//	return the result.

}

int main(){
	pthread_t 	threadID;
	void 		*exit_status;
	double		*result;
	int 		i;
	
	pthread_create(&threadID,NULL,thread_function,NULL);
	pthread_join(threadID,&exit_status);
	
	printf("\n\nComputation under process. Please wait...\n\n");
	
	result = (double *) exit_status;
	
	for(i=0;i<100;i++){
		printf("\ncbrt(%d) = %lf",i,result[i]);
	}
	
	free(result);	
	
	printf("\n\n");
	return 0;
}
