#ifndef SJF_SCHEDULER_H
#define SJF_SCHEDULER_H

#include "scheduler.h"

/**
 * @class SJFScheduler
 * @brief Shortest Job First scheduling algorithm implementation
 * 
 * Processes are executed based on their burst time, with the shortest job getting priority.
 * This implementation supports both preemptive and non-preemptive modes.
 */
class SJFScheduler : public Scheduler {
private:
    bool preemptive; // Flag to determine if scheduler is preemptive

public:
    /**
     * @brief Constructor for SJFScheduler
     * @param processes List of processes to schedule
     * @param preemptive Flag to determine if scheduler is preemptive
     */
    SJFScheduler(const vector<Process>& processes, bool preemptive = false);
    
    /**
     * @brief Runs the SJF scheduling algorithm
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

#endif // SJF_SCHEDULER_H