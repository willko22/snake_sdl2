@echo off
set OBJ_DIR=build\obj
set HPP_DIR=include
set CPP_DIR=src
set EXE_PATH=build\main.exe
set INCLUDES= -IC:\SDL\include -LC:\SDL\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf
set WINDOW_MODE=

call :recompile_o
if errorlevel 1 goto :error
call :main
goto :eof


:compile_file
    echo Compiling %1
    if exist %%2 dek %%2
    g++ -c "%1" -Wall -std=c++23 %INCLUDES% -o "%2"
    if errorlevel 1 exit /b 1
    exit /b 0


:recompile_o

    setlocal EnableDelayedExpansion

    if not exist "%OBJ_DIR%" mkdir "%OBJ_DIR%"

    for %%f in (%CPP_DIR%\*.cpp) do (
        set "OBJ_FILE=!OBJ_DIR!\%%~nf.o"
        set "HPP_FILE=!HPP_DIR!\%%~nf.hpp"
        
        REM Check if .o exists and compare dates
        if not exist !OBJ_FILE! (
            call :compile_file "%%f" "!OBJ_FILE!"
        ) else (
            FOR %%A IN ("%%f") DO SET cppdate=%%~tA
            FOR %%B IN ("!HPP_FILE!") DO SET hppdate=%%~tB
            FOR %%C IN ("!OBJ_FILE!") DO SET objdate=%%~tC

            @REM echo %%f !cppdate! !hppdate! !objdate!

            if "!cppdate!" GTR "!objdate!" (
                call :compile_file "%%f" "!OBJ_FILE!"
            ) else if "!hppdate!" GTR "!objdate!" (
                call :compile_file "%%f" "!OBJ_FILE!"
            )
        )
    )
    exit /b 0

:main

    echo Compiling %EXE_PATH%...

    :: Delete the existing executable if it exists
    if exist "%EXE_PATH%" del "%EXE_PATH%"

    :: Compile the main source file (ensure main.cpp is present in the correct location) 
    g++ -o "%EXE_PATH%" "%OBJ_DIR%\*.o" %WINDOW_MODE% -Wall -std=c++23 %INCLUDES%
    :: -pg -s -Os
    timeout /t 1 /nobreak > nul


    :: Check if the executable was created and run it
    if exist "%EXE_PATH%" (
        echo Compilation successful
        echo Running %EXE_PATH%...
        "%EXE_PATH%" 2>&1
    ) else (
        echo Compilation failed
    )
    exit /b 0
