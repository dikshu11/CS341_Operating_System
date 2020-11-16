/*
Usage:  
g++ Q3.cpp -o Q3 -lpthread
./Q3

*/


#include<bits/stdc++.h>
#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
  
using namespace std;

#define n 5
#define left pos%n
#define right (pos+1)%n

int allocation_matrix[n][n], request_matrix[n][n];

int no_of_pil_eating=0; //no. of phil.  currently no_of_pil_eatinging
int forks[n];	//fork semaphore
pthread_mutex_t wait_mut;
pthread_mutex_t print_mut;
int ph[n]={0,1,2,3,4}; //philosophers id array

void print()
{
	pthread_mutex_lock(&print_mut);
	printf("Allocation Matrix : \n");
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++)
			printf("%d ", allocation_matrix[i][j]);
		printf("\n");
	}
	printf("\nRequest Matrix : \n");
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++)
			printf("%d ",request_matrix[i][j]);
		printf("\n");
	}
	printf("\n\n");
	pthread_mutex_unlock(&print_mut);
}

void pick(int pos,int p)
{
	//if philosopher has dropped his left fork to avoid deadlock, and wants to pick right fork, we simply return	
	if(p==right && allocation_matrix[pos][left]==0)
		return;
	//wait till the fork is not free
	while(!forks[p])
	{
		//if deadlock,and left dropped, then drop right fork also

		if(p==right && allocation_matrix[pos][left]==0)
		{
			request_matrix[pos][p] = 0;
			return;
		}
			
	}
	pthread_mutex_lock(&wait_mut);
	forks[p]=0;	//busy the fork
	request_matrix[pos][p]=0;	//accepted request and close
	allocation_matrix[pos][p]=1;	//allocate fork p to philosopher pos
	pthread_mutex_unlock(&wait_mut);
	return;
}

void drop(int pos,int p)
{
	forks[p]=1;	//free fork
	allocation_matrix[pos][p]=0;	//unallocate
	return;
}

void check_deadlock()
{
	if(no_of_pil_eating>0)
		return;	//no deadlock if someone is no_of_pil_eatinging

	for(int i=0;i<n;i++)
	{
		if(forks[i])	//no deadlock if some fork is free
			return;
	}

	//there might be allocation_matrix case that allocation_matrix philosopher picked right fork just before deadlock was checking for busy forks, in this case, this function would consider that no one is no_of_pil_eatinging and all forks are busy, meaning deadlock, while actually there is no deadlock

	sleep(0.4);
	if(no_of_pil_eating > 0)
		return;

	printf("Parent detects deadlock, do recovery");
	int x=rand()%5;
	drop(x,x);
	printf("Parent pre-empts Philosopher %d\n", x);
	print();
	return;
}

void *dinner(void* p)
{
	int pos=*((int*)p);
	while(1)
	{
		request_matrix[pos][left]=request_matrix[pos][right]=0;
		printf("philosopher %d starts thinking\n",pos);
		sleep(rand()%3);	//think  for 0-2 secs

		printf("Philosopher %d is Hungry\n", pos);
		request_matrix[pos][left]=1;	//request left fork
		pick(pos,left);
		printf("Philosopher %d grabs fork %d (left)\n", pos, left);

		request_matrix[pos][right] = 1;
		sleep(rand() % 1 + 1);	//philosopher wait for 1 or 2 seconds to pick second fork
		pick(pos, right);

		if(allocation_matrix[pos][left] == 0 && allocation_matrix[pos][right] == 0)	//if deadlock was achieved and philosopher dropped his left fork
			continue;
		printf("Philosopher %d grabs fork %d (right)\n", pos, right);

		no_of_pil_eating++;	//inc. count of no_of_pil_eating after philosopher no_of_pil_eatings
		printf("Philosopher %d starts eating.\n",pos);
		sleep(rand() % 2 + 1);		//philosopher no_of_pil_eatings for at least 1 sec or at most 3 seconds

		printf("Philosopher %d ends eating and releases forks %d (left) and %d (right)\n",pos, left, right);
		
		drop(pos, left);		//leaves left fork
		drop(pos, right);		//leaves right fork
		no_of_pil_eating--;


	}
	pthread_exit(0);
}

int main()
{

	srand(2);
	pthread_t tid[5];
	if(pthread_mutex_init(&wait_mut,NULL))
		printf("failed wait init");
	if(pthread_mutex_init(&print_mut,NULL))
		printf("failed print init");
	//crno_of_pil_eatinge threads
	for(int i=0;i<n;i++)
	{
		if(pthread_create(&tid[i],NULL,dinner,&ph[i]))
			printf("failed thread crno_of_pil_eatingion");

	}
	//initialise matrices
	for(int i=0;i<n;i++)
	{
		forks[i]=1; 	//fork is free
		for(int j=0;j<n;j++)
		{
			allocation_matrix[i][j]=0;	//nothing allocated
			request_matrix[i][j]=0;	//nothing requested
		}
	}
	//Checks for deadlock
	while(1){
		check_deadlock();
	}

	//Thread joins 
	for(int i = 0; i < 5; i++)
		pthread_join(tid[i],NULL);

	pthread_mutex_destroy(&wait_mut);
	pthread_mutex_destroy(&print_mut);

	return 0;
}