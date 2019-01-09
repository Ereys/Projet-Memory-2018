


memory : menu.o main.o jeu.o
	gcc -o memory menu.o jeu.o main.o -lgraph

menu.o: menu.c
	gcc -c menu.c

jeu.o: jeu.c
	gcc -c jeu.c 

main.o: main.c menu.h jeu.h
	gcc -c main.c 

run: memory
		./memory

clean :
	rm -f menu.o jeu.o main.o memory