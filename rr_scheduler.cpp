#include "rr_scheduler.h"
#include <algorithm>
#include <queue>

RRScheduler::RRScheduler(const vector<Process>& processes, int timeQuantum)
    : Scheduler(processes), timeQuantum(timeQuantum) {}

SchedulerResult RRScheduler::run() {
    // Reset all processes and simulation time
    resetProcesses();
    
    // Create a copy of processes to work with
    vector<Process> processQueue = processes;
    
    // Sort processes by arrival time initially
    sort(processQueue.begin(), processQueue.end(), 
         [](const Process& a, const Process& b) {
             return a.getArrivalTime() < b.getArrivalTime();
         });
    
    // Ready queue for processes that have arrived
    queue<Process*> readyQueue;
    
    // Current running process
    Process* currentProcess = nullptr;
    
    // Time left in current time quantum
    int remainingQuantum = 0;
    
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
        
        // If current process has finished its time quantum or is completed
        if (currentProcess != nullptr && 
            (remainingQuantum == 0 || currentProcess->getRemainingTime() == 0)) {
            
            // If process still has work to do, put it back in the ready queue
            if (currentProcess->getRemainingTime() > 0) {
                readyQueue.push(currentProcess);
            } else {
                // Process is completed
                currentProcess->setCompletionTime(currentTime);
                completedProcesses++;
            }
            
            // Reset current process
            currentProcess = nullptr;
            remainingQuantum = 0;
        }
        
        // If no current process, get the next one from ready queue
        if (currentProcess == nullptr && !readyQueue.empty()) {
            currentProcess = readyQueue.front();
            readyQueue.pop();
            remainingQuantum = timeQuantum;
            
            // Set response time if this is the first time process gets CPU
            if (!currentProcess->hasStarted()) {
                currentProcess->setResponseTime(currentTime - currentProcess->getArrivalTime());
            }
        }
        
        // If we have a process to run
        if (currentProcess != nullptr) {
            // Execute process for 1 time unit
            currentProcess->execute(1);
            remainingQuantum--;
            
            // Add to Gantt chart
            ganttChart.push_back({currentProcess->getId(), currentTime});
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

string RRScheduler::getName() const {
    return "Round Robin (RR)";
}

string RRScheduler::getDescription() const {
    return "A preemptive scheduling algorithm that allocates a fixed time quantum to each process in a circular queue. "
           "If a process doesn't complete within its time quantum, it's preempted and placed at the back of the ready queue. "
           "Provides fair CPU sharing and good response time for interactive systems.";
}