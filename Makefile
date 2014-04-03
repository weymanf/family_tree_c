family.out: file.o main.o search.o vector.o
	gcc -Wall -o family.out file.o main.o search.o vector.o 

file.o: file.c file.h vector.h 
	gcc -Wall -c file.c

main.o: main.c main.h file.h vector.h search.h 
	gcc -Wall -c main.c

search.o: search.c search.h 
	gcc -Wall -c search.c

vector.o: vector.c vector.h 
	gcc -Wall -c vector.c

clean:
	rm -f family.out file.o main.o search.o vector.o 
