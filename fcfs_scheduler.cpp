#include "fcfs_scheduler.h"
#include <algorithm>
#include <queue>

FCFSScheduler::FCFSScheduler(const vector<Process>& processes)
    : Scheduler(processes) {}

SchedulerResult FCFSScheduler::run() {
    // Reset all processes and simulation time
    resetProcesses();
    
    // Create a copy of processes to work with
    vector<Process> processQueue = processes;
    
    // Sort processes by arrival time
    sort(processQueue.begin(), processQueue.end(), 
         [](const Process& a, const Process& b) {
             return a.getArrivalTime() < b.getArrivalTime();
         });
    
    // Ready queue for processes that have arrived
    queue<Process*> readyQueue;
    
    // Current running process
    Process* currentProcess = nullptr;
    
    // Track remaining processes
    size_t completedProcesses = 0;
    size_t totalProcesses = processQueue.size();
    
    // Main scheduling loop
    while (completedProcesses < totalProcesses) {
        // Check for newly arrived processes
        for (auto& process : processQueue) {
            if (process.getArrivalTime() <= currentTime && 
                process.getRemainingTime() > 0 && 
                !process.hasStarted()) {
                readyQueue.push(&process);
            }
        }
        
        // If no current process, get the next one from ready queue
        if (currentProcess == nullptr && !readyQueue.empty()) {
            currentProcess = readyQueue.front();
            readyQueue.pop();
            
            // Set response time if this is the first time process gets CPU
            if (currentProcess->getResponseTime() == -1) {
                currentProcess->setResponseTime(currentTime - currentProcess->getArrivalTime());
            }
        }
        
        // If we have a process to run
        if (currentProcess != nullptr) {
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

string FCFSScheduler::getName() const {
    return "First Come First Serve (FCFS)";
}

string FCFSScheduler::getDescription() const {
    return "A non-preemptive scheduling algorithm that executes processes in the order they arrive. "
           "Once a process gets the CPU, it runs until completion. "
           "Simple to implement but may cause convoy effect where short processes wait behind long ones.";
}