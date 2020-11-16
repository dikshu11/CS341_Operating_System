#include<bits/stdc++.h>
using namespace std;


int i,j,np,nr;
int main()
{
  int allocation_matrix[100][100];
  int request_matrix[100][100];
  int available_matrix[100];
  int sequence[100];
  int r[100];
  int w[100];
  int mark[100];

  printf("\nEnter the no of process: ");
  scanf("%d",&np);
  printf("\nEnter the no of resources: ");
  scanf("%d",&nr);

  for(i=0;i<nr;i++)
  {
    printf("\nTotal Amount of the Resource R%d: ",i+1);
    scanf("%d",&r[i]);
  }

  printf("\nEnter the request matrix:\n");

  for(i=0;i<np;i++){
    for(j=0;j<nr;j++)
      scanf("%d",&request_matrix[i][j]);
  }
    

  printf("\nEnter the allocation matrix:\n");
  for(i=0;i<np;i++){
    for(j=0;j<nr;j++)
      scanf("%d",&allocation_matrix[i][j]);
  }
  
  /*Available Resource calculation*/
  for(j=0;j<nr;j++)
  {
    available_matrix[j]=r[j];
    for(i=0;i<np;i++)
    {
      available_matrix[j]-=allocation_matrix[i][j];
    }
  }

  for(j=0;j<nr;j++)
      w[j]=available_matrix[j];

  //mark processes with request less than or equal to W(available resource)
  int cnt=0;int prev_cnt=0;
  for(i=0;i<np;i++){
    mark[i]=0;
  }
  while(cnt<np){
    for(i=0;i<np;i++)
    {
      if(mark[i]!=1)
      {
        int canbeprocessed=0;
        for(j=0;j<nr;j++)
        {
          if(request_matrix[i][j]<=w[j])
            canbeprocessed=1;
          else
          {
            canbeprocessed=0;
            break;
          }
        }
        if(canbeprocessed==1)
        {
          mark[i]=1;
          sequence[cnt]=i;
          for(j=0;j<nr;j++)
            w[j]+=allocation_matrix[i][j];
          cnt++;
        }
      }
    }
    if(cnt==prev_cnt){
      break;
    }
    prev_cnt=cnt;
  }

  //checking for unmarked processes
  int deadlock=0;
  for(i=0;i<np;i++){
    if(mark[i]!=1)
      deadlock=1;
  }

  if(deadlock)
    printf("\nDeadlock detected\n");
  else{
    printf("\nNo Deadlock possible, System in Safe State \n");
    printf("Safe Sequence is: ");
    for(i=0;i<np;i++){
      printf("P%d ",sequence[i]);
    }
    printf("\n");
  }
}

