#include <string>
#include <fstream>
using namespace std;

class Util {
    public:
        static string convertToTime(long int seconds);
        static string getProgressBar(string percent);
        static ifstream getStream(string path);
};

ifstream Util::getStream(string path) {
    ifstream readFile(path);
    
}