Unix_SDL:
	gcc -Wall -ansi -pedantic main.c -o main `sdl2-config --cflags --libs` -lm && ./main
static:
	gcc -Wall -ansi -pedantic main.c -o main `sdl2-config --cflags --static-libs` -lm -static && ./main
clean:
	rm main
clean_frames:
	rm o/*.bmp
