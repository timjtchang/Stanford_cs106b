// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "lexicon.h"
#include "Boggle.h"
#include "simpio.h"
#include "filelib.h"
#include "bogglegui.h"

void human( Boggle& boggle ){

    cout<< "It's your turn!" <<endl;

    while(1){

        // your words & score
        cout<< "Your words"<< boggle.getHumanWords()<<endl;
        cout<< "Your score: "<< boggle.getScoreHuman() <<endl;

        // input
        string input = toUpperCase( getLine("Type a word (or Enter to stop): ") );

        if( input == "") return;

        // backtracking
        boggle.humanWordSearch(input);
        clearConsole();

    }

}

void computer( Boggle& boggle ){

    cout<<"It's my turn!" <<endl;

    Set<string> result;
    result = boggle.computerWordSearch();

    cout<< "My words (" << result.size() << "): {";

    auto it = result.begin();
    while( it != result.end() ){

        cout<< "\""<<*it<< "\"";
        it++;

        if( it == result.end() ) cout<<"}"<<endl;
        else cout<<", ";
    }
    cout<< "My score: "<< boggle.getScoreComputer()<<endl;

}

void playOneGame(Lexicon& dictionary) {

    string input;

    BoggleGUI::initialize( 4, 4 );

    for( int i=0 ; i<16 ; i++ ) input+='0';

    if( !getYesOrNo("Do you want to generate a random board?")){

        input = getLine( "Type the 16 letters to appear on the board: ");

        while( input.size() != 16 ){

            cout<<"That is not a valid 16-letter board string. Try again."<<endl;
            input = getLine( "Type the 16 letters to appear on the board: ");

        }

    }

    Boggle boggle( dictionary, input );
    cout<< boggle <<endl;

    // human
    human(boggle);

    // computer
    computer(boggle);

    if( boggle.getScoreComputer()>boggle.getScoreHuman() ){


        cout<<"Ha ha ha, I destroyed you. Better luck next time, puny human!"<<endl;
        BoggleGUI::setStatusMessage("Ha ha ha, I destroyed you. Better luck next time, puny human!");

    }else{

        cout<<"WOW, you defeated me! Congratulations!"<<endl;
        BoggleGUI::setStatusMessage("WOW, you defeated me! Congratulations!");
    }

}

