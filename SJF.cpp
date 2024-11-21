#include <bits/stdc++.h>
using namespace std;

struct Process
{
    string process_name;
    int arrival_time;    // Arrival time
    int burst_time;      // Burst time
    int completion_time; // Completion time
    int turnaround_time; // Turnaround time = Completion time - Arrival time
    int waiting_time;    // Waiting time = Turnaround time - Burst time
    int response_time;   // Response time = Start time - Arrival time
    int start_time;      // Start time of the process
    int end_time;        // End time of the process
};

void take_input(vector<Process> &proc, int n)
{
    for (int i = 0; i < n; i++)
    {
        cin >> proc[i].process_name >> proc[i].arrival_time >> proc[i].burst_time;
    }
}

void sort_by_arrival_time(vector<Process> &proc, int n)
{
    sort(proc.begin(), proc.end(), [](const Process &a, const Process &b)
         { return a.arrival_time < b.arrival_time; });
}

void calculate_sjf(vector<Process> &proc, int n, vector<pair<int, string>> &gantt_chart)
{

    sort_by_arrival_time(proc, n); // Sort processes by arrival time

    int current_time = 0;
    int completed = 0;
    vector<bool> is_completed(n, false);

    while (completed < n)
    {
        int idx = -1;
        int min_burst_time = INT_MAX;

        // Find the process with the shortest burst time that has arrived
        for (int i = 0; i < n; i++)
        {
            if (proc[i].arrival_time <= current_time && !is_completed[i] && proc[i].burst_time < min_burst_time)
            {
                min_burst_time = proc[i].burst_time;
                idx = i;
            }
        }

        // If no process is ready, CPU is idle
        if (idx == -1)
        {
            gantt_chart.push_back({1, "IDLE"});
            current_time++;
        }
        else
        {
            // Process the selected process
            proc[idx].start_time = current_time;
            proc[idx].completion_time = current_time + proc[idx].burst_time;
            proc[idx].turnaround_time = proc[idx].completion_time - proc[idx].arrival_time;
            proc[idx].waiting_time = proc[idx].turnaround_time - proc[idx].burst_time;
            proc[idx].response_time = proc[idx].start_time - proc[idx].arrival_time;

            gantt_chart.push_back({proc[idx].burst_time, proc[idx].process_name});
            current_time = proc[idx].completion_time;
            is_completed[idx] = true;
            completed++;
        }
    }
}

void sort_based_on_id(vector<Process> &proc, int n)
{
    sort(proc.begin(), proc.end(), [](const Process &a, const Process &b)
         {
        int id_a = stoi(a.process_name.substr(1)); // Assuming process_name is of the form "pX"
        int id_b = stoi(b.process_name.substr(1));
        return id_a < id_b; });
}

void print_all(const vector<Process> &proc, int n)
{
    cout << "SJF Scheduling:\n";
    cout << left << setw(15) << "ProcName"
         << setw(15) << "ArrivalTime"
         << setw(15) << "BurstTime"
         << setw(20) << "CompletionTime"
         << setw(20) << "TurnaroundTime"
         << setw(15) << "WaitingTime"
         << setw(15) << "ResponseTime" << "\n";

    for (int i = 0; i < n; i++)
    {
        cout << left << setw(15) << proc[i].process_name
             << setw(15) << proc[i].arrival_time
             << setw(15) << proc[i].burst_time
             << setw(20) << proc[i].completion_time
             << setw(20) << proc[i].turnaround_time
             << setw(15) << proc[i].waiting_time
             << setw(15) << proc[i].response_time << "\n";
    }
}

void print_gantt_chart(const vector<pair<int, string>> &gantt_chart)
{
    cout << "Gantt Chart:\n";

    // Print process names
    for (const auto &entry : gantt_chart)
    {
        cout << "[" << entry.second << "] ";
    }
    cout << "\n";

    // Print time intervals
    int current_time = 0;
    for (const auto &entry : gantt_chart)
    {
        cout << "[" << current_time << "]";
        current_time += entry.first;
    }
    cout << "[" << current_time << "]" << endl; // Final time
}

int main()
{
    int n;
    cin >> n;

    vector<Process> proc(n);
    vector<pair<int, string>> gantt_chart;

    take_input(proc, n);

    print_all(proc, n);

    calculate_sjf(proc, n, gantt_chart);

    sort_based_on_id(proc, n);

    print_all(proc, n);
    print_gantt_chart(gantt_chart);

    return 0;
}
