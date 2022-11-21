// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cmath>
#include "Boggle.h"
#include "shuffle.h"
#include "simpio.h"
#include "bogglegui.h"

// letters on all 6 sides of every cube
static string CUBES[16] = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

// letters on every cube in 5x5 "Big Boggle" version (extension)
static string BIG_BOGGLE_CUBES[25] = {
   "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
   "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
   "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
   "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
   "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

Boggle::Boggle(Lexicon& dictionary, string boardText) {

    if( boardText == "0000000000000000" ){

        grid = "";
        for( int i=0 ; i<boardText.size(); i++ ){

           grid+=shuffle(CUBES[i])[(i+3)%6];
        }

    }else{

        grid = boardText;
    }

    //BoggleGUI::initialize( sqrt(boardText.size()), sqrt(boardText.size()) );
    BoggleGUI::labelAllCubes( grid );
    BoggleGUI::setAnimationDelay( 10 );

    dic = &dictionary;

}

char Boggle::getLetter(int col, int row) { // get a letter in the board

    return grid[ row*4+col];
}

bool Boggle::checkWord(string word) {

    return word.size()>=4 && dic->contains(word);

}

bool Boggle::humanWordSearch(string word) {

    BoggleGUI::setStatusMessage( "It's your turn!" );
    BoggleGUI::clearHighlighting();

    if( !checkWord( word ) || humanst.count(word) ){

        BoggleGUI::setStatusMessage( "You must enter an unfound 4+ letter word from the dictionary." );
        return false;
    }

    vector<bool> record;
    for( int i=0 ; i<grid.size() ; i++ ) record.push_back(0);

    for( int i=0 ;i<grid.size() ; i++ ){

        if( grid[i] == word[0] ){

            if( humanHelper( grid, record, i%4, i/4, word, 0) ){

                humanScore += (word.size()-3);
                humanst.insert(word);

                BoggleGUI::recordWord( word, BoggleGUI::HUMAN );
                BoggleGUI::setScore( humanScore, BoggleGUI::HUMAN );

                string tmpstr = "You found a new word! \"";
                tmpstr += word;
                tmpstr += "!\"";

                BoggleGUI::setStatusMessage( tmpstr );

                return true;
            }else{

                BoggleGUI::setStatusMessage( "That word can't be formed on this board" );
            }
        }

    }

    return false;

}

int Boggle::getScoreHuman() {

    return humanScore;
}

Set<string> Boggle::computerWordSearch() {

    set<string> result;
    vector<bool> record;

    for( int i=0 ; i<16 ; i++ ) record.push_back(0);

    for( int i=0 ; i<4 ; i++ ){

        for( int j=0 ; j<4 ; j++ ){

            computerHelper( result, record, j, i, "");
        }
    }

    BoggleGUI::setScore( computerScore, BoggleGUI::COMPUTER );

    Set<string> output;

    for( const auto& str:result ){

        output.insert( str );
    }

    return output;        // remove this
}

int Boggle::getScoreComputer() {

    return computerScore;
}

ostream& operator<<(ostream& out, Boggle& boggle) {

    for( int i=0 ; i<boggle.grid.size() ; i++ ){

        if( i%4==0 && i!=0 ) cout<<endl;
        cout<<boggle.grid[i];
    }

    cout<<endl;
    return out;
}

string Boggle::getHumanWords(){

    string yourWords = "("+ integerToString(humanst.size()) + "): {";

    auto it = humanst.begin();

    if( humanst.size() == 0 ) yourWords+="}";

    while( it!=humanst.end() ){

        yourWords+="\""+*it+"\"";
        it++;

        if( it == humanst.end() ) yourWords+="}";
        else yourWords+=", ";
    }

    return yourWords;
}


// private function
bool Boggle::humanHelper( string& grid, vector<bool>& record, int x, int y, string word, int index ){

    //cout<<"explore="<<getLetter(x,y)<<endl;

    // base case
    if( index == word.length() ) return true;
    BoggleGUI::setHighlighted( y, x, true );

    if( getLetter(x,y) != word[index] ){

        BoggleGUI::setHighlighted( y, x, false );
        return false;
    }

    // select
    record[y*4+x] = 1;
    //cout<<"select="<<getLetter(x,y)<<endl;

    // explore
    for( int yi=-1 ; yi<2 ; yi++ ){

        if( y+yi<0 || y+yi>3 ) continue;

        for( int xi=-1 ; xi<2 ; xi++ ){

            if( yi==0 && xi==0 ) continue;
            if( x+xi<0 || x+xi>3 ) continue;
            if( record[ (y+yi)*4+(x+xi)] ) continue;

            if( humanHelper( grid, record, x+xi, y+yi, word, index+1) ) return true;
            else continue;
        }
    }

    // unselect
    record[y*4+x] = 0;
    BoggleGUI::setHighlighted( y, x, false );

    return false;

}

void Boggle::computerHelper( set<string>& result, vector<bool>& record, int x, int y, string word ){

    // base case
    if( word.size()>16 || !dic->containsPrefix(word)) return;

    // add in set
    if( word.size()>=4 && dic->contains(word) && humanst.count(word)==0 && result.count(word)==0 ){

        BoggleGUI::recordWord( word, BoggleGUI::COMPUTER );

        result.insert(word);
        computerScore += (word.size()-3);
        //cout<< "score=" << computerScore <<endl;

        //cout<< "find:" << word <<endl;

        /*
        for( const auto& str:result ){

            cout<<str<<" ";
        }
        cout<<endl;
        */

        return;
    }

    // choose
    record[y*4+x] = 1;
    word+=getLetter(x,y);

    // explore
    for( int yi=-1 ; yi<2 ; yi++ ){

        if( y+yi<0 || y+yi>3 ) continue;

        for( int xi=-1 ; xi<2 ; xi++ ){

            if( yi==0 && xi==0 ) continue;
            if( x+xi<0 || x+xi>3 ) continue;
            if( record[ (y+yi)*4+(x+xi)] ) continue;

            computerHelper( result, record, x+xi, y+yi, word );
        }
    }

    // un-choose
    record[y*4+x] = 0;
    word.pop_back();
    //out<< "un-select="<<getLetter(x,y)<<endl;

}
