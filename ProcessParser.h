#include <algorithm>
#include <iostream>
#include <math.h>
#include <thread>
#include <chrono>
#include <iterator>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cerrno>
#include <cstring>
#include <dirent.h>
#include <time.h>
#include <unistd.h>
#include "constants.h"
#include "util.h"

class ProcessParser {
    public:
        static std::string get_cmd(std::string pid);
        static std::vector<std::string> get_pid_list();
        static std::string get_vm_size(std::string pid);
        static std::string get_cpu_percent(std::string pid);
        static long int get_sys_up_time();
        static std::string get_proc_up_time(std::string pid);
        static std::string get_proc_user(std::string pid);
        static int get_no_of_cores();
        static std::vector<std::string> get_sys_cpu_percent(std::string coreNumber = "");
        static float get_sys_ram_percent();
        static std::string get_sys_kernel_version();
        static int get_total_threads();
        static int get_total_number_of_processes();
        static int get_number_of_running_processes();
        static string get_os_name();
        static std::string print_cpu_stats(std::vector<std::string> values1, std::vector<std::string>values2);
};

std::string ProcessParser::get_cmd(std::string pid){
    std::string line;
    ifstream readFile = Util::getStream((Path::basePath() + pid + Path::cmdPath()));
    std::getline(readFile, line);
    return line;
}

std::vector<std::string> ProcessParser::get_pid_list() {
    DIR* dir;
    dirent* entry;
    std::vector<std::string> pidLists;
    dir = opendir("/proc");
    if(!dir)
        throw std::runtime_error("No Directory Exists");
    while(entry = readdir(dir)){
        if(entry->d_type != DT_DIR){
            continue;
        }
        if(std::all_of(entry->d_name, entry->d_name + std::strlen(entry->d_name), [](char c){ return std::isdigit(c); })){
            pidLists.push_back(entry->d_name);
        }
    }
    if(closedir(dir))
        throw std::runtime_error(std::strerror(errno));
    return pidLists;
}

std::string ProcessParser::get_vm_size(std::string pid) {
    std::string line;
    string vm_data, total_size;
    float output;
    ifstream readFile = Util::getStream((Path::basePath() + pid + Path::memPath()));
    while(std::getline(readFile, line)){
        std::istringstream lines(line);
        if(lines >> vm_data >> total_size){
            if(vm_data=="VmData:"){
                output = (std::stof(total_size)/1024);
                break;
            }
            else {
                continue;
            }
                
        }
    }
    return std::to_string(output) + " MB";
}

std::string ProcessParser::get_cpu_percent(std::string pid) {
    std::string line;
    float cpu_percent;
    ifstream readFile = Util::getStream(Path::basePath() + pid + "/" + Path::statPath());
    std::getline(readFile, line);
    std::istringstream lines(line);
    std::istream_iterator<std::string> beg(lines), end;
    std::vector<std::string> statList (beg, end);
    float upTime = std::stof(ProcessParser::get_proc_up_time(pid));
    float kernelTime = std::stof(statList[14]);
    float cuTime = std::stof(statList[15]);
    float csTime = std::stof(statList[16]);
    float totalTime = upTime + kernelTime + cuTime + csTime;
    float startTime = std::stof(statList[21]);
    float sys_up_time = ProcessParser::get_sys_up_time();
    float seconds = sys_up_time - (startTime / sysconf(_SC_CLK_TCK));
    cpu_percent = 100.0 * ((totalTime / sysconf(_SC_CLK_TCK)) / seconds);
    return std::to_string(cpu_percent);
}

long int ProcessParser::get_sys_up_time() {
    std::string line;
    long int time;
    ifstream readFile = Util::getStream((Path::basePath() + Path::upTimePath()));
    std::getline(readFile, line);
    std::string uptime, freetime;
    std::istringstream lines(line);
    lines >> uptime >> freetime;
    time = std::stoi(uptime);
    return time;
}

std::string ProcessParser::get_proc_up_time(std::string pid) {
    std::string line;
    float output;
    ifstream readFile = Util::getStream(Path::basePath() + pid + "/" + Path::statPath());
    std::getline(readFile, line);
    std::istringstream lines(line);
    std::istream_iterator<std::string> beg(lines), end;
    std::vector<std::string> statList (beg, end);
    output = stof(statList[13])/sysconf(_SC_CLK_TCK);
    return std::to_string(output);
}

std::string ProcessParser::get_proc_user(std::string pid)  {
    std::string line;
    ifstream readFile = Util::getStream(Path::basePath() + pid + Path::statPath());
    std::string output;
    while(std::getline(readFile, line)){
        std::istringstream lines(line);
        std::string tag;
        std::string uid;
        lines >> tag >> uid;
        if(tag == "Uid:")
            output = "x:"+ uid;
            break;
    }

    readFile = Util::getStream("/etc/passwd");
    while(std::getline(readFile, line)){
         if(line.find(output) != -1) {
             output = line.substr(0, line.find(":"));
             return output;
         }
     }

     return "";
}

int ProcessParser::get_no_of_cores() {
    std::string line;
    ifstream readFile = Util::getStream(Path::basePath() + "cpuinfo");
    while(std::getline(readFile, line)){
        if(line.find("cpu cores") != -1) {
            std::istringstream lines(line);
            std::istream_iterator<std::string> beg(lines), end;
            std::vector<std::string> cpu_cores (beg, end);
            return std::stoi(cpu_cores[3]);
        }
    }
    return 0;
}

std::vector<std::string> ProcessParser::get_sys_cpu_percent(std::string coreNumber) {
    std::string line;
    ifstream readFile = Util::getStream(Path::basePath() + Path::statPath());
    while(std::getline(readFile, line)){
        if(line.find("cpu") != -1){
            std::istringstream lines(line);
            std::istream_iterator<std::string> beg(lines), end;
            std::vector<std::string> cpuStates (beg, end);
            return cpuStates;
        }
    }
    return std::vector<std::string>();
}

float get_sys_total_cpu_time(std::vector<std::string> cpuStates) {
    float s_user = std::stof(cpuStates[S_USER]);
    float s_nice = std::stof(cpuStates[S_NICE]);
    float s_system = std::stof(cpuStates[S_SYSTEM]);
    float s_idle = std::stof(cpuStates[S_IDLE]);
    float s_iowait = std::stof(cpuStates[S_IOWAIT]);
    float s_irq = std::stof(cpuStates[S_IRQ]);
    float s_softirq = std::stof(cpuStates[S_SOFTIRQ]);
    float s_steal = std::stof(cpuStates[S_STEAL]);
    float total_cpu_time = s_user + s_nice + s_system + s_idle + s_iowait + s_irq + s_softirq + s_steal;
    return total_cpu_time;
}

float get_sys_idle_cpu_time(std::vector<std::string> cpuStates) {
    float s_idle = std::stof(cpuStates[S_IDLE]);
    float s_iowait = std::stof(cpuStates[S_IOWAIT]);
    float idle_cpu_time = s_idle + s_iowait;
    return idle_cpu_time;
}

std::string ProcessParser::print_cpu_stats(std::vector<std::string> previous_time, std::vector<std::string> current_time) {
    float cpu_total_time = get_sys_total_cpu_time(current_time) - get_sys_total_cpu_time(previous_time);
    float cpu_idle_time = get_sys_idle_cpu_time(current_time) - get_sys_idle_cpu_time(previous_time);
    float cpu_active_time = cpu_total_time - cpu_idle_time;
    float sys_cpu_percent = 100.0 * (cpu_active_time / cpu_total_time);
    return std::to_string(sys_cpu_percent);
}

float ProcessParser::get_sys_ram_percent() {
    std::string line;
    ifstream readFile = Util::getStream(Path::basePath() + Path::memPath());
    float memAvailable = 0;
    float memFree = 0;
    float buffers = 0;
    float system_ram_percent;
    while(std::getline(readFile, line)){
        if(memAvailable != 0 && memFree != 0 && buffers !=0)
            break;
        if(line.find("MemAvailable:") != -1) {
            std::istringstream lines(line);
            std::string tag, value;
            lines >> tag >> value;
            memAvailable = stof(value);
        }
        if(line.find("MemFree:") != -1) {
            std::istringstream lines(line);
            std::string tag, value;
            lines >> tag >> value;
            memFree = stof(value);
        }
        if(line.find("Buffers:") != -1) {
            std::istringstream lines(line);
            std::string tag, value;
            lines >> tag >> value;
            buffers = stof(value);
        }
    }

    system_ram_percent = 100.0 * (memFree / (memAvailable - buffers));
    return system_ram_percent;
}

std::string ProcessParser::get_sys_kernel_version(){
    std::string line;
    ifstream readFile = Util::getStream(Path::basePath() + Path::versionPath());
    std::getline(readFile, line);
    if(line.find("Linux version") != -1) {
    	std::istringstream lines(line);
      	std::istream_iterator<std::string> beg(lines), end;
      	std::vector<std::string> versionList (beg, end);
      	return versionList[2];
    }
    return "";
}

int ProcessParser::get_total_threads(){
    std::string line;
    std::vector<std::string> pidList = ProcessParser::get_pid_list();
    int total_threads = 0;
    for(int i=0; i<pidList.size(); i++) {
        std::string pid = pidList[i];
        ifstream readFile = Util::getStream(Path::basePath() + pid + Path::statusPath());
        while(std::getline(readFile, line)){
            if(line.find("Thread") != -1) {
                std::istringstream lines(line);
                std::string tag, value;
                lines >> tag >> value;
                total_threads += std::stoi(value);
                break;
            }
        }
    }
    return total_threads;
}

int ProcessParser::get_total_number_of_processes() {
    std::string line;
    int total_processes = 0;
    ifstream readFile = Util::getStream(Path::basePath() + Path::statPath());
    while(std::getline(readFile, line)) {
        if(line.find("processes") != -1) {
            std::istringstream lines(line);
            std::string tag, value;
            lines >> tag >> value;
            total_processes = std::stoi(value);
            break;
        }
    }
    return total_processes;
}

int ProcessParser::get_number_of_running_processes() {
    std::string line;
    int total_running_processes = 0;
    ifstream readFile = Util::getStream(Path::basePath() + Path::statPath());
    while(std::getline(readFile, line)) {
        if(line.find("procs_running") != -1) {
            std::istringstream lines(line);
            std::string tag, value;
            lines >> tag >> value;
            total_running_processes = std::stoi(value);
            break;
        }
    }
    return total_running_processes;
}



std::string ProcessParser::get_os_name() {
    std::string line;
    ifstream readFile = Util::getStream("/etc/os-release");
    std::string os_name;
    while(std::getline(readFile, line)){
        if(line.find("PRETTY_NAME") != -1) {
            std::size_t seperator = line.find("=") + 1;
            os_name = line.substr(seperator);
            os_name.erase(std::remove(os_name.begin(), os_name.end(), '"'), os_name.end());
            break;
        }
    }
    return os_name;
}