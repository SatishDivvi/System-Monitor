# System Monitor

### Introduction:

System Monitor is a C++ based Process Monitor which stores system resources and processes metadata and displays information on the screen very much like [**htop - An Intereactive Process Viewer**](https://hisham.hm/htop/).

### Installation:

1. Clone the repository using command `git clone https://github.com/SatishDivvi/System-Monitor.git`.
2. Install **ncurses** package using command `sudo apt-get install libncurses5-dev libncursesw5-dev`.

**Note:** _For Step-2 to successfully execute make sure you are in GPU Mode._ 

### Project Execution:

1. Compile `SystemMonitor.cpp` file by executing command `g++ -std=c++17 SystemMonitor.cpp -lncurses`.
2. Execute command `./a.out`.
3. System Monitor should now be displayed on the screen.

**Note:** _For **Step-1** command line argument `-lncurses` is required as the program will throw compile error without it's presence._

### Screenshots:

### Author

Divvi Naga Venkata Satish - [Portfolio](https://satishdivvi.github.io)