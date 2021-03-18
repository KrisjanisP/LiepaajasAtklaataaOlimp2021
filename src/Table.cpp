#include "Table.h"
#include <windows.h>
using namespace std;

Table::Table(unsigned int _rowCount, unsigned int _colCount)
{
    rowCount = _rowCount;
    colCount = _colCount;
    buffer = new CharCell*[rowCount];
    for(int i=0;i<rowCount;i++){
        CharCell * sub_buffer = new CharCell[colCount];
        buffer[i] = sub_buffer;
    }
}

CharCell*& Table::operator[](unsigned int index)
{
    return buffer[index];
}  

Table::~Table()
{
    for(int i=0;i<rowCount;i++){
        delete[ ] buffer[i];
    }
    delete[ ] buffer;
}

void Table::print()
{
    std::string res;
    
    printTopDelimiter();
    cout<<endl;

    printColumnIndices();
    cout<<endl;

    printTableBase();
    cout<<endl;

    printBottomDelimiter();
    cout<<endl;
}

void Table::printTopDelimiter(){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	cout << "┌──";
	for(int i=0; i<std::to_string(rowCount).size(); i++) cout << "─";
    for(int i=0; i<colCount; i++) cout << "┬───";
	cout << "┐";
}

void Table::printColumnIndices(){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
    cout << "│  ";
	for(int i=0; i<std::to_string(rowCount).size(); i++) cout << " ";
	cout << "│";
	for(int i=0; i<colCount; i++){
        if(i<26){
            cout << " ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
            cout << (char)(i+'A');
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
            cout << " │";
        }
        else{
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
            cout << (char)(i/26+'A'-1);
            cout << (char)(i%26+'A');
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
            cout << " ";
            cout << "│";
        }
	}
}

void Table::printTableBase(){
	for(int i=0; i<rowCount; i++){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
        if(i) cout << '\n';
        cout << "├─";
        for(int j=0; j<=std::to_string(rowCount).size(); j++) cout << "─";
        for(int j=0; j<colCount; j++) cout << "┼───";
        cout << "┤\n";

        std::string nstring = std::to_string(i+1);
        cout << "│ ";
        for(int j=0; j<std::to_string(rowCount).size()-nstring.size(); j++)cout << " ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
        cout<< nstring;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
        cout << " │";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);

        for(int j=0; j<colCount; j++){
            cout << " ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), buffer[i][j].clr);
            cout << buffer[i][j].val;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
            cout << " │";
        }
	}
}

void Table::printBottomDelimiter(){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
    cout << "└──";
	for(int i=0; i<std::to_string(rowCount).size(); i++) cout << "─";
    for(int i=0; i<colCount; i++) cout << "┴───";
	cout << "┘";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

unsigned int Table::getWidthInChar(){
    return ((string)"└──").size()+std::to_string(rowCount).size()+colCount*((string)"┴───").size()+((string)"┘").size();
}