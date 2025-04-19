NAME        := ft_ssl
CC          := gcc
CFLAGS      := -Wall -Wextra -Werror
DEBUG_FLAGS := -g3 -DDEBUG_MODE

SRC_DIR     := src
OBJ_DIR     := obj
INC_DIR     := inc

# Find all .c files under SRC_DIR
SRCS        := $(shell find $(SRC_DIR) -name '*.c')
# Convert src/x.c → obj/x.o
OBJS        := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

INCLUDES    := -I$(INC_DIR)

all: $(NAME)

# Link
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

# Compile .c → .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Debug target
debug: CFLAGS += $(DEBUG_FLAGS)
debug: re

# Clean object files
clean:
	rm -rf $(OBJ_DIR)

# Clean everything
fclean: clean
	rm -f $(NAME)

# Rebuild
re: fclean all