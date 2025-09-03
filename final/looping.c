/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   looping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:24:09 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/03 11:43:09 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	parse_and_prepare(t_sh *sh, char *in)
{
	sh->parsed_args = custom_split(in, sh);
	display_string_array(sh->parsed_args);
	sh->cmd = build_cmd(sh, sh->parsed_args);
}

static int	process_input(t_sh *sh, char *in)
{
	if (!in || *in == '\0')
		return (0); //(cleanup_sh_iter(sh, in), 0);
	add_history(in);
	if (ft_strcmp(in, "exit") == 0)
		return (1); //(cleanup_sh_iter(sh, in), 1);
	parse_and_prepare(sh, in);
	display_linked_list_of_string_array(sh->cmd);
	launch_process(sh);
	return (free(in), 2);
}

static char	*read_user_input(void)
{
	char	*input;

	input = readline("ᕕ( ᐛ )ᕗ minish$ ");
	if (!input)
		write(1, "exit\n", 5);
	return (input);
}

int	looping(t_sh *sh)
{
	char	*in;
	int		retour;

	retour = 0;
	while (1)
	{
		in = read_user_input();
		if (!in)
			break ;
		retour = process_input(sh, in);
		if (retour == 1)
			break ;
	}
	return (0);
}
