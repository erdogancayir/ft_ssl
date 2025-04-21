#include "input_reader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BUFFER_SIZE 4096

char *read_from_stdin(void)
{
	char *buffer = NULL;
	size_t size = 0;
	ssize_t bytes;
	char tmp[BUFFER_SIZE];

	while ((bytes = read(STDIN_FILENO, tmp, BUFFER_SIZE)) > 0) {
		char *new_buffer = realloc(buffer, size + bytes + 1);
		if (!new_buffer) {
			free(buffer);
			return NULL;
		}
		buffer = new_buffer;
		memcpy(buffer + size, tmp, bytes);
		size += bytes;
	}
	if (buffer)
		buffer[size] = '\0';
	return buffer;
}

char *read_from_file(const char *filename)
{
	int fd = open(filename, O_RDONLY);
	if (fd < 0)
		return NULL;

	struct stat st;
	if (fstat(fd, &st) < 0) {
		close(fd);
		return NULL;
	}

	char *content = malloc(st.st_size + 1);
	if (!content) {
		close(fd);
		return NULL;
	}

	ssize_t bytes_read = read(fd, content, st.st_size);
	close(fd);

	if (bytes_read < 0) {
		free(content);
		return NULL;
	}

	content[bytes_read] = '\0';
	return content;
}

char *duplicate_string_input(const char *str)
{
	return strdup(str);
}