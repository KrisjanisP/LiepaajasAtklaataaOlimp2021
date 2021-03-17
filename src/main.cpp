#include <bits/stdc++.h>
#include <locale>
#include "Table.h"
#include <windows.h>
using namespace std;

vector<string> cities;

void testTable(){
    Table table(3,3);
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            table[i][j].val = 'A'+i+j;
            cout<<table[i][j].val<<" ";
        }
        cout<<"\n";
    }
    table.print();
}

void inputCities(){
    ifstream cityConfig("cities.config");
    string city;
    while(cityConfig>>city) cities.push_back(city);
    cityConfig.close();
}

int main(){
    SetConsoleOutputCP(65001);
    testTable();
    inputCities();
    for(auto city: cities) cout<<city<<" ";
}

