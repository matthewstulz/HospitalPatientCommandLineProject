#ifndef PROJECT_3_PATIENT_H
#define PROJECT_3_PATIENT_H
#include <vector>
#include <queue>

using namespace std;

// Patient class
class Patient {
    string firstName;
    string middleName;
    string lastName;
    string suffix;
    vector<string> ailmentList;
    string doctor;
    int treated;
    priority_queue<Patient> patients;
    vector<Patient> treatedPatients;

public:
    int priority;
    Patient();
    Patient(string, string, string, string, vector<string>, string, int, int);
    void printP();
    void printA(vector<string> ailmentList);
    void printPatientsReport(priority_queue<Patient>);
    void nextPatientToBeTreated(priority_queue<Patient>);
    void printTriage(priority_queue<Patient>);
    void treatAllPatients(priority_queue<Patient>);
    void printAllPatientsByDoctor(priority_queue<Patient>);
    void bulkAddPatientsViaFile();
    void printAllTreatedPatients();
    void addPatient();
    void treatPatient();
    string getFirstName() const;
    string getMiddleName() const;
    string getLastName() const;
    string getSuffix() const;
    vector<string> getAilmentList() const;
    string getDoctor() const;
    priority_queue<Patient> getPatientList() const;
    vector<Patient> getTreatedPatientList() const;
    int getTreated() const;
    int getPriority() const;
    void setFirstName(string);
    void setMiddleName(string);
    void setLastName(string);
    void setSuffix(string);
    void setAilmentList(vector<string>);
    void setDoctor(string);
    void setTreated(int);
    void setPriority(int);
    void setPatientList(priority_queue<Patient>);
    void setTreatedPatientList(vector<Patient>);

    class doctorSort {
    public:
        bool operator() (const Patient &, const Patient &);
    };

    //friend class doctorSort;
};

bool operator<(const Patient& lhs, const Patient& rhs);
//bool Patient::doctorSort::operator() (const Patient &p1, const Patient &p2);


#endif //PROJECT_3_PATIENT_H