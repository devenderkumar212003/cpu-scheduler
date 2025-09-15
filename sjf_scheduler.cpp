#include "sjf_scheduler.h"
#include <algorithm>
#include <queue>
#include <limits>

SJFScheduler::SJFScheduler(const vector<Process>& processes, bool preemptive)
    : Scheduler(processes), preemptive(preemptive) {}

SchedulerResult SJFScheduler::run() {
    // Reset all processes and simulation time
    resetProcesses();
    
    // Create a copy of processes to work with
    vector<Process> processQueue = processes;
    
    // Sort processes by arrival time initially
    sort(processQueue.begin(), processQueue.end(), 
         [](const Process& a, const Process& b) {
             return a.getArrivalTime() < b.getArrivalTime();
         });
    
    // Current running process
    Process* currentProcess = nullptr;
    
    // Track remaining processes
    size_t completedProcesses = 0;
    size_t totalProcesses = processQueue.size();
    
    // Main scheduling loop
    while (completedProcesses < totalProcesses) {
        // Find the process with shortest remaining time among arrived processes
        Process* shortestJob = nullptr;
        int shortestTime = numeric_limits<int>::max();
        
        for (auto& process : processQueue) {
            if (process.getArrivalTime() <= currentTime && 
                process.getRemainingTime() > 0) {
                
                if (process.getRemainingTime() < shortestTime) {
                    shortestJob = &process;
                    shortestTime = process.getRemainingTime();
                }
            }
        }
        
        // If we found a process to run
        if (shortestJob != nullptr) {
            // For preemptive SJF (SRTF), we always select the shortest job
            // For non-preemptive SJF, we only switch if no process is currently running
            if (preemptive || currentProcess == nullptr) {
                // If we're switching to a new process
                if (currentProcess != shortestJob) {
                    currentProcess = shortestJob;
                    
                    // Set response time if this is the first time process gets CPU
                    if (!currentProcess->hasStarted()) {
                        currentProcess->setResponseTime(currentTime - currentProcess->getArrivalTime());
                    }
                }
            }
            
            // Execute process for 1 time unit
            int remaining = currentProcess->execute(1);
            
            // Add to Gantt chart
            ganttChart.push_back({currentProcess->getId(), currentTime});
            
            // If process is completed
            if (remaining == 0) {
                currentProcess->setCompletionTime(currentTime + 1);
                completedProcesses++;
                currentProcess = nullptr;
            }
        } else {
            // CPU is idle
            ganttChart.push_back({"IDLE", currentTime});
        }
        
        // Advance simulation time
        currentTime++;
    }
    
    // Calculate and return metrics
    return calculateMetrics();
}

string SJFScheduler::getName() const {
    if (preemptive) {
        return "Shortest Remaining Time First (SRTF)";
    } else {
        return "Shortest Job First (SJF)";
    }
}

string SJFScheduler::getDescription() const {
    if (preemptive) {
        return "A preemptive scheduling algorithm that selects the process with the shortest remaining time. "
               "If a new process arrives with a shorter burst time than the remaining time of the current process, "
               "the current process is preempted. Optimal for minimizing average waiting time.";
    } else {
        return "A non-preemptive scheduling algorithm that selects the process with the shortest burst time. "
               "Once a process gets the CPU, it runs until completion. "
               "Provides better average waiting time than FCFS but requires knowledge of burst times.";
    }
}