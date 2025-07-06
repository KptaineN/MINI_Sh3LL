# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
NAME = minishell

# Source files
SRCS = 	main.c \
		costum_split.c \
		t_list.c \
		t_arr.c \
		path.c \
		tool_lexer.c \
		lexer.c \
		cmd.c \
		oper_handlers_func.c \
		builtin_func.c \
		display.c


# Object files
OBJS = $(SRCS:.c=.o)

# Header files
HEADERS = mini.h

# Default target
all: $(NAME)

# Build the executable
$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

# Compile source files to object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	rm -f $(OBJS)

# Clean everything
fclean: clean
	rm -f $(NAME)

# Rebuild everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re