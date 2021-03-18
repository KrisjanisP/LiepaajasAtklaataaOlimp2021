@echo off
echo Compiling source code
g++ -o bin\compiled.exe src\main.cpp src\Table.cpp src\Console.cpp || exit /b
echo Running compiled executable
.\bin\compiled.exe || exit /b