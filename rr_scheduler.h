#ifndef RR_SCHEDULER_H
#define RR_SCHEDULER_H

#include "scheduler.h"

/**
 * @class RRScheduler
 * @brief Round Robin scheduling algorithm implementation
 * 
 * Processes are executed in a circular queue with a fixed time quantum.
 * This is a preemptive algorithm where each process gets a fixed time slice.
 */
class RRScheduler : public Scheduler {
private:
    int timeQuantum; // Time slice allocated to each process

public:
    /**
     * @brief Constructor for RRScheduler
     * @param processes List of processes to schedule
     * @param timeQuantum Time slice allocated to each process
     */
    RRScheduler(const vector<Process>& processes, int timeQuantum);
    
    /**
     * @brief Runs the RR scheduling algorithm
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

#endif // RR_SCHEDULER_H