CC = gcc -std=gnu99 -Wall -Werror -pedantic -ggdb

app.exe : main.o io.o dictionary.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -c $^

clean:
	rm *.o *.exe
