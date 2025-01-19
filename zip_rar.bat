set EXE_DIR=./build
set FILES=./build/.manifest
set FOLDERS=./assets ./build/dll
set DESTINATION=./build

:: Get the name of the current directory
for %%I in (.) do set "ZIP_NAME=%%~nxI"

set ZIP_PATH=%DESTINATION%\%ZIP_NAME%.zip

:: Delete the existing zip file if it exists
if exist "%ZIP_PATH%" del "%ZIP_PATH%"

:: Zip the specified files and folders using WinRAR
winrar a -afzip -ep1 "%ZIP_PATH%" %FILES% %EXE_DIR%\%ZIP_NAME%.exe %FOLDERS%

echo Zipping completed. Created %ZIP_PATH%.