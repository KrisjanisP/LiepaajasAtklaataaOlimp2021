#include "Table.h"
#include <windows.h>
#include <boost/interprocess/ipc/message_queue.hpp>
#define BLACK_FG_WHITE_BG_CLR 240

using namespace std;

struct TableUpdate{
    int row, col;
    int clr;
    int byteCount;
    char arr[20];
};

Table::Table(unsigned int _rowCount, unsigned int _colCount, string mqName)
{
    rowCount = _rowCount;
    colCount = _colCount;
    buffer = new CharCell*[rowCount];
    for(int i=0;i<rowCount;i++){
        CharCell * sub_buffer = new CharCell[colCount];
        buffer[i] = sub_buffer;
    }
    printed = new CharCell*[rowCount];
    for(int i=0;i<rowCount;i++){
        CharCell * sub_printed = new CharCell[colCount];
        printed[i] = sub_printed;
    }
    messageQueueName = mqName;
    using namespace boost::interprocess;
    message_queue::remove(messageQueueName.c_str());
    messageQueue = new message_queue(
        create_only,
        messageQueueName.c_str(),
        2000,
        sizeof(TableUpdate)
    );
    string command = "start child.exe "+to_string(rowCount)+" "+to_string(colCount)+" "+mqName;
    system(command.c_str());
}

CharCell*& Table::operator[](unsigned int index)
{
    return buffer[index];
}  

Table::~Table()
{
    for(int i=0;i<rowCount;i++){
        delete[ ] buffer[i];
    }
    delete[ ] buffer;
    
    for(int i=0;i<rowCount;i++){
        delete[ ] printed[i];
    }
    delete[ ] printed;
}

void Table::update(){
    for(int i=0; i<rowCount; i++){
        for(int j=0; j<colCount; j++){
            if(buffer[i][j].clr!=printed[i][j].clr
            || buffer[i][j].val!=printed[i][j].val){
                updateCell(i, j);
            }
        }
    }
}

void Table::updateCell(uint cellY, uint cellX){
    TableUpdate tableUpdate{
        row: cellY,
        col: cellX,
        clr: buffer[cellY][cellX].clr,
        byteCount: (int)buffer[cellY][cellX].val.size()
    };
    for(uint i=0;i<buffer[cellY][cellX].val.size();i++){
        tableUpdate.arr[i] = buffer[cellY][cellX].val[i];
    }
    (*messageQueue).send(&tableUpdate, sizeof(tableUpdate), 0);
    printed[cellY][cellX] = buffer[cellY][cellX];
}