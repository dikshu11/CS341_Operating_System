#include <bits/stdc++.h>
using namespace std; 

struct process{
	int arrival_time;
	int burst_time;
	int priority;
	int pid;
};


bool custom_sort(process p1, process p2){
	if(p1.arrival_time < p2.arrival_time )
		return true;
	if(p1.arrival_time == p2.arrival_time && p1.priority < p2.priority)
		return true;
	return false;
}

struct custom_sort1{
	bool operator()(process const& p1, process const& p2){
		if(p1.priority > p2.priority)
			return true;
		return false;
	}
};

int main(){

	int n;
	cin>>n;

	process proc[n];

	for(int i=0; i<n; i++){
		proc[i].pid = i+1;
		cin>>proc[i].arrival_time>>proc[i].burst_time>>proc[i].priority;
	}
	sort(proc, proc+n, custom_sort);
	

	queue<int> completion_order;
	priority_queue< process, vector<process>, custom_sort1 > pq;
	pq.push(proc[0]);

	int ctime = proc[0].arrival_time, completed_jobs=0, jobs_ind = 1;
	double wait_time = 0, turn_time = 0;

	while(completed_jobs!=n){

		while(jobs_ind <n && proc[jobs_ind].arrival_time <= ctime){
			pq.push(proc[jobs_ind]);
			jobs_ind++;
		}
		
		if(pq.empty()){	
			ctime++;
			continue;
		}


		process p = pq.top();
		pq.pop();

		ctime += p.burst_time;
		wait_time += ctime - p.arrival_time -p.burst_time;
		turn_time += ctime - p.arrival_time;
		completion_order.push(p.pid);
		completed_jobs++;

		//cout<<p.pid<<" "<<ctime<<" "<<" "<<jobs_ind<<endl;
	}

	cout<<fixed<<setprecision(2)<<wait_time/n<<" "<<turn_time/n<<endl;
	while(!completion_order.empty()){
		cout<<"P"<<completion_order.front()<<" ";
		completion_order.pop();
	}

}

/*

4 
0 10 5
1 6 4
3 2 2
5 4 0
*/