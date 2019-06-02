#include <iostream>
#include <string>
#include "ProcessParser.h"
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
        Process(string pid){
            this->PID = pid;
            this->user = ProcessParser::get_proc_user(pid);
            this->cmd = ProcessParser::get_cmd(pid);
            this->cpu_utilization = ProcessParser::get_cpu_percent(pid);
            this->memory = ProcessParser::get_vm_size(pid);
            this->up_time = ProcessParser::get_proc_up_time(pid);
        };
        // Setter for assigining values to class attributes.
        void set_PID(int pid);
        // Getter for PID Attribute
        string get_PID() const;
        // Getter for user attribute
        string get_user() const;
        // Getter for cmd attribute
        string getCMD() const;
        // Getter for Cpu_utilization attribute
        string getCPUUsage() const;
        // Getter for memory_utilization attribute
        string getMemoryUsage() const;
        // Getter for time attribute
        string getUpTime() const;
};