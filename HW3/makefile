CC=gcc
CCLINK=$(CC)
CFLAGS=-g -Wall -std=c99
OBJS=main.o file0.o file1.o file2.o file3.o file4.o 
EXEC=prog.exe
RM=rm -rf *.o *.exe
#seed ID: 204840805

#Rule1 links OBJS files to EXEC
prog.exe: $(OBJS)
	$(CCLINK) $(OBJS) -o $(EXEC)

#Compiles main.c (is dependant on f0, f1, f2, f3, f4)
main.o: main.c file0.h file1.h file2.h file3.h file4.h
	$(CC) $(CFLAGS) -c main.c

#Compiles file0.c (is dependant on f0, f1, f2, f4)
file0.o: file0.c file0.h file1.h file2.h file4.h
	$(CC) $(CFLAGS) -c file0.c

#Compiles file1.c (is dependant on f0, f1, f2, f4)
file1.o: file1.c file1.h file0.h file2.h file4.h
	$(CC) $(CFLAGS) -c file1.c

#Compiles file2.c (is dependant on f0, f1, f2, f4)
file2.o: file2.c file2.h file0.h file1.h file4.h
	$(CC) $(CFLAGS) -c file2.c

#Compiles file3.c (is dependant on f0, f1, f2, f3, f4)
file3.o: file3.c file3.h file0.h file1.h file2.h file4.h
	$(CC) $(CFLAGS) -c file3.c

#Compiles file4.c (non dependant)
file4.o: file4.c file4.h
	$(CC) $(CFLAGS) -c file4.c

#Cleans .o and .exe files in current directory
clean:
	$(RM)
