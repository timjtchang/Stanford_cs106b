// This is the H file you will edit and turn in. (TODO: Remove this comment!)

#pragma once

#include <iostream>
#include <string>
#include "patientqueue.h"
#include <vector>
using namespace std;

class VectorPatientQueue : public PatientQueue {
public:
    VectorPatientQueue() {};
    ~VectorPatientQueue() {};
    string frontName();
    void clear();
    int frontPriority();
    bool isEmpty();
    void newPatient(string name, int priority);
    string processPatient();
    void upgradePatient(string name, int newPriority);
    string toString();

private:

    vector<string> name_list;
    vector<int> prio_list;
    vector<int> time;
    int timeStamp = 0;

};
