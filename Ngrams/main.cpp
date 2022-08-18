#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include "simpio.h"
#include "gwindow.h"
#include "filelib.h"
#include "console.h"
#include <queue>
#include <climits>
#include "random.h"
using namespace std;

void readFile( ifstream&);
void getCollection( ifstream&, map<vector<string>, vector<string>>&, int&, int&);
void writeFile( map<vector<string>, vector<string>>&, int&);
void helper( map<vector<string>, vector<string>>&, vector<string>&, int&, int );


int main(){

    cout<< "Welcome to CS 106B Random Writer ('N-Grams')."<<endl;
    cout<< "This program makes random text based on a document."<<endl;
    cout<< "Give me an input file and an 'N' value for groups"<<endl;
    cout<< "of words, and I'll create random text for you."<<endl;

    map<vector<string>, vector<string>> collection;
    int gramN = INT_MAX;
    int wordNum = INT_MAX;

    ifstream input;

    readFile(input);

    do{

        if( gramN<2 ) cout<<"N must be 2 or greater."<<endl;
        gramN = getInteger("Value of N?");
    }while(gramN<2);

    while(1){

        getCollection( input, collection, gramN, wordNum);
        if(!wordNum) break;
        writeFile( collection, wordNum);
        cout<<endl;

    }

    cout<<"Exiting."<<endl;
    return 0;
}

void readFile( ifstream& input){

    string fileName;

    while(1){

        fileName = getLine("Inpute file name?");
        fileName = "res/"+fileName;

        if( !fileExists(fileName) ) cout<< "Unable to open that file. Try again."<<endl;
        else break;

    }

    input.open(fileName);

    if( input.fail()){

        cout<< " it is fail "<<endl;
    }

    return;
}

void getCollection( ifstream& input, map<vector<string>, vector<string>>& collection, int& gramN, int& wordNum){

    do{

        if( wordNum<gramN) cout<<"Must be at least "<<gramN<<" words."<<endl;
        wordNum = getInteger("# of random words to generate (0 to quit)?");
        if( !wordNum) return;
    }while(wordNum<gramN);



    vector<string> wrappingWord;
    vector<string> key;

    string word;

    for( int i=0 ; i<gramN-1 ; i++ ){

        input>>word;
        wrappingWord.push_back(word);
        key.push_back(word);
    }

    while( input>>word){

        collection[key].push_back( word);

        key.erase(key.begin());
        key.push_back(word);
    }

    for( auto& word:wrappingWord){

        collection[key].push_back(word);

        key.erase(key.begin());
        key.push_back(word);
    }

}
void writeFile( map<vector<string>, vector<string>>& collection, int& wordNum){

    vector<string> start;
    int random = randomInteger( 0, collection.size() );
    int count = 0;

    for( auto it = collection.begin() ; count != random ; ++it ){

        start = it->first;
        count++;
    }

    cout<<"...";
    helper( collection, start, wordNum, 0);
    cout<<"...";
    return;
}
void helper( map<vector<string>, vector<string>>& collection, vector<string>& prefix, int& wordNum, int count){

    if( wordNum == count ) return;

    vector<string> suffix = collection[prefix];

    int random = randomInteger(0, suffix.size()-1);
    string word = suffix[random];
    cout<<word<<" ";

    prefix.erase( prefix.begin() );
    prefix.push_back(word);

    helper( collection, prefix, wordNum, ++count);
}
