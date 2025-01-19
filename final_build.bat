@echo off
set CPP_DIR=src
set EXE_DIR=build
set INCLUDES= -IC:\SDL\include -LC:\SDL\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf
set OPTIMIZATION_FLAGS= -O3
set WINDOW_MODE= -mwindows


echo Compiling %EXE_PATH%...

for %%I in (.) do set "ZIP_NAME=%%~nxI"
set EXE_PATH=%EXE_DIR%\%ZIP_NAME%.exe

:: Delete the existing executable if it exists
if exist "%EXE_PATH%" del "%EXE_PATH%"

:: Compile the main source file (ensure main.cpp is present in the correct location) 
g++ -o "%EXE_PATH%" "%CPP_DIR%\*.cpp" %WINDOW_MODE% -Wall -std=c++23 %INCLUDES%  %OPTIMIZATION_FLAGS% 
:: -pg -s -Os
timeout /t 1 /nobreak > nul


:: Check if the executable was created and run it
if exist "%EXE_PATH%" (
    echo Compilation successful
) else (
    echo Compilation failed
)

