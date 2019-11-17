gcc -std=c11 -Wall -Werror -pedantic -ggdb -c *.c
gcc -std=c11 -Wall -Werror -pedantic -ggdb -o user.exe minimum.o func_distance.o user_main.o printing_matrix.o
gcc -std=c11 -Wall -Werror -pedantic -ggdb -o exp.exe func_distance.o minimum.o func_analys.o exp_main.o
gcc -std=c11 -Wall -Werror -Wstack-usage=10485760 -pedantic -ggdb -o exp1.exe func_distance.o minimum.o func_analys.o exp_mainr.o
