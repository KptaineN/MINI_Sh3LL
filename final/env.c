/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:27:31 by nkiefer           #+#    #+#             */
/*   Updated: 2025/09/02 13:51:18 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

int	builtin_env(void *v_sh, void **v_argv)
{
	t_sh	*sh;
	t_list	*cur;
	t_env	*env;
	char	**args;

	sh = (t_sh *)v_sh;
	args = (char **)v_argv;
	if (args[1])
	{
		ft_putstr_fd("( ͡ಠ ʖ̯ ͡ಠ)╭∩╮minish: env: too many arguments\n", 2);
		return (sh->exit_status = 1);
	}
	cur = sh->env;
	while (cur)
	{
		env = cur->content;
		if (env->value)
		{
			write(STDOUT_FILENO, env->key, ft_strlen(env->key));
			write(STDOUT_FILENO, "=", 1);
			write(STDOUT_FILENO, env->value, ft_strlen(env->value));
			write(STDOUT_FILENO, "\n", 1);
		}
		cur = cur->next;
	}
	sh->exit_status = 0;
	return (0);
}
