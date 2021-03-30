#include <bits/stdc++.h>
#include "Console/Console.h"
#include "Puzzle/Puzzle.h"
#include "Table/Table.h"
#include "ConsoleUI/ConsoleUI.h"
#include <windows.h>
#define LAST_WORD u8"Jaunākais viedais luksofors"
#define PLACE_CONFIG_FILE "places.config"
#define PUZZLE_CONFIG_FILE "puzzle.config"
#define DEFAULT_SYMBOL u8"?"
#define NICE_CODE 69
#define BAD_CODE 96
using namespace std;

typedef unsigned int uint;
vector<string> PLACES;
int MAX_ROW_COUNT = 25;
int MAX_COL_COUNT = 46;

//utf8 string characters may span multiple bytes
//And so the string is converted to vector of strings
vector<string> MultiByteCharsToStringsRupjmaize(string& str)
{
    vector<string> res;
    char* s = &str[0];
    string multiByteChar;
    while (*s){
        if((*s & 0xc0) != 0x80 && multiByteChar.size()){
            res.push_back(multiByteChar);
            multiByteChar="";
        }
        multiByteChar+=*s;
        s++;
    }
    if(multiByteChar.size()) res.push_back(multiByteChar);
    return res;
}

void processPlacesConfig(){
    ifstream placesConfig(PLACE_CONFIG_FILE);
    string place;
    while(placesConfig>>place) PLACES.push_back(place);
    placesConfig.close();
}

void processPuzzleConfig(){
    ifstream puzzleConfig(PUZZLE_CONFIG_FILE);
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
    if(start.X>=MAX_COL_COUNT) return false;
    if(start.Y>=MAX_ROW_COUNT) return false;
    if(start.X==end.X) return true; //vertical
    if(start.Y==end.Y) return true; //horizontal
    int x1=start.X, x2=end.X;
    int y1=start.Y, y2=end.Y;
    if(fabs(x1-x2)==fabs(y1-y2)) return true; //diagonal
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

bool validCoordStr(string str){
    if(str.size()>5) return false;
    string letterPart;
    int i=0;
    for(;i<str.size();i++){
        if(str[i]>='0'&&str[i]<='9') break;
        letterPart += str[i];
    }
    if(i==str.size()) return false;
    if(letterPart.size()>2||letterPart.size()==0) return false;
    if(str[i]=='-') return false;
    if(str[i]=='0') return false;
    i++;
    for(;i<str.size();i++){
        if(str[i]>='0'&&str[i]<='9') continue;
        return false;
    } 
    return true;
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
    string lastWord = LAST_WORD;
    vector<string> lastWordVec = 
        MultiByteCharsToStringsRupjmaize(lastWord);
    vector<COORD> charLocations;
    for(int l=0;l<lastWordVec.size();l++){
        int low_dist_i = 0, low_dist_j = 0;
        int high_dist_i = puzzle.rowCount-1;
        int high_dist_j = puzzle.colCount-1;
        int k_i = low_dist_i + std::rand() % (high_dist_i - low_dist_i); 
        int k_j = low_dist_j + std::rand() % (high_dist_j - low_dist_j); 
        while(table[k_i][k_j].val!=DEFAULT_SYMBOL){
            k_i = low_dist_i + std::rand() % (high_dist_i - low_dist_i); 
            k_j = low_dist_j + std::rand() % (high_dist_j - low_dist_j);
        }
        table[k_i][k_j].val = lastWordVec[l];
        table[k_i][k_j].clr = 252;
        charLocations.push_back({k_i, k_j});
    }
    //fill in the gaps
    for(int i=0;i<puzzle.rowCount;i++){
        for(int j=0;j<puzzle.colCount;j++){
            if(table[i][j].val!=DEFAULT_SYMBOL) continue;
            vector<string> vec = {
                u8"A", u8"Ā", u8"B",
                u8"C", u8"Č", u8"D",
                u8"E", u8"Ē", u8"F",
                u8"G", u8"Ģ", u8"H",
                u8"I", u8"Ī", u8"J",
                u8"K", u8"Ķ", u8"L",
                u8"Ļ", u8"M", u8"N",
                u8"Ņ", u8"O", u8"P",
                u8"R", u8"S", u8"Š",
                u8"T", u8"U", u8"Ū",
                u8"V", u8"Z", u8"Ž"
            };
            int low_dist_a = 0;
            int high_dist_a = vec.size()-1;
            int k_a = low_dist_a + std::rand() % (high_dist_a - low_dist_a);
            table[i][j].val = vec[k_a];
        }
    }
    table.update();

    ConsoleUI consoleUI(PLACES);
    int foundCount = 0;
    set<pair<string,string>> visited;
    while(foundCount<PLACES.size()){
        string startBoardCoord, endBoardCoord;
        consoleUI.queryUser(startBoardCoord, endBoardCoord);
        if(validCoordStr(startBoardCoord)==false||validCoordStr(endBoardCoord)==false){
            consoleUI.addLog("Koordinātes ievadītas nekorekti :(", INFO_MESSAGE);
            continue;
        }
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
        int place_index=-1;
        for(int i=0; i<PLACES.size(); i++){
            if(place == PLACES[i]){
                place_index=i;
            }
        }
        //
        consoleUI.addLog("Atrastais vārds:", DEFAULT_CLR);
        cout<<place<<"\n";
        if(place_index!=-1){
            foundCount++;
            markCells(table, start, end);
            consoleUI.markPlace(place);
            consoleUI.addLog("Vārds veiksmīgi atzīmēts kā atrasts :)", SUCCESS_MESSAGE);
        }else{
            consoleUI.addLog("Vārds neietilpst sarakstā... :(", INFO_MESSAGE);
        }
    }
    //system("cls");
    string end_word="";
    cout<<"Ievadi vārdu no iezīmētajiem burtiem!\n"<<flush;
    cin >> end_word;
    while(end_word != u8"Jaunākais viedais luksofors"){
        cout<<"Nepareizi, mini vēlreiz\n"<<flush;
        cin >> end_word;
    }
    cout<<"Pareizi! Tu pabeidzi šo burtu jūkli!";
}
