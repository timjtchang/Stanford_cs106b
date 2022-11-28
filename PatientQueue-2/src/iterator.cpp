
#include "iterator.h"

// iterator

patient::iterator::iterator(){

    front = nullptr;
    current = nullptr;

    index = 0;
}

patient::iterator::iterator( PatientNode* node ){

    front = node;
    current  = node;

    index = 0;
}

patient::iterator::~iterator(){


}

void patient::iterator::begin( PatientNode* node ){

    front = node;
    current  = front;
}

void patient::iterator::end( PatientNode* node ){

    front = node;
    current = front;

    while( current!=nullptr ){

        current= current->next;
        index+=1;
    }

    current = &endNode;

}


patient::iterator patient::iterator::operator+( int count ){

    iterator it;
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


patient::iterator patient::iterator::operator++( int i ){


    patient::iterator it = (*this);

    *this = *(this)+1;

    return it;

}

patient::iterator& patient::iterator::operator++(){

    *this = (*this)+1;

    return (*this);
}

patient::iterator patient::iterator::operator--( int i ){

    patient::iterator it = *this;

    *this = *(this)-1;

    return it;

}

patient::iterator& patient::iterator::operator--(){

    *this = (*this)-1;
    return (*this);
}


patient::iterator patient::iterator::operator-( int count ){

    iterator it;
    it.front = this->front;
    it.current = this->front;

    while( it.index != this->index-1 ){

        it.current = it.current->next;
        it.index++;

    }

    return it;

}
PatientNode& patient::iterator::operator*(){

    if( current == nullptr ) return endNode;
    else return *current;

}

bool patient::iterator::operator==( iterator it ){

    return it.front==it.front && it.index==index;
}

bool patient::iterator::operator!=( iterator it ){

    return it.front!=it.front || it.index!=index;
}

void patient::iterator::content(){

    std::cout<< "index=" << index <<std::endl;
    if( front == nullptr ) std::cout<< "front=nullptr" <<std::endl;
    else{

        std::cout<< front->name <<std::endl;
    }

    if( current == nullptr ) std::cout<<"current=nullptr"<<std::endl;
    else{

        std::cout<< current->name <<std::endl;
    }

    std::cout<<std::endl;
}


