gcc -std=c11 -Wall -Werror -pedantic -ggdb -c *.c
gcc -std=c11 -Wall -Werror -pedantic -ggdb -o user.exe io.o func_matrix_mult.o user_main.o func_matrix_creation.o
gcc -std=c11 -Wall -Werror -pedantic -ggdb -o exp.exe func_matrix_mult.o io.o func_analys.o exp_main.o func_matrix_creation.o
