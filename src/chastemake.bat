SET PATH=C:\raylib\w64devkit\bin

gcc -o main.exe main.c C:\raylib\raylib\src\raylib.rc.data -s -static -Os -std=c99 -Wall -IC:\raylib\raylib\src -lraylib -lopengl32 -lgdi32 -lwinmm
