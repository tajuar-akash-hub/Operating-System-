# Shortest Job First (SJF) Scheduling

### Implementation Overview

The implementation of the **Shortest Job First (SJF) Scheduling** algorithm is straightforward. The core decision-making depends on the **burst time** of the processes. Below, we outline the steps and scenarios that can arise when constructing the Gantt chart for SJF scheduling.

### Key Scenarios in SJF Gantt Chart Construction

1. **Multiple Processes in the Ready Queue**:
   - When more than one process arrives in the ready queue at a given time, compare their **burst times**.
   - The process with the **shortest burst time** is selected for execution.
     - **Sub-scenario**: If two or more processes have the same burst time, then compare their **arrival times**. The process that arrived **earlier** is selected.

2. **Single Process in the Ready Queue**:
   - If only one process is available in the ready queue at the current time, it is directly added to the Gantt chart.

### Why These Rules Matter

The SJF algorithm prioritizes processes with the shortest burst time to minimize waiting time and improve efficiency. By addressing tie-breaking scenarios (such as identical burst times or arrival times), this approach ensures a deterministic and fair scheduling order.


### Key Functions and Workflow in the SJF Scheduling Code

This section explains the major functions and the working procedure of the **Shortest Job First (SJF) Scheduling** implementation to help understand the code's flow and logic.

---

#### 1. `take_input(vector<Process> &proc, int n)`

**Purpose**: 
Takes input for all processes from the user. Each process has the following attributes:
- Process name (e.g., `p1`, `p2`)
- Arrival time
- Burst time

**Working**:
- Loops through the `proc` vector to assign the provided attributes to each process.

---

#### 2. `sort_by_arrival_time(vector<Process> &proc, int n)`

**Purpose**: 
Sorts the processes by their **arrival time**. This ensures that the scheduler processes tasks in the order they arrive in the system.

**Working**:
- Uses the `std::sort` function with a custom comparator lambda to sort the `proc` vector based on the `arrival_time` field.

---

#### 3. `calculate_sjf(vector<Process> &proc, int n, vector<pair<int, string>> &gantt_chart)`

**Purpose**: 
Implements the **SJF Scheduling Algorithm** to calculate scheduling metrics and generate the Gantt chart.

**Working**:
1. **Initialize Variables**:
   - `current_time`: Tracks the current time in the scheduling process.
   - `completed`: Counts the number of processes completed.
   - `is_completed`: A boolean vector to track if a process is finished.

2. **Loop Until All Processes Are Completed**:
   - Searches for the process with the shortest burst time that has arrived and is not yet completed.
   - If no process is ready, the CPU remains idle, and "IDLE" is added to the Gantt chart.

3. **Process Execution**:
   - The selected process is executed, and the following metrics are updated:
     - `start_time`: The time when the process starts execution.
     - `completion_time`: When the process finishes execution.
     - `turnaround_time`: `completion_time - arrival_time`.
     - `waiting_time`: `turnaround_time - burst_time`.
     - `response_time`: `start_time - arrival_time`.

4. **Update the Gantt Chart**:
   - Adds the process and its burst time to the Gantt chart.

---

#### 4. `sort_based_on_id(vector<Process> &proc, int n)`

**Purpose**: 
Sorts the processes based on their IDs (e.g., `p1`, `p2`) to display results in the original order.

**Working**:
- Extracts the numeric part of the `process_name` (e.g., `1` from `p1`) using `stoi`.
- Sorts the processes based on these IDs.

---

#### 5. `print_all(const vector<Process> &proc, int n)`

**Purpose**: 
Displays the final scheduling details for all processes.

**Output Fields**:
- Process name
- Arrival time
- Burst time
- Completion time
- Turnaround time
- Waiting time
- Response time

**Working**:
- Loops through the `proc` vector and prints each process's details in a tabular format.

---

#### 6. `print_gantt_chart(const vector<pair<int, string>> &gantt_chart)`

**Purpose**: 
Visualizes the Gantt chart for the scheduling process.

**Working**:
1. **Process Names**:
   - Prints the sequence of processes (or "IDLE") from the Gantt chart.

2. **Time Intervals**:
   - Prints the corresponding time intervals for each process, showing the timeline of execution.

---

### Workflow

1. **Input**:
   - User provides the number of processes, along with each process's name, arrival time, and burst time.

2. **Sorting**:
   - Processes are sorted by arrival time using `sort_by_arrival_time`.

3. **Scheduling**:
   - The `calculate_sjf` function performs the SJF scheduling:
     - Selects the process with the shortest burst time from the ready queue.
     - Handles idle times when no process is ready.
     - Updates the Gantt chart and calculates metrics.

4. **Sorting by ID**:
   - The `sort_based_on_id` function reorders the processes by their original IDs for reporting.

5. **Output**:
   - Metrics are displayed using `print_all`.
   - The Gantt chart is visualized using `print_gantt_chart`.

---

### Summary

This implementation efficiently handles **Shortest Job First Scheduling** by prioritizing processes with the shortest burst times. It ensures:
- Accurate handling of CPU idle periods.
- Proper tie-breaking for processes with the same burst time.
- Clear and detailed visualization of results and the Gantt chart.

The modular structure of the code makes it easy to follow, test, and debug, ensuring adaptability for different scheduling scenarios.
