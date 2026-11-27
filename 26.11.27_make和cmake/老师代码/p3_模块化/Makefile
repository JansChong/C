#main:main.c add.c sub.c
#	gcc main.c add.c sub.c -o main

main:./src/main.o ./src/add.o ./src/sub.o
	gcc ./src/main.o ./src/add.o ./src/sub.o -o ./bin/main 

./src/main.o:./src/main.c
	gcc ./src/main.c -o ./src/main.o -c -I./inc
./src/add.o:./src/add.c
	gcc ./src/add.c -o ./src/add.o -c -I./inc
./src/sub.o:./src/sub.c
	gcc ./src/sub.c -o ./src/sub.o -c -I./inc

clean:
	rm ./src/*.o ./bin/main

.PHONY:clean