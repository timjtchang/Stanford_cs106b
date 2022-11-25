// heappatientqueue.h
// THIS IS AN EXTENSION AND NOT REQUIRED FOR THE ASSIGNMENT
// This is the H file you will edit and turn in. (TODO: Remove this comment!)

#pragma once

#include <iostream>
#include <string>
#include "patientqueue.h"
#include "patientnode.h"
using namespace std;

class HeapPatientQueue : public PatientQueue  {
public:
    HeapPatientQueue();
    ~HeapPatientQueue();
    string frontName();
    void clear();
    int frontPriority();
    bool isEmpty();
    void newPatient(string name, int priority);
    string processPatient();
    void upgradePatient(string name, int newPriority);
    string toString();

private:

    struct HeapNode{

        string name="";
        int priority=0;
    };

    HeapNode* list;
    int last_flag = 0;
    int heap_capacity = 0;

    void processHeap();

};
