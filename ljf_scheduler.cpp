#include "ljf_scheduler.h"
#include <algorithm>
#include <queue>
#include <limits>

LJFScheduler::LJFScheduler(const vector<Process>& processes, bool preemptive)
    : Scheduler(processes), preemptive(preemptive) {}

SchedulerResult LJFScheduler::run() {
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
        // Find the process with longest remaining time among arrived processes
        Process* longestJob = nullptr;
        int longestTime = -1;
        
        for (auto& process : processQueue) {
            if (process.getArrivalTime() <= currentTime && 
                process.getRemainingTime() > 0) {
                
                if (process.getRemainingTime() > longestTime) {
                    longestJob = &process;
                    longestTime = process.getRemainingTime();
                }
            }
        }
        
        // If we found a process to run
        if (longestJob != nullptr) {
            // For preemptive LJF, we always select the longest job
            // For non-preemptive LJF, we only switch if no process is currently running
            if (preemptive || currentProcess == nullptr) {
                // If we're switching to a new process
                if (currentProcess != longestJob) {
                    currentProcess = longestJob;
                    
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

string LJFScheduler::getName() const {
    if (preemptive) {
        return "Longest Remaining Time First (LRTF)";
    } else {
        return "Longest Job First (LJF)";
    }
}

string LJFScheduler::getDescription() const {
    if (preemptive) {
        return "A preemptive scheduling algorithm that selects the process with the longest remaining time. "
               "If a new process arrives with a longer burst time than the remaining time of the current process, "
               "the current process is preempted. Generally results in poor average waiting time.";
    } else {
        return "A non-preemptive scheduling algorithm that selects the process with the longest burst time. "
               "Once a process gets the CPU, it runs until completion. "
               "Generally results in poor average waiting time but may be useful in specific scenarios.";
    }
}