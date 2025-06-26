/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:32:48 by eganassi          #+#    #+#             */
/*   Updated: 2025/06/26 08:29:48 by nkiefer          ###   ########.fr       */
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



char	*get_valid_path(char *cmd,t_env *env)
{
	char	*path;

	path = pwd_path(cmd, env);
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
		full_path = ft_strjoin3(paths[i], "/", cmd, 1);
		if (!full_path)
			return (ft_free_split(paths), NULL);
		if (access(full_path, X_OK) == 0)
			return (ft_free_split(paths), full_path);
		free(full_path);
	}
	return (ft_free_split(paths), NULL);
}
// SRC/from_pipex/find_command_path.c
char *find_command_path(char *cmd, t_minishell *shell)
{
	(void)shell;
	return ft_strdup(cmd); // Béta : retourne le nom direct
}


/*char	*find_command_path(char *cmd, t_env *env)
{
    char	*path_env;
    char	**paths;

    if (!env || !cmd)
        return (NULL);
    if (ft_strchr(cmd, '/'))
    {
        if (access(cmd, F_OK) == 0)
            return (ft_strdup(cmd));
        else
            return (NULL);
    }
    // Utiliser get_env_path_list qui prend un t_env* et retourne la valeur de PATH
    path_env = get_env_value(env, "PATH");
    if (!path_env)
        return (get_valid_path(cmd, env));
    // Split PATH en un tableau de chemins
    paths = ft_split(path_env, ':');
    if (!paths)
        return (NULL);
    return (search_in_paths(paths, cmd));
}*/

