/*
In indexed an index block store the pointer address of 
all the block in the disk which are allocated to the 
corresponding blocks of file.

*/
#include<bits/stdc++.h>
using namespace std;


int* arr[1000][100000];
string map_files[100000];
int map_start_idx[100000];
int sz[100000];
int disk[100000];

int main()
{
	int num_blocks, num_files = 0, temp;
	cout<<"Indexed File\n";
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

		if(temp == 1){
			string file_name;
			int index_block, total_block, j=0, cnt = 0;

			cout<<("Enter File name,indexed block and total number of block in file\n");
			cin>>file_name>>index_block>>total_block;

			if(index_block <0 || index_block >=num_blocks ||disk[index_block]!=-1){
				cout<<"Index Block is not empty or invalid\n";
				continue;
			}
			
			int freeBlock[total_block];
			disk[index_block] = num_files;
			for(int i=0; i<total_block; i++){
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
				for(int i=0;i<total_block;i++){
					arr[num_files][i] = disk+freeBlock[i];
					disk[freeBlock[i]] = num_files;
				}

				map_files[num_files] = file_name;
				map_start_idx[num_files] = index_block;
				sz[num_files]=total_block;
				num_files++;
				cout<<"Successfully added\n";
			}
			else{
				disk[index_block]=-1;
				cout<<"Not Enough free Space\n";
			}
		}
		else if(temp == 2)
		{
			cout<<"File name        Index Block        Block Stored\n";
			for(int i=0;i<num_files;i++){
				cout<<map_files[i]<<"            "<<map_start_idx[i]<<"            ";
				for(int j=0;j<sz[i];j++)
					cout<<(int)(arr[i][j]-disk)<<" ";
				cout<<"\n";
			}
		}
		else if(temp == 3)
			break;
		else
			cout<<("Invalid Input\n");
	}
}