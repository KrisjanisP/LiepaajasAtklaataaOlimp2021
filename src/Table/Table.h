#include <bits/stdc++.h>
#include <boost/interprocess/ipc/message_queue.hpp>

using namespace std;

typedef unsigned int uint;

class CharCell{
public:
    string val = u8"?";
    int clr=240;
};

class Table{
public:
    Table(uint rowCount, uint colCount, string mqName);
    ~Table();
    
    uint rowCount, colCount;
    
    void update(); // updates printed table content <- ievieto daudz figņas queue

    CharCell *& operator[](uint index);
private:
    CharCell ** buffer; // table data 
    CharCell ** printed; // table printed data
    // printing table
    void printTopDelimiter();
    void printColumnIndices();
    void printTableBase();
    void printBottomDelimiter();
    
    void updateCell(uint cellY, uint cellX); //updates the color of the cell

    std::string messageQueueName;
    boost::interprocess::message_queue* messageQueue;
};