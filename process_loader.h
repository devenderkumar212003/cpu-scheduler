#ifndef PROCESS_LOADER_H
#define PROCESS_LOADER_H

#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include "process.h"

using namespace std;

/**
 * @class ProcessLoader
 * @brief Utility class to load process data from files
 */
class ProcessLoader {
public:
    /**
     * @brief Load processes from a CSV file
     * @param filePath Path to the CSV file
     * @return Vector of Process objects
     * 
     * CSV format: ID,ArrivalTime,BurstTime,Priority
     * Example: P1,0,5,2
     */
    static vector<Process> loadFromCSV(const string& filePath) {
        vector<Process> processes;
        ifstream file(filePath);
        
        if (!file.is_open()) {
            throw runtime_error("Failed to open file: " + filePath);
        }
        
        string line;
        // Skip header if present
        getline(file, line);
        
        while (getline(file, line)) {
            if (line.empty()) continue;
            
            // Parse CSV line
            size_t pos = 0;
            vector<string> tokens;
            string delimiter = ",";
            string token;
            string tempLine = line;
            
            while ((pos = tempLine.find(delimiter)) != string::npos) {
                token = tempLine.substr(0, pos);
                tokens.push_back(token);
                tempLine.erase(0, pos + delimiter.length());
            }
            tokens.push_back(tempLine); // Add the last token
            
            if (tokens.size() < 4) {
                continue; // Skip invalid lines
            }
            
            // Create Process object
            string id = tokens[0];
            int arrivalTime = stoi(tokens[1]);
            int burstTime = stoi(tokens[2]);
            int priority = stoi(tokens[3]);
            
            processes.push_back(Process(id, arrivalTime, burstTime, priority));
        }
        
        file.close();
        return processes;
    }
    
    /**
     * @brief Get list of available test case files in the test_cases directory
     * @return Vector of file paths
     */
    static vector<string> getAvailableTestCases() {
        vector<string> testCases;
        string testCasesDir = "test_cases";
        
        // In a real implementation, you would use filesystem functions
        // to list files in the directory. For simplicity, we'll just
        // return the known test case files.
        testCases.push_back(testCasesDir + "/small_processes.csv");
        testCases.push_back(testCasesDir + "/medium_processes.csv");
        testCases.push_back(testCasesDir + "/large_processes.csv");
        testCases.push_back(testCasesDir + "/random_processes.csv");
        testCases.push_back(testCasesDir + "/high_priority_processes.csv");
        
        return testCases;
    }
};

#endif // PROCESS_LOADER_H