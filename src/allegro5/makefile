allegro_linux:
	gcc -Wall -ansi -pedantic main.c -o main -lallegro -lallegro_primitives -lallegro_image && ./main
mac:
	gcc main.c -o main `pkg-config allegro-5 allegro_primitives-5 allegro_image-5 allegro_main-5 allegro_font-5 --libs --cflags` && ./main
