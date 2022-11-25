// heappatientqueue.cpp
// THIS IS AN EXTENSION AND NOT REQUIRED FOR THE ASSIGNMENT
// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include "HeapPatientQueue.h"
#include "strlib.h"

HeapPatientQueue::HeapPatientQueue() { // initialize Patient node
                                       // O(1)
    list = new HeapNode [10];
    heap_capacity=10;
}

HeapPatientQueue::~HeapPatientQueue() { // delete all element in the linkiedlist recrusively
                                        // O(N)

    delete [] list;
}

void HeapPatientQueue::clear() { // O(N)

    delete [] list;
    list = new HeapNode [10];
}

string HeapPatientQueue::frontName() { // O(1)

    return list[1].name;

}

int HeapPatientQueue::frontPriority() { // O(1)

    return list[1].priority;
}

bool HeapPatientQueue::isEmpty() { // O(1)

    return last_flag==0;
}

void HeapPatientQueue::newPatient(string name, int priority) { // O(logN)

    if( last_flag+1>heap_capacity) {     // expand list if neccessary O(10)

        heap_capacity += 10;
        HeapNode* ptr = new HeapNode [heap_capacity];

        for( int i=0 ; i<last_flag ; i++ ) ptr[i]=list[i];
        delete [] list;
        list = ptr;

    }

    last_flag++;
    list[last_flag].name=name;
    list[last_flag].priority=priority;

    while( list[last_flag].priority<list[last_flag/2].priority && last_flag ){  // swap O(logN)

        HeapNode tmp=list[last_flag/2];
        list[last_flag/2]=list[last_flag];
        list[last_flag]=tmp;

    }

}

string HeapPatientQueue::processPatient() { // O(N)

    if( isEmpty() ) throw std::exception();

    string name=list[1].name;

    //replace list[1] with list[last_flag]
    list[1]=list[last_flag];
    last_flag--;

    int count = 1;

    while( count<last_flag ){       // O(N)

        if( count+2 <= last_flag ){ // have 2 subtree


            if( list[count+1].priority<=list[count].priority && list[count+1].priority<=list[count+2].priority ){

                HeapNode tmp;
                tmp = list[count];
                list[count] = list[count+1];
                list[count+1] = tmp;

            }else if( list[count+2].priority<=list[count].priority && list[count+2].priority<=list[count+1].priority ){

                HeapNode tmp;
                tmp = list[count];
                list[count] = list[count+2];
                list[count+2] = tmp;
            }


        }else if( count+1 <= last_flag ){ // have 1 subtree

            if( list[count+1].priority<=list[count].priority ){

                HeapNode tmp;
                tmp = list[count];
                list[count] = list[count+1];
                list[count+1] = tmp;
            }


        }

        count++;

    }

    return name;

}

void HeapPatientQueue::upgradePatient(string name, int newPriority) { //O(N)

    if( isEmpty() ) throw std::exception();

    for( int i=1 ; i<=last_flag ; i++ ){

        if( list[i].name == name ){

            list[i].name = name;
            list[i].priority = newPriority;

            // swap the node with last node

            HeapNode tmpNode = list[i];
            list[i] = list[last_flag];
            list[last_flag] = tmpNode;

            // processHeap
            while( list[last_flag].priority<list[last_flag/2].priority && last_flag ){  // swap O(logN)

                HeapNode tmp=list[last_flag/2];
                list[last_flag/2]=list[last_flag];
                list[last_flag]=tmp;

            }

            return;

        }

    }

    throw std::exception();

}

string HeapPatientQueue::toString() { //O(N)

    //cout<<"to String"<<endl;
    //cout<<"last_flag= "<< last_flag<<endl;

    string result = "{";

    for( int i=1 ; i<=last_flag ; i++ ){

        result+=integerToString( list[i].priority );
        result+=":";
        result+=list[i].name;

        if( i+1<=last_flag ) result+=", ";
    }

    result+="}";
    return result;
}

