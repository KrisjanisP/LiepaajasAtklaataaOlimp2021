#include <bits/stdc++.h>
#include <windows.h>
typedef unsigned int uint;

void getDesktopResolution(uint& horizontal, uint& vertical)
{
   RECT desktop;
   const HWND hDesktop = GetDesktopWindow();
   GetWindowRect(hDesktop, &desktop);
   horizontal = desktop.right;
   vertical = desktop.bottom;
}

void adjustConsoleFont()
{
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;// Width of each character in the font
    cfi.dwFontSize.Y = 14;// Height
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    std::wcscpy(cfi.FaceName, ((std::wstring)L"Lucida Console").c_str()); // Choose your font
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
    SetConsoleOutputCP(CP_UTF8);
    // Enable buffering to prevent VS from chopping up UTF-8 byte sequences
    setvbuf(stdout, nullptr, _IOFBF, 1000);
}

void adjustConsoleSize(std::string pos, uint width, uint height)
{
    uint horizontal = 1920;
    uint vertical = 1080;
    uint padding = 40;
    getDesktopResolution(horizontal, vertical);
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r); //stores the console's current dimensions
    if(pos=="left")
        MoveWindow(console, padding, padding, width, height, TRUE); // 800 width, 100 height
    else
        MoveWindow(console,horizontal-padding-width, padding, width, height, TRUE);
}

void adjustConsole(std::string pos, uint width, uint height)
{
    adjustConsoleFont();
    adjustConsoleSize(pos, width, height);
}