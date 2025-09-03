/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:55:22 by nkiefer           #+#    #+#             */
/*   Updated: 2025/09/02 12:27:25 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

void	print_env_debug(t_list *env)
{
	t_env	*e;

	while (env)
	{
		e = env->content;
		printf("[DEBUG] %s=", e->key);
		if (e->value)
			printf("%s\n", e->value);
		else
			printf("\n");
		env = env->next;
	}
}

int	builtin_export(void *v_sh, void **v_argv)
{
	t_sh	*sh;
	char	**argv;
	sh = (t_sh *)v_sh;
	argv = (char **)v_argv;
	int	error;
	int	i;

	i = 0;
	if (!argv[1])
		return (export_no_arguments(sh));
	error = 0;
	i = 1;
	while (argv[i])
	{
		error |= process_export_argument(argv[i], sh);
		i++;
	}
	sh->exit_status = error;
	return (error);
}
