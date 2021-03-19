#include <bits/stdc++.h>
#include "Console/Console.h"
#include "Puzzle/Puzzle.h"
#include "Table/Table.h"
#include <windows.h>
#define MAX_ROW_COUNT 25
#define MAX_COL_COUNT 46
#define DEFAULT_SYMBOL u8"?"
using namespace std;

typedef unsigned int uint;

vector<string> places;

void inputPlaces(){
    ifstream placeConfig("places.config");
    string place;
    while(placeConfig>>place) places.push_back(place);
    placeConfig.close();
}

void testTable(){
    Table table(20, 20, "table-message-queue");
    for(int i=0;i<table.rowCount;i++){
        for(int j=0;j<table.colCount;j++){
            table[i][j].val = 'A';
        }
    }
    table.update();
}

void queryUser(){
    cout<<"here!!!";
}

int main(){
    inputPlaces();
    adjustConsole("right",1000,1000);
    //testTable();

    //enable random number
    std::srand( ( unsigned int )std::time( nullptr ) );

    Matrix<string> puzzle(MAX_ROW_COUNT, MAX_COL_COUNT, DEFAULT_SYMBOL);
    generatePuzzle(places, puzzle);
    
    Table table(puzzle.rowCount, puzzle.colCount, "table-message-queue");
    for(int i=0;i<puzzle.rowCount;i++){
        for(int j=0;j<puzzle.colCount;j++){
            table[i][j].val = puzzle[i][j];
        }
    }
    table.update();
    queryUser();
    system("pause");
}
/*
int answerCheck(uint beginX, uint beginY, uint endX, uint endY, Table table){
    if(beginX != endX && beginY != endY && fabs(beginX-beginY) != fabs(endX-endY) ){
        return -1;
    }

    string guessedWord = "";
    COORD myLocation {
        X: (short int)beginX,
        Y: (short int)beginY
    };
    COORD myDirection {
        X: 0, 
        Y: 0
    };

    if(endX - beginX > 0) myDirection.X = 1;
    else if(endX - beginX < 0) myDirection.X = -1;
    if(endY - beginY > 0) myDirection.Y = 1;
    else if(endY - beginY < 0) myDirection.Y = -1;

    for(; !(myLocation.X==endX && myLocation.Y==endY);){
        guessedWord.push_back(table[myLocation.Y][myLocation.X].val);
    }

    for(int i=0; i<places.size(); i++){
        if(guessedWord == places[i]){
            return i;
        }
    }
    return -1;
}

COORD coordinateConversion(string inputString){
    COORD coord;
    for(int i=0; i<inputString.size(); i++){
        if(inputString[i]>=48 && inputString[i]<=57){
            coord.X=coord.X*10 + (int)(inputString[i]-'0');
        }
        else{
            if(i==inputString.size()-1){
                coord.Y++;
                coord.Y *= 26;
            }
            else coord.Y += (int)(inputString[i]-'A');
        }
    }
    coord.X--;
    return coord;
}

void checkInput(string inputBegin, string inputEnd, Table &table){
    COORD wordBegin = coordinateConversion(inputBegin);
    COORD wordEnd = coordinateConversion(inputEnd);
    
    int wordIndex = answerCheck(wordBegin.X, wordBegin.Y, wordEnd.X, wordEnd.Y, table);
    if(wordIndex == -1){
        //nav pareizi
    }
    else{
        COORD myLocation = wordBegin;
        COORD myDirection {
            X: 0, 
            Y: 0
        };
        if(wordEnd.X - wordBegin.X > 0) myDirection.X = 1;
        else if(wordEnd.X - wordBegin.X < 0) myDirection.X = -1;
        if(wordEnd.Y - wordBegin.Y > 0) myDirection.Y = 1;
        else if(wordEnd.Y - wordBegin.Y < 0) myDirection.Y = -1;
        
        for(; !(myLocation.X==wordEnd.X && myLocation.Y==wordEnd.Y);){
            table[myLocation.Y][myLocation.X].clr = 250;
        }
    }
}

*/