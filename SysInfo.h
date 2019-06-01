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
    
    public:
        void set_attributes();
        void set_last_cpu_measures();
        string get_mem_percent() const;
        long get_up_time() const;
        string get_threads() const;
        string get_total_proc() const;
        string get_running_proc() const;
        string get_kernel_version() const;
        string get_os_name() const;
        string get_cpu_percent() const;
        void get_other_cores(int _size);
        void set_cpu_cores_stats();
        vector<string> get_cores_stats() const;
};