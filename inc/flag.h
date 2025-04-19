#ifndef FLAG_H
#define FLAG_H

#include <stdbool.h>

typedef struct s_flags {
	bool p;
	bool q;
	bool r;

	char **strings;
	int string_count;

	char **files;
	int file_count;
} t_flags;

int parse_flags(int argc, char **argv, t_flags *flags);

#endif