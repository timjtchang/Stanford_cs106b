// This is the H file you will edit and turn in. (TODO: Remove this comment!)

#pragma once

#include <iostream>
#include <string>
#include "patientnode.h"
#include "iterator.h"

class PatientQueue {
public:
    PatientQueue() {}
    ~PatientQueue() {}
    virtual void clear() {}
    virtual std::string frontName() {return ""; }
    virtual int frontPriority() {return 0;}
    virtual bool isEmpty() {return false;}
    virtual void newPatient(std::string name, int priority) {}
    virtual std::string processPatient() {return "";}
    virtual void upgradePatient(std::string name, int newPriority) {}
    virtual std::string toString() { return "";}
    PatientNode* list;
    patient::iterator* it;

private:
    friend std::ostream& operator <<(std::ostream& out, PatientQueue& queue) {
        out << queue.toString();
        return out;
    }

};


