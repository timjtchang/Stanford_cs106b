// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: remove this comment header

#include "encoding.h"
// TODO: include any other headers you need

Map<int, int> buildFrequencyTable(istream& input) {
    // TODO: implement this function
    Map<int, int> freqTable;   // this is just a placeholder so it will compile

    while(1){

        int key = input.get();
        if( key == -1 ) break; // EOF

        if( freqTable.containsKey(key) ) freqTable[key]++;  // O(logN)
        else freqTable.add( key, 1 );   // O(1)

    }

    freqTable.add( PSEUDO_EOF, 1 );

    rewindStream(input);

    return freqTable;          // this is just a placeholder so it will compile
}

HuffmanNode* buildEncodingTree(const Map<int, int>& freqTable) {
    // TODO: implement this function

    if( freqTable.isEmpty() ) return nullptr;

    PriorityQueue< HuffmanNode*> pq;

    for( auto it=freqTable.begin() ; it!=freqTable.end() ; it++ ){

        HuffmanNode* node = new HuffmanNode();

        node->character = *it;
        node->count = freqTable[*it];

        pq.enqueue( node, node->count );

    }


    while( pq.size()>1 ){

        HuffmanNode* first = pq.peek();
        pq.dequeue();

        HuffmanNode* second = pq.peek();
        pq.dequeue();

        HuffmanNode* node = new HuffmanNode();
        node->character = NOT_A_CHAR;
        node->count = first->count+second->count;
        node->zero = first;
        node->one = second;

        pq.enqueue( node, node->count );

    }

    return pq.peek();   // this is just a placeholder so it will compile
}

Map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    // TODO: implement this function
    Map<int, string> encodingMap;   // this is just a placeholder so it will compile

    // using recursion to built the map

    string leftValue = "0";
    string rightValue = "1";

    if( !encodingTree->zero && !encodingTree->one ) encodingMap.add( encodingTree->character, "" );
    else{

        if( encodingTree->zero != nullptr) helper( encodingMap, encodingTree->zero, leftValue );
        if( encodingTree->one != nullptr) helper( encodingMap, encodingTree->one, rightValue );

    }

    return encodingMap;             // this is just a placeholder so it will compile
}

void helper( Map<int, string>& map, HuffmanNode* node, string value ){

    if( node->character != NOT_A_CHAR ){    // base case

        map.add( node->character, value );
        return;

    }else{  // recursive case

        if( node->zero != nullptr ){

            helper( map, node->zero, value+'0' );
        }

        if( node->one != nullptr ){

            helper( map, node->one, value+'1' );
        }

    }

    return;
}

void encodeData(istream& input, const Map<int, string>& encodingMap, obitstream& output) {
    // TODO: implement this function

    char c;

    cout<<endl;
    while( !input.fail() ){

        input.get(c);
        string value;
        value=encodingMap[c];

        for( char bit:value ){

            //cout<<bit-'0';
            output.writeBit( bit-'0' );

        }

    }

    cout<<endl;
    string value;
    value=encodingMap[PSEUDO_EOF];

    for( char bit:value ){

        output.writeBit( bit-'0' );
    }


    rewindStream(input);

}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    // TODO: implement this function

    bool c;

    HuffmanNode* node = encodingTree;

    while( node->character != PSEUDO_EOF ){

        if( node->character != NOT_A_CHAR ){

            output.put( node->character );
            node = encodingTree;


        }else{

            c=input.readBit();

            if( c==0 ) node=node->zero;
            else if( c==1 ) node=node->one;

        }

    }

    rewindStream(input);
}

void compress(istream& input, obitstream& output) {
    // TODO: implement this function

    Map<int, int> freqTable = buildFrequencyTable(input );
    HuffmanNode* huffTree = buildEncodingTree( freqTable );
    Map<int, string> huffMap = buildEncodingMap( huffTree );

    cout<< freqTable.size() <<endl;
    output<< freqTable;
    encodeData( input, huffMap, output);

    freeTree( huffTree );

}

void decompress(ibitstream& input, ostream& output) {
    // TODO: implement this function

    Map<int, int> freqTable;
    input>>freqTable;

    HuffmanNode* huffTree = buildEncodingTree( freqTable );
    Map<int, string> huffMap = buildEncodingMap( huffTree );

    decodeData( input, huffTree, output );
    freeTree( huffTree );
}

void freeTree(HuffmanNode* node) {
    // TODO: implement this function

    if( node->one==nullptr && node->zero==nullptr ){  // base case

        delete node;
        return;
    }else{

        if( node->one != nullptr ) freeTree( node->one );
        if( node->zero !=  nullptr ) freeTree( node->zero );
    }

    return;

}

