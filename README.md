# CPU Scheduling Simulator

This project implements various CPU scheduling algorithms to simulate and compare their performance metrics.

## Implemented Algorithms

1. **First Come First Serve (FCFS)**
   - Non-preemptive algorithm that executes processes in order of arrival

2. **Shortest Job First (SJF)**
   - Non-preemptive version: Selects the process with the shortest burst time
   - Preemptive version (SRTF): Preempts when a process with shorter remaining time arrives

3. **Round Robin (RR)**
   - Preemptive algorithm that allocates CPU to each process for a fixed time quantum

4. **Priority Scheduling**
   - Non-preemptive version: Selects the process with the highest priority
   - Preemptive version: Preempts when a process with higher priority arrives

5. **Longest Job First (LJF)**
   - Non-preemptive version: Selects the process with the longest burst time
   - Preemptive version (LRTF): Preempts when a process with longer remaining time arrives

6. **Highest Response Ratio Next (HRRN)**
   - Non-preemptive algorithm that selects the process with the highest response ratio
   - Response Ratio = (Waiting Time + Burst Time) / Burst Time

## Compilation

### Using Make

If you have `make` installed, simply run:

```bash
make
```

This will compile all source files and create an executable named `cpu_scheduler`.

### Manual Compilation

If you don't have `make`, you can compile manually using g++:

```bash
g++ -std=c++11 -Wall -Wextra -o cpu_scheduler main.cpp process.cpp scheduler.cpp fcfs_scheduler.cpp sjf_scheduler.cpp rr_scheduler.cpp priority_scheduler.cpp ljf_scheduler.cpp hrrn_scheduler.cpp
```

## Running the Simulator

After compilation, run the executable:

```bash
./cpu_scheduler  # On Linux/macOS
```

Or on Windows:

```bash
cpu_scheduler.exe
```

## Output

The program will run all implemented scheduling algorithms on a set of sample processes and display:

- Average Turnaround Time
- Average Waiting Time
- Average Response Time
- CPU Utilization
- Gantt Chart visualization

## Customizing Processes

To customize the processes being simulated, modify the `processes` vector in `main.cpp`. Each process has:

- ID: A unique identifier
- Arrival Time: When the process arrives in the ready queue
- Burst Time: Total CPU time required
- Priority: Priority value (lower number means higher priority)

## Project Structure

- `process.h/cpp`: Process class definition and implementation
- `scheduler.h/cpp`: Base Scheduler class with common functionality
- `*_scheduler.h/cpp`: Specific algorithm implementations
- `main.cpp`: Sample usage and comparison of algorithms