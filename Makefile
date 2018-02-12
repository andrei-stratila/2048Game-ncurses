build:leaderbord.o modes.o settings.o menu.o main.o gamePlay.o
	gcc leaderbord.o modes.o settings.o menu.o main.o gamePlay.o functions.h -o 2048 -lncurses -lpanel -lm

run:
	./2048
	
leaderbord.o:leaderbord.c
	gcc -Wall -c leaderbord.c

modes.o:modes.c
	gcc -Wall -c modes.c

settings.o:settings.c
	gcc -Wall -c settings.c

menu.o:menu.c
	gcc -Wall -c menu.c

gamePlay.o:gamePlay.c
	gcc -Wall -c gamePlay.c

main.o:main.c
	gcc -Wall -c main.c

.PHONY:clean
clean:
	rm -f *.o *.txt 2048
