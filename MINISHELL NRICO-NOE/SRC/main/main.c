/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:24:10 by eganassi          #+#    #+#             */
/*   Updated: 2025/06/17 11:46:33 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//int main(void)
int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;

	(void)argc;
	(void)argv;
	init_signals();
	if (!start_minishell(&shell, envp))
	{
		ft_putendl_fd("Error initializing minishell\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	free_minishell(&shell);
	return (shell.exit_status);
}
