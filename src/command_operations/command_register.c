#include "commands.h"
#include <stdio.h>
#include "debug_mode.h"

#define MAX_COMMANDS 10

static t_command g_commands[MAX_COMMANDS + 1];
static int g_command_count = 0;

void register_commands(void)
{
    g_commands[0] = (t_command){ "md5", handle_md5 };
    g_commands[1] = (t_command){ "sha256", handle_sha256 };
    g_commands[2] = (t_command){ NULL, NULL }; // Sentinel
    g_command_count = 2;

    for (int i = 0; g_commands[i].name != NULL; i++)
    {
        DEBUG("Command: %s\n", g_commands[i].name);
    }
}

const t_command* get_registered_commands(void)
{
    return g_commands;
}
