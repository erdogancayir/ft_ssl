#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "flag.h"

static void add_string(t_flags *flags, char *str)
{
	flags->strings = realloc(flags->strings, sizeof(char *) * (flags->string_count + 1));
	flags->strings[flags->string_count++] = str;
}

static void add_file(t_flags *flags, char *file)
{
	flags->files = realloc(flags->files, sizeof(char *) * (flags->file_count + 1));
	flags->files[flags->file_count++] = file;
}

int parse_flags(int argc, char **argv, t_flags *flags)
{
	memset(flags, 0, sizeof(t_flags));

	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i], "-p") == 0)
			flags->p = true;
		else if (strcmp(argv[i], "-q") == 0)
			flags->q = true;
		else if (strcmp(argv[i], "-r") == 0)
			flags->r = true;
		else if (strcmp(argv[i], "-s") == 0) {
			if (i + 1 >= argc) {
				fprintf(stderr, "ft_ssl: Error: -s flag requires a string argument\n");
				return 1;
			}
			add_string(flags, argv[++i]);
		} else {
			add_file(flags, argv[i]);
		}
	}
	return 0;
}