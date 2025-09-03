/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:55:54 by nkiefer           #+#    #+#             */
/*   Updated: 2025/09/02 12:27:25 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

t_list	*find_env_var(t_sh *sh, const char *key)
{
	t_env	*env;
	t_list	*node;

	node = sh->env;
	while (node)
	{
		env = (t_env *)node->content;
		if (ft_strcmp(env->key, key) == 0)
			return (node);
		node = node->next;
	}
	return (NULL);
}

int	update_env_var(t_list *env_node, const char *value)
{
	t_env	*env;

	env = (t_env *)env_node->content;
	free(env->value);
	if (value != NULL)
		env->value = ft_strdup(value);
	else
		env->value = NULL;
	return (0);
}

int	create_env_var(t_sh *sh, const char *key, const char *value)
{
	t_env	*new_env;
	t_list	*new_node;

	new_env = malloc(sizeof(*new_env));
	if (new_env == NULL)
		return (1);
	new_env->key = ft_strdup(key);
	if (value != NULL)
		new_env->value = ft_strdup(value);
	else
		new_env->value = NULL;
	new_node = malloc(sizeof(*new_node));
	if (new_node == NULL)
	{
		free(new_env->key);
		free(new_env->value);
		free(new_env);
		return (1);
	}
	new_node->content = new_env;
	new_node->next = sh->env;
	sh->env = new_node;
	return (0);
}

int	set_env_var(t_sh *sh, const char *key, const char *value)
{
	t_list	*existing;

	existing = find_env_var(sh, key);
	if (existing)
		return (update_env_var(existing, value));
	else
		return (create_env_var(sh, key, value));
}
