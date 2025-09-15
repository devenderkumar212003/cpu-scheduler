#ifndef HRRN_SCHEDULER_H
#define HRRN_SCHEDULER_H

#include "scheduler.h"

/**
 * @class HRRNScheduler
 * @brief Highest Response Ratio Next scheduling algorithm implementation
 * 
 * A non-preemptive scheduling algorithm that selects the process with the highest response ratio.
 * Response Ratio = (Waiting Time + Burst Time) / Burst Time
 */
class HRRNScheduler : public Scheduler {
public:
    /**
     * @brief Constructor for HRRNScheduler
     * @param processes List of processes to schedule
     */
    HRRNScheduler(const vector<Process>& processes);
    
    /**
     * @brief Runs the HRRN scheduling algorithm
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
    
private:
    /**
     * @brief Calculates the response ratio for a process
     * @param process The process to calculate response ratio for
     * @param currentTime The current simulation time
     * @return The response ratio value
     */
    double calculateResponseRatio(const Process& process, int currentTime) const;
};

#endif // HRRN_SCHEDULER_H