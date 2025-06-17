/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util-0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:30:56 by eganassi          #+#    #+#             */
/*   Updated: 2025/06/17 15:01:42 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void ft_free_array(char **arr)
{
    int i = 0;
    if (!arr) return;
    while (arr[i]) free(arr[i++]);
    free(arr);
}


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
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	handle_error(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}


 //* Libère toute la mémoire de la structure minishell.
 //* À compléter selon l'évolution de ta structure.

void	free_minishell(t_minishell *shell)
{
	if (!shell)
		return;

	// Libère la ligne d'entrée utilisateur
	if (shell->input)
		free(shell->input);

	// Libère le tableau d'arguments (ft_free_array est un helper type free_split)
	if (shell->args)
		ft_free_array(shell->args);

	// Libère l'AST
	if (shell->ast)
		free_ast(shell->ast);

	// Libère la liste chaînée des variables d'environnement
	if (shell->env)
		free_env(shell->env);

	// (OPTIONNEL selon évolution de la struct)
	// if (shell->env_list)
	//     free_env_list(shell->env_list);

	// (OPTIONNEL plus tard) : libère l'historique ou d'autres ressources globales
	// free_history(shell->history);

	// (OPTIONNEL plus tard) : libère des fd ou autres buffers
	// if (shell->some_fd != -1) close(shell->some_fd);

	// (OPTIONNEL plus tard) : libère des structures temporaires
	// if (shell->tmp_data) free_tmp_data(shell->tmp_data);
/*
	Quand tu ajouteras un nouveau champ à t_minishell, par exemple :

    un buffer (char *buffer)

    une nouvelle liste (t_list *jobs)

    un tableau de file descriptors (int *fd_tab)

Ajoute la ligne de libération dans free_minishell comme ceci :

if (shell->buffer)
	free(shell->buffer);

if (shell->jobs)
	free_job_list(shell->jobs);

if (shell->fd_tab)
	free(shell->fd_tab);
*/
	// ... ajoute ici tout ce que tu ajoutes dans la struct plus tard !
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
/*void	print_prompt(t_minishell *shell)
{
	// You can customize the prompt here, e.g.,
	//	add colors or display the current directory
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
}*/
