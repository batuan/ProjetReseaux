CC = gcc
CCFLAGS = -g3 -Wall -std=c99
OBJECTS = iftun.o ../tunalloc/tunalloc.o ../util.o

all : iftun

iftun: iftun.c $(OBJECTS)
	$(CC) $(CCFLAGS) -o iftun test_iftun.c $(OBJECTS)

%.o : %.c
	$(CC) $(CCFLAGS) -c $^

.PHONY : clean

clean :
	rm -vf *.o iftun
