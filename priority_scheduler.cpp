#include "priority_scheduler.h"
#include <algorithm>
#include <queue>
#include <limits>

PriorityScheduler::PriorityScheduler(const vector<Process>& processes, bool preemptive)
    : Scheduler(processes), preemptive(preemptive) {}

SchedulerResult PriorityScheduler::run() {
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
        // Find the process with highest priority (lowest priority value) among arrived processes
        Process* highestPriorityProcess = nullptr;
        int highestPriority = numeric_limits<int>::max();
        
        for (auto& process : processQueue) {
            if (process.getArrivalTime() <= currentTime && 
                process.getRemainingTime() > 0) {
                
                if (process.getPriority() < highestPriority) {
                    highestPriorityProcess = &process;
                    highestPriority = process.getPriority();
                }
            }
        }
        
        // If we found a process to run
        if (highestPriorityProcess != nullptr) {
            // For preemptive Priority, we always select the highest priority job
            // For non-preemptive Priority, we only switch if no process is currently running
            if (preemptive || currentProcess == nullptr) {
                // If we're switching to a new process
                if (currentProcess != highestPriorityProcess) {
                    currentProcess = highestPriorityProcess;
                    
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

string PriorityScheduler::getName() const {
    if (preemptive) {
        return "Priority Scheduling (Preemptive)";
    } else {
        return "Priority Scheduling (Non-Preemptive)";
    }
}

string PriorityScheduler::getDescription() const {
    if (preemptive) {
        return "A preemptive scheduling algorithm that selects the process with the highest priority (lowest priority value). "
               "If a new process arrives with a higher priority than the current process, "
               "the current process is preempted. Can lead to starvation of low-priority processes.";
    } else {
        return "A non-preemptive scheduling algorithm that selects the process with the highest priority (lowest priority value). "
               "Once a process gets the CPU, it runs until completion. "
               "Can lead to starvation of low-priority processes if high-priority processes keep arriving.";
    }
}