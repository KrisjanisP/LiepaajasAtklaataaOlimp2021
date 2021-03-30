@echo off
echo Creating bin folder
mkdir bin
echo Copying confing files
copy src\Config\places.config bin
echo Compiling main source code
g++ -w -o bin\main.exe ^
    src\main.cpp ^
    src\Table\Table.cpp ^
    src\Matrix\Matrix.cpp ^
    src\Puzzle\Puzzle.cpp ^
    src\Console\Console.cpp ^
    src\ConsoleUI\ConsoleUI.cpp ^
    -I "C:/Program Files/boost_1_62_0" ^
    || exit /b
echo Compiling child source code
g++ -o bin\child.exe ^
    src\Child\child-main.cpp ^
    src\Child\child-util.cpp ^
    src\Console\Console.cpp ^
    -I "C:/Program Files/boost_1_62_0" ^
    || exit /b
echo Running compiled source code
run.bat