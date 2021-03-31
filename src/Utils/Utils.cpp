#include "Utils.h"

UTF8Container stringToUTF8Container(std::string& str)
{
    UTF8Container res;
    char* s = &str[0];
    std::string multiByteChar;
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


UTF8Container getLatvianUppercaseChars(){
    return {
        u8"A", u8"Ā", u8"B",
        u8"C", u8"Č", u8"D",
        u8"E", u8"Ē", u8"F",
        u8"G", u8"Ģ", u8"H",
        u8"I", u8"Ī", u8"J",
        u8"K", u8"Ķ", u8"L",
        u8"Ļ", u8"M", u8"N",
        u8"Ņ", u8"O", u8"P",
        u8"R", u8"S", u8"Š",
        u8"T", u8"U", u8"Ū",
        u8"V", u8"Z", u8"Ž"
    };
}

int fetchRandomInt(int low, int high){
    return low + std::rand() % (high-low);
}

COORD GetConsoleCursorPosition(HANDLE hConsoleOutput)
{
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
    {
        return cbsi.dwCursorPosition;
    }
    else
    {
        // The function failed. Call GetLastError() for details.
        COORD invalid = { 0, 0 };
        return invalid;
    }
}