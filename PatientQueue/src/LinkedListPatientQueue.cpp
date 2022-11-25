// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include "LinkedListPatientQueue.h"

LinkedListPatientQueue::LinkedListPatientQueue() {  // initialize Patient node
                                                    // O(1)
    list = nullptr;
    it = new Iterator( list );

}

LinkedListPatientQueue::~LinkedListPatientQueue() { // delete all element in the linkiedlist recrusively
                                                    // O(N)

    while( list!= nullptr ){

        PatientNode* node = list;
        list = list->next;

        delete node;
    }

    delete it;

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

        PatientNode* ptr=list;

        if( ptr->priority > priority ){

            node->next = list;
            list = node;
            return;

        }else{

            while( ptr->next != nullptr && ptr->next->priority <= priority ){

                ptr = ptr->next;
            }

            node->next = ptr->next;
            ptr->next = node;
            return;

        }

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


Iterator LinkedListPatientQueue::begin(){

    Iterator it;
    it.begin( list );

    return it;
}

Iterator LinkedListPatientQueue::end(){

    Iterator it;
    it.end( list );

    return it;

}

// Iterator

Iterator::Iterator(){

    front = nullptr;
    current = nullptr;

    index = 0;
}

Iterator::Iterator( PatientNode* node ){

    front = node;
    current  = node;

    index = 0;
}

Iterator::~Iterator(){


}

void Iterator::begin( PatientNode* node ){

    front = node;
    current  = front;
}

void Iterator::end( PatientNode* node ){

    front = node;
    current = front;

    while( current!=nullptr ){

        current= current->next;
        index+=1;
    }

    current = &endNode;

}


Iterator Iterator::operator+( int count ){

    Iterator it;
    it.front = front;
    it.current = current;
    it.index = index;

    for( int i=0 ; i<count ; i++ ){

        if( it.current == nullptr ){

            current  = &endNode;
            return it;
        }
        it.current = it.current->next;
        it.index++;
    }

    return it;
}

/*
Iterator Iterator::operator++(){


    return *this+1;
}

Iterator Iterator::operator--(){

    return *this-1;
}
*/

Iterator Iterator::operator-( int count ){

    Iterator it;
    it.index = index-count;
    it.front = front;

    for( int i=0 ; i<index ; i++ ){

        if( it.current == nullptr ){

            *current = endNode;
            return it;

        }

        it.current = it.current->next;
    }

    return it;

}
PatientNode Iterator::operator*(){

    if( current == nullptr ) return endNode;
    else return *current;

}

bool Iterator::operator==( Iterator it ){

    return it.front==it.front && it.index==index;
}

bool Iterator::operator!=( Iterator it ){

    return it.front!=it.front || it.index!=index;
}

void Iterator::content(){

    cout<< "index=" << index <<endl;
    if( front == nullptr ) cout<< "front=nullptr" <<endl;
    else{

        cout<< front->name <<endl;
    }

    if( current == nullptr ) cout<<"current=nullptr"<<endl;
    else{

        cout<< current->name <<endl;
    }

    cout<<endl;
}
