programa: main.o algoritmo.o
	gcc -o entrega main.o algoritmo.o

main.o: main.c algoritmo.h
	gcc -c main.c

algoritmo.o: algoritmo.c algoritmo.h
	gcc -c algoritmo.c

clean:
	rm -f entrega *.o

correr:
	./entrega