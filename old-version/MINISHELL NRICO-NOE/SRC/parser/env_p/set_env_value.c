/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 10:44:58 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/29 10:45:03 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_env_value(t_env *cur, const char *value)
{
	char	*dup;

	dup = ft_strdup(value);
	if (!dup)
		return (1);
	free(cur->value);
	cur->value = dup;
	return (0);
}

static void	free_env_struct(t_env *e)
{
	if (!e)
		return ;
	free(e->key);
	free(e->value);
	free(e);
}
static t_env	*new_env_struct(const char *key, const char *value)
{
	t_env	*env_entry;

	env_entry = malloc(sizeof(*env_entry));
	if (!env_entry)
		return (NULL);
	env_entry->key = ft_strdup(key);
	if (!env_entry->key)
		return (free(env_entry), (t_env *)NULL);
	env_entry->value = ft_strdup(value);
	if (!env_entry->value)
	{
		free(env_entry->key);
		free(env_entry);
		return (NULL);
	}
	return (env_entry);
}

int	set_env_value(t_list **env, const char *key, const char *value)
{
	t_env	*existing;
	t_env	*entry;
	t_list	*node;

	if (!env || !key || !value)
		return (1);
	existing = env_lookup(*env, key);
	if (existing)
		return (update_env_value(existing, value));
	entry = new_env_struct(key, value); // ex- "e"
	if (!entry)
		return (1);
	node = ft_lstnew(entry); // ft_lstnew ne copie pas, il garde le pointeur
	if (!node)
		return (free_env_struct(entry), 1);
	ft_lstadd_front(env, node);
	return (0);
}
