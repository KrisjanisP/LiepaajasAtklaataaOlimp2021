typedef unsigned int uint;

struct TableUpdate{
    int row, col;
    int clr;
    char val;
};

void constructTable(uint rowCount, uint colCount);
void updateTable(TableUpdate tableUpdate, uint rowCount, uint colCount);
void printTopDelimiter(uint rowCount, uint colCount);
void printColumnIndices(uint rowCount, uint colCount);
void printTableBase(uint rowCount, uint colCount);
void printBottomDelimiter(uint rowCount, uint colCount);