#INCLUDE_DIRS = Unity/src/unity.h
LIB_DIRS = 
#gcc test_dll.c doubly_ll.c Unity/src/unity.c -o first

CDEFS=
LIBS=-lpthread -lrt

HFILES=

CFILES1= test_dll.c 
CFILES2= doubly_ll.c
CFILES3= Unity/src/unity.c
# I am a comment, and I want to say that the variable CC will be
# the compiler to use.
CC=gcc
# Hey!, I am comment number 2. I want to say that CFLAGS will be the
# options I'll pass to the compiler.
CFLAGS=-c -Wall

all: test_dll

test_dll: test_dll.o doubly_ll.o unity.o
	$(CC) test_dll.o doubly_ll.o unity.o -o test_dll 

test_dll.o: test_dll.c
	$(CC) $(CFLAGS) test_dll.c

doubly_ll.o: doubly_ll.c
	$(CC) $(CFLAGS) doubly_ll.c

unity.o: Unity/src/unity.c
	$(CC) $(CFLAGS) Unity/src/unity.c
clean:
	rm -rf *.o *.d *.txt test_dll
