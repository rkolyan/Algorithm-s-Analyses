CC = gcc -std=c11 -Wall -Werror -pedantic -ggdb

app.exe : user_main.o io.o list.o func_memory.o notaco.o aco.o way.o
	$(CC) -o $@ $^ -lm

%.o : %.c
	$(CC) -c $^ -lm

clean:
	rm *.o *.exe
