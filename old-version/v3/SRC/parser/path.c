
#include "../../include/minishell.h"

/*char **linked_to_array_string(t_list *env)
{
    int len = 0;
    t_list *tmp = env;
    while (tmp)
    {
        len++;
        tmp = tmp->next;
    }
    char **arr = malloc(sizeof(char *) * (len + 1));
    tmp = env;
    for (int i = 0; i < len; i++)
    {
        arr[i] = tmp->content;
        tmp = tmp->next;
    }
    arr[len] = NULL;
    return arr;
}*/

/*
void set_env_value(t_list **env, const char *key, const char *value)
{
    t_list *tmp = *env;
    size_t key_len = strlen(key);
    char *new_str;

    // Cherche si ça existe
    while (tmp)
    {
        char *entry = tmp->content;
        if (strncmp(entry, key, key_len) == 0 && entry[key_len] == '=')
        {
            free(tmp->content);
            new_str = malloc(key_len + 1 + strlen(value) + 1);
            sprintf(new_str, "%s=%s", key, value);
            tmp->content = new_str;
            return;
        }
        tmp = tmp->next;
    }
    // Sinon, on ajoute
    new_str = malloc(key_len + 1 + strlen(value) + 1);
    sprintf(new_str, "%s=%s", key, value);
    t_list *new_node = malloc(sizeof(t_list));
    new_node->content = new_str;
    new_node->next = NULL;
    // Ajout fin de liste
    if (!*env)
        *env = new_node;
    else
    {
        tmp = *env;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_node;
    }
}*/
// Remplace ou ajoute une variable
int set_env_value(t_list **env, const char *key, const char *value)
{
	t_list *tmp = *env;
	size_t key_len = ft_strlen(key);
	char *new_str;

	// Cherche si la clé existe déjà
	while (tmp)
	{
		char *content = (char *)tmp->content;
		char *equal = ft_strchr(content, '=');
		if (equal && (size_t)(equal - content) == key_len && !strncmp(content, key, key_len))
		{
			free(tmp->content);
			new_str = malloc(key_len + 1 + ft_strlen(value) + 1);
			if (!new_str) exit(1);
			sprintf(new_str, "%s=%s", key, value);
			tmp->content = new_str;
			return 0;
		}
		tmp = tmp->next;
	}
	// Sinon ajoute un noeud
	new_str = malloc(key_len + 1 + ft_strlen(value) + 1);
	if (!new_str) exit(1);
	sprintf(new_str, "%s=%s", key, value);
	t_list *node = malloc(sizeof(t_list));
	if (!node) exit(1);
	node->content = new_str;
	node->next = *env;
	*env = node;
	return 0;
}

/*
char *get_env_value(t_list *env, const char *key)
{
    size_t key_len = strlen(key);
    while (env)
    {
        char *entry = env->content;
        if (strncmp(entry, key, key_len) == 0 && entry[key_len] == '=')
            return entry + key_len + 1;
        env = env->next;
    }
    return NULL;
}*/
char *get_env_value(t_list *env, const char *key)
{
    size_t key_len = ft_strlen(key);
    while (env)
    {
        char *content = env->content;
        char *equal = ft_strchr(content, '=');
        if (equal && (size_t)(equal - content) == key_len && !ft_strncmp(content, key, key_len))
            return equal + 1;
        env = env->next;
    }
    return NULL;
}



char	*get_value_env(t_list *env, char *value, int len)
{
	t_list	*temp;
	temp = env;
	while (1)
	{
		if (ft_strncmp(temp->content, value, len) == 0 && *(char* )(temp->content+len) == '=')
			return (temp->content + len +1); // Skip "value="
		temp = temp->next;
		if (temp == env)
			return (NULL);
	}
	return (NULL);
}

// Helper function to get PATH from environment
static char	*get_path_env(t_list *env)
{
	t_list	*temp;

	temp = env;
	while (1)
	{
		if (ft_strncmp(temp->content, "PATH=", 5) == 0)
			return (temp->content + 5); // Skip "PATH="
		temp = temp->next;
		if (temp == env)
			return (NULL);
	}
	return (NULL);
}

// Helper function to join path and command
static char	*join_path(char *dir, char *cmd)
{
	char	*full_path;
	int		dir_len;
	int		cmd_len;

	dir_len = ft_strlen(dir);
	cmd_len = ft_strlen(cmd);
	int i, j;
	full_path = malloc(dir_len + cmd_len + 2); // +2 for '/' and '\0'
	if (!full_path)
		return (NULL);
	// Copy directory
	i = 0;
	while (i < dir_len)
	{
		full_path[i] = dir[i];
		i++;
	}
	// Add separator
	full_path[i++] = '/';
	// Copy command
	j = 0;
	while (j < cmd_len)
	{
		full_path[i + j] = cmd[j];
		j++;
	}
	full_path[i + j] = '\0';
	return (full_path);
}

// Main function to find command path
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
	path_env = get_path_env(env);
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
}


int count_exp_len(t_subtoken *b,int *k)
{
	int var_len = 0;
	if (ft_isalpha(b->p[*k + 1]) || b->p[*k + 1] == '_') {
        var_len = 1;
        while (*k + 1 + var_len < b->len &&
               (ft_isalnum(b->p[*k + 1 + var_len]) || b->p[*k + 1 + var_len] == '_')) {
            var_len++;
        }
	}
	return var_len;
}

void expand_variable(t_subtoken *b, int *k, t_list **curr, int *count, t_list *env)
{
    int var_len;
	var_len=count_exp_len(b,k);
	if (var_len>0)
	{
		char *value = get_value_env(env , (char *)&b->p[(*k)+1], var_len);
        push_lst(curr,ft_strdup_count (value,count));
		*k += var_len;
	}
}

void expand_str(t_subtoken *b, t_list *env, int *count, t_list **curr)
{
	int k = 0;
	while(k<b->len)
	{
		if (k < b->len && b->p[k] == '$') 
		{
			if (k + 1 == b->len || b->p[k + 1] == ' ') 
				push_lst(curr, ft_strdup_count("$", count));
			else if (b->p[k + 1] == '$')
			{
				push_lst(curr, ft_strdup(get_value_env(env,"PID",3)));
				k++;
			}
			else
				expand_variable(b, &k, curr, count,env); // Handles variable case	
		}
		else
			(*count)++;
		k++;
	}
}

char *build_expansion(t_subtoken_container *a,int count, t_list **add_head)
{
	t_list *head = *add_head;
	char *new = malloc(count+1);
	if (!new)
		perror("MALLOC build_expansion");
	int i = 0;	
	int j = 0;
	int k;
	t_subtoken *b;
	t_list *tmp;

	while(j<a->n_parts) // 
	{
		b = &a->parts[j];
		if (b->type == QUOTE_SINGLE) 	//no expansion
		{
			ft_strncpy(&new[i],b->p,b->len);
			i+=b->len;
		}
		else							//expansion
		{
			k = 0;
			while(k<b->len)
			{
				if (b->p[k] == '$')
				{
					ft_strcpy(&new[i],head->content);
					i+= ft_strlen(head->content);
					tmp = head;
					head = head->next;
					free(tmp->content);
					free(tmp);
					if (k+1<b->len && b->p[k+1] == '$')
						k++;
					else
						k+=count_exp_len(b,&k);
				}
				else
					new[i++] = b->p[k];
				k++;
			}
		}	
		j++;
	}
	new[i] = 0;
	return new;
}

char *expand_container(t_subtoken_container *a, t_list **head, t_list *env)
{
	t_list *curr = *head;
	int j = 0;
	t_subtoken *b;
	int count = 0;
	//char *arr_str = malloc(sizeof(char *)*a->n_parts);
	while(j<a->n_parts) // 
	{
		b = &a->parts[j];
		if (b->type == QUOTE_SINGLE) 	//no expansion
			count+=b->len;
		else							//expansion
			expand_str(b,env,&count,&curr);
		//if (curr && (curr)->content)
		//	printf("%s\n", (char *)(curr)->content);
		j++;
	}
	return build_expansion(a,count,&((*head)->next));
}


char **expand_cmd(t_token *token, t_list *env)
{
	int i;
	t_list *head = ft_lstnew(NULL);
	char **res = malloc(sizeof(char *) * (token->cmd_args_parts->n_parts + 1)); // +1 for NULL terminator
	if (!res)
		perror("MALLOC expand_cmd");


	// input "hello"a 'mom' 
	// {"hello"a}, {mom} container
	// {hello,a}, {mom} subtoken
	// {h,e,l,l,o} char * 
	i = 0;
	while(i<token->cmd_args_parts->n_parts) // container
	while (i < token->cmd_args_parts->n_parts) // container
	{
		// Créer un container temporaire pour un seul subtoken
		t_subtoken_container temp_container;
		temp_container.parts = &token->cmd_args_parts->parts[i];
		temp_container.n_parts = 1;
		
		// Pass the address of temp_container, not a t_subtoken*
		res[i] = expand_container(&temp_container, &head, env);
		i++;
	}
	return res;
}

int (*get_builtin_handler(t_arr *bcmd, int idx))(void *, int)
{
    if (!bcmd || !bcmd->arr || idx < 0 || idx >= bcmd->len)
        return NULL;
    t_dic *dic = (t_dic *)bcmd->arr[idx];
    return (int (*)(void *, int))dic->value;
}


void execute_cmd(t_minishell *shell, t_token *cmd)
{
    if (!cmd || !cmd->value) 
    {
        fprintf(stderr, "Erreur interne: cmd null\n");
        exit(1); // Quitter le process fils proprement
    }

    // 1. Gestion des builtins
    int idx = is_in_t_arr_str(shell->parser.bcmd, cmd->value);
    if (idx != -1) 
    {
        // Appel du handler builtin : il faut une table de fonction (voir plus bas)
        int (*handler)(void *, int) = get_builtin_handler(shell->parser.bcmd, idx);
        if (handler)
        {
            shell->exit_status = handler(shell, 0); // ou passer les bons args
            exit(shell->exit_status);
        }
        else
        {
            fprintf(stderr, "Erreur interne: handler builtin null pour %s\n", cmd->value);
            exit(1);
        }
    }

    // 2. Expansion des arguments
    char **args = expand_cmd(cmd, shell->parser.env);
    if (!args || !args[0]) // args[0] est toujours la commande
    {
        fprintf(stderr, "%s: command not found\n", cmd->value);
        exit(127);
    }

    // 3. Recherche du PATH
    char *cmd_path = find_command_path(cmd->value, shell->parser.env);
    if (!cmd_path)
    {
        fprintf(stderr, "%s: command not found\n", cmd->value);
        exit(127);
    }
	if (!args[0] || !cmd_path)
	{
    	fprintf(stderr, "%s: command not found\n", cmd->value);
    	exit(127);
    }
	printf("DEBUG: shell->parser.env pointe sur %p\n", (void*)shell->parser.env);
	char **envp = linked_to_array_string(shell->parser.env);
	t_list *test = (t_list*)shell->parser.env;
	printf("Premier env : content=%s\n", (char *)test->content);
	// 4. Exécution
    execve(cmd_path, args, envp);
	free_tab(envp);
    // Si execve échoue :
    fprintf(stderr, "%s: command not found\n", cmd->value);
    exit(127);
}
