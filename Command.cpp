#include <iostream>
#include <map>
#include "Command.h"
#include "Patient.h"

using namespace std;

// no arg Command constructor
Command::Command() {}

// Command constructor
Command::Command(string userInput) {
    this->userInput = userInput;
}

// accessor and mutator for user input
string Command::getUserInput() {return userInput;}
void Command::setUserInput(string userInput){
    this->userInput = userInput;
}

// enums of string values to be stored in a map
enum stringValue {
    _notDefined, _stringValue1, _stringValue2, _stringValue3, _stringValue4,
    _stringValue5, _stringValue6, _stringValue7, _stringValue8, _stringValue9,
    _stringValue10, _quit
};

// map to store the sting and corresponding string value
map<string, stringValue> _mapStringValues;

// initialize the values to be stored in the map
void Command::initialize() {
    _mapStringValues["add"] = _stringValue1;
    _mapStringValues["treat"] = _stringValue2;
    _mapStringValues["report"] = _stringValue3;
    _mapStringValues["next"] = _stringValue4;
    _mapStringValues["triage"] =_stringValue5;
    _mapStringValues["all"] =_stringValue6;
    _mapStringValues["doctor"] =_stringValue7;
    _mapStringValues["-help"] =_stringValue8;
    _mapStringValues["file"] =_stringValue9;
    _mapStringValues["gone"] =_stringValue10;
    _mapStringValues["quit"] = _quit;
}

// command interface to get what the user wants to do
int Command::getUserCommand(Command c) {
    Patient temp = Patient();
    string tempUserInput;
    int returnInt = 0;
    do {
        cout << "Add a patient to the system: type add" << endl;
        cout << "Treat a patient in triaged order: type treat" << endl;
        cout << "Print out a patient's info as a report: type report" << endl;
        cout << "To find out who is the next patient to be treated: type next" << endl;
        cout << "To print out a report of all the patients in triage: type triage" << endl;
        cout << "To treat all patients: type all" << endl;
        cout << "To print a report of all patients by doctor: type doctor" << endl;
        cout << "Add a bulk of patients from a file: type file" << endl;
        cout << "To print out a report of all patients that have been treated: type gone" << endl;
        cout << "Type -help to get a guide on each command: " << endl;
        cout << "Enter your choice or enter quit: ";
        cout.flush();
        cin >> tempUserInput;
        c.setUserInput(tempUserInput);
        cout << endl;
        // switch statement that uses the map values and calls the corresponding functions
        switch (_mapStringValues[c.getUserInput()]){
            case _stringValue1:
                temp.addPatient();
                break;
            case _stringValue2:
                temp.treatPatient();
                break;
            case _stringValue3:
                temp.printPatientsReport(temp.getPatientList());
                break;
            case _stringValue4:
                temp.nextPatientToBeTreated(temp.getPatientList());
                break;
            case _stringValue5:
                temp.printTriage(temp.getPatientList());
                break;
            case _stringValue6:
                temp.treatAllPatients(temp.getPatientList());
                break;
            case _stringValue7:
                temp.printAllPatientsByDoctor(temp.getPatientList());
                break;
            case _stringValue8:
                helpGuide();
                break;
            case _stringValue9:
                temp.bulkAddPatientsViaFile();
                break;
            case _stringValue10:
                temp.printAllTreatedPatients();
                break;
            case _quit:
                cout << endl << "You have chosen to quit";
                returnInt = 1;
                break;
            default:
                cout << endl << "That option is not valid";
        }
        cout << endl;

    } while(c.getUserInput() != "quit");
    return returnInt;
}

// prints out detail command functions
void Command::helpGuide() {
    cout << "add -> Adds a patient to the system" << endl;
    cout << "treat -> Treats a patient in triage order" << endl;
    cout << "report -> Print out a patient's info as a report" << endl;
    cout << "next -> Finds out who is the next patient to be treated" << endl;
    cout << "triage -> Prints out a report of all the patients in triage" << endl;
    cout << "all -> Treats all patients" << endl;
    cout << "doctor -> Prints a report of all patients by doctor" << endl;
    cout << "file -> Adds patients to the system in bulk via file" << endl;
    cout << "gone -> Prints out a report of all the patients that have been treated" << endl;
    cout << "quit -> Ends the program";
}