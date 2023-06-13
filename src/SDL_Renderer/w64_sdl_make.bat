SET DEVKIT=C:\w64devkit
SET COMPILER_PATH=%DEVKIT%\bin
SET PATH=%COMPILER_PATH%

gcc -Wall -ansi -pedantic main.c -o main -I%DEVKIT%\include\SDL2 -L%DEVKIT%\lib -lmingw32 -lSDL2main -lSDL2 && main
