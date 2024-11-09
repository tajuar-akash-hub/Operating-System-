#include <bits/stdc++.h>
using namespace std;

struct Process
{
    string process_name;
    int pid;             // process id
    int arrival_time;    // arrival time
    int burst_time;      // burst time
    int completion_time; // completion time
    int turnaround_time; // turnaround time
    int waiting_time;    // waiting time

    int start_time ;
};


void calculate_times(Process proc[], int n) {
    // Initialize the first process start and completion times
    proc[0].start_time = proc[0].arrival_time;
    proc[0].completion_time = proc[0].start_time + proc[0].burst_time;
    proc[0].turnaround_time = proc[0].completion_time - proc[0].arrival_time;
    proc[0].waiting_time = proc[0].turnaround_time - proc[0].burst_time;

    // Calculate times for each subsequent process
    for (int i = 1; i < n; i++) {
        // Start time is either the arrival time (if idle) or the previous process’s completion time
        proc[i].start_time = max(proc[i].arrival_time, proc[i - 1].completion_time);
        proc[i].completion_time = proc[i].start_time + proc[i].burst_time;
        proc[i].turnaround_time = proc[i].completion_time - proc[i].arrival_time;
        proc[i].waiting_time = proc[i].turnaround_time - proc[i].burst_time;
    }
}

void print_all(Process proc[],int n){
   
  cout << "FCFS Scheduling:" << endl;
  cout << "ProcName-\tPID - \tArrivalTime\tBurst Time\tCompletion Time\tTurnaround "
          "Time\t\tWaiting Time"
       << endl;

  for (int i = 0; i < n; i++) {
    cout<<proc[i].process_name<<"\t\t\t"<< proc[i].pid << "\t\t\t" << proc[i].arrival_time << "\t\t"
         << proc[i].burst_time << "\t\t\t\t\t" << proc[i].completion_time << "\t\t\t"
         << proc[i].turnaround_time << "\t\t\t\t\t" << proc[i].waiting_time << endl;
  }
    

}

int main()
{
    int n = 5; // number of processes
    Process proc[5] = {{"p1",1, 3, 1}, {"p2",2, 4, 5}, {"p3",3, 0, 2}, {"p4",4, 3, 7}, {"p5",5, 5, 5}};

    sort(proc, proc + n, [](Process a, Process b) {
        return a.arrival_time < b.arrival_time;
    });

    calculate_times(proc, n);


    sort(proc, proc + n, [](Process a, Process b) {
        return a.pid < b.pid;
    });



    print_all(proc,n);
    
}