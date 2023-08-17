SET COMPILER_PATH=C:\SFML\mingw64\bin
SET SFML_PATH=C:\SFML\SFML-2.6.0
SET PATH=%COMPILER_PATH%;%SFML_PATH%\bin

g++ main.cpp -o main -I%SFML_PATH%\include -L%SFML_PATH%\lib -lsfml-graphics -lsfml-window -lsfml-system && main
