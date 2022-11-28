// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include "LinkedListPatientQueue.h"
using namespace std;

LinkedListPatientQueue::LinkedListPatientQueue() {  // initialize Patient node
                                                    // O(1)
    list = nullptr;
    it = new patient::iterator( list );

}

LinkedListPatientQueue::~LinkedListPatientQueue() { // delete all element in the linkiedlist recrusively
                                                    // O(N)
    patient::iterator it = begin();

    while( list != nullptr ){

        patient::iterator it = begin();
        PatientNode* node = &*it;
        it++;

        list = &*it;
        delete node;

    }

    return;
}

void LinkedListPatientQueue::clear() {  // O(N)

    while( list!= nullptr ){

        PatientNode* node = list;
        list = list->next;

        delete node;
    }

    return;
}

string LinkedListPatientQueue::frontName() { // O(1)

    return list->name;
}

int LinkedListPatientQueue::frontPriority() { // O(1)

    return list->priority;
}

bool LinkedListPatientQueue::isEmpty() {    // O(1)

    return list==nullptr;
}

void LinkedListPatientQueue::newPatient(string name, int priority) { // O(N)

    PatientNode* node = new PatientNode();
    node->name = name;
    node->priority = priority;
    node->next = nullptr;

    if( list!=nullptr){

        patient::iterator it = begin();
        while( it+1 != end() ) ++it;
        (*it).next = node;

    }else list=node;

    return;
}

string LinkedListPatientQueue::processPatient() { // O(1)

    PatientNode* ptr=list;
    string name = ptr->name;

    list = list->next;
    delete ptr;

    return name;
}

void LinkedListPatientQueue::upgradePatient(string name, int newPriority) { //O(N)

    PatientNode* ptr=list;

    while( ptr!=nullptr ){  // O(N)

      if( ptr->next == nullptr && name == ptr->name ){  // the queue have one element

          ptr->priority = newPriority;
          return;

      }else if( name == ptr->next->name ){     // the queue have numbers of elements

          PatientNode* tmpNode = ptr->next;
          ptr->next = tmpNode->next;

          delete tmpNode;

          newPatient( name, newPriority );
          return;

      }else ptr = ptr->next;

    }

    throw std::exception();
}

string LinkedListPatientQueue::toString() { //O(N)

    string str="{";
    PatientNode* ptr=list;

    while( ptr!=nullptr ){

        str+=to_string(ptr->priority);
        str+=":";
        str+=(ptr->name);

        if( ptr->next!=nullptr ) str+=", ";

        ptr=ptr->next;
    }

    str+="}";
    return str;
}

patient::iterator LinkedListPatientQueue::begin(){

    patient::iterator it;
    it.begin( list );

    return it;
}

patient::iterator LinkedListPatientQueue::end(){

    patient::iterator it;
    it.end( list );

    return it;

}
