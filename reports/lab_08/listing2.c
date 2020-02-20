#define ALPHABET_SIZE 26
typedef struct tree
{
	unsigned char count : 5;
	char is_next_null : 3;
	char next_symbol_positions[ALPHABET_SIZE];
	struct tree **nexts;
} dictionary_t;
