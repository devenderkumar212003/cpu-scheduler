#ifndef PRIORITY_SCHEDULER_H
#define PRIORITY_SCHEDULER_H

#include "scheduler.h"

/**
 * @class PriorityScheduler
 * @brief Priority scheduling algorithm implementation
 * 
 * Processes are executed based on their priority, with lower priority values indicating higher priority.
 * This implementation supports both preemptive and non-preemptive modes.
 */
class PriorityScheduler : public Scheduler {
private:
    bool preemptive; // Flag to determine if scheduler is preemptive

public:
    /**
     * @brief Constructor for PriorityScheduler
     * @param processes List of processes to schedule
     * @param preemptive Flag to determine if scheduler is preemptive
     */
    PriorityScheduler(const vector<Process>& processes, bool preemptive = false);
    
    /**
     * @brief Runs the Priority scheduling algorithm
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

#endif // PRIORITY_SCHEDULER_H