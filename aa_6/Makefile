CC = gcc -std=c11 -Wall -Werror -pedantic -ggdb

app.exe : user_main.o io.o aco.o list.o func_memory.o notaco.o
	$(CC) -o $@ $^ -lm

%.o : %.c
	$(CC) -c $^ -lm

clean:
	rm *.o *.exe
