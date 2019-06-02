#include <iostream>
#include <string>
#include <vector>
#include "process.h"

using namespace std;

class ProcessContainer {

    private:
        vector<Process> _list;

    public:
        ProcessContainer() {

        }

        void refreshList();
        string printList();
        vector<string> get_list();
};