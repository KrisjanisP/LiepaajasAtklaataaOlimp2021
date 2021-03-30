
#include "ConsoleUI.h"

ConsoleUI::ConsoleUI(vector<string> places){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
    cout<<flush;
    system("cls");
    outputList(places);
    cursorPosition = {X:0,Y:places.size()};
    allPlaces = places;
}

void ConsoleUI::resetCursor(){

    SetConsoleCursorPosition(
        GetStdHandle( STD_OUTPUT_HANDLE ),
        cursorPosition
    );
}

vector<string> MultiByteCharsToStringsKvass(string& str)
{
    vector<string> res;
    char* s = &str[0];
    string multiByteChar;
    while (*s){
        if((*s & 0xc0) != 0x80 && multiByteChar.size()){
            res.push_back(multiByteChar);
            multiByteChar="";
        }
        multiByteChar+=*s;
        s++;
    }
    if(multiByteChar.size()) res.push_back(multiByteChar);
    return res;
}

void ConsoleUI::outputList(vector<string> places){
    int cell_width[2]={0, 0};
    int word_size[places.size()];
    for(int i=0; i<places.size(); i++){
        word_size[i] = MultiByteCharsToStringsKvass(places[i]).size();
        cell_width[i%2]=max(cell_width[i%2], word_size[i]);
    }
    string svitrinas0 = "";
    string svitrinas1 = "";

    for(int i=0; i<cell_width[0]; i++){
        svitrinas0 += "─";
    }
    for(int i=0; i<cell_width[1]; i++){
        svitrinas1 += "─";
    }

    cout << "┌──" << svitrinas0 << "┬──" << svitrinas1 << "┐\n";
    int height = (places.size()+1)/2;
	for(int i=0; i<height-1; i++){
        cout << "│ ";
        cout << places[i*2];
        for(int j = word_size[i*2]; j<cell_width[0]; j++){
            cout<<" ";
        }
        cout << " │ " << places[i*2+1];
        for(int j = word_size[i*2+1]; j<cell_width[1]; j++){
            cout<<" ";
        }
        cout << " │\n";
        cout << "├──" << svitrinas0 << "┼──" << svitrinas1 << "┤\n";
	}
    //hewwo
    cout << "│ ";
    cout << places[places.size() /2 * 2 -2];
    for(int i = word_size[places.size() /2 * 2 -2]; i<cell_width[0]; i++){
        cout<<" ";
    }
    cout << " │ ";
    if(places.size()%2==0){
        cout << places[places.size()-1];
        for(int i = word_size[places.size()-1]; i<cell_width[1]; i++){
            cout<<" ";
        }
    }
    else{
        for(int i=0; i<cell_width[1]; i++){
            cout<<" ";
        }
    }
    cout << " │\n";
    cout << "└──" << svitrinas0 << "┴──" << svitrinas1 << "┘\n";
}

void ConsoleUI::markPlace(string place){
    //
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