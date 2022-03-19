CC=gcc -std=c99

smallsh:
	$(CC) prog3.c -o smallsh 

clean:
	rm -f smallsh