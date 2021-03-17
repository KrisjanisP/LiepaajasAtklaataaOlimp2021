#include <bits/stdc++.h>

class CharCell{
public:
    char val='-';
    char clr='F';
};

class Table{
public:
    Table(unsigned int rowCount, unsigned int colCount);
    ~Table();
    CharCell *& operator[](unsigned int index);
    
    void print();
    unsigned int rowCount, colCount;
private:
    CharCell ** buffer;
    void printTopDelimiter();
    void printColumnIndices();
    void printTableBase();
    void printBottomDelimiter();
};