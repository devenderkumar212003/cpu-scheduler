#include "process.h"
#include <algorithm>

Process::Process(string id, int arrivalTime, int burstTime, int priority, int deadline)
    : id(id), arrivalTime(arrivalTime), burstTime(burstTime), remainingTime(burstTime),
      priority(priority), deadline(deadline), completionTime(0), turnaroundTime(0),
      waitingTime(0), responseTime(-1), started(false) {}

// Getters
string Process::getId() const { return id; }
int Process::getArrivalTime() const { return arrivalTime; }
int Process::getBurstTime() const { return burstTime; }
int Process::getRemainingTime() const { return remainingTime; }
int Process::getPriority() const { return priority; }
int Process::getDeadline() const { return deadline; }
int Process::getCompletionTime() const { return completionTime; }
int Process::getTurnaroundTime() const { return turnaroundTime; }
int Process::getWaitingTime() const { return waitingTime; }
int Process::getResponseTime() const { return responseTime; }
bool Process::hasStarted() const { return started; }

// Setters
void Process::setCompletionTime(int time) {
    completionTime = time;
    turnaroundTime = completionTime - arrivalTime;
    waitingTime = turnaroundTime - burstTime;
}

void Process::setTurnaroundTime(int time) {
    turnaroundTime = time;
}

void Process::setWaitingTime(int time) {
    waitingTime = time;
}

void Process::setResponseTime(int time) {
    responseTime = time;
}

int Process::execute(int time) {
    if (!started) {
        started = true;
    }
    
    int executed = min(time, remainingTime);
    remainingTime -= executed;
    return remainingTime;
}

double Process::getResponseRatio(int currentTime) const {
    int waitTime = currentTime - arrivalTime;
    return (waitTime + burstTime) / static_cast<double>(burstTime);
}

void Process::reset() {
    remainingTime = burstTime;
    completionTime = 0;
    turnaroundTime = 0;
    waitingTime = 0;
    responseTime = -1;
    started = false;
}