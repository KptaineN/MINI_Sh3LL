/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:27:31 by nkiefer           #+#    #+#             */
/*   Updated: 2025/09/04 14:27:52 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"


static void	print_env_pair(t_env *env)
{
	if (!env || !env->key || !env->value)
		return ;
	write(STDOUT_FILENO, env->key, ft_strlen(env->key));
	write(STDOUT_FILENO, "=", 1);
	write(STDOUT_FILENO, env->value, ft_strlen(env->value));
	write(STDOUT_FILENO, "\n", 1);
}

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
		return (g_exit_status = 1);
	}
	cur = sh->env;
	while (cur)
	{
		env = cur->content;
		print_env_pair(env);
		cur = cur->next;
	}
	g_exit_status = 0;
	return (0);
}