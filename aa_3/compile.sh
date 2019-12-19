rm -rf calculations
mkdir calculations
gcc -std=c11 -Wall -Werror -pedantic -ggdb -c *.c
gcc -std=c11 -Wall -Werror -pedantic -ggdb -o user.exe io.o func_sort.o user_main.o
gcc -std=c11 -Wall -Werror -pedantic -ggdb -o exp.exe func_sort.o func_analys.o exp_main.o
