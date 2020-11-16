/*
gcc -g -o Q2_1 Q2_1.c -lpthread -lm
./Q2_1


Method -1 :
Assigning equal work to each thread + sieve(Asked from TA) + Lock on Base 

*/


#include <stdio.h>
#include <math.h>
#include <pthread.h>  
#include <stdlib.h>
#define MAX_N 100000
#define MAX_THREADS 10

int nthreads, n, prime[MAX_N+1], nextbase, sum = 2;  
pthread_mutex_t nextbaselock = PTHREAD_MUTEX_INITIALIZER;
pthread_t id[MAX_THREADS];

// "crosses out" all odd multiples of k
void crossout(int k)
{  int i;
   for (i = 3; i*k <= n; i += 2)  {
      prime[i*k] = 0;
   }
}

// each thread runs this routine
void* worker(void * arg)  
{  
   int lim,base,work = 0; 
   lim = n;
   do  {
      pthread_mutex_lock(&nextbaselock);
      base = nextbase;
      nextbase += 2;
      pthread_mutex_unlock(&nextbaselock);
      if (base <= lim)  {
         if (prime[base])  {
            crossout(base);
            work++;  
            sum+=base;
         }
      }
      else return NULL; 
   } while (1);
}

int main(int argc, char **argv){  
   int primes_sum, i, work;
   n = 10000;
   nthreads = 4;
   for (i = 3; i <= n; i++)  {
      if (i%2 == 0) prime[i] = 0;
      else prime[i] = 1;
   }
   nextbase = 3;
   for (i = 0; i < nthreads; i++) {
      pthread_create(&id[i],NULL,&worker,NULL);
   }
   

   for (i = 0; i < nthreads; i++)  {
      pthread_join(id[i],NULL);
   }
   
   
   printf("The sum of primes found was %d \n", sum);
}
