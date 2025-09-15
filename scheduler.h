#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include <string>
#include <map>
#include "process.h"

using namespace std;

/**
 * @struct SchedulerResult
 * @brief Contains the results of a scheduling simulation
 */
struct SchedulerResult {
    vector<pair<string, int>> ganttChart;  // Process ID and time slice pairs
    double avgTurnaroundTime;                            // Average turnaround time
    double avgWaitingTime;                               // Average waiting time
    double avgResponseTime;                              // Average response time
    double throughput;                                   // Processes per unit time
    double cpuUtilization;                               // Percentage of CPU utilization
};

/**
 * @class Scheduler
 * @brief Base class for all CPU scheduling algorithms
 */
class Scheduler {
protected:
    vector<Process> processes;                      // List of processes to schedule
    vector<pair<string, int>> ganttChart; // Timeline of process execution
    int currentTime;                                     // Current simulation time
    
    /**
     * @brief Calculates performance metrics after scheduling
     * @return SchedulerResult containing all metrics
     */
    SchedulerResult calculateMetrics();
    
    /**
     * @brief Resets all processes to their initial state
     */
    void resetProcesses();

public:
    /**
     * @brief Constructor for Scheduler
     * @param processes List of processes to schedule
     */
    Scheduler(const std::vector<Process>& processes);
    
    /**
     * @brief Virtual destructor
     */
    virtual ~Scheduler() = default;
    
    /**
     * @brief Pure virtual function to run the scheduling algorithm
     * @return SchedulerResult containing all metrics
     */
    virtual SchedulerResult run() = 0;
    
    /**
     * @brief Gets the name of the scheduling algorithm
     * @return String name of the algorithm
     */
    virtual string getName() const = 0;
    
    /**
     * @brief Gets the description of the scheduling algorithm
     * @return String description of the algorithm
     */
    virtual string getDescription() const = 0;
};

#endif // SCHEDULER_H