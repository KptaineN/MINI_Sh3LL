/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:24:52 by nkiefer           #+#    #+#             */
/*   Updated: 2025/09/02 13:33:10 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	unset_one(t_list **env, const char *key)
{
	t_list	*prev;
	t_list	*cur;
	t_env	*env_var;

	prev = NULL;
	cur = *env;
	while (cur)
	{
		env_var = cur->content;
		if (ft_strcmp(env_var->key, key) == 0)
		{
			if (prev)
				prev->next = cur->next;
			else
				*env = cur->next;
			free(env_var->key);
			free(env_var->value);
			free(env_var);
			free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

int	builtin_unset(void *v_sh, void **v_argv)
{
	t_sh	*sh;
	char	**argv;

	sh = (t_sh *)v_sh;
	argv = (char **)v_argv;
	int	i;

	i = 1;
	while (argv[i])
	{
		unset_one((t_list **)&sh->env, argv[i]);
		i++;
	}
	sh->exit_status = 0;
	return (0);
}

void	unset_env_value(t_list **env, const char *key)
{
	t_list	*tmp;
	t_list	*prev;
	t_env	*env_var;

	tmp = *env;
	prev = NULL;
	while (tmp)
	{
		env_var = tmp->content;
		if (ft_strcmp(env_var->key, key) == 0)
		{
			if (prev)
				prev->next = tmp->next;
			else
				*env = tmp->next;
			free(env_var->key);
			free(env_var->value);
			free(env_var);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}
