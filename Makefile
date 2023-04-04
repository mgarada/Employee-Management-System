#Makefile 
#
#
#// File           : Makefile
#// Description    : The makefile for this project
#// Author         : Mohammad Garada
#// Date           : 04-02-23

# Make environtment 
CC=gcc
CFLAGS= -c -g -Wall  $(INCLUDES)

# Files
OBJECT_FILES=   project2.o p2-support.o

# Productions 
all : p2

p2 : $(OBJECT_FILES)
	$(CC) $(OBJECT_FILES)   -o $@

project2.o : cmsc257-p2.c p2-support.h
		$(CC) $(CFLAGS) $< -o $@
	
p2-support.o : p2-support.c p2-support.h
	$(CC) $(CFLAGS) $< -o $@

clean : 
	rm -v p2 $(OBJECT_FILES)  
