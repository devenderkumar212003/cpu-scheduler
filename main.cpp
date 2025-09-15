#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

#include "process.h"
#include "process_loader.h"
#include "fcfs_scheduler.h"
#include "sjf_scheduler.h"
#include "rr_scheduler.h"
#include "priority_scheduler.h"
#include "ljf_scheduler.h"
#include "hrrn_scheduler.h"

using namespace std;

// Function to print scheduler results
void printResults(const string& algorithmName, const SchedulerResult& result) {
    cout << "\n===== " << algorithmName << " =====" << endl;
    cout << "Average Turnaround Time: " << fixed << setprecision(2) << result.avgTurnaroundTime << endl;
    cout << "Average Waiting Time: " << fixed << setprecision(2) << result.avgWaitingTime << endl;
    cout << "Average Response Time: " << fixed << setprecision(2) << result.avgResponseTime << endl;
    cout << "CPU Utilization: " << fixed << setprecision(2) << result.cpuUtilization << "%" << endl;
    
    cout << "\nGantt Chart:" << endl;
    cout << "|";
    for (const auto& entry : result.ganttChart) {
        cout << " " << entry.first << " |";
    }
    cout << "\n|";
    for (const auto& entry : result.ganttChart) {
        cout << " " << entry.second << " |";
    }
    cout << "\n" << endl;
}

// Function to display the menu and get user choice
int displayMenu() {
    int choice;
    cout << "\n===== CPU Scheduling Simulator =====\n";
    cout << "Select a test case file:\n";
    
    vector<string> testCases = ProcessLoader::getAvailableTestCases();
    for (size_t i = 0; i < testCases.size(); i++) {
        cout << i + 1 << ". " << testCases[i] << "\n";
    }
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;
    
    return choice;
}

int main() {
    while (true) {
        int choice = displayMenu();
        if (choice == 0) {
            cout << "Exiting...\n";
            break;
        }
        
        vector<string> testCases = ProcessLoader::getAvailableTestCases();
        if (choice < 1 || choice > static_cast<int>(testCases.size())) {
            cout << "Invalid choice. Please try again.\n";
            continue;
        }
        
        string selectedFile = testCases[choice - 1];
        cout << "\nLoading processes from: " << selectedFile << "\n";
        
        // Load processes from the selected file
        vector<Process> processes;
        try {
            processes = ProcessLoader::loadFromCSV(selectedFile);
            cout << "Loaded " << processes.size() << " processes.\n";
        } catch (const exception& e) {
            cout << "Error: " << e.what() << "\n";
            continue;
        }
        
        if (processes.empty()) {
            cout << "No processes loaded. Please select another file.\n";
            continue;
        }
    
    // Run different scheduling algorithms
    
    // 1. First Come First Serve (FCFS)
    FCFSScheduler fcfs(processes);
    SchedulerResult fcfsResult = fcfs.run();
    printResults(fcfs.getName(), fcfsResult);
    
    // 2. Shortest Job First (SJF) - Non-preemptive
    SJFScheduler sjf(processes, false);
    SchedulerResult sjfResult = sjf.run();
    printResults(sjf.getName(), sjfResult);
    
    // 3. Shortest Job First (SJF) - Preemptive (SRTF)
    SJFScheduler srtf(processes, true);
    SchedulerResult srtfResult = srtf.run();
    printResults(srtf.getName(), srtfResult);
    
    // 4. Round Robin (RR) with time quantum = 2
    RRScheduler rr(processes, 2);
    SchedulerResult rrResult = rr.run();
    printResults(rr.getName(), rrResult);
    
    // 5. Priority Scheduling - Non-preemptive
    PriorityScheduler ps(processes, false);
    SchedulerResult psResult = ps.run();
    printResults(ps.getName(), psResult);
    
    // 6. Priority Scheduling - Preemptive
    PriorityScheduler pps(processes, true);
    SchedulerResult ppsResult = pps.run();
    printResults(pps.getName(), ppsResult);
    
    // 7. Longest Job First (LJF) - Non-preemptive
    LJFScheduler ljf(processes, false);
    SchedulerResult ljfResult = ljf.run();
    printResults(ljf.getName(), ljfResult);
    
    // 8. Longest Job First (LJF) - Preemptive (LRTF)
    LJFScheduler lrtf(processes, true);
    SchedulerResult lrtfResult = lrtf.run();
    printResults(lrtf.getName(), lrtfResult);
    
    // 9. Highest Response Ratio Next (HRRN)
    HRRNScheduler hrrn(processes);
    SchedulerResult hrrnResult = hrrn.run();
    printResults(hrrn.getName(), hrrnResult);
    
    }
    return 0;
}