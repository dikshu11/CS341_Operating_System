/*
In sequential File block of file is present in contiguous location 
i.e between start and end inclusive.
User input start block 
we check if it is available and contiguously block equals 
to total number of block is present.
*/

#include<bits/stdc++.h>
using namespace std;

string map_files[100000];
int map_start_idx[100000];
int map_end_idx[100000];
int disk[1000000];

int main()
{
	int num_blocks, num_files=0, temp;
	cout<<"Sequential File\n";
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
			int start_block,total_block;
			cout<<"Enter File name,starting block and total number of block in file\n";
			cin>>file_name>>start_block>>total_block;
			int flag = 0;

			for(int i=start_block;i<num_blocks;i++){
				if(disk[i] != -1)
					break;
				if(start_block+total_block-1 == i){
					flag = 1;
					break;
				}				
			}
			if(total_block == 0)
				flag = 0;
			if(flag == 1)
			{
				for(int i=start_block;i<start_block+total_block;i++)
					disk[i] = num_files;
				map_files[num_files] = file_name;
				map_start_idx[num_files]=start_block;
				map_end_idx[num_files] = start_block+total_block-1;
				num_files++;
				cout<<"Successfully added\n";
			}
			else
				cout<<"Failed: Error : either someone has occupied that space or out of bound\n";
		}
		else if(temp == 2){
			cout<<"File name 	Start Block 	EndBlock\n";
			for(int i=0;i<num_files;i++)
				cout<<map_files[i]<<" 		"<<map_start_idx[i]<<" 		"<<map_end_idx[i]<<endl; ;
		}
		else if(temp == 3)
			break;
		else
			cout<<"Invalid Input\n";
		
	}
}