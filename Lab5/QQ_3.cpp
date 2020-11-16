#include <bits/stdc++.h>
using namespace std; 

int main(){
	int n;
	cin>>n;

	if(n<=0){
		return 0;
	}

	vector< pair< pair<int, int>, int> > process_info(n);

	int completion_order[n];
	int completion_time[n];
	double waiting_time = 0;
	double turn_time = 0;

	for(int i=0; i<n; i++){
		process_info[i].second = i;
		cin>>process_info[i].first.first>>process_info[i].first.second;
		waiting_time -= process_info[i].first.second;
	}

	sort(process_info.begin(), process_info.end());

	int complete = 0, t = 0, minm = 0; 
    int shortest = 0, finish_time; 
    bool check = false; 
 
    while (complete != n) { 
  
        // Find process with minimum remaining time among the 
        // processes that arrives till the current time` 
        for (int j = 0; j < n; j++) { 
            if(process_info[j].first.first <= t && process_info[j].first.second >0 && process_info[j].first.second > minm ){
            	check = true;
            	shortest = j;
            	minm = process_info[j].first.second;
            }
        } 
  
        if (check == false) { 
            t++; 
            continue; 
        } 
  
        process_info[shortest].first.second--;
  
        // Update minimum 
        minm = 0; 
  
        // If a process gets completely executed 
        if (process_info[shortest].first.second == 0) { 
  			completion_order[complete] = shortest+1;
            complete++; 
            check = false; 
  
            finish_time = t + 1; 
  			completion_time[shortest] = finish_time;
   
            if(finish_time - process_info[shortest].first.first - process_info[shortest].first.second >= 0 )
            	waiting_time +=  completion_time[shortest] - process_info[shortest].first.first;
            turn_time += finish_time-process_info[shortest].first.first;
            // cout<<waiting_time<<" "<<turn_time<<" "<<finish_time<<" "<<process_info[shortest].first.second<<endl;
        } 
        // Increment time 
        t++; 
    } 


	cout<<waiting_time/n<<" "<<turn_time/n<<endl;

	for(int i=0; i<n; i++){
		cout<<"P"<<completion_order[i]<<" ";
	}



}
