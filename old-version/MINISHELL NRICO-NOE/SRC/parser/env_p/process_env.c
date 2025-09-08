/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:34:25 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/29 10:42:28 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launch/launcher.h"

t_list	*find_env_entry(t_list *env, const char *key)
{
	size_t	key_len;
	char	*entry;

	if (!env || !key)
		return (NULL);
	key_len = ft_strlen(key);
	while (env)
	{
		entry = (char *)env->content;
		if (entry && ft_strncmp(entry, key, key_len) == 0
			&& entry[key_len] == '=')
			return (env);
		env = env->next;
	}
	return (NULL);
}

char	*build_kv_string(const char *key, const char *value)
{
	size_t	key_len;
	size_t	val_len;
	char	*strkv;

	if (!key)
		return (NULL);
	key_len = ft_strlen(key);
	if (value)
		val_len = ft_strlen(value);
	else
		val_len = 0;
	strkv = (char *)malloc(key_len + 1 + val_len + 1);
	if (!strkv)
		return (NULL);
	ft_memcpy(strkv, key, key_len);
	strkv[key_len] = '=';
	if (val_len)
		ft_memcpy(strkv + key_len + 1, value, val_len);
	strkv[key_len + 1 + val_len] = '\0';
	return (strkv);
}

static int	replace_env_if_exists(t_list *env, const char *key,
		const char *value)
{
	t_list	*cur;
	char	*str;
	size_t	klen;

	klen = ft_strlen(key);
	cur = env;
	while (cur)
	{
		if (cur->content && ft_strncmp((char *)cur->content, key, klen) == 0
			&& ((char *)cur->content)[klen] == '=')
		{
			if (value)
				str = build_kv_string(key, value);
			else
				str = build_kv_string(key, "");
			if (!str)
				return (-1);
			free(cur->content);
			cur->content = str;
			return (1);
		}
		cur = cur->next;
	}
	return (0);
}

void	replace_or_add_env(t_list **env, const char *key, const char *value)
{
	int		ret;
	char	*str;
	t_list	*node;

	if (!env || !key)
		return ;
	ret = replace_env_if_exists(*env, key, value);
	if (ret != 0)
		return ;
	if (value)
		str = build_kv_string(key, value);
	else
		str = build_kv_string(key, "");
	if (!str)
		return ;
	node = ft_lstnew(str);
	if (!node)
	{
		free(str);
		return ;
	}
	ft_lstadd_back(env, node);
}
