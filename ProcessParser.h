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
    std::string output;
    ifstream readFile = Util::getStream(Path::basePath() + pid + "/" + Path::statPath());
    std::getline(readFile, line);
    std::istringstream lines(line);
    std::istream_iterator<std::string> beg(lines), end;
    std::vector<std::string> statList (beg, end);
    output = stof(statList[13])/sysconf(_SC_CLK_TCK);
    return output;
}