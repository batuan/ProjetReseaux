all: tunalloc
tunalloc: tunalloc.o
	gcc test_tunalloc.c tunalloc.c -o tunalloc
tunalloc.o:
	gcc -c tunalloc.c
clean:
	rm tunalloc.o tunalloc