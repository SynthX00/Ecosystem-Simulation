ecosystem: main.o object.o rabbit.o fox.o
	gcc -fopenmp main.o object.o rabbit.o fox.o -o ecosystem

main.o: main.c
	gcc -fopenmp -c main.c -o main.o

object.o: object.c object.h
	gcc -fopenmp -c object.c -o object.o

rabbit.o: rabbit.c rabbit.h
	gcc -fopenmp -c rabbit.c -o rabbit.o

fox.o: fox.c fox.h
	gcc -fopenmp -c fox.c -o fox.o

clean:
	rm *.o ecosystem