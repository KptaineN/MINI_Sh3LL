/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 12:47:33 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/08 13:28:44 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		perror("MALLOC in ft_lstnew");
	new->content = content;
	new->arr_content = NULL;
	new->next = NULL;
	return (new);
}

//gives to the next
void	push_lst(t_list **tail, void *content)
{
	t_list *new;

	if (!tail || !*tail)
		return ;
	new = malloc(sizeof(t_list));
	if (!new)
		perror("MALLOC push_list");
	
	(*tail)->next = new;
	(*tail) = (*tail)->next; 
	new->content = content;
	new->next = NULL;
}

static char	*join_path(const char *dir, const char *cmd)
{
	char	*full_path;
	int		dir_len;
	int		cmd_len;

	dir_len = ft_strlen(dir);
	cmd_len = ft_strlen(cmd);
	full_path = malloc(dir_len + cmd_len + 2);
	if (!full_path)
		return (NULL);
	ft_strncpy(full_path,dir,dir_len);
	full_path[dir_len++] = '/';
	ft_strncpy(&full_path[dir_len],cmd,cmd_len);
	full_path[cmd_len+dir_len] = '\0';
	return (full_path);
}

static char *try_cmd_in_dir(const char *dir, const char *cmd)
{
	char *full;

	full = join_path(dir, cmd);
	if (!full)
		return (NULL);
	if (access(full, F_OK | X_OK) == 0)
		return (full);
	free(full);
	return (NULL);
}

/* renvoie une copie modifiable de PATH (à free) et écrit sa longueur dans *out_len */
static char *dup_path_env(t_list *env)
{
	char *path_env;
	char *copy;
	path_env = get_env_value(env, "PATH");
	if (!path_env)
		return (NULL);
	copy = ft_strdup(path_env);
	if (!copy)
		return (NULL);
	return (copy);
}

/* boucle principale: parcourt path_copy séparé par ':' (on mute les ':' en '\0') */
static char *search_cmd_in_path(char *path_copy, const char *cmd)
{
	int   i;
	int   start;
	char *dir;
	char *found;

	start = 0;
	i = 0;
	while (path_copy[i])
	{
		if (path_copy[i] == ':' || path_copy[i] == '\0')
		{
			path_copy[i] = '\0';            
			dir = path_copy + start;
			if (*dir != '\0')               
			{
				found = try_cmd_in_dir(dir, cmd);
				if (found)
					return (found);          
			}
			start = i + 1;                   
		}
		i++;
	}
	return (NULL);
}

char	*find_command_path(char *cmd, t_list *env)
{
	char *path_copy;
	char *found;
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_copy = dup_path_env(env);
	if (!path_copy)
		return (NULL);
	found = search_cmd_in_path(path_copy, cmd);
	free(path_copy);
	return (found);
}

t_dic	*env_lookup(t_list *env, const char *key)
{
	t_list	*tmp;
	t_dic	*cur;

	tmp = env;
	while (tmp)
	{
		cur = (t_dic *)tmp->content;
		if (cur && cur->key && ft_strcmp(cur->key, key) == 0)
			return (cur);
		tmp = tmp->next;
	}
	return (NULL);
}

static int	update_env_value(t_dic *cur, const char *value)
{
	char	*dup;

	dup = ft_strdup(value);
	if (!dup)
		return (1);
	free(cur->value);
	cur->value = dup;
	return (0);
}

static t_dic	*new_env_struct(const char *key, const char *value)
{
	t_dic	*env_entry;

	env_entry = malloc(sizeof(*env_entry));
	if (!env_entry)
		return (NULL);
	env_entry->key = ft_strdup(key);
	if (!env_entry->key)
		return (free(env_entry), (t_dic *)NULL);
	env_entry->value = ft_strdup(value);
	if (!env_entry->value)
	{
		free(env_entry->key);
		free(env_entry);
		return (NULL);
	}
	return (env_entry);
}

static void	ft_lstadd_front(t_list **lst, void *content)
{
	t_list	*new_node;

	if (!lst || !content)
		return ;
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->content = ft_strdup((char *)content);
	if (!new_node->content)
	{
		free(new_node);
		return ;
	}
	new_node->next = *lst;
	*lst = new_node;
}

int	set_env_value(t_list **env, const char *key, const char *value)
{
	t_dic	*existing;
	t_dic	*entry;
	t_list	*node;

	if (!env || !key || !value)
		return (1);
	existing = env_lookup(*env, key);
	if (existing)
		return (update_env_value(existing, value));
	entry = new_env_struct(key, value); // ex- "e"
	if (!entry)
		return (1);
	node = ft_lstnew(entry);
	if (!node)
		return (free(entry->key), free(entry->value), free(entry), 1);
	ft_lstadd_front(env, node);
	return (0);
}
