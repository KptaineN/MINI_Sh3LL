#include "../../include/minishell.h"

// Assemble trois chaînes (ex: "bin", "/", "ls" -> "bin/ls")
char	*ft_strjoin_3(const char *a, const char *b, const char *c)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(a, b);
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, c);
	free(tmp);
	return (res);
}

void	ft_free_split(char **tab)
{
	int i = 0;
	if (!tab)
		return;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void handle_error(const char *message)
{
    perror(message);
    exit(EXIT_FAILURE);
}

void free_minishell(t_minishell *shell)
{
    if (shell->input)
        free(shell->input);
    if (shell->args)
        ft_free_array(shell->args);
    if (shell->ast)
        free_ast(shell->ast); // Assuming you have a function to free the AST
    if (shell->env)
        free_env(shell->env);
    // Add any other cleanup needed for your minishell
}
/*void handle_signal(int signal)
{
    if (signal == SIGINT)
    {
        // Handle Ctrl+C
        write(STDOUT_FILENO, "\n", 1); // Print a newline
        rl_replace_line("", 0); // Clear the current line in readline
        rl_on_new_line(); // Move to a new line
        rl_redisplay(); // Redisplay the prompt
    }
    else if (signal == SIGQUIT)
    {
        // Handle Ctrl+\ (SIGQUIT)
        write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
    }
}*/
void print_prompt(t_minishell *shell)
{
    // You can customize the prompt here, e.g., add colors or display the current directory
    char *cwd = getcwd(NULL, 0); // Get current working directory
    if (cwd)
    {
        printf("\033[1;32m%s\033[0m$ ", cwd); // Print in green color
        free(cwd);
    }
    else
    {
        printf("minishell$ ");
    }
}
void parse_input(t_minishell *shell)
{
    // This function should parse the input and build the AST
    // For now, we will just print the input for debugging
    if (shell->input)
    {
        printf("Parsing input: %s\n", shell->input);
        // Here you would typically call a function to build the AST
        // shell->ast = build_ast(shell->input);
    }
}

void free_ast(t_ast *ast)
{
    // This function should free the AST structure
    // For now, we will just print a message for debugging
    if (ast)
    {
        printf("Freeing AST...\n");
        // Here you would typically free the AST nodes
        // free_ast_nodes(ast);
    }
}
void clean_exit(char **cmd_args, char *msg, int code)
{
    if (msg)
        ft_putendl_fd(msg, 2);
    if (cmd_args)
        ft_free_split(cmd_args);
    exit(code);
}
