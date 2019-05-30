#include <string>
#include <fstream>
using namespace std;

class Util {
    public:
        static string convertToTime(long int seconds);
        static string getProgressBar(string percent);
        static ifstream getStream(string path);
};

string Util::convertToTime(long int seconds) {
    long minutes = seconds / 60;
    long hours = minutes / 60;
    long seconds = int(seconds%60);
    minutes = int(minutes%60);
    string result = to_string(hours) + ":" + to_string(minutes) + ":" + to_string(seconds);
    return result;
}

ifstream Util::getStream(string path) {
    ifstream readFile(path);
    if(!readFile)
        throw runtime_error("No File Exists");
    return readFile;
}