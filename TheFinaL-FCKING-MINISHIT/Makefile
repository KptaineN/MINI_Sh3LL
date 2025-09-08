##############################################################################
#                                   VARIABLES                                 #
###############################################################################
NAME        := minishell
CC          := cc
CFLAGS      := -Wall -Wextra -Werror
INC_DIR     := include
LIBFT_DIR   := include/LIBFT
INCLUDES    := -I$(INC_DIR) -I$(LIBFT_DIR)

SRC_FILES   := \
	SRC/main/main_loop.c \
	SRC/main/main.c \
	SRC/main/print_main_head.c \
	SRC/main/process_input.c \
	SRC/main/read_more.c \
	SRC/built/echo/echo_quote.c \
	SRC/built/echo/echo_value.c \
	SRC/built/echo/echo_var.c \
	SRC/built/echo/echo.c \
	SRC/built/echo/replace_variables.c \
	SRC/built/export/export_args.c \
	SRC/built/export/export_env.c \
	SRC/built/export/export_utils.c \
	SRC/built/export/export.c \
	SRC/built/builtin_func.c \
	SRC/built/builtin.c \
	SRC/built/cd.c \
	SRC/built/env.c \
	SRC/built/exit.c \
	SRC/built/pwd.c \
	SRC/built/unset.c \
	SRC/env/env_list.c \
	SRC/env/init_env.c \
	SRC/env/utils_env.c \
	SRC/exec/cmd_lexer.c \
	SRC/exec/execute_cmd.c \
	SRC/exec/executor.c \
	SRC/expand/expansion.c \
	SRC/expand/replace_exit.c \
	SRC/fck_split/split_count-arg.c \
	SRC/fck_split/split_extract-arg.c \
	SRC/fck_split/split_part_1.c \
	SRC/handle_utils/handler/handler-1.c \
	SRC/handle_utils/handler/handler-2.c \
	SRC/handle_utils/util-0.c \
	SRC/handle_utils/util-2-free.c \
	SRC/handle_utils/util-3-free.c \
	SRC/handle_utils/util-4-free-token.c \
	SRC/init/t_arr/t_arr.c \
	SRC/init/t_arr/t_arr_init.c \
	SRC/init/t_arr/t_arr_dic.c \
	SRC/init/signal.c \
	SRC/init/start_init.c \
	SRC/init/terminal.c \
	SRC/parser/env_p/find_path.c \
	SRC/parser/env_p/parse_env.c \
	SRC/parser/env_p/process_env.c \
	SRC/parser/env_p/set_env_value.c \
	SRC/parser/expand_p/exp_cmd.c \
	SRC/parser/expand_p/expand_container.c \
	SRC/parser/expand_p/path_util.c \
	SRC/parser/launch/launch.c \
	SRC/parser/launch/launcher_helper.c \
	SRC/parser/launch/pid.c \
	SRC/parser/launch/process.c \
	SRC/parser/launch/update_status.c \
	SRC/parser/lexer/asign_redir_lex.c \
	SRC/parser/lexer/r_lexer.c \
	SRC/parser/lexer/redir_iter.c \
	SRC/parser/lexer/tool_lexer.c \
	SRC/parser/cmd.c \
	SRC/parser/str_utils.c \
	SRC/parser/t_list.c \
	SRC/redir/advanced_redir.c \
	SRC/redir/fdp.c \
	SRC/redir/handle_heredoc.c \
	SRC/redir/handle_redir.c \
	SRC/redir/heredoc.c \
	SRC/redir/prepare_heredoc.c \
	SRC/redir/redir_help.c \
	SRC/redir/redir_util.c \
	SRC/utils/quotes.c \
	SRC/parser/token/token.c \
	SRC/parser/token/subtoken/subtoken.c \
	SRC/parser/token/subtoken/attribution_subok.c \
	SRC/parser/token/subtoken/subsubtok.c \
	SRC/parser/token/subtoken/subtok_hlp.c \
	SRC/parser/token/help_help_tok.c \
	SRC/parser/token/help_token.c \
	SRC/parser/token/token_tool.c \

OBJ_FILES   := $(SRC_FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -L$(LIBFT_DIR) -lft -lreadline -o $@

%.o: %.c $(INC_DIR)/minishell.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
