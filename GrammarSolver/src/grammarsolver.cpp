/*
 * File: grammarsolver.cpp
 * --------------------------
 * Name:
 * Section leader:
 * This file contains grammar generating code for CS106B.
 */

#include "grammarsolver.h"
#include "strlib.h"
#include <map>

using namespace std;

/**
 * Generates grammar for a given symbol a certain number of times given
 * a BNF input file.
 *
 * This will be called by grammarmain.cpp.
 *
 * @param input - Input stream of BNF file.
 * @param symbol - Symbol to generate
 * @param times - Number of times grammar is generated
 * @return Vector of strings of size times with random generations of symbol
 */

void createMap( map<string, vector<string>>& mp, istream& input ){

    string str;
    vector<string> strs;


    // store each line in strs
    while(getline( input, str )){

        strs.push_back(str);
    }

    // store each non_terminals and rules into map
    for( const auto& ch:strs ){

        vector<string> non_terminals;
        vector<string> rules;

        non_terminals = stringSplit( ch, "::=");
        rules = stringSplit( non_terminals[1], "|");

        mp[non_terminals[0]] = rules;

    }

    // print the map

    /*
    for( const auto& m:mp ){

        cout<< "[" << m.first << "]= ";
        for( const auto& rule:m.second){


            cout<< rule <<", ";
        }

        cout<<endl;

    }
    */


}

string helper( string symbol, map<string, vector<string>> mp, int seed ){

    // base case
    if( mp.count( symbol) == 0 ) return symbol+" ";

    // recursive case

    string rule = mp[symbol][seed%mp[symbol].size()];
    vector<string> content;
    string result = "";

    content = stringSplit( rule, " ");

    for( const auto& str:content ){

        if( mp.count(str) != 0 ) result += helper( str, mp, seed+1 );
        else{

            result += str;
            result += " ";
        }

    }

    return result;
}




Vector<string> grammarGenerate(istream& input, string symbol, int times) {
    // TODO: write this function

    Vector<string> results;
    map<string, vector<string>> mp;

    createMap( mp, input );

    for( int i=0 ; i<times ; i++ ){

        results.add( helper( symbol, mp, i) );
    }


    return results;           // This is only here so it will compile
}

