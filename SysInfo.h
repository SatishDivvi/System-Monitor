#ifndef SysInfo_H
#define SysInfo_H

#include <iostream>
#include <string>
#include <vector>
#include "ProcessParser.h"

using namespace std;

class SysInfo {
    private:
        vector<string> last_cpu_stats;
        vector<string> current_cpu_stats;
        vector<string> cores_stats;
        vector<vector<string>> last_cpu_cores_stats;
        vector<vector<string>> current_cpu_cores_stats;
        string cpu_percent;
        float mem_percent;
        string os_name;
        string kernel_ver;
        long up_time;
        int total_proc;
        int running_proc;
        int threads;
    
    public:
        SysInfo() {
            this->get_other_cores(ProcessParser::get_no_of_cores());
            this->set_last_cpu_measures();
            this->set_attributes();
            this->os_name = ProcessParser::get_os_name();
            this->kernel_ver = ProcessParser::get_sys_kernel_version();
        };
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

string SysInfo::get_cpu_percent() const {
    return this->cpu_percent;
}

string SysInfo::get_mem_percent() const {
    return to_string(this->mem_percent);
}

string SysInfo::get_os_name() const {
    return this->os_name;
}

string SysInfo::get_kernel_version() const {
    return this->kernel_ver;
}

long SysInfo::get_up_time() const {
    return this->up_time;
}

string SysInfo::get_total_proc() const {
    return to_string(this->total_proc);
}

string SysInfo::get_running_proc() const {
    return to_string(this->running_proc);
}

string SysInfo::get_threads() const {
    return to_string(this->threads);
}

void SysInfo::set_last_cpu_measures() {
    this->last_cpu_stats = ProcessParser::get_sys_cpu_percent();
}

void SysInfo::get_other_cores(int _size) {
    this->cores_stats = vector<string>();
    this->cores_stats.resize(_size);
    this->last_cpu_cores_stats = vector<vector<string>>();
    this->last_cpu_cores_stats.resize(_size);
    this->current_cpu_cores_stats = vector<vector<string>>();
    this->current_cpu_cores_stats.resize(_size);
    for(int i=0; i<_size; i++) {
        this->last_cpu_cores_stats[i] = ProcessParser::get_sys_cpu_percent(to_string(i));
    }
}

void SysInfo::set_cpu_cores_stats() {
    for(int i=0; i < this->current_cpu_cores_stats.size(); i++) {
        this->current_cpu_cores_stats[i] = ProcessParser::get_sys_cpu_percent(to_string(i));
    }

    for(int i=0; i < this->current_cpu_cores_stats.size(); i++) {
        this->cores_stats[i] = ProcessParser::print_cpu_stats(this->last_cpu_cores_stats[i], this->current_cpu_cores_stats[i]);
    }

    this->last_cpu_cores_stats = this->current_cpu_cores_stats;
}

void SysInfo::set_attributes() {
    this->mem_percent = ProcessParser::get_sys_ram_percent();
    this->up_time = ProcessParser::get_sys_up_time();
    this->total_proc = ProcessParser::get_total_number_of_processes();
    this->running_proc = ProcessParser::get_number_of_running_processes();
    this->threads = ProcessParser::get_total_threads();
    this->current_cpu_stats = ProcessParser::get_sys_cpu_percent();
    this->cpu_percent = ProcessParser::print_cpu_stats(this->last_cpu_stats, this->current_cpu_stats);
    this->last_cpu_stats = this->current_cpu_stats;
    this->set_cpu_cores_stats();
}

vector<string> SysInfo::get_cores_stats() const
{
    vector<string> result = vector<string>();
    for (int i = 0; i < this->cores_stats.size() ;i++) {
        string temp = ("cpu" + to_string(i) +": ");
        float check = stof(this->cores_stats[i]);
        if (!check || this->cores_stats[i] == "nan") {
            return vector<string>();
        }
        temp += Util::getProgressBar(this->cores_stats[i]);
        result.push_back(temp);
    }
    return result;
}

#endif