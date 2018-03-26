#ifndef LOGGER_H
#define LOGGER_H
#include <string>

using namespace std;

// logger class to log all activity from the user
class Logger {
public:
    static Logger* getUniqueInstance();
    void log(const string);
    void setPath(string);
    string getPath() const;
    static void destroyUniqueInstance();
private:
    Logger();
    ~Logger();
    Logger(const Logger&);
    static Logger* myUniqueInstance;
    string path;
};


#endif //LOGGER_H