#include <bits/stdc++.h>
#include "Console/Console.h"
#include "Puzzle/Puzzle.h"
#include "Table/Table.h"
#include "ConsoleUI/ConsoleUI.h"
#include "Utils/Utils.h"
#include "Config/Config.h"
#include <chrono>
#include <windows.h>
using namespace std;

typedef unsigned int uint;

bool validCoordinates(Coord start, Coord end){
    if(start.first>=COL_COUNT) return false;
    if(start.second>=ROW_COUNT) return false;
    if(start.first==end.first) return true; //vertical
    if(start.second==end.second) return true; //horizontal
    if(fabs(start.first-end.first)==fabs(start.second-end.second))
        return true; //diagonal
    return false;
}

void initSettings(){
    processConfig();
    adjustConsole("right",1000,1000);
    std::srand( ( unsigned int )std::time( nullptr ) );
}

void initPuzzle(Table& table){
    Matrix<string> puzzle(ROW_COUNT, COL_COUNT, DEFAULT_SYMBOL);
    generatePuzzle(PLACES, puzzle);
    for(int i=0;i<puzzle.rowCount;i++){
        for(int j=0;j<puzzle.colCount;j++){
            table[i][j].val = puzzle[i][j];
        }
    }
}

vector<Coord> charLocations;

void placeLastWord(Table& table){
    string lastWordStr = LAST_WORD;
    UTF8Container lastWord = stringToUTF8Container(lastWordStr);
    for(int l=0;l<lastWord.size();l++){
        int i = fetchRandomInt(0, ROW_COUNT-1);
        int j = fetchRandomInt(0, COL_COUNT-1);
        while(table[i][j].val!=DEFAULT_SYMBOL){
            i = fetchRandomInt(0, ROW_COUNT-1);
            j = fetchRandomInt(0, COL_COUNT-1);
        }
        table[i][j].val = lastWord[l];
        charLocations.push_back({i, j});
    }
}

void fillRemaining(Table& table){
    if(!FILL_REMAINING) return;
    UTF8Container chars = getLatvianUppercaseChars();
    for(int i=0;i<ROW_COUNT;i++){
        for(int j=0;j<COL_COUNT;j++){
            if(table[i][j].val!=DEFAULT_SYMBOL) continue;
            table[i][j].val = chars[fetchRandomInt(0, chars.size()-1)];
        }
    }
}

void fillTable(Table& table){
    initPuzzle(table);
    placeLastWord(table);
    fillRemaining(table);
    table.update();    
}

void queryUser(Table& table){
    ConsoleUI consoleUI(PLACES);
    int foundCount = 0;
    set<pair<Coord,Coord>> visited;
    while(foundCount<PLACES.size()){
        Coord startCoord, endCoord;
        //Acquire coordinates from input and validate their format
        consoleUI.queryUser(startCoord, endCoord);

        //Check if coordinates were already processed
        if(visited.count({startCoord, endCoord})){
            consoleUI.addLog("Koordinātes jau tika apskatītas :(", INFO_MESSAGE);
            continue;
        }
        visited.insert({startCoord, endCoord});

        //Proceed if coordinate values ar valid
        if(!validCoordinates(startCoord, endCoord)){
            consoleUI.addLog("Koordinātes ir nekorektas... :(", INFO_MESSAGE);
            continue;
        }
        
        //Fetch coordinate described word from table
        string place = table.fetchWord(startCoord, endCoord);
        consoleUI.addLog("Atrastais vārds:", DEFAULT_CLR);
        cout<<place<<endl;

        int place_index=-1;
        for(int i=0; i<PLACES.size(); i++){
            if(place == PLACES[i])
                place_index=i;
        }
        //Check if word is included in the list
        if(place_index==-1){
            consoleUI.addLog("Vārds neietilpst sarakstā... :(", INFO_MESSAGE);
            continue;
        }

        //Mark the word as found
        table.markCells(startCoord, endCoord);
        consoleUI.markPlace(place);
        foundCount++;
        consoleUI.addLog("Vārds veiksmīgi atzīmēts kā atrasts :)", SUCCESS_MESSAGE);
    }
    system("cls");
    for(int i=0;i<charLocations.size();i++){
        table[charLocations[i].first][charLocations[i].second].clr = 252;
    }
    table.update();
    string end_word="";
    cout<<"Atmini, ievadi vārdu no iezīmētajiem burtiem!"<<endl;
    cout<<"(ar visiem lielajiem burtiem, bez garumzīmēm, domuzīmes NEaizstājot ar atstarpēm)"<<endl;
    cin >> end_word;
    while(end_word != u8"JAUNAKAIS-VIEDAIS-LUKSOFORS"){
        cout<<end_word<<endl;
        cout<<"Nepareizi... mini vēlreiz"<<endl;
        cin >> end_word;
    }
    cout<<"Pareizi! Tu pabeidzi šo burtu jūkli!"<<endl;
}

std::string time_string() {
    std::chrono::system_clock::time_point time_point = std::chrono::system_clock::now();
    std::time_t time_t = std::chrono::system_clock::to_time_t(time_point);
    std::tm* tm = std::localtime(&time_t);

    std::stringstream stream;
    stream << std::put_time(tm, "%Y-%m-%d %X");
    return stream.str();
}

int main(){
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    initSettings();
    Table table(ROW_COUNT, COL_COUNT, "table-message-queue");
    fillTable(table);
    queryUser(table);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Tavs izpildes laiks - " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() << " sekundes." << std::endl;
    
    std::ofstream outfile;
    outfile.open("results.txt", std::ios_base::app);
    outfile << time_string()<<"   "<<std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() << "[s]" <<endl;
    std::cout << "Tas tika pieglabāts results.txt" <<endl;
    system("pause");
}
