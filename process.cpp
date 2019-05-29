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
        int getPID() const;
        string getUser() const;
        string getCMD() const;
        double getCPUUsage() const;
        string getMemoryUsage() const;
};