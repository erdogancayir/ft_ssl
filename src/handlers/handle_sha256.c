#include "debug_mode.h"
#include "flag.h"
#include <stdio.h>

int handle_sha256(int argc, char **argv)
{
    DEBUG("Handling SHA256 command");

	t_flags flags;

	if (parse_flags(argc, argv, &flags) != 0)
		return 1;

	if (flags.p)
        DEBUG("[SHA256] STDIN flag -p enabled");

	for (int i = 0; i < flags.string_count; i++)
        DEBUG("[SHA256] -s \"%s\"", flags.strings[i]);

	for (int i = 0; i < flags.file_count; i++)
        DEBUG("[SHA256] File: %s", flags.files[i]);

	return 0;
}