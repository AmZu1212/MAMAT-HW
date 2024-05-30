CC=gcc
CCLINK=$(CC)
CFLAGS=-g -Wall -std=c99
OBJS=grades.o
EXEC=libgrades.so
RM=rm -rf grades.o libgrades.so


libgrades.so: $(OBJS)
	$(CCLINK) -shared $(OBJS) -o libgrades.so -llinked-list -L.

grades.o: grades.c grades.h linked-list.h
	$(CC) -c -fpic grades.c

#Cleans .o and .so files in current directory
clean:
	$(RM)
