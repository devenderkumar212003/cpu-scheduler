#include "hrrn_scheduler.h"
#include <algorithm>
#include <limits>

HRRNScheduler::HRRNScheduler(const vector<Process>& processes)
    : Scheduler(processes) {}

double HRRNScheduler::calculateResponseRatio(const Process& process, int currentTime) const {
    // Response Ratio = (Waiting Time + Burst Time) / Burst Time
    // Waiting Time = Current Time - Arrival Time
    int waitingTime = currentTime - process.getArrivalTime();
    
    // Ensure waiting time is not negative
    waitingTime = waitingTime > 0 ? waitingTime : 0;
    
    // Calculate response ratio
    return (waitingTime + process.getBurstTime()) / static_cast<double>(process.getBurstTime());
}

SchedulerResult HRRNScheduler::run() {
    // Reset all processes and simulation time
    resetProcesses();
    
    // Create a copy of processes to work with
    vector<Process> processQueue = processes;
    
    // Sort processes by arrival time initially
    sort(processQueue.begin(), processQueue.end(), 
         [](const Process& a, const Process& b) {
             return a.getArrivalTime() < b.getArrivalTime();
         });
    
    // Track remaining processes
    size_t completedProcesses = 0;
    size_t totalProcesses = processQueue.size();
    
    // Main scheduling loop
    while (completedProcesses < totalProcesses) {
        // Find the process with highest response ratio among arrived processes
        Process* selectedProcess = nullptr;
        double highestRatio = -1.0;
        
        for (auto& process : processQueue) {
            if (process.getArrivalTime() <= currentTime && 
                process.getRemainingTime() > 0) {
                
                double ratio = calculateResponseRatio(process, currentTime);
                
                if (ratio > highestRatio) {
                    selectedProcess = &process;
                    highestRatio = ratio;
                }
            }
        }
        
        // If we found a process to run
        if (selectedProcess != nullptr) {
            // Set response time if this is the first time process gets CPU
            if (!selectedProcess->hasStarted()) {
                selectedProcess->setResponseTime(currentTime - selectedProcess->getArrivalTime());
            }
            
            // Since HRRN is non-preemptive, execute the process until completion
            int burstTime = selectedProcess->getRemainingTime();
            
            // Add to Gantt chart for each time unit
            for (int i = 0; i < burstTime; i++) {
                ganttChart.push_back({selectedProcess->getId(), currentTime + i});
            }
            
            // Execute the process for its full burst time
            selectedProcess->execute(burstTime);
            
            // Update completion time
            selectedProcess->setCompletionTime(currentTime + burstTime);
            
            // Update simulation time
            currentTime += burstTime;
            
            // Increment completed processes counter
            completedProcesses++;
        } else {
            // No process available at current time, advance time to next arrival
            int nextArrival = numeric_limits<int>::max();
            
            for (const auto& process : processQueue) {
                if (process.getArrivalTime() > currentTime && 
                    process.getRemainingTime() > 0 && 
                    process.getArrivalTime() < nextArrival) {
                    nextArrival = process.getArrivalTime();
                }
            }
            
            // If there are no more arrivals, something went wrong
            if (nextArrival == numeric_limits<int>::max()) {
                break;
            }
            
            // Add idle time to Gantt chart
            for (int i = currentTime; i < nextArrival; i++) {
                ganttChart.push_back({"IDLE", i});
            }
            
            // Jump to next arrival time
            currentTime = nextArrival;
        }
    }
    
    // Calculate and return metrics
    return calculateMetrics();
}

string HRRNScheduler::getName() const {
    return "Highest Response Ratio Next (HRRN)";
}

string HRRNScheduler::getDescription() const {
    return "A non-preemptive scheduling algorithm that selects the process with the highest response ratio. "
           "Response Ratio = (Waiting Time + Burst Time) / Burst Time. "
           "It balances between SJF and FCFS by considering both burst time and waiting time.";
}