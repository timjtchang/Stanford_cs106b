// This is the H file you will edit and turn in. (TODO: Remove this comment!)

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "patientnode.h"
#include "patientqueue.h"

using namespace std;

class LinkedListPatientQueue : public PatientQueue, public patient::iterator {
public:
    LinkedListPatientQueue();
    ~LinkedListPatientQueue();
    string frontName();
    void clear();
    int frontPriority();
    bool isEmpty();
    void newPatient(string name, int priority);
    string processPatient();
    void upgradePatient(string name, int newPriority);
    string toString();

    patient::iterator begin();
    patient::iterator end();


};




