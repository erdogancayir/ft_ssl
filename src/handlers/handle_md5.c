#include "debug_mode.h"
#include "flag.h"
#include "input_reader.h"
#include "md5_compute.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void print_output(const char *input, const char *label, const char *digest, t_flags *flags, int is_stdin)
{
    (void)input;
	if (flags->q)
		printf("%s\n", digest);
	else if (flags->r)
	{
		if (is_stdin)
			printf("%s\n", digest);
		else if (label)
			printf("%s %s\n", digest, label);
	}
	else
	{
		if (is_stdin)
			printf("(stdin)= %s\n", digest);
		else if (label)
			printf("MD5 (%s) = %s\n", label, digest);
	}
}

int handle_md5(int argc, char **argv)
{
	DEBUG("Handling MD5 command");

	t_flags flags;
	if (parse_flags(argc, argv, &flags) != 0)
		return 1;

	// -p (STDIN)
	if (flags.p)
	{
		char *input = read_from_stdin();
		if (!input)
			return 1;

		printf("%s", input); // echo STDIN to STDOUT
		char *digest = md5_compute(input);
		print_output(input, NULL, digest, &flags, 1);
		free(digest);
		free(input);
	}

	// -s (string)
	for (int i = 0; i < flags.string_count; i++)
	{
		char *input = duplicate_string_input(flags.strings[i]);
		char *digest = md5_compute(input);
		print_output(input, flags.strings[i], digest, &flags, 0);
		free(digest);
		free(input);
	}

	// dosyalar
	for (int i = 0; i < flags.file_count; i++)
	{
		char *input = read_from_file(flags.files[i]);
		if (!input)
		{
			fprintf(stderr, "ft_ssl: md5: %s: No such file or directory\n", flags.files[i]);
			continue;
		}
		char *digest = md5_compute(input);
		print_output(input, flags.files[i], digest, &flags, 0);
		free(digest);
		free(input);
	}

	return 0;
}