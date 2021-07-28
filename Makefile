#The Makefile of the program

#Student Name: Le Minh Truong
#Student ID: 1078113
#Subject Name: Algorithms and Data Structures
#Subject Code: COMP20003

#Assignment 1

dict: dict.o make_dict.o
	gcc -Wall -o dict dict.o make_dict.o

make_dict.o: make_dict.c declarations.h
	gcc -c -Wall make_dict.c

dict.o: dict.c declarations.h
	gcc -c -Wall dict.c
