// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include "simpio.h"
#include "gwindow.h"
#include "filelib.h"
#include "console.h"
#include <vector>
#include <queue>
#include <climits>

using namespace std;

void getDic(unordered_map<string,int>&);
bool doLadder( unordered_map<string,int>&, unordered_map<string,string>&, string&, string& );
void printAns(unordered_map<string, string>&, string&start, string &end);
void helper( unordered_map<string, string>&, string&, string& );

int main() {
    // TODO: Finish the program!

    unordered_map<string, int>  distance;
    unordered_map<string, string> predecessor;
    getDic( distance );

    while(1){

        stack<string> ans;

        string word1;
        string word2;

        word1 = getLine("Word #1 (or Enter to quit):");
        if(!word1.size()) break;
        word2 = getLine("Word #2 (or Enter to quit):");
        if(!word2.size()) break;

        word1 = toLowerCase(word1);
        word2 = toLowerCase(word2);

        if( word1.size() != word2.size() ){

            cout<<"The two words must be the same length."<<endl;
            continue;
         }

        if( distance.count(word1) == 0 || distance.count(word2)==0 ){

            cout<<"The two words must be found in the dictionary."<<endl;
            continue;
        }

        if( word1 == word2 ){

            cout<<"The two words must be different."<<endl;
            continue;
        }

        cout<<"A ladder from cat back to dog:"<<endl;

        distance[word1] = 0;
        if(doLadder(distance, predecessor, word1, word2) ){

            printAns( predecessor, word1, word2);
        }else{

            cout<<"The two words must be found in the dictionary."<<endl;
        }

    }

    cout << "Have a nice day." << endl;
    return 0;
}

void printAns( unordered_map<string,string>& predecessor, string& start, string& end){

    helper( predecessor, start, end );
    cout<< start << endl;
    return;

}

void helper( unordered_map<string,string>& predecessor, string& start, string& word){

    if( word == start ) return;

    cout<< word << " ";
    helper( predecessor, start, predecessor[word]);
}
bool doLadder( unordered_map<string,int>& distance, unordered_map<string, string>& predecessor, string& start, string& end ){

    queue<string> q;

    q.push(start);

    while( !q.empty()){  // BFS

        int size = q.size();
        for( int i=0 ; i<size ; i++){

            string word = q.front();
            q.pop();

            if(word == end) return true;

            for( int i=0 ; i<word.size() ; i++){  // get 1-step word

                string tmp = word;

                for( char ch='a'; ch<='z' ; ch++ ){

                    tmp[i] = ch;
                    if( tmp == start ) continue;
                    if( distance.count(tmp)!=0){

                        if( distance[tmp]>distance[word]+1){

                            predecessor[tmp] = word;
                            //cout<< "next word= "<<tmp<<endl;
                            //cout<< "original distance= "<<distance[tmp]<<endl;
                            //cout<< "new distance= "<<distance[word]+1<<endl;
                            distance[tmp] = distance[word]+1;
                            q.push(tmp);
                        }
                    }
                }
            }
        }
        cout<< "size="<<size<<endl;
    }

    return false;

}



void getDic( unordered_map<string,int>& distance ){

    ifstream input;
    string fileName;

    while(1){

        fileName = getLine("Dictionary file name?");
        fileName = "res/"+fileName;

        if( !fileExists(fileName) ) cout<< "Unable to open that file. Try again."<<endl;
        else break;

    }

    input.open(fileName);

    if( input.fail()){

        cout<< " it is fail "<<endl;
    }

    string line;

    while( getline( input, line)){

      distance[line] = INT_MAX;

    }

}

