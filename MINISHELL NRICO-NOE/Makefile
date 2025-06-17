NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT = ./include/LIBFT/libft.a

# Fichiers sources (récupère tous les .c dans tous les sous-dossiers)
# Liste explicite des fichiers source
SRC = \
SRC/main/main.c \
SRC/main/main_loop.c \
SRC/main/start_init.c \
SRC/built/env.c \
SRC/built/export.c \
SRC/built/unset.c \
SRC/parser/lexer.c \
SRC/parser/parser.c \
SRC/parser/ast.c \
SRC/exec/executor.c \
SRC/exec/redirection.c \
SRC/env/env_list.c \
SRC/env/export.c \
SRC/env/unset.c \
SRC/env/utils_env.c \
SRC/signal/signal.c \
SRC/handle_utils/util-0.c \
SRC/handle_utils/util-3.c \
SRC/handle_utils/util-2.c \
SRC/handle_utils/util-1.c \
SRC/from_pipex/from_pipex.c \
SRC/from_pipex/execute_pipe.c \
SRC/from_pipex/pipex_path.c \
SRC/parser/ast_helper.c \
SRC/built/builtin.c \

# SRC/builtins/echo.c 
# SRC/builtins/exit.c  SRC/exec/utils_exec.c \ 
# SRC/exec/pipeline.c 


OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -L./include/LIBFT -lft -lreadline -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
