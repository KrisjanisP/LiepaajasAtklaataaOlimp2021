#include <bits/stdc++.h>
#include "../Utils/Utils.h"
#include "windows.h"

#define SUCCESS_MESSAGE 242
#define WARNING_MESSAGE 252
#define INFO_MESSAGE    249
#define DEFAULT_CLR     240
using namespace std;

class ConsoleUI{
public:
    ConsoleUI(vector<string> places);
    void resetCursor();
    void addLog(string message, int type_code);
    void queryUser(string& startBoardCoord, string& endBoardCoord);
    void queryUser(Coord& startCoord, Coord& endCoord);
    void markPlace(string place);
private:
    void outputList();
    COORD cursorPosition;
    vector<string> places;
    int leftColWidth, rightColWidth;
};