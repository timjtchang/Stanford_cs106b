/*
 * File: Life.cpp
 * --------------
 * Assignment 1 for Stanford CS106b
 * @author Tim J. Chang
 * @version 2022/08/02
 */

#include <iostream>
#include <fstream>
#include "console.h"
#include "queue.h"
#include "simpio.h"
#include "gwindow.h"
#include "filelib.h"
using namespace std;

void printWelcome();
bool checkWrapping();
void implementGeneration(vector<vector<char>>&, bool);

void workAnimate( vector<vector<char>>&, bool);
void workTick( vector<vector<char>>&, bool);

void getMap( vector<vector<char>>& );
void generateNewMap( vector<vector<char>>&, vector<vector<char>>&, bool );
int countNeighbors( vector<vector<char>>&, int, int, bool);
void printMap( vector<vector<char>>& );


int main(){


    vector<vector<char>> map;
    bool ifWrapping;

    printWelcome();
    getMap( map );
    ifWrapping = checkWrapping();

    cout<< "document map:" <<endl;
    printMap(map);

    implementGeneration( map, ifWrapping );
    cout<< "Have a Nice Life!" <<endl;
    return 0;

}

void implementGeneration( vector<vector<char>>& map, bool ifWrapping){

    while(1){

        char mode = getChar("a)nimate, t)ick, q)uit?","Invalid choice; please try again.");
        mode = toLowerCase(mode);

        if( mode == 'a') workAnimate( map, ifWrapping );
        else if( mode == 't') workTick( map, ifWrapping );
        else if( mode == 'q') break;
        else{

            cout<<"Invalid choice; please try again."<<endl;
            continue;
        }
    }

    return;

}

void workTick( vector<vector<char>>& map, bool ifWrapping ){

    vector<vector<char>> new_map;
    generateNewMap( new_map, map, ifWrapping);
    map = new_map;

    printMap(map);
    return;

}

void workAnimate( vector<vector<char>>& map, bool ifWrapping){

    int frames = getInteger( "How many frames?", "Illegal integer format. Try again.");


    for( int i=0 ; i<frames ; i++ ){

        clearConsole();
        vector<vector<char>> new_map;
        generateNewMap( new_map, map, ifWrapping);
        map = new_map;

        printMap(map);

        pause(50);


    }

    return;
}

bool checkWrapping(){

    bool ifWrapping = 0;
    char ifWrapping_ch;

    while(1){

        ifWrapping_ch = getChar("Should the simulation wrap around the grid(y/n)?");
        toLowerCase(ifWrapping_ch);

        if( ifWrapping_ch == 'y'){

            ifWrapping=1;
            break;
        }else if( ifWrapping_ch == 'n'){

            ifWrapping=0;
            break;
        }

    }

    return ifWrapping;


}
void printWelcome(){

    cout<< "Welcome to the CS 106B Game of Life,\n";
    cout<< "a simulation of the lifecycle of a bacteria colony.\n";
    cout<< "Cells (X) live and die by the following rules:";
    cout<< "- A cell with 1 or fewer neighbors dies.\n";
    cout<< "- Location with 2 neighbors remain stable.\n";
    cout<< "- Loaction with 3 neighbors will create Life.\n"<<endl;


}
void printMap( vector<vector<char>>& map ){

    for( auto const& row_map:map){

        for( auto const& ch:row_map){

            cout<< ch;
        }

        cout<<endl;
    }

}

int countNeighbors( vector<vector<char>>& map, int row, int col, bool ifWrapping ){

    int count=0;
    int current_r = 0;
    int current_c = 0;

    for( int r=-1 ; r<2 ; r++){

        for( int c=-1 ; c<2 ; c++ ){

            if( ifWrapping ){

                current_r = ( row+map.size()+r )%map.size();
                current_c = ( col+map.at(current_r).size()+c)%map.at(current_r).size();

            }else{

                current_r = row+r;
                current_c = col+c;
            }

            if( current_r>=map.size() || current_r<0 ) break;
            if( current_c>=map.at(current_r).size() || current_c<0) continue;
            if( current_r == row && current_c == col ) continue;

            if( map[current_r][current_c] == 'X' ) count++;
        }
    }


    return count;
}

void generateNewMap( vector<vector<char>>& new_map, vector<vector<char>>& last_map, bool ifWrapping){

    int count=0;
    for( int r=0; r<last_map.size() ; r++ ){

        vector<char> tmp;

        for( int c=0; c<last_map[r].size() ; c++ ){

            count = countNeighbors( last_map, r, c, ifWrapping );

            //cout<< count;
            if( count == 0 || count == 1 || count>=4 ) tmp.push_back('-');
            else if( count == 2 ) tmp.push_back( last_map[r][c] );
            else if( count == 3 ) tmp.push_back( 'X' );
        }
        //cout<<endl;

        new_map.push_back( tmp );
    }
}

void getMap( vector<vector<char>>& map){

    string fileName;
    ifstream input;

    while(1){
        fileName= getLine( "Grid input file name?");
        fileName = "res/"+fileName;

        if( !fileExists(fileName) ) cout<< "Unable to open that file. Try again."<<endl;
        else break;

    }

    input.open(fileName);

    if( input.fail()){

        cout<< " it is fail "<<endl;
    }

    string line;
    int row=0;
    int col=0;

    getline(input,  line);
    row = stringToInteger(line);
    getline(input, line);
    col = stringToInteger(line);

    int tmp_row = 0;

    while( getline( input, line) ){

        vector<char> ch;
        for( int i=0 ; i<line.length() ; i++ ){

           ch.push_back( line[i] );

        }

        map.push_back( ch );

        tmp_row++;
        if( tmp_row == row ) break;
    }
    input.close();

}


