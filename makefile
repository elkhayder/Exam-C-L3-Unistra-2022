exo1: exo1.c constants.h
	gcc -ansi -Wall exo1.c -o exo1
	
exo2: exo2.c constants.h
	gcc -ansi -Wall exo2.c -o exo2

clean:
	rm exo1 exo2