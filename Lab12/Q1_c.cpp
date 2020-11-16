#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;

void plot(vector<double> &coord_x, vector<double> &coord_y, string name){
    int cnt_points = coord_x.size(), cnt_commands = 3;
    name =  "\"" + name + "\"";
    name = "set title " + name;
    char * title = new char [name.length()+1];
    strcpy (title, name.c_str());
    char * commands[10000];
    commands[0] = title;
    commands[1] = "set xlabel \"Seek time (ms)\"";
    commands[2] = "set ylabel \"#Cylinders\"";
    
    for (int i=0; i < cnt_points; i++){
      string tmp= "\"" + to_string(  (int)coord_x[i]) + " " + to_string((int)coord_y[i]) + "\"" ;
      tmp = "set label " + tmp + " at " +  to_string( coord_x[i]) + "," + to_string(coord_y[i]);
      char * label = new char [tmp.length()+1];
      strcpy (label, tmp.c_str());
      commands[ cnt_commands] = label;
      cnt_commands++;
    }
    commands[cnt_commands++] = "plot 'data.temp' with linespoints";

    FILE * temp = fopen("data.temp", "w");
    FILE * gnu_plot_pipe = popen ("gnuplot -persistent", "w");
    for (int i=0; i < cnt_points; i++)
    fprintf(temp, "%lf %lf \n", coord_x[i], coord_y[i]); //Write the data to a temporary file
    
    for (int i=0; i < cnt_commands; i++)
      fprintf(gnu_plot_pipe, "%s \n", commands[i]); //Send commands to gnuplot one by one.
}

int CSCAN(int head,int* work_queue, int work_queue_size, int cnt_cylinder, int seek_rate  )
{
  vector<double> coord_x, coord_y;
  coord_x.push_back(0);
  coord_y.push_back(head);
  // CSCAN : Same as SCAN but when at one end it reaches the other by just one movement.
  int direction = 0; // 0 for left and 1 for right
  int st = INT_MAX, cnt = 0, THM = 0;;
  for(int i=0 ; i < work_queue_size ; i++){
    if(abs(head-work_queue[i])<st){
      direction = (work_queue[i]<head)?0:1;
      st = abs(work_queue[i]-head);
    }
  }
  int avail[cnt_cylinder] = {0};
  for(int i=0 ; i < work_queue_size ; i++){
    avail[work_queue[i]]++;
  }
  if(avail[head]==1){
    avail[head]--;
    cout << head << "--> ";
    coord_x.push_back(seek_rate*THM);
    coord_y.push_back(head);
    cnt++;
  }
  //if left movement 
  if(direction == 0){
    for(int i=head-1 ; i>=0&&cnt < work_queue_size ; i--){
      if(avail[i]==1){
        cnt++;
        THM += abs(head-i);
        avail[i]--;
        head = i;
        cout << head << "--> ";
        coord_x.push_back(seek_rate*THM);
        coord_y.push_back(head);
      }
    }
    //extra left
    if(cnt!=work_queue_size){
      THM+=head;
      head = 0;
    }
    //as CSCAN can move from 0 to cnt_cylinder-1 in one movement but no head moveement
    head = cnt_cylinder-1;
    for(int i=cnt_cylinder-1 ; i>=0&& cnt < work_queue_size ; i--){
      if(avail[i]==1){
        cnt++;
        THM+=abs(head-i);
        head = i;
        avail[i]--;
        cout << head << "--> ";
        coord_x.push_back(seek_rate*THM);
        coord_y.push_back(head);
      }
    }
  }else
  {
    for(int i=head+1 ; i < cnt_cylinder && cnt < work_queue_size ; i++){
      if(avail[i]==1){
        cnt++;
        THM+=abs(head-i);
        head = i;
        avail[i]--;
        cout << head << "--> ";
        coord_x.push_back(seek_rate*THM);
        coord_y.push_back(head);
      }
    }
    if(cnt!=work_queue_size){
      THM+=abs(cnt_cylinder-1-head);
      head = 0;
    }
    //as CSCAN move to 0 from cnt_cylinder-1
    head = 0;
    for(int i=0 ; i < cnt_cylinder && cnt < work_queue_size ; i++){
      if(avail[i]==1){
        cnt++;
        THM+=abs(head-i);
        head = i;
        avail[i]--;
        cout << head << "--> ";
        coord_x.push_back(seek_rate*THM);
        coord_y.push_back(head);
      }
    }
  }
  cout <<"null" <<  endl;
  cout << "Total Head movement : " << THM << endl;
  cout << "Seek time : " << seek_rate*THM << " ms\n" << endl;
  plot(coord_x, coord_y, "CSCAN");
  return seek_rate*THM;
}  

int main()
{
  int head ;
  int seek_rate;
  int work_queue_size;
  int cnt_cylinder;
  cout<<"Enter the seek_rate:\n";
  cin>>seek_rate;
  cout<<"Enter Count of Cylinders:\n";
  cin>>cnt_cylinder;
  cout<<"Enter disk head:\n";
  cin>>head;
  cout<<"Enter work queue size:\n";
  cin>>work_queue_size;
  int work_queue[work_queue_size];
  for(int i=0; i<work_queue_size; i++){
   cout<<"Enter " <<i+1<<" th element of work queue:\n";
   cin>>work_queue[i];
  }
  cout << "CSCAN disk Scheduling Algorithm: " << endl << endl;
  cout << "Request Processed Order :" << endl;
  int scan = CSCAN(head,work_queue, work_queue_size, cnt_cylinder, seek_rate);
}