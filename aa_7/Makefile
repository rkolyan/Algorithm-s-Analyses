CC = gcc -std=c18 -Wall -Werror -pedantic -ggdb

app.exe : user_main.o func_string.o
	$(CC) -o $@ $^

%.o : %.c
	$(CC) -c $^

clean :
	rm *.o *.exe
