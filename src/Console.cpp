#include <bits/stdc++.h>
#include <windows.h>

void GetDesktopResolution(int& horizontal, int& vertical)
{
   RECT desktop;
   const HWND hDesktop = GetDesktopWindow();
   GetWindowRect(hDesktop, &desktop);
   horizontal = desktop.right;
   vertical = desktop.bottom;
}

void AdjustConsoleFont(std::wstring fontFamily, unsigned int fontSize)
{
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;// Width of each character in the font
    cfi.dwFontSize.Y = fontSize;// Height
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    std::wcscpy(cfi.FaceName, fontFamily.c_str()); // Choose your font
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
    std::wcout << L"Font: "+fontFamily+L", Size: "+std::to_wstring(fontSize)+L"\n";
    SetConsoleOutputCP(65001);
}

void AdjustConsoleSize(int padding, unsigned int consoleWidthInChar, unsigned int fontSize)
{
    int horizontal = 1920;
    int vertical = 1080;
    GetDesktopResolution(horizontal, vertical);
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r); //stores the console's current dimensions
    MoveWindow(console, padding, padding, consoleWidthInChar*fontSize*0.21, vertical-2*padding, TRUE); // 800 width, 100 height
}

void AdjustConsole(std::wstring fontFamily, unsigned int fontSize, unsigned int screenPadding, unsigned int consoleWidthInChar)
{
    AdjustConsoleFont(fontFamily, fontSize);
    AdjustConsoleSize(screenPadding, consoleWidthInChar, fontSize);
}