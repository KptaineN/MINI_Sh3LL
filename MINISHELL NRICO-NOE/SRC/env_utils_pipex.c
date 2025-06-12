/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_pipex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:37:06 by eganassi          #+#    #+#             */
/*   Updated: 2025/06/12 16:37:07 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_env_value(t_env *env, const char *name);
char	*ft_strjoin_3(const char *a, const char *b, const char *c);
char	*find_cmd(char *cmd, t_env *env);
void	ft_free_split(char **tab);

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

void	ft_free_split(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}
