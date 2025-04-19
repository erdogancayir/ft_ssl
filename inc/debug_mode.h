#ifndef DEBUG_MODE_H
#define DEBUG_MODE_H

#include <stdio.h>

// Define DEBUG_MODE to enable debug messages
#ifdef DEBUG_MODE
    #define DEBUG(...) do { \
        fprintf(stderr, "[DEBUG] %s:%d: ", __FILE__, __LINE__); \
        fprintf(stderr, __VA_ARGS__); \
        fprintf(stderr, "\n"); \
    } while (0)
#else
    #define DEBUG(...) do {} while (0)
#endif

#endif