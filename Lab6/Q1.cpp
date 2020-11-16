

#include <bits/stdc++.h>
using namespace std; 

// storing process info in struct
struct process{
	int pid;
	int arrival_time;
	int burst_time;
	int remaining_time;
};

// custom function to sort process according to arrival time
bool custom_sort(process p1, process p2){
	if(p1.arrival_time < p2.arrival_time )
		return true;
	return false;
}
int main(){

	int n, quantum;
	cin>>n>>quantum;

	process proc[n];

	// Taking inputs
	for(int i=0; i<n; i++){
		proc[i].pid = i+1;
		cin>>proc[i].arrival_time>>proc[i].burst_time;
		proc[i].remaining_time = proc[i].burst_time;
	}

	sort(proc, proc+n, custom_sort);
	
	queue<int> completion_order;
	queue<process> pq;
	pq.push(proc[0]);

	int ctime = proc[0].arrival_time, completed_jobs=0, jobs_ind = 1;
	double wait_time = 0, turn_time = 0;


	// Round Robin
	while(completed_jobs != n){

		while(jobs_ind <n && proc[jobs_ind].arrival_time <= ctime){
			pq.push(proc[jobs_ind]);
			jobs_ind++;
		}

		if(pq.empty()){	
			ctime++;
			continue;
		}

		process p = pq.front();
		pq.pop();
		

		if(p.remaining_time > quantum ){
			ctime += quantum;
			p.remaining_time -= quantum;
		}
		else{
			ctime += p.remaining_time;
			turn_time += ctime-p.arrival_time;
			wait_time += ctime-p.arrival_time-p.burst_time;
			completed_jobs++;
			p.remaining_time = 0;
			completion_order.push(p.pid);
			// cout<<p.pid<<" ctime: "<<ctime<<endl;
		}

		while(jobs_ind <n && proc[jobs_ind].arrival_time <= ctime){
			pq.push(proc[jobs_ind]);
			jobs_ind++;
		}

		if(p.remaining_time > 0){
			pq.push(p);
		}

	}

	// printing outputs
	cout<<fixed<<setprecision(2)<<wait_time/n<<" "<<turn_time/n<<endl;
	while(!completion_order.empty()){
		cout<<"P"<<completion_order.front()<<" ";
		completion_order.pop();
	}


}

/*
6 2 
0 4 
1 5 
2 2 
3 1 
4 6 
6 3

*/

