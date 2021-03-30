echo Changing working directory
cd bin
echo Running compiled executable
start .\main.exe || exit /b
echo Changing working directory back to previous
cd ..