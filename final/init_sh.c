/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_sh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:01:10 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/01 14:01:18 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

// »»-----► Number of lines: 31
static t_list	*set_linked_env(char **env)
{
	t_list	*head;
	t_list	*node;
    t_list	*last;
	char 	*p;
	t_dic 	*dic;
	int		i;
	i = 0;
    while (env[i])
	{
		dic = malloc(sizeof(t_dic));
		p = ft_strchr(env[i],'=');
		p[0] = 0;
		dic->key = ft_strdup(env[i]);
		dic->value = ft_strdup(&p[1]);
		node = ft_lstnew((void *)dic);
		if (!node)
			return (NULL);
        if(i == 0)
        {    
            head = node;
            last = node;
        }
        else
        {    
            last->next = node;
            last = last->next;
        }
        last->next = NULL;
		i++;
	}
	return (head);
}
// »»-----► Number of lines: 16
static void	init_family(t_sh *sh)
{
	int			i;
	t_family	f[][2] = {{one_child, one_parent}, {multi_child, multi_parent},
			{end_child, end_parent}, {NULL, NULL}};
	int			len;

	i = 0;
	sh->f_core = malloc(sizeof(t_family *) * 5);
	len = sizeof(f) / sizeof(f[0]) - 1;
	while (i < len)
	{
		sh->f_core[i] = malloc(sizeof(t_family) * 2);
		sh->f_core[i][0] = f[i][0];
		sh->f_core[i][1] = f[i][1];
		i++;
	}
	sh->f_core[len] = NULL;
}
// »»-----► Number of lines: 9
void	init_sh(t_sh *sh, char **envp)
{
	sh->env = set_linked_env(envp);
	replace_or_add(&sh->env,"PID","0");
	replace_or_add(&sh->env,"0","bash");
	replace_or_add(&sh->env,"?","0");
	init_all_t_arr(sh);
	sh->msg_error = ft_calloc(6, sizeof(char));
	g_exit_status = 0;
	ft_strcpy(sh->msg_error, "0");
	init_family(sh);
}