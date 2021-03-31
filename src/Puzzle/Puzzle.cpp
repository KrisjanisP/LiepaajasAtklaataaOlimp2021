#include "Puzzle.h"

using namespace std;

vector<string> MultiByteCharsToStrings(string& str)
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

void outputPuzzle(Matrix<string>& puzzle)
{
    cout<<"Printing puzzle"<<endl;
    for(int i=0;i<puzzle.rowCount;i++){
        for(int j=0;j<puzzle.colCount;j++){
            string str;
            str+=puzzle[i][j];
            cout<<str;
            cout<<" ";
        }
        cout<<endl;
    }
    cout<<"\n";
    cout<<"\n";
}

int xOffsetByDir[8] = {0, 1, 1, 1, 0, -1, -1, -1};
int yOffsetByDir[8] = {1, 1, 0, -1, -1, -1, 0, 1};

bool canPlace(int y, int x, int dir, vector<string>& UTF8Word, Matrix<string>& puzzle)
{
    for(int i=0;i<UTF8Word.size();i++){
        int nY = y+i*yOffsetByDir[dir];
        int nX = x+i*xOffsetByDir[dir];
        if(nY<0||nY>=puzzle.rowCount) return false;
        if(nX<0||nX>=puzzle.colCount) return false;
        if(puzzle[nY][nX]==u8"?") continue;
        if(puzzle[nY][nX]==UTF8Word[i]) continue;
        return false;
    }
    return true;
}

//places the word and returns overwritten characters
void placeWord(vector<string>& chars, int y, int x, int dir, vector<string>& UTF8Word, Matrix<string>& puzzle)
{
    for(int i=0;i<UTF8Word.size();i++){
        int nY = y+i*yOffsetByDir[dir];
        int nX = x+i*xOffsetByDir[dir];
        chars.push_back(puzzle[nY][nX]);
        puzzle[nY][nX] = UTF8Word[i];
    }
}

void removeWord(vector<string>& chars, int y, int x, int dir, vector<string>& UTF8Word, Matrix<string>& puzzle)
{
    for(int i=0;i<UTF8Word.size();i++){
        int nY = y+i*yOffsetByDir[dir];
        int nX = x+i*xOffsetByDir[dir];
        puzzle[nY][nX] = chars[i];
    }
}

void genPuzzle(int wordIndex, vector<string>& words, Matrix<string>& puzzle, bool& found)
{
    if(found) return;
    if(wordIndex==words.size()){
        //outputPuzzle(puzzle);
        found = true;
        return ;
    }
    //put the word somewhere ffs
    UTF8Container UTF8Word = MultiByteCharsToStrings(words[wordIndex]);
    int dir_i = fetchRandomInt(0, 1);
    int dir_j = fetchRandomInt(0, 1);
    int k_i = fetchRandomInt(0, puzzle.rowCount-1);
    for(int ii=k_i;ii<k_i+puzzle.rowCount;ii++){
        int k_j = fetchRandomInt(0, puzzle.colCount-1);
        for(int jj=k_j;jj<k_j+puzzle.colCount;jj++){
            int k_d = fetchRandomInt(0, 7);
            for(int d=k_d;d<k_d+8;d++){
                int i = ii%puzzle.rowCount;
                int j = jj%puzzle.colCount;
                if(dir_i) i = puzzle.rowCount-i-1;
                if(dir_j) j = puzzle.colCount-j-1;
                if(canPlace(i,j,d%8,UTF8Word, puzzle)){
                    vector<string> chars; //replaced chars
                    placeWord(chars,i,j,d%8,UTF8Word,puzzle);
                    genPuzzle(wordIndex+1, words, puzzle, found);
                    if(found) return;
                    removeWord(chars, i,j,d%8,UTF8Word,puzzle);
                }
            }
        }
    }
}

void sortByLen(vector<string>& words)
{
    vector<pair<int, string>> lengthWordPairs;
    for(auto word: words) lengthWordPairs.push_back({word.size(), word});
    sort(lengthWordPairs.begin(), lengthWordPairs.end(), greater<pair<int,string>>());
    for(int i=0;i<words.size();i++) words[i] = lengthWordPairs[i].second;
}

void generatePuzzle(vector<string> words, Matrix<string> &puzzle)
{
    sortByLen(words);
    bool found = false;
    genPuzzle(0, words, puzzle, found);
}