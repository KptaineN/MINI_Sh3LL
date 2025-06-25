/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:35:29 by eganassi          #+#    #+#             */
/*   Updated: 2025/06/25 16:58:12 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

#include <stdlib.h>

int env_len(t_env *env)
{
	int count = 0;

	while (env)
	{
		count++;
		env = env->next;
	}
	return count;
}

/*
char	**env_to_envp(t_env *env)
{
    t_env	*curr;
    int		count = 0;
    char	**envp;
    int		i;

    curr = env;
    while (curr)
    {
        count++;
        curr = curr->next;
    }
    envp = malloc(sizeof(char *) * (count + 1));
    if (!envp)
        handle_error("malloc");
    i = 0;
    curr = env;
    while (curr)
    {
        envp[i] = ft_strjoin_3(curr->key, "=", curr->value);
        i++;
        curr = curr->next;
    }
    envp[i] = NULL;
    return (envp);
}*/

// parse la string "KEY=VALUE" en t_env
// Dans ton create_env (ou équivalent) :
/*
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
	if (ft_strlcpy(node->key, env_str, key_len + 1) != key_len)
		handle_error("ft_strlcpy error copying key");
	node->value = ft_strdup(equal + 1);
	node->next = NULL;
	return (node);
}*/
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
	ft_memcpy(node->key, env_str, key_len);
	node->key[key_len] = '\0'; // ajout du null terminator manuellement

	node->value = ft_strdup(equal + 1);
	if (!node->value)
	{
		free(node->key);
		free(node);
		return (NULL);
	}
	node->next = NULL;
	return (node);
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