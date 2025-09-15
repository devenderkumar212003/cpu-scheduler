#include "scheduler.h"
#include <numeric>

Scheduler::Scheduler(const vector<Process>& processes)
    : processes(processes), currentTime(0) {}

SchedulerResult Scheduler::calculateMetrics() {
    SchedulerResult result;
    result.ganttChart = ganttChart;
    
    // Calculate average metrics
    double totalTurnaroundTime = 0;
    double totalWaitingTime = 0;
    double totalResponseTime = 0;
    
    for (const auto& process : processes) {
        totalTurnaroundTime += process.getTurnaroundTime();
        totalWaitingTime += process.getWaitingTime();
        totalResponseTime += process.getResponseTime();
    }
    
    int numProcesses = processes.size();
    result.avgTurnaroundTime = totalTurnaroundTime / numProcesses;
    result.avgWaitingTime = totalWaitingTime / numProcesses;
    result.avgResponseTime = totalResponseTime / numProcesses;
    
    // Calculate throughput (processes per unit time)
    int totalTime = currentTime > 0 ? currentTime : 1; // Avoid division by zero
    result.throughput = static_cast<double>(numProcesses) / totalTime;
    
    // Calculate CPU utilization
    int totalBurstTime = 0;
    for (const auto& process : processes) {
        totalBurstTime += process.getBurstTime();
    }
    
    result.cpuUtilization = static_cast<double>(totalBurstTime) / totalTime * 100.0;
    
    return result;
}

void Scheduler::resetProcesses() {
    for (auto& process : processes) {
        process.reset();
    }
    currentTime = 0;
    ganttChart.clear();
}