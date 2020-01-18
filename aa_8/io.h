#ifndef IO_H
#define IO_H

#include "dictionary.h"
#include "error_codes.h"
#include <stdio.h>

error_t fill_dictionary_from_file(dictionary_t ***dictionary, FILE *file);
error_t read_and_print_not_in_dictionary(dictionary_t **dictionary, FILE *file);

#endif
