SET RAYLIB_PATH=C:\raylib\raylib
SET COMPILER_PATH=C:\raylib\w64devkit\bin
SET PATH=%COMPILER_PATH%
SET CC=gcc
SET CFLAGS=%RAYLIB_PATH%\src\raylib.rc.data -s -static -Os -std=c99 -Wall -I%RAYLIB_PATH%\src -Iexternal -DPLATFORM_DESKTOP
SET LDFLAGS=-lraylib -lopengl32 -lgdi32 -lwinmm

%CC% -o main.exe main.c %CFLAGS% %LDFLAGS%
main


