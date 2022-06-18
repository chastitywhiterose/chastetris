SET RAYLIB_PATH=C:\raylib\raylib
SET COMPILER_PATH=C:\raylib\tcc
SET PATH=%COMPILER_PATH%
SET CC=tcc
SET CFLAGS=%RAYLIB_PATH%\src\raylib.rc.data -std=c99 -Wall -I%RAYLIB_PATH%\src -Iexternal -DPLATFORM_DESKTOP
SET LDFLAGS=-L%RAYLIB_PATH%\src -lmsvcrt -lraylib -lopengl32 -lgdi32 -lwinmm -lkernel32 -lshell32 -luser32 -Wl

%CC% -o main.exe main.c %CFLAGS% %LDFLAGS%
main
