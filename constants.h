#ifndef PATH_H
#define PATH_H

#include <string>
using namespace std;

class Path {
    public:
        static string BasePath() {
            return "/proc/";
        }

        static string cmdPath() {
            return "/cmdline";
        }

        static string statusPath() {
            return "/status";
        }
        
};

#endif