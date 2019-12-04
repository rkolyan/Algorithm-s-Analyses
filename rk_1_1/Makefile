CC = gcc -std=c1x -Wall -Werror -pedantic -ggdb

app.exe: main.o clique.o clique_stack.o number_stack.o matrix.o vertices.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -c $^

clean:
	rm *.o *.exe res.*
