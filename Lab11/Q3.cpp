/*
n linked file system a start block is used which stores the address of next block for the corresponding file

*/
#include<bits/stdc++.h>
using namespace std;


struct node
{
	node* ptr;
	int val;
};

struct node* arr[100];
string map_files[100];
int map_start_idx[100];
int sz[100];
int disk[100000];

int main()
{
	int num_blocks, num_files = 0, temp;
	cout<<"Linked List File\n";
	cout<<"Enter the number of Block in disk\n";

	cin>>num_blocks;

	for(int i=0;i<num_blocks;i++)
		disk[i]=-1;

	while(1)
	{
		cout<<"Enter : \n";
		cout<<"1. To add File\n";
		cout<<"2. To Print Directory \n";
		cout<<"3. To exit\n";
		cin>>temp;

		if(temp == 1)
		{
			string file_name;
			int start_block, total_block, j=0, cnt=0;
			cout<<"Enter File name,start block and total number of block in file\n";
			cin>>file_name>>start_block>>total_block;

			if(start_block <0 || start_block >=num_blocks ||disk[start_block]!=-1)
			{
				cout<<"Start Block is not empty or invalid\n";
				continue;
			}
			
			int freeBlock[total_block];
			freeBlock[0] = start_block;
			cnt++;
			for(int i=1;i<total_block;i++){
				for(;j<num_blocks;j++){
					if(disk[j]==-1){
						freeBlock[i] = j;
						cnt++;
						j++;
						break;
					}
				}
			}

			if(cnt == total_block){
				disk[start_block] = num_files;
		
				struct node* head = NULL;
				for(int i=0;i<total_block;i++){
					struct node* idx = new node();
					idx->val = freeBlock[i];
					idx->ptr = NULL;
					if(head == NULL){
						arr[num_files] =idx;
						head = idx;
					}
					else{
						head->ptr = idx;
						head = idx;
					}
					disk[freeBlock[i]] = num_files;
				}

				map_files[num_files] = file_name;				
				sz[num_files]=total_block;
				num_files++;
				cout<<"Successfully added\n";
			}
			else
				cout<<"Not Enough free Space\n";
		}
		else if(temp == 2){
			cout<<"File name     Block Stored\n";
			for(int i=0;i<num_files;i++){
				cout<<map_files[i]<<" 		";
				struct node* head = arr[i];
				while(head!=NULL){
					cout<<head->val<<" ->";
					head = head->ptr;
				}
				cout<<"NULL\n";
			}
		}
		else if(temp == 3)
			break;
		else
			cout<<("Invalid Input\n");
	}
}