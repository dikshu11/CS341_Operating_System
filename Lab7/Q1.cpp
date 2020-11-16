/*
Usage:  
g++ Q1.cpp -o Q1 -lpthread
./Q1

*/
#include<bits/stdc++.h>
#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
  
using namespace std;

pthread_t tid[2]; 
pthread_mutex_t lock;
  
void* f(void * arg) 
{ 
    int id = *( (int* ) arg);

    while(true){
        if( pthread_mutex_trylock(&lock) !=0  ){
            cout<<"pthread"<<id<<" cannot access function f() as lock acquired by pthread";
            int other_thread_id = (id == 1)?2:1;
            cout<<other_thread_id<<endl;    
            sleep(1);
        }
        else{
            cout<<"lock acquired by pthread"<<id<<endl; 
            cout<<"pthread"<<id<<" is accessing function f()"<<endl;
          
            sleep(6);
          
            cout<<"lock released by pthread"<<id<<endl; 
            pthread_mutex_unlock (&lock);
            break; 
        } 
    }
      
    return NULL; 
} 
  
int main(void) 
{ 
    int i = 0; 
    int error; 
  
    if (pthread_mutex_init(&lock, NULL) != 0) { 
        printf("\n mutex init has failed\n"); 
        return 1; 
    } 
  
    while (i < 2) { 
        int* arg = (int *) malloc(sizeof(* arg));
        *arg = i+1;
        error = pthread_create(&(tid[i]), NULL, &f, (void *)arg ); 

        if (error != 0) 
            printf("\nThread can't be created :[%s]", strerror(error)); 
        i++; 
    } 
  
    pthread_join(tid[0], NULL); 
    pthread_join(tid[1], NULL); 
    pthread_mutex_destroy(&lock); 
  
    return 0; 
} 
