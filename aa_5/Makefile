CC = gcc -std=c11 -Wall -Werror -pedantic -pthread -ggdb

exp.exe : exp_main.o func_conveyer.o func_thread_conveyer.o io.o memory_resources.o function_resources.o
	$(CC) -o $@ $^

app.exe : user_main.o func_conveyer.o func_thread_conveyer.o io.o memory_resources.o function_resources.o
	$(CC) -o $@ $^

%.o : %.c
	$(CC) -c $^

clean:
	rm *.o *.exe
