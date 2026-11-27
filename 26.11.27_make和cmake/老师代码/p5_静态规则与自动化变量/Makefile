#main:main.c add.c sub.c
#	gcc main.c add.c sub.c -o main
#内置变量
CC = gcc
CFLAGS = -I./inc 

#自定义变量
BIN = ./bin/main
#SRC = ./src/main.c ./src/add.c ./src/sub.c
SRC = $(wildcard ./src/*.c)
OBJ = ./src/main.o ./src/add.o ./src/sub.o


$(BIN):$(OBJ)
	$(CC) $(OBJ) -o $(BIN) $(CFLAGS)

#静态规则
$(OBJ):%.o:%.c
	$(CC) $< -o $@ -c $(CFLAGS) #运用了自动化变量


clean:
	rm $(OBJ) $(BIN)

.PHONY:clean