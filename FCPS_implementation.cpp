#include <bits/stdc++.h>
using namespace std;

struct Process {
    string process_name;
    int arrival_time;    // arrival time
    int burst_time;      // burst time
    int completion_time; // time in the Gantt chart
    int turnaround_time; // completion_time - arrival_time
    int waiting_time;    // turnaround_time - burst_time
    int response_time;   // first time in the Gantt chart - arrival time
    int start_time;
    int end_time;
};

void take_input(vector<Process>& proc, int n) {
    for (int i = 0; i < n; i++) {
        cin >> proc[i].process_name >> proc[i].arrival_time >> proc[i].burst_time;
    }
}

void sort_by_arrival_time(vector<Process>& proc, int n) {
    // Sort processes by arrival time for scheduling
    sort(proc.begin(), proc.end(), [](const Process& a, const Process& b) {
        return a.arrival_time < b.arrival_time;
    });
}

void sort_based_on_id(vector<Process>& proc, int n) {
    sort(proc.begin(), proc.end(), [](const Process& a, const Process& b) {
        int id_a = stoi(a.process_name.substr(1)); // Assuming process_name is of the form "pX"
        int id_b = stoi(b.process_name.substr(1));
        return id_a < id_b;
    });
}

void calculate_times(vector<Process>& proc, int n, vector<pair<int, string>>& gantt_chart) {
    // Sort processes by arrival time for scheduling
    
    sort_by_arrival_time(proc, n);

    int current_time = 0;

    for (int i = 0; i < n; i++) {

        // If CPU is idle
        if (current_time < proc[i].arrival_time) {
            gantt_chart.push_back({proc[i].arrival_time - current_time, "IDLE"});
            // idle time = proc[i].arrival_time - current_time
            current_time = proc[i].arrival_time;
        }

        // Process execution
        proc[i].start_time = current_time;
        proc[i].completion_time = proc[i].start_time + proc[i].burst_time;
        proc[i].turnaround_time = proc[i].completion_time - proc[i].arrival_time;
        proc[i].waiting_time = proc[i].turnaround_time - proc[i].burst_time;
        proc[i].response_time = proc[i].start_time - proc[i].arrival_time;
        proc[i].end_time = proc[i].completion_time;

        gantt_chart.push_back({proc[i].burst_time, proc[i].process_name});
        current_time = proc[i].completion_time;
    }
}

void print_gantt_chart(const vector<pair<int, string>>& gantt_chart) {
    cout << "Gantt Chart:\n";

    //printing process name
    for (const auto& entry : gantt_chart) {
        cout << "[" << entry.second << "] ";
    }
    cout << "\n";

    //printing time 

    int current_time = 0;

    for (const auto& entry : gantt_chart) {
        cout<<"[" << current_time << "]";
        current_time += entry.first;
    }
    cout << current_time << endl; // Final time
}

void print_all(const vector<Process>& proc, int n) {
    cout << "FCFS Scheduling:\n";
    cout << left << setw(15) << "ProcName"
         << setw(15) << "ArrivalTime"
         << setw(15) << "BurstTime"
         << setw(20) << "CompletionTime"
         << setw(20) << "TurnaroundTime"
         << setw(15) << "WaitingTime"
         << setw(15) << "ResponseTime" << "\n";

    for (int i = 0; i < n; i++) {
        cout << left << setw(15) << proc[i].process_name
             << setw(15) << proc[i].arrival_time
             << setw(15) << proc[i].burst_time
             << setw(20) << proc[i].completion_time
             << setw(20) << proc[i].turnaround_time
             << setw(15) << proc[i].waiting_time
             << setw(15) << proc[i].response_time << "\n";
    }
}

// Driver code
int main() {
    int n; // Number of processes
    cin >> n;
    vector<Process> proc(n);
    vector<pair<int, string>> gantt_chart;

    // Take input
    take_input(proc, n);

    // Calculate times and Gantt chart
    calculate_times(proc, n, gantt_chart);

    // Print Gantt chart
    print_gantt_chart(gantt_chart);

    // Print process details
    sort_based_on_id(proc, n);
    print_all(proc, n);



    //printin gaant chart entry 
    cout<<"printing gaant chart entries"<<endl;
    for(const auto&p :gantt_chart){
        cout<<p.first<<" "<<p.second<<endl;
    }

    return 0;
}
