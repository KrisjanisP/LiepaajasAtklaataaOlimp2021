#include <bits/stdc++.h>
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
    vector<string> UTF8Word = MultiByteCharsToStrings(words[wordIndex]);
    int low_dist_i = 0, low_dist_j = 0, low_dist_d = 0;
    int high_dist_i = puzzle.rowCount-1;
    int high_dist_j = puzzle.colCount-1;
    int high_dist_d = 7;
    int k_i = low_dist_i + std::rand() % (high_dist_i - low_dist_i); 
    for(int ii=0;ii<k_i+puzzle.rowCount;ii++){
        int k_j = low_dist_j + std::rand() % (high_dist_j - low_dist_j);
        for(int jj=0;jj<k_j+puzzle.colCount;jj++){
            int k_d = low_dist_d + std::rand() % (high_dist_d - low_dist_d);
            for(int d=k_d;d<k_d+8;d++){
                int i = ii%puzzle.rowCount;
                int j = jj%puzzle.colCount;
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