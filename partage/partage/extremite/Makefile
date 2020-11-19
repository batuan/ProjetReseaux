CC = gcc
CCFLAGS = -g3 -Wall
OBJECTS = extremite.o ../tunalloc/tunalloc.o ../iftun/iftun.o ../util.o

all : extremite

extremite: extremite.c $(OBJECTS)
	$(CC) $(CCFLAGS) -o extremite test_extremite.c $(OBJECTS)

%.o : %.c
	$(CC) $(CCFLAGS) -c $^

.PHONY : clean

clean :
	rm -vf *.o extremite
