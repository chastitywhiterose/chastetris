SET COMPILER_PATH=C:\mingw64\bin
SET SDL_PATH=C:\SDL\SDL2-2.26.3\x86_64-w64-mingw32
SET PATH=%COMPILER_PATH%;%SDL_PATH%\bin

gcc -Wall -ansi -pedantic main.c -o main -I%SDL_PATH%\include\SDL2 -L%SDL_PATH%\lib -lmingw32 -lSDL2main -lSDL2 -mwindows && main
