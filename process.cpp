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
};