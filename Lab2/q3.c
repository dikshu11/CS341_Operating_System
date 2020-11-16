/*
Write a program in C that
will create seven child processes 
and report number of prime pid .
The child processes must be terminated 
in the following sequence:  4, 3, 6, 1, 7, 2, 5
*/ 

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<math.h>

int  isprime(int num){

	for(int i=2; i<num; i++){
		if(num%i == 0)
			return 0;
	}
	return 1;
}
int main()
{   
    int no_of_process=7,i,new_process, prime_cnt=0;
    int terminate_order[7] = {4,3,6,1,7,2,5};
	int p[no_of_process];

    for(i=0;i<no_of_process;i++){
        new_process=fork();
        if (new_process == 0) {
            // This is a child process. Just spin until killed.
            while(1){
            }
        }
        p[i] = new_process;
        if(isprime(new_process) == 1)
        	prime_cnt++;
        printf("process %d : %d\n", i+1, p[i]);
    }
    
    printf("Prime PID : %d\n", prime_cnt);
    for(i=0; i<no_of_process; i++){
        printf("%dth process %d killed\n", terminate_order[i], p[ terminate_order[i]-1 ]);
    	kill( p[ terminate_order[i]-1 ], SIGKILL);
    }

    return 0;
}