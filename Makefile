.PHONY: all clean test
all:
	gcc -O3 -o junk main.c -Wall
	size ./junk

clean:
	rm -f ./junk

test:
	gcc -o junktest -isystem ./munit ./munit/munit.c main_test.c -Wall && ./junktest
