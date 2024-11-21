#include <bits/stdc++.h>
using namespace std;

// Global variables
int time_quantum;

struct Process
{
    string process_name;
    int arrival_time;    // Arrival time
    int burst_time;      // Burst time
    int completion_time; // Completion time
    int turnaround_time; // Turnaround time = Completion time - Arrival time
    int waiting_time;    // Waiting time = Turnaround time - Burst time
    int response_time;   // Response time = Start time - Arrival time
    int remaining_time;  // Remaining burst time
};

void take_input(vector<Process> &proc, int n)
{
    for (int i = 0; i < n; i++)
    {
        cin >> proc[i].process_name >> proc[i].arrival_time >> proc[i].burst_time;
        proc[i].remaining_time = proc[i].burst_time; // Initialize remaining time
    }
}

void calculate_rr(vector<Process> &proc, int n, vector<pair<int, string>> &gantt_chart)
{
    queue<int> ready_queue; // Queue to hold process indices

    int current_time = 0;
    int completed = 0;
    vector<bool> is_visited(n, false); // To track if a process has been added to the ready queue

    // Add processes to the ready queue as they arrive
    while (completed < n)
    {
        // Add new processes to the ready queue
        for (int i = 0; i < n; i++)
        {
            if (proc[i].arrival_time <= current_time && !is_visited[i])
            {
                ready_queue.push(i);
                is_visited[i] = true;
            }
        }

        // If no process is ready, CPU is idle
        if (ready_queue.empty())
        {
            gantt_chart.push_back({1, "IDLE"});
            current_time++;
            continue;
        }

        

        // Process at the front of the ready queue
        int idx = ready_queue.front();
        ready_queue.pop();

        // If it's the process's first execution, set its response time
        if (proc[idx].remaining_time == proc[idx].burst_time)
        {
            proc[idx].response_time = current_time - proc[idx].arrival_time;
        }

        // Execute the process for the time quantum or its remaining time
        int execution_time = min(time_quantum, proc[idx].remaining_time);
        gantt_chart.push_back({execution_time, proc[idx].process_name});
        proc[idx].remaining_time -= execution_time;
        current_time += execution_time;

        // If the process is completed
        if (proc[idx].remaining_time == 0)
        {
            proc[idx].completion_time = current_time;
            proc[idx].turnaround_time = proc[idx].completion_time - proc[idx].arrival_time;
            proc[idx].waiting_time = proc[idx].turnaround_time - proc[idx].burst_time;
            completed++;
        }
        else
        {
            // If not completed, re-add to the queue
            ready_queue.push(idx);
        }

        // Add newly arrived processes to the ready queue (for strict ordering)
        for (int i = 0; i < n; i++)
        {
            if (proc[i].arrival_time <= current_time && !is_visited[i])
            {
                ready_queue.push(i);
                is_visited[i] = true;
            }
        }
    }
}

void sort_by_arrival_time(vector<Process> &proc, int n)
{
    sort(proc.begin(), proc.end(), [](const Process &a, const Process &b)
         { return a.arrival_time < b.arrival_time; });
}

void print_all(const vector<Process> &proc, int n)
{
    cout << "Round Robin Scheduling:\n";
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
    cin >> n >> time_quantum;

    vector<Process> proc(n);
    vector<pair<int, string>> gantt_chart;

    take_input(proc, n);
    sort_by_arrival_time(proc,n);

    calculate_rr(proc, n, gantt_chart);

    print_all(proc, n);

    print_gantt_chart(gantt_chart);

    return 0;
}





