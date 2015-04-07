all : GUI AI

GUI : main.o functions.o 
	  gcc -Wall -o PolygammonLinux main.o functions.o `sdl2-config --cflags --libs` -ldl -lSDL2main -lSDL2_image -lSDL2_ttf

main.o : main.c
	  gcc -c main.c

functions.o : functions.c
	  gcc -c functions.c


AI : backgammon.o
	  gcc -o IAOliverJohn.so -shared backgammon.o

backgammon.o : backgammon.c
	  gcc -fPIC -c backgammon.c


clean : 
	  rm backgammon.o PolygammonLinux IAOliverJohn.so main.o functions.o