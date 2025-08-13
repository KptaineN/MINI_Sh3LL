# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline
NAME = minishell

# Source files
SRCS = 	$(wildcard *.c)

# Object files
OBJS = $(SRCS:.c=.o)

# Header files
HEADERS = mini.h

# Default target
all: $(NAME)

# Build the executable
$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

# Compile source files to object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

newfile:
	@read -p "Enter filename (with .c): " filename; \
	if [ -f "$(filename)" ]; then \
		ecnho "❌ File $(filename) already exists!"; \
	else \
		echo "/* ************************************************************************** */" >> "$(filename)"; \
		echo "/*                                                                            */" >> "$(filename)"; \
		echo "/*                                                        :::      ::::::::   */" >> "$(filename)"; \
		echo "/*   $(filename)                                      :+:      :+:    :+:   */" >> "$(filename)"; \
		echo "/*                                                    +:+ +:+         +:+     */" >> "$(filename)"; \
		echo "/*   By: eganassi <eganassi@student.42.fr>              +#+  +:+       +#+        */" >> "$(filename)"; \
		echo "/*                                                +#+#+#+#+#+   +#+           */" >> "$(filename)"; \
		echo "/*   Created: $(date '+%Y/%m/%d %H:%M:%S') by eganassi             #+#    #+#             */" >> "$(filename)"; \
		echo "/*   Updated: $(date '+%Y/%m/%d %H:%M:%S') by eganassi            ###   ########.fr       */" >> "$(filename)"; \
		echo "/*                                                                            */" >> "$(filename)"; \
		echo "/* ************************************************************************** */" >> "$(filename)"; \
		echo "" >> "$(filename)"; \
		for header in $(HEADERS); do \
			echo "#include \"$(header)\"" >> "$(filename)"; \
		done; \
		echo "" >> "$(filename)"; \
		echo "// Your code here" >> "$(filename)"; \
		echo "" >> "$(filename)"; \
		echo "✅ Created $(filename) with headers: $(HEADERS)"; \
	fi

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