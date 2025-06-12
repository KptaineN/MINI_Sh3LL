/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:32:48 by eganassi          #+#    #+#             */
/*   Updated: 2025/06/12 16:34:54 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_env_value(t_env *env, const char *name)
{
	size_t	n;

	n = ft_strlen(name);
	while (env)
	{
		if (ft_strncmp(env->key, name, n) == 0 && env->key[n] == '\0')
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

// Assemble trois chaînes (ex: "bin", "/", "ls" -> "bin/ls")
char	*ft_strjoin_3(const char *a, const char *b, const char *c)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(a, b);
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, c);
	free(tmp);
	return (res);
}

char	*get_valid_path(char *cmd, t_minishell *envp)
{
	char	*path;

	path = pwd_path(cmd, envp);
	if (path && access(path, X_OK) == 0)
		return (path);
	free(path);
	return (NULL);
}

char	*search_in_paths(char **paths, char *cmd)
{
	char	*full_path;
	int		i;

	i = -1;
	while (paths[++i])
	{
		full_path = ft_strjoin_3(paths[i], "/", cmd);
		if (!full_path)
			return (ft_free_split(paths), NULL);
		if (access(full_path, F_OK) == 0)
			return (ft_free_split(paths), full_path);
		free(full_path);
	}
	return (ft_free_split(paths), NULL);
}

char	*find_command_path(char *cmd, t_env *env)
{
	char	**envp;
	char	*path_env;

	if (!env || !cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	path_env = get_env_path(envp, "PATH=");
	if (!path_env)
		return (get_valid_path(cmd, envp));
	path_env = ft_split(path_env, ':');
	if (!path_env)
		return (NULL);
	return (search_in_paths(path_env, cmd));
}

