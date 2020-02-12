CC = gcc -std=c1x -Wall -Werror -pedantic -pthread -O2

all: user.exe exp.exe

user.exe: user_main.o io.o func_matrix_creation.o func_matrix_mult.o
	$(CC) -o $@ $^

exp.exe: exp_main.o func_matrix_creation.o func_matrix_mult.o func_matrix_mult2.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -c $^

clean:
	rm *.o *.exe
