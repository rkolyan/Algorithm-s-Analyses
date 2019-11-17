#ifndef FUNC_DISTANCE_H
#define FUNC_DISTANCE_H

#include "error_codes.h"

error_t find_levenstein_distance_recursive(char *s1, char *s2, int length1, int length2, unsigned *result);
error_t find_levenstein_distance_matrix_version(char *s1, char *s2, int length1, int length2, unsigned int *result, unsigned int *matrix);//Big Memory Version
error_t find_levenstein_distance(char *s1, char *s2, int length1, int length2, unsigned int *result, unsigned int *rows);//Small Memory Version
error_t find_levenstein_distance_modified(char *s1, char *s2, int length1, int length2, unsigned int *result, unsigned int *rows);//Small Memory Version
error_t find_levenstein_distance_modified_matrix_version(char *s1, char *s2, int length1, int length2, unsigned int *result, unsigned int *main_matrix);//Big Memory Version
error_t find_levenstein_distance_matrix_sum_version(char *s1, char *s2, int length1, int length2, unsigned int *result, unsigned int *matrix);//Big Memory Version
error_t find_levenstein_distance_modified_matrix_sum_version(char *s1, char *s2, int length1, int length2, unsigned int *result, unsigned int *main_matrix);//Big Memory Version

#endif
