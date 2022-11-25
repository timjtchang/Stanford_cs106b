// This is the H file you will edit and turn in. (TODO: Remove this comment!)

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "patientnode.h"
#include "patientqueue.h"
using namespace std;

class Iterator{

public:

    Iterator();
    Iterator( PatientNode* );
    ~Iterator();

    Iterator operator+( int );
    Iterator operator-( int );
    PatientNode operator*();
   // Iterator operator++();
   // Iterator operator--();

    bool operator==( Iterator );
    bool operator!=( Iterator );

    void begin( PatientNode* );
    void end( PatientNode* );

    void content();

private:

    PatientNode* front;
    PatientNode* current;
    PatientNode endNode;
    int index;

};


class LinkedListPatientQueue : public PatientQueue {
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

    Iterator begin();
    Iterator end();

private:

    Iterator* it;

};




