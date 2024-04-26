Unix_SDL_Mixer:
	gcc -Wall -ansi -pedantic main.c -o main `sdl2-config --cflags --libs` -lSDL2_mixer -lm && ./main
Unix_SDL:
	gcc -Wall -ansi -pedantic main.c -o main `sdl2-config --cflags --libs` -lm && ./main
static:
	gcc -Wall -ansi -pedantic main.c -o main `sdl2-config --cflags --static-libs` -lm && ./main

	
