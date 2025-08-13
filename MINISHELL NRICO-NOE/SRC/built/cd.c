/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:35:57 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/13 15:30:56 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtin_cd(t_shell *shell, char **args)
{
	char		old_pwd[4096];
	char		new_pwd[4096];
	const char	*target;

	if (!getcwd(old_pwd, sizeof(old_pwd)))
		return (perror("cd"), shell->exit_status = 1);
	if (args[1] == NULL || *args[1] == '\0')
		target = getenv("HOME");
	else if (ft_strcmp(args[1], "-") == 0)
		target = getenv("OLDPWD");
	else
		target = args[1];
	if (!target)
		return (perror("cd: HOME/OLDPWD not set"), shell->exit_status = 1);
	if (chdir(target) != 0)
		return (perror("cd"), shell->exit_status = 1);
	if (!getcwd(new_pwd, sizeof(new_pwd)))
		return (perror("cd"), shell->exit_status = 1);
	set_env_value((t_list **)&shell->env, "OLDPWD", old_pwd);
	set_env_value((t_list **)&shell->env, "PWD", new_pwd);
	return (shell->exit_status = 0);
}

int	builtin_pwd(t_shell *shell, char **argv)
{
	char	cwd[1024];

	(void)shell;
	(void)argv;
	if (getcwd(cwd, sizeof(cwd)))
	{
		printf("%s\n", cwd);
		return (0);
	}
	perror("pwd");
	return (1);
}
