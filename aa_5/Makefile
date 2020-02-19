CC = gcc -std=c11 -Wall -Werror -pedantic -pthread -ggdb

all: app.exe exp.exe

exp.exe : exp_main.o func_conveyer.o func_thread_conveyer.o io.o memory_resources.o function_resources.o
	$(CC) -o $@ $^

exp.exe : exp_main.o func_conveyer.o func_thread_conveyer.o io.o memory_resources.o function_resources.o
	$(CC) -o $@ $^

%.o : %.c
	$(CC) -c $^

clean:
	rm *.o *.exe
