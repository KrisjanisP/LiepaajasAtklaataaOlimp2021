#include <bits/stdc++.h>
#include "Table.h"
#include "Console.h"
#include <windows.h>
using namespace std;

vector<string> cities;

void inputCities()
{
    ifstream cityConfig("cities.config");
    string city;
    while(cityConfig>>city) cities.push_back(city);
    cityConfig.close();
}

int main(){
    //inputCities();
    //for(auto city: cities) cout<<city<<" ";
    Table table(30,30);
    for(int i=0;i<table.rowCount;i++){
        for(int j=0;j<table.colCount;j++){
            table[i][j].val = 'A';
        }
    }
    unsigned int tableWidthInChar = table.getWidthInChar();
    AdjustConsole(L"Lucida Console",14,20,tableWidthInChar);
    table.print();

    //freeze conosle
    while(true){
        cin.get();
        system("cls");
        table.print();
    }
}

