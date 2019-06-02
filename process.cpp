#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

class Process {

    private:
        string PID;
        string user;
        string cmd;
        string cpu_utilization;
        string memory;
        string up_time;
    
    public:
        // Default Constructor
        Process(){};
        // Setter for assigining values to class attributes.
        void setProcessAttributes(string pid, string user, string cmd, string cpu_utilization, string memory, string up_time);
        // Getter for PID Attribute
        string getPID() const;
        // Getter for user attribute
        string getUser() const;
        // Getter for cmd attribute
        string getCMD() const;
        // Getter for Cpu_utilization attribute
        string getCPUUsage() const;
        // Getter for memory_utilization attribute
        string getMemoryUsage() const;
        // Getter for time attribute
        string getUpTime() const;
};