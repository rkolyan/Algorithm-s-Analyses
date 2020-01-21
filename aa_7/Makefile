CC = gcc -std=c18 -Wall -Werror -pedantic -ggdb

app.exe : user_main.o func_string_usual.o func_string_horpuskull.o func_string_boyer_mur.o func_string_kmp.o
	$(CC) -o $@ $^

%.o : %.c
	$(CC) -c $^

clean :
	rm *.o *.exe
