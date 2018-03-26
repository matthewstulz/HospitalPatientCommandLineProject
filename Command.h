#ifndef PROJECT_3_COMMAND_H
#define PROJECT_3_COMMAND_H

using namespace std;

// Command class
class Command {
    string userInput;
public:
    Command();
    Command(string);
    int getUserCommand(Command);
    string getUserInput();
    void setUserInput(string);
    void initialize();
    void helpGuide();
};


#endif //PROJECT_3_COMMAND_H