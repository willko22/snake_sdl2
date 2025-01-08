@echo off
:: set CPP_FILE_PATH=src\main.cpp
set CPP_FILE_PATH=src\*.cpp
set FILE_PATH=build\main.exe

echo Compiling %CPP_FILE_PATH%...

:: Delete the existing executable if it exists
if exist "%FILE_PATH%" (
    del "%FILE_PATH%"
)

::set WINDOW_MODE=-mwindows
set WINDOW_MODE=
:::: SDL2
set VERSION= -IC:\SDL\include -LC:\SDL\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

:: Compile the main source file (ensure main.cpp is present in the correct location) 
g++ -o "%FILE_PATH%" "%CPP_FILE_PATH%" %WINDOW_MODE% -Wall -std=c++23 %VERSION%
:: -pg -s -Os
timeout /t 1 /nobreak > nul


:: Check if the executable was created and run it
if exist "%FILE_PATH%" (
    echo Compilation successful
    echo Running %FILE_PATH%...
    "%FILE_PATH%" 2>&1
) else (
    echo Compilation failed
)