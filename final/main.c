/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 12:49:43 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/02 12:17:29 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"


int main(int argc, char **argv, char **envp)
{
    
    if (argc != 1 || argv[1])
	{
		ft_putstr_fd("Usage: ./minish\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
    t_sh *sh = calloc(1,sizeof(t_sh));
    init_sh(sh,envp);
    looping(sh);
    free_sh(sh);
	return (sh->exit_status);
}

/*
    //"$USER-\"USER\"-'$USER'", //"$USER-'$USER-\"$USER\"'-\"$USER\"", problem, c'Est le charactere '-' que j'ai pas pris en compte
    sh->parsed_args = custom_split("cat | cat | ls", sh);
    display_string_array(sh->parsed_args);
    sh->cmd = build_cmd(sh, sh->parsed_args);
    
    launch_process(sh,&sh->cmd);

*/