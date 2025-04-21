#include "input_reader.h"
#include "debug_mode.h"
#include "flag.h"
#include <stdio.h>
#include <stdlib.h>

int handle_sha256(int argc, char **argv)
{
    DEBUG("Handling SHA256 command");

	t_flags flags;

	if (parse_flags(argc, argv, &flags) != 0)
		return 1;

    if (flags.p) {
        char *input = read_from_stdin();
        DEBUG("STDIN content: %s", input);
        free(input);
    }

    for (int i = 0; i < flags.string_count; i++) {
        char *input = duplicate_string_input(flags.strings[i]);
        DEBUG("String to hash: %s", input);
        free(input);
    }

    for (int i = 0; i < flags.file_count; i++) {
        char *input = read_from_file(flags.files[i]);
        if (input)
            DEBUG("File content [%s]: %s", flags.files[i], input);
        else
            fprintf(stderr, "ft_ssl: md5: %s: No such file or directory\n", flags.files[i]);
        free(input);
    }

	return 0;
}