#main:main.c add.c sub.c
#	gcc main.c add.c sub.c -o main

main:main.o add.o sub.o
	gcc main.o add.o sub.o -o main

main.o:main.c
	gcc main.c -o main.o -c
add.o:add.c
	gcc add.c -o add.o -c
sub.o:sub.c
	gcc sub.c -o sub.o -c