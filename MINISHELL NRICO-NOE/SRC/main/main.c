/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:24:10 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/13 15:20:21 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	if (argc != 1 || argv[1])
	{
		ft_putstr_fd("Usage: ./minishell\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (!start_shell(&shell, envp))
	{
		ft_putstr_fd("Failed to start minishell\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	looping(&shell);
	free_minishell(&shell);
	return (shell.exit_status);
}
/*
pour etre conforme a la norminette ajouter soi meme le header
// print_header_emote();
apres la 1er condition
*/