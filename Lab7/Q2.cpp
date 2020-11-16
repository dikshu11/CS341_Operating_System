/*
Usage:  
g++ Q2.cpp -o Q2 -lpthread
./Q2

*/

#include<bits/stdc++.h>
#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
  
using namespace std;

#define MAX_N 10000

long long int sum =0;
bool prime[11000];
pthread_t tid[10]; 
pthread_mutex_t lock;

void SieveOfEratosthenes(int n) 
{  
    prime[1] = false;
    for (int p=2; p*p<=n; p++) { 
        if (prime[p] == true) { 
            for (int i=p*p; i<=n; i += p) 
                prime[i] = false; 
        } 
    } 
} 

void* f(void * arg) 
{ 
    int id = *( (int* ) arg);
    pthread_mutex_lock(&lock);
    for(int i=id*2500 + 1; i<(id+1)*2500+1; i++)
      if(prime[i])
         sum += i;
    pthread_mutex_unlock(&lock); 
  
    return NULL; 
} 

int main(void) 
{ 
    memset(prime, true, sizeof(prime)); 
    SieveOfEratosthenes(MAX_N);
    int i = 0; 
    int error; 
  
    if (pthread_mutex_init(&lock, NULL) != 0) { 
        printf("\n mutex init has failed\n"); 
        return 1; 
    } 
  
    while (i < 4) { 
        int* arg = (int *) malloc(sizeof(* arg));
        *arg = i;
        error = pthread_create(&(tid[i]), NULL, &f, (void *)arg ); 

        if (error != 0) 
            printf("\nThread can't be created :[%s]", strerror(error)); 
        // cout<<i<<" "<<tid[i]<<endl;

        i++; 
    } 
  
    pthread_join(tid[0], NULL); 
    pthread_join(tid[1], NULL); 
    pthread_join(tid[2], NULL); 
    pthread_join(tid[3], NULL); 
    pthread_mutex_destroy(&lock); 
      
    cout<<"Prime sum till "<<MAX_N<<" "<<sum<<endl;
    return 0; 
} 