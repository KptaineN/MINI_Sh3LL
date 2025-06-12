NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

# Fichiers sources (récupère tous les .c dans tous les sous-dossiers)
# Liste explicite des fichiers source
SRC = \
SRC/main.c \
SRC/init.c \
SRC/built/env.c \
SRC/built/export.c \
SRC/built/unset.c \
SRC/parser/lexer.c \
SRC/parser/parser.c \
SRC/parser/ast.c \
SRC/parser/split_utils.c \
SRC/exec/executor.c \
SRC/exec/pipeline.c \
SRC/exec/redirection.c \
SRC/exec/utils_exec.c \
SRC/env/env_list.c \
SRC/env/export.c \
SRC/env/unset.c \
SRC/env/utils_env.c \
SRC/signals/signals.c \
SRC/utils/util-3.c \
SRC/utils/util-2.c \
SRC/utils/util-1.c \

# SRC/builtins/echo.c 
# SRC/builtins/exit.c 


OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lreadline

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
