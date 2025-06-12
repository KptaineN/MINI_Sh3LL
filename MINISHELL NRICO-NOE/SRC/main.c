/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:24:10 by eganassi          #+#    #+#             */
/*   Updated: 2025/06/12 16:29:05 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(void) // int argc, char **argv, char **envp)
{
	t_minishell	shell;

	(void)argc;
	(void)argv;
	if (!start_init_minishell(&shell, envp))
	{
		ft_putendl_fd("Error initializing minishell\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	free_minishell(&shell);
	return (shell.exit_status);
}
