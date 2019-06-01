#include <iostream>
#include <string>
#include <vector>
#include "ProcessParser.h"

using namespace std;

class SysInfo {
    private:
        vector<string> last_cpu_stats;
        vector<string> current_cpu_stats;
        vector<string> core_stats;
        vector<vector<string>> last_cpu_cores_stats;
        vector<vector<string>> current_cpu_cores_stats;
        string cpu_stats;
        float mem_percent;
        string os_name;
        string kernel_ver;
        long up_time;
        int total_proc;
        int running_proc;
        int threads;
};