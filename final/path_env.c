/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 12:47:33 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/03 19:44:33 by eganassi         ###   ########.fr       */
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

void advance_node(t_list **node)
{
    t_list *curr;
    if (!(*node))
        return;
    curr = (*node);
 	(*node) = (*node)->next;
    free(curr);
}

//gives to the next
void	push_lst(t_list **tail, void *content)
{
	t_list *new;

	if (!*tail)
		return ;
	new = malloc(sizeof(t_list));
	if (!new)
		perror("MALLOC push_list");
	
	(*tail)->next = new;
	(*tail) = (*tail)->next; 
	new->content = content;
	new->next = NULL;
}


t_list	*set_linked_env(char **env)
{
	t_list	*head;
	t_list	*node;
    t_list	*last;
	int		i;
	i = 0;
    while (env[i])
	{
        node = ft_lstnew(ft_strdup(env[i]));
		if (!node)
			return (NULL);
        if(i == 0)
        {    
            head = node;
            last = node;
        }
        else
        {    
            last->next = node;
            last = last->next;
        }
        last->next = NULL;
		i++;
	}
	return (head);
}

bool special_strcmp(char *dst, char *str, char c, int len)
{
	int	i;
	i = 0;
	if (dst == NULL || str == NULL || len <= 0)
		return true;
	while(i<len)
	{
		if (dst[i] != str[i])
			return true;
		i++;
	}
	if (dst[i] == c)
		return false;
	return true;
}

static char	*get_value_env(t_list *env, char *value, int len)
{
	t_list	*temp;
	temp = env;
	while (temp != NULL)
	{
		if (special_strcmp((char *)temp->content, value, '=', len) == 0)
			return (temp->content + len +1); // Skip "value="
		temp = temp->next;
	}
	return (NULL);
}

static char	*join_path(const char *dir, const char *cmd)
{
	char	*full_path;
	int		dir_len;
	int		cmd_len;

	dir_len = ft_strlen(dir);
	cmd_len = ft_strlen(cmd);
	full_path = malloc(dir_len + cmd_len + 2); // +2 for '/' and '\0'
	if (!full_path)
		return (NULL);
	// Copy directory
	ft_strncpy(full_path,dir,dir_len);
	full_path[dir_len++] = '/';
	ft_strncpy(&full_path[dir_len],cmd,cmd_len);
	full_path[cmd_len+dir_len] = '\0';
	return (full_path);
}

/********************** -> f cmd path
char	*find_command_path(char *cmd, t_list *env)
{
	char	*path_env;
	char	*path_copy;
	char	*dir;
	char	*full_path;

	int i, start, len;
	// If command contains '/', it's already a path
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	// Get PATH envirnment variable
	path_env = get_value_env(env, "PATH", 4);
	if (!path_env)
		return (NULL);
	// Make a copy of PATH to work with
	len = ft_strlen(path_env);
	path_copy = malloc(len + 1);
	if (!path_copy)
		return (NULL);
	ft_strcpy(path_copy, path_env);
	// Search through each directory in PATH
	start = 0;
	i = 0;
	while (i <= len)
	{
		if (path_copy[i] == ':' || path_copy[i] == '\0')
		{
			path_copy[i] = '\0'; // Null-terminate current directory
			dir = path_copy + start;
			// Skip empty directories
			if (*dir != '\0')
			{
				full_path = join_path(dir, cmd);
				if (full_path && access(full_path, F_OK | X_OK) == 0)
				{
					free(path_copy);
					return (full_path);
				}
				if (full_path)
					free(full_path);
			}
			start = i + 1;
		}
		i++;
	}
	free(path_copy);
	return (NULL);
}*/

/** */
/* --- helpers --------------------------------------------------------- */

static char *try_cmd_in_dir(const char *dir, const char *cmd)
{
	char *full;

	full = join_path(dir, cmd);
	if (!full)
		return (NULL);
	if (access(full, F_OK | X_OK) == 0)
		return (full);              /* gardé: le caller fera le return */
	free(full);
	return (NULL);
}

/* renvoie une copie modifiable de PATH (à free) et écrit sa longueur dans *out_len */
static char *dup_path_env(t_list *env, int *out_len)
{
	char *path_env;
	char *copy;
	int   len;

	path_env = get_value_env(env, "PATH", 4);
	if (!path_env)
		return (NULL);
	len = ft_strlen(path_env);
	copy = (char *)malloc((size_t)len + 1);
	if (!copy)
		return (NULL);
	ft_strcpy(copy, path_env);
	if (out_len)
		*out_len = len;
	return (copy);
}

/* boucle principale: parcourt path_copy séparé par ':' (on mute les ':' en '\0') */
static char *search_cmd_in_path(char *path_copy, int len, const char *cmd)
{
	int   i;
	int   start;
	char *dir;
	char *found;

	start = 0;
	i = 0;
	while (i <= len)
	{
		if (path_copy[i] == ':' || path_copy[i] == '\0')
		{
			path_copy[i] = '\0';             /* termine le segment courant */
			dir = path_copy + start;
			if (*dir != '\0')                /* skip segments vides (comportement identique au tien) */
			{
				found = try_cmd_in_dir(dir, cmd);
				if (found)
					return (found);          /* à free par le caller si besoin */
			}
			start = i + 1;                   /* prochain segment */
		}
		i++;
	}
	return (NULL);
}

/* --- API ------------------------------------------------------------- */

char	*find_command_path(char *cmd, t_list *env)
{
	char *path_copy;
	char *found;
	int   len;

	/* 1) chemin explicite contenant un '/' */
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}

	/* 2) dupliquer PATH pour itérer proprement */
	path_copy = dup_path_env(env, &len);
	if (!path_copy)
		return (NULL);

	/* 3) chercher cmd dans chaque segment de PATH */
	found = search_cmd_in_path(path_copy, len, cmd);

	/* 4) cleanup et retour */
	free(path_copy);
	return (found);
}

/********find-cmd-path ******/



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

void	ft_lstadd_front(t_list **lst, void *content)
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
	node = ft_lstnew(entry);
	if (!node)
		return (free(entry->key), free(entry->value), free(entry), 1);
	ft_lstadd_front(env, node);
	return (0);
}
