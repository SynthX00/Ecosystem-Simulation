ecosystem: main.o object.o rabbit.o fox.o
	gcc main.o object.o rabbit.o fox.o -o ecosystem

main.o: main.c
	gcc -c main.c -o main.o

object.o: object.c object.h
	gcc -c object.c -o object.o

rabbit.o: rabbit.c rabbit.h
	gcc -c rabbit.c -o rabbit.o

fox.o: fox.c fox.h
	gcc -c fox.c -o fox.o

clean:
	rm *.o ecosystem