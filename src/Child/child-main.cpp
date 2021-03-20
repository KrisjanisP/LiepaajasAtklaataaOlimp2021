#include <bits/stdc++.h>
#include <boost/interprocess/ipc/message_queue.hpp>
#include "child-util.h"
#include "../Console/Console.h"
#include "windows.h"
using namespace std;
using namespace boost::interprocess;

typedef unsigned int uint;

uint rowCount, colCount;
const char* queueName;

/*
first argument - name of the executable
second argument - row count
third argument - column count
fourth argument - message_queue name
*/
int main(int argc, char* argv[]){
    if(argc!=4){
        cout<<"Please provide the required arguments"<<endl;
        return 1;
    }
    adjustConsole("left",1700,900);
    
    rowCount = stoi(argv[1]);
    colCount = stoi(argv[2]);
    constructTable(rowCount, colCount);

    queueName = argv[3];
    try{
        //Open a message queue.
        message_queue mq(open_only, queueName);

        unsigned int priority;
        message_queue::size_type recvd_size;

        TableUpdate tableUpdate;
        while(true){
            mq.receive(&tableUpdate, sizeof(tableUpdate), recvd_size, priority);
            updateTable(tableUpdate, rowCount, colCount);
        }
    }
    catch(interprocess_exception &ex){
        message_queue::remove(queueName);
        std::cout << ex.what() << std::endl;
        return 1;
    }
    message_queue::remove(queueName);
    return 0;
}


