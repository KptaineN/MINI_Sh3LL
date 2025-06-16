/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:25:33 by eganassi          #+#    #+#             */
/*   Updated: 2025/06/16 16:20:40 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	setup_redirections(t_ast *ast)
{
	int	fd;

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

void	execute_simple_command(t_ast *ast, t_env *env)
{
	pid_t	pid;
	char	*cmd_path;
	char	**env_tab;
	int		status;

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
		env_tab = env_to_char_tab(env);
		execve(cmd_path, ast->args, env_tab);
		perror("execve");
		exit(127);
	}
	waitpid(pid, &status, 0);
}
/*
Étendre parse_line_to_ast() pour qu’il détecte et convertisse les redirections en nœuds AST de type :

    NODE_REDIR_OUT pour >

    NODE_REDIR_APPEND pour >>

    NODE_REDIR_IN pour <

    NODE_HEREDOC pour <<

	Gérer plusieurs redirections (cat < in > out)

Gérer les quotes autour du nom de fichier

Détecter et afficher les erreurs de syntaxe (>, sans fichier)

 Étape 1 : Détection des redirections

On va scanner les tokens de la commande et dès qu’on voit une redirection, on :

    extrait l’opérateur (>, >>, etc.)

    extrait le fichier cible

    construit un nœud NODE_REDIR_*

    rattache la commande précédente au champ .left du nœud

t_ast *parse_redirection(char **args)
{
	t_ast	*cmd;
	t_ast	*redir;
	int		i;

	// Commande initiale
	cmd = init_command_node(args);
	if (!cmd)
		return (NULL);

	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], ">") == 0 || ft_strcmp(args[i], ">>") == 0 ||
			ft_strcmp(args[i], "<") == 0 || ft_strcmp(args[i], "<<") == 0)
		{
			t_node_type type;

			if (args[i + 1] == NULL)
				return (cmd); // erreur : pas de fichier après opérateur

			// Détecte le type
			if (!ft_strcmp(args[i], ">"))
				type = NODE_REDIR_OUT;
			else if (!ft_strcmp(args[i], ">>"))
				type = NODE_REDIR_APPEND;
			else if (!ft_strcmp(args[i], "<"))
				type = NODE_REDIR_IN;
			else
				type = NODE_HEREDOC;

			// Crée nœud de redirection
			redir = init_redirection_node(type, args[i + 1], cmd);

			// Supprime opérateur et fichier des args pour le nœud commande
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


version de chatgpt

static char **split_on_pipes(const char *input)
{
	return ft_split(input, '|');
}

void free_strtab(char **tab)
{
	int i = 0;
	while (tab && tab[i])
		free(tab[i++]);
	free(tab);
}

static t_ast *parse_redirection(char **args)
{
	t_ast *cmd = init_command_node(args);
	if (!cmd)
		return NULL;

	for (int i = 0; args[i]; i++)
	{
		t_node_type type;
		if (!ft_strcmp(args[i], ">") || !ft_strcmp(args[i], ">>") ||
			!ft_strcmp(args[i], "<") || !ft_strcmp(args[i], "<<"))
		{
			if (!args[i + 1])
				return cmd; // Erreur : pas de fichier après l'opérateur

			if (!ft_strcmp(args[i], ">"))
				type = NODE_REDIR_OUT;
			else if (!ft_strcmp(args[i], ">>"))
				type = NODE_REDIR_APPEND;
			else if (!ft_strcmp(args[i], "<"))
				type = NODE_REDIR_IN;
			else
				type = NODE_HEREDOC;

			t_ast *redir = init_redirection_node(type, args[i + 1], cmd);

			// Supprime les arguments de redirection
			free(args[i]);
			free(args[i + 1]);
			args[i] = NULL;
			args[i + 1] = NULL;

			return redir;
		}
	}
	return cmd;
}

t_ast *parse_line_to_ast(const char *input)
{
	char **segments = split_on_pipes(input);
	t_ast *current = NULL;
	t_ast *right = NULL;

	if (!segments)
		return NULL;

	int i = 0;
	current = parse_redirection(ft_split(segments[i], ' '));
	i++;
	while (segments[i])
	{
		t_ast *pipe_node = init_ast_node(NODE_PIPE);
		right = parse_redirection(ft_split(segments[i], ' '));

		pipe_node->left = current;
		pipe_node->right = right;
		current = pipe_node;
		i++;
	}
	free_strtab(segments);
	return current;
}

void parse_input(t_minishell *shell)
{
	shell->ast = parse_line_to_ast(shell->input);
}

*/