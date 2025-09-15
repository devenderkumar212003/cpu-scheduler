@echo off
echo Compiling CPU Scheduler...

:: Check if g++ is available
where g++ >nul 2>nul
if %ERRORLEVEL% neq 0 (
    echo Error: g++ compiler not found. Please install MinGW or another C++ compiler.
    echo and ensure it's added to your PATH environment variable.
    pause
    exit /b 1
)

:: Compile the program
g++ -std=c++11 -Wall -Wextra -o cpu_scheduler.exe main.cpp process.cpp scheduler.cpp fcfs_scheduler.cpp sjf_scheduler.cpp rr_scheduler.cpp priority_scheduler.cpp ljf_scheduler.cpp hrrn_scheduler.cpp process_loader.cpp

if %ERRORLEVEL% neq 0 (
    echo Compilation failed.
    pause
    exit /b 1
)

echo Compilation successful!
echo.
echo Running CPU Scheduler...
echo.

:: Run the program
cpu_scheduler.exe

echo.
echo Program execution completed.
pause