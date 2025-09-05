/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minsh_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 12:56:27 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/01 12:30:00 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

//char	*get_env_value(t_list *env_list, const char *key)
//{
//	t_list	*current;
//	size_t	key_len;
//	char	*env_entry;
//
//	current = env_list;
//	key_len = ft_strlen(key);
//	while (current)
//	{
//		env_entry = (char *)current->content;
//		if (env_entry && ft_strncmp(env_entry, key, key_len) == 0
//			&& env_entry[key_len] == '=')
//		{
//			return (env_entry + key_len + 1); // Return value after '='
//		}
//		current = current->next;
//	}
//	return (NULL); // Variable not found
//}
