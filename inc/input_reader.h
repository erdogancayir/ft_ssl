#ifndef INPUT_READER_H
#define INPUT_READER_H

char *read_from_stdin(void);
char *read_from_file(const char *filename);
char *duplicate_string_input(const char *str);

#endif