#ifndef FCFS_SCHEDULER_H
#define FCFS_SCHEDULER_H

#include "scheduler.h"

/**
 * @class FCFSScheduler
 * @brief First Come First Serve scheduling algorithm implementation
 * 
 * Processes are executed in the order they arrive in the ready queue.
 * This is a non-preemptive algorithm where once a process gets the CPU,
 * it keeps it until it completes its CPU burst.
 */
class FCFSScheduler : public Scheduler {
public:
    /**
     * @brief Constructor for FCFSScheduler
     * @param processes List of processes to schedule
     */
    FCFSScheduler(const vector<Process>& processes);
    
    /**
     * @brief Runs the FCFS scheduling algorithm
     * @return SchedulerResult containing all metrics
     */
    SchedulerResult run() override;
    
    /**
     * @brief Gets the name of the scheduling algorithm
     * @return String name of the algorithm
     */
    string getName() const override;
    
    /**
     * @brief Gets the description of the scheduling algorithm
     * @return String description of the algorithm
     */
    string getDescription() const override;
};

#endif // FCFS_SCHEDULER_H