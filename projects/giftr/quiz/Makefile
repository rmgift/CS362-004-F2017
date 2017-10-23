CFLAGS = -fprofile-arcs -ftest-coverage -lm

testme: testme.c
	gcc -o testme testme.c $(CFLAGS)
	./testme
gtm:
	gcov ./testme.c -b

all: testme gtm

clean:
	rm testme *.gcda *.gcno *.c.gcov
