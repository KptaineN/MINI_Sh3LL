/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:35:57 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/02 13:45:10 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static int	cd_too_many(char **args, t_sh *sh)
{
	if (args[1] && args[2])
	{
		ft_putstr_fd("(;・_・)՞minish: cd: too many arguments\n", 2);
		sh->exit_status = 1;
		return (1);
	}
	return (0);
}

static const char	*cd_pick_target(char **args)
{
	if (args[1] == NULL || *args[1] == '\0')
		return (getenv("HOME"));
	if (ft_strcmp(args[1], "-") == 0 || ft_strcmp(args[1], "--") == 0)
		return (getenv("OLDPWD"));
	return (args[1]);
}

static int	cd_switch_to(const char *target, t_sh *sh)
{
	if (!target)
	{
		ft_putstr_fd("minish: cd: HOME/OLDPWD not set\n", 2);
		sh->exit_status = 1;
		return (0);
	}
	if (chdir(target) != 0)
	{
		perror("cd");
		sh->exit_status = 1;
		return (0);
	}
	return (1);
}

static int	cd_update_pwds(t_sh *sh, const char *old_pwd)
{
	char	new_pwd[4096];

	if (!getcwd(new_pwd, 4096))
	{
		perror("cd");
		sh->exit_status = 1;
		return (0);
	}
	if ((set_env_value((t_list **)&sh->env, "OLDPWD", (char *)old_pwd) != 0)
		|| (set_env_value((t_list **)&sh->env, "PWD", new_pwd) != 0))
	{
		perror("set_env_value");
		sh->exit_status = 1;
		return (0);
	}
	sh->exit_status = 0;
	return (1);
}

int	builtin_cd(void *v_sh, void **v_argv)
{
	t_sh	*sh = (t_sh *)v_sh;
	char		old_pwd[4096];
	const char	*target;
	char		**args = (char **)v_argv;

	if (cd_too_many(args, sh))
		return (sh->exit_status);
	if (!getcwd(old_pwd, 4096))
	{
		perror("cd");
		sh->exit_status = 1;
		return (sh->exit_status);
	}
	target = cd_pick_target(args);
	if (!cd_switch_to(target, sh))
		return (sh->exit_status);
	if (!cd_update_pwds(sh, old_pwd))
		return (sh->exit_status);
	return (sh->exit_status);
}
