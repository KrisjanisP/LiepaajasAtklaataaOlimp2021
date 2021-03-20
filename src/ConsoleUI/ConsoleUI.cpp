
#include "ConsoleUI.h"

ConsoleUI::ConsoleUI(vector<string> places){
    for(auto place: places){
        cout<<place<<endl;
    }
    cursorPosition = {X:0,Y:places.size()};
    allPlaces = places;
}

void ConsoleUI::resetCursor(){

    SetConsoleCursorPosition(
        GetStdHandle( STD_OUTPUT_HANDLE ),
        cursorPosition
    );
}

void ConsoleUI::markPlace(string place){

}

void ConsoleUI::addLog(string message, int type_code){

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), type_code);
    cout<<message<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DEFAULT_CLR);
}

void ConsoleUI::queryUser(string& startBoardCoord, string& endBoardCoord){
    cout<<"Ievadi objekta nosaukuma sākuma koordināti: "<<flush;
    cin>>startBoardCoord;
    cout<<"Ievadi objekta nosaukuma beigu koordināti: "<<flush;
    cin>>endBoardCoord;
}