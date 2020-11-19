CC = gcc
CCFLAGS = -g3 -Wall -std=c99

OBJECTS = tunalloc.o ../util.o

all : tunalloc

tunalloc: tunalloc.c $(OBJECTS)
	$(CC) $(CCFLAGS) -o tunalloc test_tunalloc.c $(OBJECTS)

%.o : %.c
	$(CC) $(CCFLAGS) -c $^

.PHONY : clean

clean :
	rm -vf *.o tunalloc
