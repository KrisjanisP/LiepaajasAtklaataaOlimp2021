#include <bits/stdc++.h>
#include "windows.h"

#define SUCCESS_MESSAGE FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define WARNING_MESSAGE FOREGROUND_RED | FOREGROUND_INTENSITY
#define INFO_MESSAGE    FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY
#define DEFAULT_CLR     FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY
using namespace std;

class ConsoleUI{
public:
    ConsoleUI(vector<string> places);
    void resetCursor();
    void outputList(vector<string> places);
    void markPlace(string place);
    void addLog(string message, int type_code);
    void queryUser(string& startBoardCoord, string& endBoardCoord);
private:
    COORD cursorPosition;
    vector<string> allPlaces;
    vector<string> markedPlaces;
};