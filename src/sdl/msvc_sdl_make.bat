set SDL_INC=C:\msvc\sdl\include
set SDL_LIB=C:\msvc\sdl\lib

call "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat"

cl main.c /I%SDL_INC% /link /LIBPATH:%SDL_LIB% SDL2.lib SDL2main.lib shell32.lib /SUBSYSTEM:CONSOLE

set PATH=%SDL_LIB%

main
