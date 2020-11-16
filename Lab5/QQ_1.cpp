#include <bits/stdc++.h>
using namespace std; 

int main(){
	int n;
	cin>>n;

	if(n<=0){
		return 0;
	}

	// process_info.first.first = arrival time
	//  process_info.first.second = burst time
	//  process_info.second = job id
	vector< pair< pair<int, int>, int> > process_info(n);
	int completion_time[n];
	int completion_order[n];
	double waiting_time = 0;
	double turn_time = 0;

	for(int i=0; i<n; i++){
		process_info[i].second = i;
		cin>>process_info[i].first.first>>process_info[i].first.second;
	}


	sort(process_info.begin(), process_info.end());


	completion_time[0] = process_info[0].first.first + process_info[0].first.second ;
	turn_time += process_info[0].first.second;



	for(int i=1; i<n; i++){
		int ind = i;
		int min_time = process_info[i].first.second;
		int curr_time = completion_time[i-1];

		for(int j=i; j<n; j++){
			if(process_info[j].first.first <= curr_time && process_info[j].first.second < min_time ){
				min_time = process_info[j].first.second;
				ind = j;
			}
		}
		swap(process_info[i], process_info[ind]);
		

		if(process_info[i].first.first <= completion_time[i-1] ){
			completion_time[i] =  completion_time[i-1]+process_info[i].first.second;
			waiting_time += completion_time[i-1]-process_info[i].first.first;
		}
		else
			completion_time[i] = process_info[i].first.first+process_info[i].first.second;

		turn_time += completion_time[i]-process_info[i].first.first;


	}



	cout<<waiting_time/n<<" "<<turn_time/n<<endl;

	for(int i=0; i<n; i++){
		cout<<"P"<<process_info[i].second+1<<" ";
	}



}


