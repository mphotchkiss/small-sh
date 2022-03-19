CC=gcc -std=c99

smallsh:
	$(CC) small_sh.c -o smallsh 

clean:
	rm -f smallsh
