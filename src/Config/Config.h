#include <bits/stdc++.h>
#define PLACE_CONFIG_FILE "places.config"
#define PUZZLE_CONFIG_FILE "puzzle.config"
#define LAST_WORD u8"Jaunākais-viedais-luksofors"
#define DEFAULT_SYMBOL u8"?"
#define NICE_CODE 69
#define BAD_CODE 96

using namespace std;

vector<string> PLACES;
int ROW_COUNT = 25;
int COL_COUNT = 46;
bool FILL_REMAINING = true;

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
        if(str=="ROW_COUNT"){
            puzzleConfig>>str;
            ROW_COUNT = stoi(str);
        }
        if(str=="COL_COUNT"){
            puzzleConfig>>str;
            COL_COUNT = stoi(str);
        }
        if(str=="FILL_REMAINING"){
            puzzleConfig>>str;
            if(str=="TRUE") FILL_REMAINING = true;
            else if(str=="FALSE") FILL_REMAINING = false;
        }
    }
    puzzleConfig.close();
}

void processConfig(){
    processPlacesConfig();
    processPuzzleConfig();
}