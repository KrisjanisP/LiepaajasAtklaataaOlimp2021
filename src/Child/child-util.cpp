#include <bits/stdc++.h>
#include "windows.h"
#include "child-util.h"
#define BLACK_FG_WHITE_BG_CLR 240
#define PURPLE_FG_WHITE_BG_CLR 245
#define GREY_FG_WHITE_BG_CLR 247

using namespace std;

void constructTable(uint rowCount, uint colCount)
{   
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
    cout<<value<<flush;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLACK_FG_WHITE_BG_CLR);
}


void printTopDelimiter(uint rowCount, uint colCount){
	cout << "┌──";
	for(int i=0; i<to_string(rowCount).size(); i++) cout << "─";
    for(int i=0; i<colCount; i++) cout << "┬───";
	cout << "┐";
}

void printColumnIndices(uint rowCount, uint colCount){
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
    cout << "└──";
	for(int i=0; i<to_string(rowCount).size(); i++) cout << "─";
    for(int i=0; i<colCount; i++) cout << "┴───";
	cout << "┘";
}
