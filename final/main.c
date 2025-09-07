/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 12:49:43 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/07 14:41:15 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"
// »»-----► Number of lines: 12
sig_atomic_t g_exit_status = 0;

int main(int argc, char **argv, char **envp)
{
    if (argc != 1 || argv[1])
	{
		ft_putstr_fd("Usage: ./minish\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
    
    t_sh *sh = calloc(1,sizeof(t_sh));
    init_sh(sh,envp);
    
    g_exit_status = looping(sh);
    free_sh(sh);
	return (g_exit_status);
}


/**========================================================================
 *                           Test pid expansion function
 *========================================================================**/
/*
    replace_or_add(&sh->env,"PID","PID=0");
    void *v_arg[4] = {NULL,NULL};
    v_arg[0] = (void *)ft_strdup("echo $");
    v_arg[1] = (void *)ft_strdup("echo $ ");
    v_arg[2] = (void *)ft_strdup("echo$");
    char **result = (char**)pid_expansion(v_arg,sh->env);
    display_string_array(result);
    return (g_exit_status);
*/