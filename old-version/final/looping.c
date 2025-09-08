/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   looping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:24:09 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/08 13:59:07 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"
// »»-----► Number of lines: 14
static int	process_input(t_sh *sh, char *in)
{
	add_history(in);
	in = expand_single_string(in,sh->env);
	sh->parsed_args = custom_split(sh, in);
	display_string_array(sh->parsed_args);
	if (sh->n_parsed == 0)
		return (free(sh->parsed_args),0);
	sh->cmd = build_cmd(sh, sh->parsed_args);
	display_linked_list_of_string_array(sh->cmd);
	if (ft_strcmp((char *)sh->cmd->arr_content[0], "exit") == 0)
	{	
		free_linked_list_of_array_string(sh->cmd);
		return -1;
	}
	return (0);
}

// »»-----► Number of lines: 15
int	looping(t_sh *sh)
{
	char	*in;
	while (1)
	{
		in = NULL;
		while(!in)
			in = get_full_line(sh);
		if (!in)
			break ;	
		g_exit_status = process_input(sh, in);
		if (g_exit_status == -1)
			break ;
		//int pipe[2] = {-1,-1};
		//sh->cmd->arr_content = (void **)rebuild_noredir_cmd(sh->oper, (char **)sh->cmd->arr_content, pipe);
		//execution_button((char **)sh->cmd->arr_content,sh);
		launch_process(sh);
		free_linked_list_of_array_string(sh->cmd);
	}	
	return (0);
}