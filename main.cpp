#include <iostream>
#include "Command.h"
#include "Logger.h"

using namespace std;

/* Matthew Stulz
 * CSC 402
 * STL & Streams (Mimics a hospital emergency room triage
 * The two major functions are cataloging and reporting of patients
 * info and simulation of "treating" patients. This program uses a
 * Singleton design pattern to log all activities. Invalid data cases
 * are not implemented and requires correct data to be input at all times.
 * A command line interface is how all user interaction happens.
 */

// created a unique instance logger object
Logger* Logger::myUniqueInstance = NULL;

int main() {
    // seed the random number generater
    srand(static_cast<unsigned int>(time(NULL)));
    // logger is created with the unique instance
    Logger* log1 = Logger::getUniqueInstance();
    // string to store the file path entered
    string str;
    cout << "Enter file path for all information to be logged to: ";
    // store the entire data path line using getline
    getline(cin >> ws, str);
    // set file directory variable in the log class
    log1->setPath(str);

    // counter for while
    int i = 0;
    // create an instance of the command class
    Command c = Command();
    // initialize the map inside the command class to use a switch statement with strings
    c.initialize();
    // continue to loop until i gets set to 1 by entering quit in the command line interface
    while (i == 0) {
        i = c.getUserCommand(c);
    }
    return 0;
}