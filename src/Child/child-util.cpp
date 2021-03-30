#include <bits/stdc++.h>
#include "windows.h"
#include "child-util.h"
#define BLACK_FG_WHITE_BG_CLR 240
#define PURPLE_FG_WHITE_BG_CLR 245
#define GREY_FG_WHITE_BG_CLR 247

using namespace std;

uint N, M;//rowCount and colCount accordingly

void constructTable(uint rowCount, uint colCount)
{   
    N = rowCount, M = colCount;

    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREY_FG_WHITE_BG_CLR);
    printTopDelimiter(rowCount, colCount);
    cout<<endl;  

    system("cls");
    printTopDelimiter(rowCount, colCount);
    cout<<endl;  
    printColumnIndices(rowCount, colCount);
    cout<<endl;

    printTableBase(rowCount, colCount);
    cout<<endl;

    printBottomDelimiter(rowCount, colCount);
    cout<<endl;
    
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLACK_FG_WHITE_BG_CLR);
}

string toLatvianUpper(string value){
    if(value==u8"?") value=u8"?";
    else if(value==u8"a") value=u8"A";
    else if(value==u8"ā") value=u8"Ā";
    else if(value==u8"b") value=u8"B";
    else if(value==u8"c") value=u8"C";
    else if(value==u8"č") value=u8"Č";
    else if(value==u8"d") value=u8"D";
    else if(value==u8"e") value=u8"E";
    else if(value==u8"ē") value=u8"Ē";
    else if(value==u8"f") value=u8"F";
    else if(value==u8"g") value=u8"G";
    else if(value==u8"ģ") value=u8"Ģ";
    else if(value==u8"h") value=u8"H";
    else if(value==u8"i") value=u8"I";
    else if(value==u8"ī") value=u8"Ī";
    else if(value==u8"j") value=u8"J";
    else if(value==u8"k") value=u8"K";
    else if(value==u8"ķ") value=u8"Ķ";
    else if(value==u8"l") value=u8"L";
    else if(value==u8"ļ") value=u8"Ļ";
    else if(value==u8"m") value=u8"M";
    else if(value==u8"n") value=u8"N";
    else if(value==u8"ņ") value=u8"Ņ";
    else if(value==u8"o") value=u8"O";
    else if(value==u8"p") value=u8"P";
    else if(value==u8"r") value=u8"R";
    else if(value==u8"s") value=u8"S";
    else if(value==u8"š") value=u8"Š";
    else if(value==u8"t") value=u8"T";
    else if(value==u8"u") value=u8"U";
    else if(value==u8"ū") value=u8"Ū";
    else if(value==u8"v") value=u8"V";
    else if(value==u8"z") value=u8"Z";
    else if(value==u8"ž") value=u8"Ž";
    return value;
}

void updateTable(TableUpdate tableUpdate, uint rowCount, uint colCount){
    COORD cellCoord {
        X: short(4*tableUpdate.col + 5 + to_string(rowCount).size()),
        Y: short(2*tableUpdate.row + 3)
    };
    SetConsoleCursorPosition(
        GetStdHandle( STD_OUTPUT_HANDLE ),
        cellCoord
    );
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), tableUpdate.clr);
    string value;
    for(int i=0;i<tableUpdate.byteCount;i++){
        value += tableUpdate.arr[i];
    }
    value = toLatvianUpper(value);
    cout<<value<<flush;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLACK_FG_WHITE_BG_CLR);
    
    COORD belowTable {
        X: short(0),
        Y: short(2*N + 3)
    };
    SetConsoleCursorPosition(
        GetStdHandle( STD_OUTPUT_HANDLE ),
        belowTable
    );
}


void printTopDelimiter(uint rowCount, uint colCount){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREY_FG_WHITE_BG_CLR);
    cout << "┌──";
	for(int i=0; i<to_string(rowCount).size(); i++) cout << "─";
    for(int i=0; i<colCount; i++) cout << "┬───";
	cout << "┐";
}

void printColumnIndices(uint rowCount, uint colCount){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREY_FG_WHITE_BG_CLR);
    cout << "│  ";
	for(int i=0; i<to_string(rowCount).size(); i++) cout << " ";
	cout << "│";
	for(int i=0; i<colCount; i++){
        if(i<26){
            cout << " ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), PURPLE_FG_WHITE_BG_CLR);
            cout << (char)(i+'A');
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREY_FG_WHITE_BG_CLR);
            cout << " │";
        }
        else{
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), PURPLE_FG_WHITE_BG_CLR);
            cout << (char)(i/26+'A'-1);
            cout << (char)(i%26+'A');
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREY_FG_WHITE_BG_CLR);
            cout << " │";
        }
	}
}

void printTableBase(uint rowCount, uint colCount){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREY_FG_WHITE_BG_CLR);
	for(int i=0; i<rowCount; i++){
        if(i) cout << '\n';
        cout << "├─";
        for(int j=0; j<=to_string(rowCount).size(); j++) cout << "─";
        for(int j=0; j<colCount; j++) cout << "┼───";
        cout << "┤\n";

        string nstring = to_string(i+1);
        cout << "│ ";
        for(int j=0; j<to_string(rowCount).size()-nstring.size(); j++)cout << " ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), PURPLE_FG_WHITE_BG_CLR);
        cout<< nstring;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREY_FG_WHITE_BG_CLR);
        cout << " │";

        for(int j=0; j<colCount; j++){
            cout << " ";
            cout << "?";
            cout << " │";
        }
	}
}

void printBottomDelimiter(uint rowCount, uint colCount){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREY_FG_WHITE_BG_CLR);
    cout << "└──";
	for(int i=0; i<to_string(rowCount).size(); i++) cout << "─";
    for(int i=0; i<colCount; i++) cout << "┴───";
	cout << "┘";
}
