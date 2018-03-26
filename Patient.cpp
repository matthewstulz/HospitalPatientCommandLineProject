#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>
#include "Patient.h"
#include "Logger.h"

using namespace std;

// Patient constructor
Patient::Patient(string firstName, string middleName, string lastName, string suffix, vector<string> ailmentList,
                 string doctor, int t, int priority) {
    this->firstName = firstName;
    this->lastName = lastName;
    this->middleName = middleName;
    this->suffix = suffix;
    this->ailmentList = ailmentList;
    this->doctor = doctor;
    this->treated = t;
    this->priority = priority;
}

// no arg Patient constructor
Patient::Patient(){}

// print function to access data members of said patient
void Patient::printP(){
    cout << "First name: " << getFirstName() << "\nMiddle name: " << getMiddleName() << "\nLast name: " <<
         getLastName() << "\nSuffix: " << getSuffix() << endl;
    printA(getAilmentList());
    cout << "Doctor: " << getDoctor() << "\n" << "Treated: " << getTreated() << "\n"
         << "Priority: " << getPriority() << "\n" << endl;

}

// used to print a patients ailments that are stored in a vector
void Patient::printA(vector<string> ailmentList) {
    vector<string>::iterator iter;
    int counter = 1;
    for(iter = ailmentList.begin(); iter != ailmentList.end(); iter++) {
        cout << "Ailment " << counter << ": " << (*iter) << endl;
        counter++;
    }
}

// prints a report of said patient
void Patient::printPatientsReport(priority_queue<Patient> pq) {
    priority_queue<Patient> pqc = pq;
    Patient tempP;
    string fName, mName, lName, suf;
    cout << "Provide the patients first name, middle name, last name, and suffix if applicable to generate a report" << endl;
    cout << "Enter patient's first name: ";
    getline(cin >> ws, fName);
    cout << "Enter patient's middle name: ";
    getline(cin >> ws, mName);
    cout << "Enter patient's last name: ";
    getline(cin >> ws, lName);
    cout << "Enter patient's suffix or press enter: ";
    if (cin.get() == '\n') {}
    else
        cin >> suf;
    int found = 0;
    while(!pqc.empty() && found == 0) {
        tempP = pqc.top();
        pqc.pop();
        if(tempP.getFirstName() == fName && tempP.getMiddleName() == mName && tempP.getLastName() == lName
                && tempP.getSuffix() == suf) {
            tempP.printP();
            found = 1;
        }
    }
    if(found == 0) {
        cout << "The patient: " << fName << " " << mName << " " << lName << " does not have a report"
                " or has already been treated";
    }
    Logger* log1 = Logger::getUniqueInstance();
    string log = "The report for " + tempP.getFirstName() + " " + tempP.getMiddleName() + " " + tempP.getLastName() + " " + tempP.getSuffix() +
                 " has been printed\n";
    log1->log(log);
}

// gets the next patient to be treated in triage order
void Patient::nextPatientToBeTreated(priority_queue<Patient> pq) {
    Patient tempP;
    tempP = pq.top();
    cout << "The next patient to be treated is:" << endl;
    tempP.printP();
    Logger* log1 = Logger::getUniqueInstance();
    string log = tempP.getFirstName() + " " + tempP.getMiddleName() + " " + tempP.getLastName() + " " + tempP.getSuffix() +
                 " is the next patient to be treated\n";
    log1->log(log);
}

// prints all patients in triage order
void Patient::printTriage(priority_queue<Patient> pq) {
    priority_queue<Patient> pqc = pq;
    Patient tempP;
    while(!pqc.empty()) {
        tempP = pqc.top();
        pqc.pop();
        tempP.printP();
    }
    Logger* log1 = Logger::getUniqueInstance();
    string log = "All patients have been printed in triaged order\n";
    log1->log(log);
}

// turns the data member treated from 0 to 1 and puts patient in a treated patient vector
void Patient::treatAllPatients(priority_queue<Patient> pq) {
    vector<Patient> temp = getTreatedPatientList();
    Patient tempP;
    while(!pq.empty()) {
        tempP = pq.top();
        pq.pop();
        tempP.setTreated(1);
        cout << "treating patient..." << endl;
        this_thread::sleep_for(chrono::seconds(rand() % 3 + 1));
        cout << "patient has been treated successfully" << endl;
        temp.push_back(tempP);
    }
    setPatientList(pq);
    setTreatedPatientList(temp);
    Logger* log1 = Logger::getUniqueInstance();
    string log = "All patients have been treated\n";
    log1->log(log);
}

// prints all patients by doctor alphabetically by overloading the operator function
// of a doctor friend class and uses priority queue to sort the patients
void Patient::printAllPatientsByDoctor(priority_queue<Patient> pq) {
    priority_queue<Patient, vector<Patient>, doctorSort> patientsSortedByDoctor;
    Patient tempP;
    while(!pq.empty()) {
        tempP = pq.top();
        pq.pop();
        patientsSortedByDoctor.push(tempP);
    }
    while(!patientsSortedByDoctor.empty()) {
        tempP = patientsSortedByDoctor.top();
        patientsSortedByDoctor.pop();
        tempP.printP();
    }
    Logger* log1 = Logger::getUniqueInstance();
    string log = "All patients have been printed out by doctor\n";
    log1->log(log);
}

// adds a bulk number of patients from a text file
void Patient::bulkAddPatientsViaFile() {
    string str;
    vector<string> tempAilments;
    cout << "Enter the full path directory: ";
    getline(cin >> ws, str);
    ifstream file (str);
    string tempPatientArray[30];
    int headingCounter = 0, dataCounter = 1;
    while(getline(file, str)) {
        istringstream tokenizer(str);
        if (!str.empty()) {
            // adds a patient to a temp Patient array that stores the type
            // and data using the semicolon as the delimiter
            getline(tokenizer, tempPatientArray[headingCounter], ':');
            getline(tokenizer, tempPatientArray[dataCounter]);

            // uses string compare to make sure the headings match the data to store data correctly
            if (tempPatientArray[headingCounter].compare("ailment") == 0) {
                tempAilments.push_back(tempPatientArray[dataCounter]);
            }
            if (tempPatientArray[headingCounter].compare("priority") == 0) {
                Patient p = Patient(tempPatientArray[1], tempPatientArray[3], tempPatientArray[5], tempPatientArray[7],
                                    tempAilments, "", 9, 0);
                int counter = 10;
                do {
                    if (tempPatientArray[counter].compare("doctor") == 0) {
                        p.setDoctor(tempPatientArray[counter + 1]);
                    }
                    if (tempPatientArray[counter].compare("treated") == 0) {
                        p.setTreated(stoi(tempPatientArray[counter + 1]));
                    }
                    counter++;
                } while (tempPatientArray[counter].compare("priority") != 0);
                if (tempPatientArray[counter].compare("priority") == 0) {
                    p.setPriority(stoi(tempPatientArray[counter + 1]));
                    // if the patient is already treated, add the patient to the treated list
                    if (p.getTreated() == 1) {
                        treatedPatients.push_back(p);
                        tempAilments.clear();
                    }
                    else {
                        patients.push(p);
                        tempAilments.clear();
                    }
                }
                // if there are several ailments to reset the indexes
                headingCounter = -2;
                dataCounter = -1;
            }
            // gets the next heading and data index
            headingCounter += 2;
            dataCounter += 2;
        }
    }
    // log that the file of patients have been added
    cout << "The file of patients has been uploaded" << endl;
    Logger* log1 = Logger::getUniqueInstance();
    string log = "The file of patients has been uploaded\n";
    log1->log(log);
}

// prints the treated Patients vector
void Patient::printAllTreatedPatients() {
    vector<Patient>::iterator iter;
    Logger* log1 = Logger::getUniqueInstance();
    for(iter = treatedPatients.begin(); iter != treatedPatients.end(); iter++) {
        iter->printP();
    }
    string log = "All patients that were in the system have been treated\n";
    log1->log(log);
}

// add a patient to the system data member by data member
void Patient::addPatient() {
    Patient p = Patient();
    string tempUserInput, tempAilmentAnswer = "Y";
    vector<string> tempAilments;
    cout << "Enter patient's first name: ";
    getline(cin >> ws, tempUserInput);
    p.setFirstName(tempUserInput);
    cout << "Enter patient's middle name: ";
    getline(cin >> ws, tempUserInput);
    p.setMiddleName(tempUserInput);
    cout << "Enter patient's last name: ";
    getline(cin >> ws, tempUserInput);
    p.setLastName(tempUserInput);
    cout << "Enter patient's suffix or press enter: ";
    getline(cin, tempUserInput);
    if (tempUserInput.empty()) {
        p.setSuffix("");
    } else {
        p.setSuffix(tempUserInput);
    }
    while (tempAilmentAnswer != "N") {
        cout << "Enter patient's ailments: ";
        getline(cin >> ws, tempUserInput);
        tempAilments.push_back(tempUserInput);
        p.setAilmentList(tempAilments);
        cout << "Is there more ailments: (Y|N) ";
        cin >> tempAilmentAnswer;
    }
    cout << "Enter doctor's name: ";
    getline(cin >> ws, tempUserInput);
    p.setDoctor(tempUserInput);
    cout << "Enter if the patient has been treated: (0|1): ";
    cin >> tempUserInput;
    p.setTreated(stoi(tempUserInput));
    cout << "Enter the patients priority: ";
    cin >> tempUserInput;
    p.setPriority(stoi(tempUserInput));

    if (p.getTreated() == 0) {
        patients.push(p);
    }
    else {
        treatedPatients.push_back(p);
    }

    Logger* log1 = Logger::getUniqueInstance();
    string log = p.getFirstName() + " " + p.getMiddleName() + " " + p.getLastName() + " " + p.getSuffix() +
            " has been added to the system\n";
    log1->log(log);
}

// treat a single patient but first name, middle name, last name, and suffix are required
void Patient::treatPatient() {
    Patient tempP = patients.top();
    tempP.setTreated(1);
    treatedPatients.push_back(tempP);
    cout << "treating patient..." << endl;
    this_thread::sleep_for(chrono::seconds(rand() % 3 + 1));
    cout << "patient has been treated successfully" << endl;
    Logger* log1 = Logger::getUniqueInstance();
    string log = tempP.getFirstName() + " " + tempP.getMiddleName() + " " + tempP.getLastName() + " " + tempP.getSuffix() +
            " has been treated\n";
    log1->log(log);
}

// all accessors and mutators
string Patient::getFirstName() const {return firstName;}
string Patient::getMiddleName() const {return middleName;}
string Patient::getLastName() const {return lastName;}
string Patient::getSuffix() const {return suffix;}
vector<string> Patient::getAilmentList() const {return ailmentList;}
string Patient::getDoctor() const {return doctor;}
int Patient::getTreated() const {return treated;}
int Patient::getPriority() const {return priority;}
priority_queue<Patient> Patient::getPatientList() const {return patients;}
vector<Patient> Patient::getTreatedPatientList() const {return treatedPatients;}
void Patient::setFirstName(string firstName) {
    this->firstName = firstName;
};
void Patient::setMiddleName(string middleName) {
    this->middleName = middleName;
}
void Patient::setLastName(string lastName) {
    this->lastName = lastName;
}
void Patient::setSuffix(string suffix) {
    this->suffix = suffix;
}
void Patient::setAilmentList(vector<string> ailmentList) {
    this->ailmentList = ailmentList;
}
void Patient::setDoctor(string doctor) {
    this->doctor = doctor;
}
void Patient::setTreated(int treated) {
    this->treated = treated;
}
void Patient::setPriority(int priority) {
    this->priority = priority;
}

void Patient::setPatientList(priority_queue<Patient> patients) {
    this->patients = patients;
}

void Patient::setTreatedPatientList(vector<Patient> treatedPatients) {
    this->treatedPatients = treatedPatients;
}

// overload < operator to sort a patients priority
bool operator<(const Patient& lhs, const Patient& rhs) {
    return lhs.priority > rhs.priority;
}

// overload () operator in the doctorSort friend class to sort by doctor
bool Patient::doctorSort::operator() (const Patient &p1, const Patient &p2) {
    return (p1.doctor > p2.doctor) || (p1.doctor ==  p2.doctor);
}