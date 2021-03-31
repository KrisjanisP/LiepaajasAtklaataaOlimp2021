
#include "ConsoleUI.h"

ConsoleUI::ConsoleUI(vector<string> _places){
    //Set private class variable
    places = _places;

    //Set background color
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
    cout<<flush;
    system("cls");

    //Output all places to be found
    outputList();
    cursorPosition = {X:0,Y:(short)places.size()};
}

void ConsoleUI::outputList(){
    int word_size[places.size()];
    int cell_width[2]={0,0};
    for(int i=0; i<places.size(); i++){
        word_size[i] = stringToUTF8Container(places[i]).size();
        if(i%2) rightColWidth = word_size[i];
        else leftColWidth = word_size[i];
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
        cout << " │ ";
        cout << places[i*2+1];
        for(int j = word_size[i*2+1]; j<cell_width[1]; j++){
            cout<<" ";
        }
        cout << " │\n";
        cout << "├──" << svitrinas0 << "┼──" << svitrinas1 << "┤\n";
	}
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
    COORD now_coord = GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE));
    int place_index = -1;
    for(int i=0;i<places.size();i++)
        if(places[i]==place)
            place_index = i;
    
    COORD coord{
        Y: (place_index)/2 * 2 + 1
    };
    if(place_index%2==0)coord.X = 2;
    else coord.X = leftColWidth + 5;
    //Set cursor to markable word coordinates
    SetConsoleCursorPosition(
        GetStdHandle( STD_OUTPUT_HANDLE ),
        coord
    );
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 250);
    cout<<places[place_index]<<flush;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
    //Reset the cursor to previous coordinates
    SetConsoleCursorPosition(
        GetStdHandle( STD_OUTPUT_HANDLE ),
        now_coord
    );
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

Coord boardToCartesianCoords(string inputString){
    Coord coord = {0, 0};
    for(int i=0; i<inputString.size(); i++){
        if(inputString[i]>='0' && inputString[i]<='9'){
            coord.second=coord.second*10 + (int)(inputString[i]-'0');
            continue;
        }
        if(inputString[i]>='A' && inputString[i]<='Z'){
            coord.first=coord.first*26 + (int)(inputString[i]-'A'+1);
        }
    }
    coord.first--;
    coord.second--;
    return coord;
}

bool validCoordStr(string str){
    //if the string is too long
    if(str.size()>5) return false;
    string letterPart;
    int i=0;
    for(;i<str.size();i++){
        if(str[i]>='0'&&str[i]<='9') break;
        letterPart += str[i];
    }
    //if there are no numbers
    if(i==str.size()) return false;
    //if there are too many letters or no letters
    if(letterPart.size()>2||letterPart.size()==0) return false;
    if(str[i]=='-') return false;
    if(str[i]=='0') return false;
    i++;
    for(;i<str.size();i++){
        if(str[i]>='0'&&str[i]<='9') continue;
        return false;
    } 
    return true;
}

void ConsoleUI::queryUser(Coord& startCoord, Coord& endCoord){
    
    string startBoardCoord, endBoardCoord;
    //acquire both strings
    queryUser(startBoardCoord, endBoardCoord);
    //convert both strings to uppercase
    for(int i=0;i<startBoardCoord.size();i++) startBoardCoord[i] = toupper(startBoardCoord[i]);
    for(int i=0;i<endBoardCoord.size();i++) endBoardCoord[i] = toupper(endBoardCoord[i]);

    if(validCoordStr(startBoardCoord)==false||validCoordStr(endBoardCoord)==false){
        addLog("Koordinātes ievadītas nekorekti :(", INFO_MESSAGE);
        queryUser(startCoord, endCoord);
    }

    startCoord = boardToCartesianCoords(startBoardCoord);
    endCoord = boardToCartesianCoords(endBoardCoord);
}