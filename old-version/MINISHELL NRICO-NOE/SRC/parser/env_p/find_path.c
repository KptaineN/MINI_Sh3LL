/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 14:54:24 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/29 11:07:54 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_dir_for_cmd(char *dir, char *cmd)
{
	char	*full;

	full = NULL;
	full = join_path(dir, cmd);
	if (!full)
		return (NULL);
	if (access(full, F_OK | X_OK) == 0)
		return (full);
	free(full);
	return (NULL);
}

char	*scan_path_copy(char *cmd, char *copy)
{
	char	*p;
	char	*qq;
	char	save_c;
	char	*hit;

	p = NULL;
	qq = NULL;
	hit = NULL;
	p = copy;
	while (1)
	{
		qq = p;
		while (*qq && *qq != ':')
			qq++;
		save_c = *qq;
		*qq = '\0';
		if (*p != '\0')
			hit = check_dir_for_cmd(p, cmd);
		*qq = save_c;
		if (hit || save_c == '\0')
			break ;
		p = qq + 1;
	}
	return (hit);
}

char	*search_in_path(char *cmd, char *path_env)
{
	char	*copy;
	char	*hit;

	copy = NULL;
	hit = NULL;
	if (!path_env)
		return (NULL);
	copy = ft_strdup(path_env);
	if (!copy)
		return (NULL);
	hit = scan_path_copy(cmd, copy);
	free(copy);
	return (hit);
}

char	*find_command_path(char *cmd, t_list *env)
{
	char	*path_env;
	char	*found;

	path_env = NULL;
	found = NULL;
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_env = get_path_env(env);
	if (!path_env)
		return (NULL);
	found = search_in_path(cmd, path_env);
	if (found)
		return (found);
	return (NULL);
}
