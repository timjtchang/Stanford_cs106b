// This is the H file you will edit and turn in. (TODO: Remove this comment!)
/*
#pragma once

#include <iostream>
#include <string>
#include "patientqueue.h"
#include <vector>
using namespace std;

class VectorPatientQueue : public PatientQueue {
public:
    VectorPatientQueue();
    ~VectorPatientQueue();
    string frontName();
    void clear();
    int frontPriority();
    bool isEmpty();
    void newPatient(string name, int priority);
    string processPatient();
    void upgradePatient(string name, int newPriority);
    string toString();

private:

    vector<string>* name_list;
    vector<int>* prio_list;

};
*/

#include "VectorPatientQueue.h"


void VectorPatientQueue::newPatient( string name, int priority){ // put new element in the end of list, check each element,
                                                                 // and swap them if it has higher priority.
                                                                 // O(1)
    name_list.push_back( name );
    prio_list.push_back( priority );
    time.push_back( timeStamp++ );

}

string VectorPatientQueue::frontName(){  // return the element of name list which is most urgent
                                         // O(N)

    int min_num = INT_MAX;
    int min_index = 0;

    for( int i=0 ; i<prio_list.size() ; i++ ){

        if( min_num>prio_list.at(i) ){

            min_num=prio_list.at(i);
            min_index = i;
        }
    }

    return name_list.at(min_index);
}

void VectorPatientQueue::clear(){   // delete all the element in the array O(1)

    prio_list.clear();

    name_list.clear();

    time.clear();

    return;
}
int VectorPatientQueue::frontPriority(){ // O(N)

    int min_num = INT_MAX;
    int min_index = 0;
    int min_time = INT_MAX;

    for( int i=0 ; i<prio_list.size() ; i++ ){

        if( min_num>prio_list.at(i) || (min_num == prio_list.at(i))&&min_time>time.at(i) ){

            min_num=prio_list.at(i);
            min_index = i;
            min_time = time.at(i);
        }
    }

    return prio_list.at(min_index);

}
bool VectorPatientQueue::isEmpty(){ //O(1)

    if( !prio_list.size() ) return 1;
    else return 0;

}

string VectorPatientQueue::processPatient(){ //O(N)

    if( name_list.size() == 0 ) throw std::exception();

    int min_num = INT_MAX;
    int min_index = 0;
    int min_time = INT_MAX;
    string name;

    for( int i=0 ; i<prio_list.size() ; i++ ){

        if( min_num>prio_list.at(i) || (min_num == prio_list.at(i))&&min_time>time.at(i) ){

            min_num=prio_list.at(i);
            min_index = i;
            min_time = time.at(i);
        }
    }

    prio_list.erase( prio_list.begin()+min_index);
    time.erase( time.begin()+min_index );

    name = name_list.at(min_index);
    name_list.erase( name_list.begin()+min_index);

    cout<< "process name= "<< name <<endl;
    return name;
}
void VectorPatientQueue::upgradePatient(string name, int newPriority){ //O(N)

    if( name_list.size() == 0) newPatient( name, newPriority );

    for( int i=0 ; i<prio_list.size() ; i++ ){

        if( name_list.at(i) == name ){

            prio_list.at(i)=newPriority;
            time.at(i) = timeStamp++;

            return;
        }

    }

    throw std::exception();

}
string VectorPatientQueue::toString(){ // O(N)

    string str="{";

    if( prio_list.size() ){

        for( int i=0 ; i<prio_list.size() ; i++ ){

            str+=to_string(prio_list.at(i));
            str+=":";
            str+=name_list.at(i);

            if( i+1<prio_list.size() ) str+=", ";

        }

    }

    str+="}";

    return str;

}

