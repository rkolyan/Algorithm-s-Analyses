rm -rf calculations
mkdir calculations
gcc -std=c11 -Wall -Werror -pedantic -ggdb -c *.c
gcc -std=c11 -Wall -Werror -pedantic -pthread -ggdb -o user.exe io.o func_matrix_mult.o user_main.o func_matrix_creation.o
gcc -std=c11 -Wall -Werror -pedantic -pthread -ggdb -o exp.exe io.o func_matrix_mult.o exp_main.o func_matrix_creation.o func_matrix_mult2.o
