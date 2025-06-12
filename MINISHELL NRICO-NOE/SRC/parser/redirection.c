#include "../../include/minishell.h"

void    setup_redirections(t_ast *ast)
{
    int fd;

    // Redirection input <
    if (ast->type == NODE_REDIR_IN && ast->filename)
    {
        fd = open(ast->filename, O_RDONLY);
        if (fd < 0)
        {
            perror(ast->filename);
            exit(1);
        }
        dup2(fd, STDIN_FILENO);
        close(fd);
    }
    // Redirection output >
    else if (ast->type == NODE_REDIR_OUT && ast->filename)
    {
        fd = open(ast->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0)
        {
            perror(ast->filename);
            exit(1);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }
    // Redirection output >>
    else if (ast->type == NODE_REDIR_APPEND && ast->filename)
    {
        fd = open(ast->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd < 0)
        {
            perror(ast->filename);
            exit(1);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }
    // Ici tu peux ajouter heredoc ou autres redirections
}

void    execute_simple_command(t_ast *ast, t_env *env)
{
    pid_t   pid;
    char    *cmd_path;
    char    **env_tab;
    int     status;

    pid = fork();
    if (pid == 0)
    {
        setup_redirections(ast); // Ici, on gère toutes les redirections de l’AST

        cmd_path = find_cmd(ast->args[0], env);
        if (!cmd_path)
        {
            ft_putendl_fd("minishell: command not found", 2);
            exit(127);
        }
        env_tab = env_to_char_tab(env);
        execve(cmd_path, ast->args, env_tab);
        perror("execve");
        exit(127);
    }
    waitpid(pid, &status, 0);
}
