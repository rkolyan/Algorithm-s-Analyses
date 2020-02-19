CC = gcc -std=gnu18 -Wall -Werror -pedantic -ggdb

app.exe: main.o func_file.o func_string.o find_control_graph.o vertice.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -c $^

clean:
	rm *.exe *.o
