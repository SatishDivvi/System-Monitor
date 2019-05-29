#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

class Process {

    private:
        int PID;
        string user;
        string cmd;
        double cpu_utilization;
        string memory_utilization;
        string time;
    
    public:
        // Default Constructor
        Process(){};
        // Setter for assigining values to class attributes.
        void setProcessAttributes(int pid, string user, string cmd, double cpu_utilization, string memory_utilization, string time);
        // Getter for PID Attribute
        int getPID() const;
        // Getter for user attribute
        string getUser() const;
        // Getter for cmd attribute
        string getCMD() const;
        // Getter for Cpu_utilization attribute
        double getCPUUsage() const;
        // Getter for memory_utilization attribute
        string getMemoryUsage() const;
        // Getter for time attribute
        string getTime() const;
};