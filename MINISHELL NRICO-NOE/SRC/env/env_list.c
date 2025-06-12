/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:35:29 by eganassi          #+#    #+#             */
/*   Updated: 2025/06/12 16:35:31 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// parse la string "KEY=VALUE" en t_env
// Dans ton create_env (ou équivalent) :
t_env	*create_env(char *env_str)
{
	t_env	*node;
	char	*equal;
	size_t	key_len;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	equal = ft_strchr(env_str, '=');
	if (!equal)
	{
		free(node);
		return (NULL);
	}
	key_len = equal - env_str;
	node->key = malloc(key_len + 1);
	if (!node->key)
	{
		free(node);
		return (NULL);
	}
	ft_strncpy(node->key, env_str, key_len);
	node->key[key_len] = '\0';
	node->value = ft_strdup(equal + 1);
	node->next = NULL;
	return (node);
}

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

// construit toute la liste à partir de envp
t_env	*init_env(char **envp)
{
	t_env *head = NULL, *tmp = NULL;
	int i = 0;
	while (envp[i])
	{
		t_env *node = create_env(envp[i]); // ← ici
		if (!head)
			head = node;
		else
			tmp->next = node;
		tmp = node;
		i++;
	}
	return (head);
}