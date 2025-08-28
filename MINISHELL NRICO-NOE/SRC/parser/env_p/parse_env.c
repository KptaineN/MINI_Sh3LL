/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 14:55:17 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/26 19:28:43 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	set_env_value(t_list **env, const char *key, const char *value)
{
	t_env	*cur;
	t_env	*new_env;
	t_list	*node;
	char	*dup;

	cur = env_lookup(*env, key);
	if (cur)
	{
		dup = ft_strdup(value);
		if (!dup)
			return (1);
		free(cur->value);
		cur->value = dup;
		return (0);
	}
	new_env = malloc(sizeof(t_env));
	node = malloc(sizeof(t_list));
	if (!new_env || !node)
	{
		free(new_env);
		free(node);
		return (1);
	}
	new_env->key = ft_strdup(key);
	if (!new_env->key)
	{
		free(new_env);
		free(node);
		return (1);
	}
	new_env->value = ft_strdup(value);
	if (!new_env->value)
	{
		free(new_env->key);
		free(new_env);
		free(node);
		return (1);
	}
	node->content = new_env;
	node->next = *env;
	*env = node;
	return (0);
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
	size_t	dl;
	size_t	cl;
	char	*full;

	dl = ft_strlen(dir);
	cl = ft_strlen(cmd);
	full = malloc(dl + 1 + cl + 1);
	if (!full)
		return (NULL);
	ft_memcpy(full, dir, dl);
	full[dl] = '/';
	ft_memcpy(full + dl + 1, cmd, cl);
	full[dl + 1 + cl] = '\0';
	return (full);
}
