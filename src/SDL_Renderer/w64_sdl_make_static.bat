SET DEVKIT=C:\w64devkit
SET COMPILER_PATH=%DEVKIT%\bin
SET PATH=%COMPILER_PATH%

gcc -Wall -ansi -pedantic main.c -o main -I%DEVKIT%\include\SDL2 -L%DEVKIT%\lib -lmingw32 -lSDL2main %DEVKIT%\lib\libSDL2.a -mwindows -Wl,--dynamicbase -Wl,--nxcompat -Wl,--high-entropy-va -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid && main

strip main.exe
