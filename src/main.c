#include <stdio.h>
#include <string.h>
#include "commands.h"

int main(int argc, char **argv)
{
    if (argc < 2) {
        return dispatch_command(0, NULL); // for print_usage
    }

    register_commands();
    return dispatch_command(argc - 1, argv + 1);
}
