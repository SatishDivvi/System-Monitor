#ifndef Process_H
#define Process_H

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
        string get_cmd() const;
        // Getter for Cpu_utilization attribute
        string get_cpu_usage() const;
        // Getter for memory_utilization attribute
        string get_memory() const;
        // Getter for time attribute
        string get_up_time() const;
        // Getter for fetching process details
        string get_process() const;
};

void Process::set_PID(int pid) {
    this->PID = pid;
}

string Process::get_PID() const {
    return this->PID;
}

string Process::get_process() const {
    return(this->PID + "  " + this->user + "  " + this->memory.substr(0,5) + "  " + this->cpu_utilization.substr(0, 5) + "  " + 
    this->up_time.substr(0, 5) + "  " + this->cmd.substr(0, 30) + "...");
}

#endif

