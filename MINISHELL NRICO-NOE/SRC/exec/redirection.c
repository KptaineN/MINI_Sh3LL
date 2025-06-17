/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:25:33 by eganassi          #+#    #+#             */
/*   Updated: 2025/06/17 14:27:22 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../include/minishell.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

/*
 * Applique les redirections définies dans l'AST.
 */
void setup_redirections(t_ast *ast)
{
    int fd;

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
    // Possibilité d'ajouter ici le traitement du HEREDOC...
}

void execute_simple_command(t_ast *ast, t_env *env)
{
    pid_t pid;
    char *cmd_path;
    char **env_tab;
    int status;

    pid = fork();
    if (pid == 0)
    {
        setup_redirections(ast); // Ici,
        //	on gère toutes les redirections de l’AST
        cmd_path = find_cmd(ast->args[0], env);
        if (!cmd_path)
        {
            ft_putendl_fd("minishell: command not found", 2);
            exit(127);
        }
        env_tab = env_to_envp(env);
        execve(cmd_path, ast->args, env_tab);
        perror("execve");
        exit(127);
    }
    waitpid(pid, &status, 0);
}

/*
 * Scanne les arguments pour détecter une redirection et créer un nœud AST approprié.
 */
t_ast *parse_redirection(char **args)
{
    t_ast *cmd = init_command_node(args);
    if (!cmd)
        return NULL;
    int i = 0;
    while (args[i])
    {
        t_node_type type;
        if ((ft_strncmp(args[i], ">", strlen(">")) == 0) ||
            (ft_strncmp(args[i], ">>", strlen(">>")) == 0) ||
            (ft_strncmp(args[i], "<", strlen("<")) == 0) ||
            (ft_strncmp(args[i], "<<", strlen("<<")) == 0))
        {
            if (!args[i + 1])
            {
                fprintf(stderr, "syntax error near unexpected token\n");
                return cmd; // ou gérer l'erreur différemment
            }
            if (!ft_strncmp(args[i], ">", ft_strlen(">") + 1))
                type = NODE_REDIR_OUT;
            else if (!ft_strncmp(args[i], ">>", ft_strlen(">>") + 1))
                type = NODE_REDIR_APPEND;
            else if (!ft_strncmp(args[i], "<", ft_strlen("<") + 1))
                type = NODE_REDIR_IN;
            else
                type = NODE_HEREDOC;
    
            t_ast *redir = init_redirection_node(type, args[i + 1], cmd);
            // Libérer les arguments de redirection dans le nœud commande 
            free(cmd->args[i]);
            free(cmd->args[i + 1]);
            cmd->args[i] = NULL;
            cmd->args[i + 1] = NULL;
            return redir;
        }
        i++;
    }
    return cmd;
}


void free_strtab(char **tab)
{
    int i = 0;
    while (tab && tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

/*
 * Parse la ligne d'entrée pour créer l'AST en tenant compte des redirections et des pipes.
 */

/*
void parse_input(t_minishell *shell)
{
    shell->ast = parse_line_to_ast(shell->input);
}*/

