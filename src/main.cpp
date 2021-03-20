#include <bits/stdc++.h>
#include "Console/Console.h"
#include "Puzzle/Puzzle.h"
#include "Table/Table.h"
#include "ConsoleUI/ConsoleUI.h"
#include <windows.h>
#define DEFAULT_SYMBOL u8"?"
#define NICE_CODE 69
#define BAD_CODE 96
using namespace std;

typedef unsigned int uint;
vector<string> PLACES;
int MAX_ROW_COUNT = 25;
int MAX_COL_COUNT = 46;

void processPlacesConfig(){
    ifstream placesConfig("places.config");
    string place;
    while(placesConfig>>place) PLACES.push_back(place);
    placesConfig.close();
}

void processPuzzleConfig(){
    ifstream puzzleConfig("puzzle.config");
    string str;
    while(puzzleConfig>>str){
        if(str=="MAX_ROW_COUNT"){
            cin>>str;
            MAX_ROW_COUNT = stoi(str);
        }
        if(str=="MAX_COL_COUNT"){
            cin>>str;
            MAX_COL_COUNT = stoi(str);
        }
    }
    puzzleConfig.close();
}

COORD boardToCartesianCoords(string inputString){
    COORD coord {X:0, Y:0};
    for(int i=0; i<inputString.size(); i++){
        if(inputString[i]>='0' && inputString[i]<='9'){
            coord.Y=coord.Y*10 + (int)(inputString[i]-'0');
            continue;
        }
        if(inputString[i]>='A' && inputString[i]<='Z'){
            coord.X=coord.X*26 + (int)(inputString[i]-'A'+1);
        }
    }
    coord.X--;
    coord.Y--;
    return coord;
}

bool validCoordinates(COORD start, COORD end){
    if(start.X==end.X) return true; //vertical
    if(start.Y==end.Y) return true; //horizontal
    if(fabs(start.X-end.X)==fabs(start.Y-end.Y)) return true; //diagonal
    return false;
}

string fetchWord(Table &table, COORD start, COORD end){
    string res;

    COORD dir {
        X: (end.X==start.X)?0:(end.X-start.X)/fabs(end.X-start.X),
        Y: (end.Y==start.Y)?0:(end.Y-start.Y)/fabs(end.Y-start.Y)
    };
    
    for(COORD pos=start; pos.X!=end.X || pos.Y!=end.Y; pos.X+=dir.X, pos.Y+=dir.Y){
        res += table[pos.Y][pos.X].val;
    }
    res += table[end.Y][end.X].val;

    return res;
}

bool validPlace(string place){
    for(auto i:PLACES){
        if(place==i) return true;
    }
    return false;
}

void markCells(Table& table, COORD start, COORD end){
    COORD dir {
        X: (end.X==start.X)?0:(end.X-start.X)/fabs(end.X-start.X),
        Y: (end.Y==start.Y)?0:(end.Y-start.Y)/fabs(end.Y-start.Y)
    };
     
    for(COORD pos=start; pos.X!=end.X || pos.Y!=end.Y; pos.X+=dir.X, pos.Y+=dir.Y){
        table[pos.Y][pos.X].clr = 250;
    }
    table[end.Y][end.X].clr = 250;
    table.update();
}

int main(){
    processPlacesConfig();
    processPuzzleConfig();
    adjustConsole("right",1000,1000);

    std::srand( ( unsigned int )std::time( nullptr ) );

    Matrix<string> puzzle(MAX_ROW_COUNT, MAX_COL_COUNT, DEFAULT_SYMBOL);
    generatePuzzle(PLACES, puzzle);
    
    Table table(puzzle.rowCount, puzzle.colCount, "table-message-queue");
    for(int i=0;i<puzzle.rowCount;i++){
        for(int j=0;j<puzzle.colCount;j++){
            table[i][j].val = puzzle[i][j];
        }
    }
    table.update();

    ConsoleUI consoleUI(PLACES);
    int foundCount = 0;
    set<pair<string,string>> visited;
    while(foundCount<PLACES.size()){
        string startBoardCoord, endBoardCoord;
        consoleUI.queryUser(startBoardCoord, endBoardCoord);

        COORD start = boardToCartesianCoords(startBoardCoord);
        COORD end = boardToCartesianCoords(endBoardCoord);

        if(visited.count({startBoardCoord, endBoardCoord})
            ||visited.count({endBoardCoord, startBoardCoord})){
            consoleUI.addLog("Koordinātes jau tika apskatītas :(", INFO_MESSAGE);
            continue;
        }

        visited.insert({startBoardCoord, endBoardCoord}),
        visited.insert({endBoardCoord, startBoardCoord});

        if(!validCoordinates(start, end)){
            consoleUI.addLog("Koordinātes ir nekorektas... :(", INFO_MESSAGE);
            continue;
        }

        string place = fetchWord(table, start, end);
        consoleUI.addLog("Atrastais vārds -\""+place+"\"", DEFAULT_CLR);
        cout<<place<<"\n";
        if(validPlace(place)){
            foundCount++;
            markCells(table, start, end);
            consoleUI.markPlace(place);
            consoleUI.addLog("Vārds veiksmīgi atzīmēts kā atrasts :)", SUCCESS_MESSAGE);
        }else{
            consoleUI.addLog("Vārds neietilpst sarakstā... :(", INFO_MESSAGE);
        }
    }
}
