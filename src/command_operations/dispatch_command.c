#include <stdio.h>
#include <string.h>
#include "commands.h"

static void print_usage(void)
{
    printf("usage: ft_ssl command [flags] [file/string]\n");
    printf("commands:\n  md5\n  sha256\n");
}

int dispatch_command(int argc, char **argv)
{
    const t_command *cmds = get_registered_commands();

    for (int i = 0; cmds[i].name != NULL; i++) {
        if (strcmp(argv[0], cmds[i].name) == 0) {
            return cmds[i].handler(argc - 1, argv + 1);
        }
    }

    fprintf(stderr, "ft_ssl: Error: '%s' is an invalid command.\n", argv[0]);
    print_usage();
    return 1;
}