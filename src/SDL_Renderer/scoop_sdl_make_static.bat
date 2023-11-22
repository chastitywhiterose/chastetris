SET DEVKIT=C:\Users\chand\scoop\apps\gcc\current

gcc -Wall -ansi -pedantic main.c -o main -I%DEVKIT%\include\SDL2 -Dmain=SDL_main -L%DEVKIT%\lib -lmingw32 -lSDL2main %DEVKIT%\lib\libSDL2.a -Wl,--dynamicbase -Wl,--nxcompat -Wl,--high-entropy-va -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid

strip main.exe

main
