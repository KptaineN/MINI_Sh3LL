/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:24:10 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/08 21:15:16 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../env/env.h"
#include "../../include/minishell.h"

int	run_stage(t_shell *sh, char *line, char *in)
{
	launch_process(sh);
	cleanup_shell_iter(sh, line);
	sh->input = NULL;
	free(in);
	return (2);
}

char	*read_user_input(void)
{
	char	*input;

	input = readline("ᕕ( ᐛ )ᕗ minishell$ ");
	if (!input)
		write(1, "exit\n", 5);
	return (input);
}

int	looping(t_shell *shell)
{
	char	*in;
	int		retour;

	retour = 0;
	while (1)
	{
		in = read_user_input();
		if (!in)
		{
			free(in);
			break ;
		}
		shell->exit_status = g_exit_status;
		retour = process_input(shell, in);
		if (retour == 2)
			g_exit_status = shell->exit_status;
		if (retour == 1)
			break ;
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	if (argc != 1 || argv[1])
	{
		ft_putstr_fd("Usage: ./minishell\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	print_header_emote();
	if (start_shell(&shell, envp))
	{
		ft_putstr_fd("Failed to start minishell\n", STDERR_FILENO);
		free_env_list(shell.env);
		return (EXIT_FAILURE);
	}
	looping(&shell);
	rl_clear_history();
	free_minishell(&shell);
	return (g_exit_status);
}
