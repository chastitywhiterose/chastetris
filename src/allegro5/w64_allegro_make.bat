SET DEVKIT=C:\w64devkit
SET COMPILER_PATH=%DEVKIT%\bin
SET PATH=%COMPILER_PATH%;

gcc -Wall -ansi -pedantic main.c -o main -I%DEVKIT%\include -L%DEVKIT%\lib -lallegro -lallegro_primitives -lallegro_image && main
