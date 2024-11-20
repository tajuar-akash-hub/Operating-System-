# CPU Scheduling Algorithms

## Table of Contents
1. [FCFS (First Come First Serve)](#fcfs-first-come-first-serve)
2. [SJF (Shortest Job First)](#sjf-shortest-job-first)
3. [Round Robin (RR)](#round-robin-rr)


# FCFS (First Come First Serve) Scheduling Algorithm

[Full Explanation of FCFS](#fcfs-first-come-first-serve

## Introduction

First Come First Serve (FCFS) is one of the simplest CPU scheduling algorithms. It allocates the CPU to processes in the order they arrive in the ready queue. This non-preemptive scheduling technique is easy to understand and implement but may suffer from issues like the *Convoy Effect* where smaller processes are delayed by larger ones.

This repository demonstrates an implementation of FCFS in C++, including core components and explanations.

---

## Main Components

### 1. **Process Structure**

The `Process` structure defines the essential attributes of a process that are used for scheduling:

```cpp
struct Process {
    string process_name;  // Name of the process (e.g., P1, P2)
    int arrival_time;     // Time at which the process arrives
    int burst_time;       // CPU time required to complete the process
    int completion_time;  // Time at which the process completes execution
    int turnaround_time;  // Total time taken by the process (completion_time - arrival_time)
    int waiting_time;     // Time spent waiting in the ready queue (turnaround_time - burst_time)
    int response_time;    // Time from arrival to the first execution (start_time - arrival_time)
    int start_time;       // Time when the process starts execution
    int end_time;         // Time when the process finishes execution
};
```

This structure encapsulates all the necessary information for FCFS scheduling and aids in tracking each process's progress.

---

### 2. **sort_by_arrival_time**

The `sort_by_arrival_time` function ensures processes are ordered by their arrival times, which is crucial for the FCFS scheduling order.

#### Function Definition:
```cpp
void sort_by_arrival_time(vector<Process>& proc, int n) {
    sort(proc.begin(), proc.end(), [](const Process& a, const Process& b) {
        return a.arrival_time < b.arrival_time;
    });
}
```

#### Explanation:
- It sorts the processes using the **arrival time** in ascending order.
- This guarantees that the CPU serves processes in the order they arrive.

---

### 3. **calculate_times**

The `calculate_times` function performs the core scheduling task. It computes all time-related metrics for each process and tracks the Gantt chart.

#### Function Definition:
```cpp
void calculate_times(vector<Process>& proc, int n, vector<pair<int, string>>& gantt_chart) {
    int current_time = 0;

    for (int i = 0; i < n; i++) {
        // Handle idle time if necessary
        if (current_time < proc[i].arrival_time) {
            gantt_chart.push_back({proc[i].arrival_time - current_time, "IDLE"});
            current_time = proc[i].arrival_time;
        }

        // Assign start, completion, and compute metrics
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
```

#### Explanation:
- **Handles Idle Time:** Checks if the CPU is idle and inserts an "IDLE" entry in the Gantt chart.
- **Computes Metrics:**
  - `start_time`: When the process starts executing.
  - `completion_time`: When the process completes execution.
  - `turnaround_time`: Total time from arrival to completion.
  - `waiting_time`: Time spent in the ready queue.
  - `response_time`: Time from arrival to the first execution.
- **Updates Gantt Chart:** Logs the execution time and process name for visualization.

---

### 4. **print_gantt_chart**

The `print_gantt_chart` function visually represents the scheduling sequence of processes in a tabular format.

#### Function Definition:
```cpp
void print_gantt_chart(const vector<pair<int, string>>& gantt_chart) {
    cout << "Gantt Chart:\n";

    // Print process names
    for (const auto& entry : gantt_chart) {
        cout << "[" << entry.second << "] ";
    }
    cout << "\n";

    // Print time spans
    int current_time = 0;
    for (const auto& entry : gantt_chart) {
        cout << "[" << current_time << "]";
        current_time += entry.first;
    }
    cout << current_time << endl; // Final time
}
```

#### Explanation:
- **Process Names:** Displays the names of the processes or "IDLE" blocks in order.
- **Time Span:** Below each process, the time span is displayed, including the final time.

---

## Example Input and Output

### Input:
```plaintext
4
P1 0 5
P2 2 3
P3 4 1
P4 6 7
```

### Output:
#### Gantt Chart:
```plaintext
Gantt Chart:
[IDLE] [P1] [P2] [P3] [P4]
[0][0][5][8][9][16]
```

#### Process Details:
```plaintext
FCFS Scheduling:
ProcName        ArrivalTime     BurstTime       CompletionTime     TurnaroundTime     WaitingTime     ResponseTime   
P1              0              5              5                  5                  0              0              
P2              2              3              8                  6                  3              3              
P3              4              1              9                  5                  4              4              
P4              6              7              16                 10                 3              3              
```

---

## Conclusion

This implementation of FCFS scheduling demonstrates its simplicity and effectiveness for process management. The addition of a Gantt chart helps visualize the scheduling sequence. However, as a non-preemptive algorithm, FCFS may not be suitable for systems requiring real-time responsiveness.
