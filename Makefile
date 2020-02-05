all: proc thread

proc:
	gcc -c multitest_proc.c
	ulimit -S -u 1500
	gcc -lm multitest_proc.o searchtest.c

thread:
	gcc -lpthread -lm -c multitest_thread.c
	gcc -lpthread -lm  multitest_thread.o searchtest.c

clean:
	rm -rf *.o
