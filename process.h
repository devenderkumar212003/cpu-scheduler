#ifndef PROCESS_H
#define PROCESS_H

#include <string>

using namespace std;

/**
 * @class Process
 * @brief Represents a process in the CPU scheduling simulation
 */
class Process {
private:
    string id;        // Process ID
    int arrivalTime;       // Time at which process arrives
    int burstTime;         // Total CPU time required
    int remainingTime;     // Remaining CPU time needed
    int priority;          // Priority level (lower value means higher priority)
    int deadline;          // Deadline for EDF scheduling
    
    // Metrics
    int completionTime;    // Time at which process completes execution
    int turnaroundTime;    // Completion time - Arrival time
    int waitingTime;       // Turnaround time - Burst time
    int responseTime;      // Time at which process first gets CPU - Arrival time
    bool started;          // Flag to track if process has started execution

public:
    /**
     * @brief Constructor for Process
     * @param id Process identifier
     * @param arrivalTime Time at which process arrives
     * @param burstTime Total CPU time required
     * @param priority Priority level (lower value means higher priority)
     * @param deadline Deadline for EDF scheduling
     */
    Process(std::string id, int arrivalTime, int burstTime, int priority = 0, int deadline = 0);
    
    // Getters
    string getId() const;
    int getArrivalTime() const;
    int getBurstTime() const;
    int getRemainingTime() const;
    int getPriority() const;
    int getDeadline() const;
    int getCompletionTime() const;
    int getTurnaroundTime() const;
    int getWaitingTime() const;
    int getResponseTime() const;
    bool hasStarted() const;
    
    // Setters
    void setCompletionTime(int time);
    void setTurnaroundTime(int time);
    void setWaitingTime(int time);
    void setResponseTime(int time);
    
    /**
     * @brief Executes the process for a given time quantum
     * @param time Time quantum to execute
     * @return Remaining time after execution
     */
    int execute(int time);
    
    /**
     * @brief Calculates the response ratio for HRRN scheduling
     * @param currentTime Current simulation time
     * @return Response ratio value
     */
    double getResponseRatio(int currentTime) const;
    
    /**
     * @brief Resets the process to its initial state
     */
    void reset();
};

#endif // PROCESS_H