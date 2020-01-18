CC = gcc -std=gnu11 -Wall -Werror -pedantic -ggdb

app.exe : main.o io.o dictionary.o
	$(CC) -o $@ $^

%.o : %.c
	$(CC) -c $^

clean :
	rm *.o *.exe
