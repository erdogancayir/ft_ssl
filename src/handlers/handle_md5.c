#include "debug_mode.h"
#include "flag.h"
#include <stdio.h>

int handle_md5(int argc, char **argv)
{
    DEBUG("Handling MD5 command\n");

	t_flags flags;

	if (parse_flags(argc, argv, &flags) != 0)
		return 1;

	if (flags.p)
        DEBUG("[MD5] STDIN flag -p enabled\n");

	for (int i = 0; i < flags.string_count; i++)
        DEBUG("[MD5] -s \"%s\"\n", flags.strings[i]);

	for (int i = 0; i < flags.file_count; i++)
        DEBUG("[MD5] File: %s\n", flags.files[i]);

	return 0;
}