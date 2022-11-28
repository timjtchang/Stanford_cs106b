#ifndef ITERATOR_H
#define ITERATOR_H

#include "patientnode.h"

namespace patient{

    class iterator{

    public:

        iterator();
        iterator( PatientNode* );
        ~iterator();

        iterator operator+( int );
        iterator operator-( int );
        PatientNode& operator*();
        iterator operator++(int);
        iterator& operator++();
        iterator operator--(int);
        iterator& operator--();

        bool operator==( iterator );
        bool operator!=( iterator );

        void begin( PatientNode* );
        void end( PatientNode* );

        void content();

    private:

        PatientNode* front;
        PatientNode* current;
        PatientNode endNode;
        int index;

    };

}

#endif // ITERATOR_H
