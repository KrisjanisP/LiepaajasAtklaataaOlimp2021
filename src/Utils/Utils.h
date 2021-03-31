#ifndef UTILS_H
#define UTILS_H

#include "bits/stdc++.h"
#include "windows.h"

using namespace std;

typedef pair<int, int> Coord;

//utf8 string characters may span multiple bytes
//and so the string is converted to vector of strings
//where each string is essentially an UTF8
typedef vector<string> UTF8Container;

UTF8Container stringToUTF8Container(string& str);

UTF8Container getLatvianUppercaseChars();

int fetchRandomInt(int low, int high);

COORD GetConsoleCursorPosition(HANDLE hConsoleOutput);

#endif