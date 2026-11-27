#main:main.c add.c sub.c
#	gcc main.c add.c sub.c -o main
#内置变量
CC = gcc
CFLAGS = -I./inc 

#自定义变量
BIN = ./bin/main
SRC = ./src/main.c ./src/add.c ./src/sub.c
OBJ = ./src/main.o ./src/add.o ./src/sub.o

$(BIN):$(OBJ)
	$(CC) $(OBJ) -o $(BIN) $(CFLAGS)

./src/main.o:./src/main.c
	$(CC) ./src/main.c -o ./src/main.o -c $(CFLAGS)
./src/add.o:./src/add.c
	$(CC) ./src/add.c -o ./src/add.o -c $(CFLAGS)
./src/sub.o:./src/sub.c
	$(CC) ./src/sub.c -o ./src/sub.o -c $(CFLAGS)

clean:
	rm $(OBJ) $(BIN)

.PHONY:clean