.PHONY: all clean
all:
	gcc -O3 -o junk main.c -Wall
	size ./junk

clean:
	rm -f ./junk
