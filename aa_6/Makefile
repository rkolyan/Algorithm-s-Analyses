CC = gcc -std=c11 -Wall -Werror -pedantic -ggdb

app.exe : user_main.o io.o aco.o
	$(CC) -o $@ $^ -lm

%.o : %.c
	$(CC) -c $^ -lm

clean:
	rm *.o *.exe
