#ifndef COMMANDS_H
#define COMMANDS_H

typedef struct s_command {
    const char *name;
    int (*handler)(int argc, char **argv);
} t_command;



int handle_md5(int argc, char **argv);
int handle_sha256(int argc, char **argv);

void register_commands(void);
int dispatch_command(int argc, char **argv);
const t_command* get_registered_commands(void);

#endif