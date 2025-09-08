/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 14:55:17 by nkiefer           #+#    #+#             */
/*   Updated: 2025/09/08 19:22:58 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_env	*env_lookup(t_list *env, const char *key)
{
	t_list	*tmp;
	t_env	*cur;

	tmp = env;
	while (tmp)
	{
		cur = (t_env *)tmp->content;
		if (cur && cur->key && ft_strcmp(cur->key, key) == 0)
			return (cur);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_value_env(t_list *env, char *value, int len)
{
	t_env	*cur;

	while (env)
	{
		cur = env->content;
		if ((int)ft_strlen(cur->key) == len && ft_strncmp(cur->key, value,
				len) == 0)
			return (cur->value);
		env = env->next;
	}
	return (NULL);
}

char	*get_path_env(t_list *env)
{
	t_env	*cur;

	while (env)
	{
		cur = env->content;
		if (ft_strcmp(cur->key, "PATH") == 0)
			return (cur->value);
		env = env->next;
	}
	return (NULL);
}

char	*join_path(char *dir, char *cmd)
{
	size_t	dir_len;
	size_t	cmd_len;
	char	*full;

	dir_len = ft_strlen(dir);
	cmd_len = ft_strlen(cmd);
	full = malloc(dir_len + 1 + cmd_len + 1);
	if (!full)
		return (NULL);
	ft_memcpy(full, dir, dir_len);
	full[dir_len] = '/';
	ft_memcpy(full + dir_len + 1, cmd, cmd_len);
	full[dir_len + 1 + cmd_len] = '\0';
	return (full);
}
