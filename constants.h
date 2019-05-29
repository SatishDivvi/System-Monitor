#ifndef PATH_H
#define PATH_H

#include <string>
using namespace std;

class Path {
    public:
        static string BasePath() {
            return "/proc/";
        }
};

#endif