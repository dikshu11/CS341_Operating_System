#include <bits/stdc++.h>
using namespace std; 

struct process{
	int arrival_time;
	int burst_time;
	int priority;
	int pid;
	int remaining_time;
};


bool custom_sort(process p1, process p2){
	if(p1.arrival_time < p2.arrival_time )
		return true;
	if(p1.arrival_time == p2.arrival_time && p1.priority < p2.priority)
		return true;
	return false;
}



int main(){

	int n, numq, tq[3] = {0, 4, 3};
	cin>>n>>numq;

	process proc[n];

	for(int i=0; i<n; i++){
		proc[i].pid = i+1;
		cin>>proc[i].arrival_time>>proc[i].burst_time>>proc[i].priority;
		proc[i].remaining_time = proc[i].burst_time;
	}
	sort(proc, proc+n, custom_sort);

	queue<int> completion_order;
	
	int ctime = 0, completed_jobs=0, jobs_ind[3] = {0};
	double wait_time = 0, turn_time = 0;

	queue<process> q[3];
	q[proc[0].priority ].push(proc[0]);
	jobs_ind[proc[0].priority]++;

	while(completed_jobs != n){
		process p;
		p.pid = 3;
		p.remaining_time = 0;

		if(!q[1].empty()){

			p = q[1].front();
			q[1].pop();

			if(p.remaining_time <= tq[1]){
				ctime += p.remaining_time;
				turn_time += ctime-p.arrival_time;
				wait_time += ctime-p.arrival_time-p.burst_time;
				completed_jobs++;
				p.remaining_time = 0;
				completion_order.push(p.pid);
			}
			else{
				p.remaining_time -= tq[1];
				ctime += tq[1];
			}
		}
		else if(!q[2].empty()){

			p = q[2].front();
			q[2].pop();

			int temp = 0;
			while(temp < tq[2]){

				if(p.remaining_time <= 1){
					ctime += p.remaining_time;
					turn_time += ctime-p.arrival_time;
					wait_time += ctime-p.arrival_time-p.burst_time;
					completed_jobs++;
					p.remaining_time = 0;
					completion_order.push(p.pid);
					break;
				}
				else{
					p.remaining_time -= 1;
					ctime += 1;
				}

				temp++;
				for(int i=1; i<3;  i++){
					while(jobs_ind[i] < n && proc[ jobs_ind[i] ].arrival_time <= ctime){
						if(proc[jobs_ind[i] ].priority == i)
							q[i].push( proc[ jobs_ind[i] ] );
						jobs_ind[i]++;
					}
				}

				if(!q[1].empty())
					break;
			}
		}
		else
			ctime++;
		

		for(int i=1; i<3;  i++){
			while(jobs_ind[i] < n && proc[jobs_ind[i]].arrival_time <= ctime){
				if(proc[jobs_ind[i] ].priority == i)
					q[i].push( proc[ jobs_ind[i] ] );
				jobs_ind[i]++;
			}
		}
		if(p.remaining_time > 0){
			q[p.priority].push(p);
		}
	}



	cout<<fixed<<setprecision(2)<<wait_time/n<<" "<<turn_time/n<<endl;
	while(!completion_order.empty()){
		cout<<"P"<<completion_order.front()<<" ";
		completion_order.pop();
	}

}

/*

5 2
0 10 2
3 7 1
4 6 2
12 5 1
18 8 1

*/