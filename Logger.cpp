#include "logger.h"
#include <iostream>
#include <fstream>

using namespace std;

// logger no arg constructor
Logger::Logger(){}

// copy constructor
Logger::Logger(const Logger& Logger){
    myUniqueInstance = Logger.myUniqueInstance;
}

// logger deconstructor
Logger::~Logger(){}

// unique instance accessor
Logger* Logger::getUniqueInstance() {
    if(myUniqueInstance == NULL)
        myUniqueInstance = new Logger();
    return myUniqueInstance;
}

// unique instance destructor
void Logger::destroyUniqueInstance() {
    delete myUniqueInstance;
    myUniqueInstance = NULL;
}

// prints contents to cout
void Logger::log(string output) {
    ofstream ofs;
    ofs.open(getPath(), ofstream::out | ofstream::app);
    ofs << output;
    ofs.close();
}

// mutator for the directory path entered by the user
void Logger::setPath(string path) {
    this->path = path;
}

// accessor for the directory path
string Logger::getPath() const {return path;}