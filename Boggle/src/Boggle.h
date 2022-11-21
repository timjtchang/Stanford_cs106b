// This is a .h file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include "lexicon.h"
using namespace std;

class Boggle {
public:
    Boggle(Lexicon& dictionary, string boardText = ""); // get 16 board cubes
    char getLetter(int row, int col);   // get a letter in board
    bool checkWord(string word);    // check if the word is valid
    bool humanWordSearch(string word); // check if the word can be formed in humand part
    Set<string> computerWordSearch(); // return all the word which can be formed in computer part
    int getScoreHuman(); // get human score
    int getScoreComputer(); // get computer score

    // TODO: add any other member functions/variables necessary
    friend ostream& operator<<(ostream& out, Boggle& boggle); // print board
    string getHumanWords();

private:
    int humanScore = 0;
    int computerScore = 0;
    string grid;
    Lexicon* dic;

    set<string> humanst;
    set<string> computerst;

    bool humanHelper(  string&, vector<bool>&, int, int, string, int );
    void computerHelper( set<string>&, vector<bool>&, int, int, string );

};

#endif // _boggle_h
