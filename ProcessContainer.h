#ifndef ProcessContainer_H
#define ProcessContainer_H

#include <iostream>
#include <string>
#include <vector>
#include "process.h"
#include "ProcessParser.h"

using namespace std;

class ProcessContainer {

    private:
        vector<Process> _list;

    public:
        ProcessContainer() {
            this->refreshList();
        }

        void refreshList();
        string printList();
        vector<vector<string>> get_list();
};

void ProcessContainer::refreshList()
{
    vector<string> pids = ProcessParser::get_pid_list();
    this->_list.clear();
    for (auto pid : pids) {
        Process proc(pid);
        this->_list.push_back(proc);
    }
}

string ProcessContainer::printList()
{
    string result="";
    for (auto i : _list) {
        result += i.get_process();
    }
    return result;
}

vector<vector<string>> ProcessContainer::get_list(){
    vector<vector<string>> values;
    vector<string> stringifiedList;
    for(int i=0; i<ProcessContainer::_list.size(); i++){
        stringifiedList.push_back(ProcessContainer::_list[i].get_process());
    }
    int lastIndex = 0;
    for (int i=0; i<stringifiedList.size();i++){
        if(i %10 == 0 && i > 0){
          vector<string>  sub(&stringifiedList[i-10], &stringifiedList[i]);
          values.push_back(sub);
          lastIndex = i;
        }
        if(i == (ProcessContainer::_list.size() - 1) && (i-lastIndex)<10){
            vector<string> sub(&stringifiedList[lastIndex],&stringifiedList[i+1]);
            values.push_back(sub);
        }
   }
    return values;
}

#endif
