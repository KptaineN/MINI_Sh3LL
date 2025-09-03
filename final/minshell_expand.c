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

static char *get_env_value(t_list *env_list, const char *key)
{
    t_list *current;
    size_t key_len;
    char *env_entry;
    
    current = env_list;
    key_len = ft_strlen(key);
    while (current)
    {
        env_entry = (char *)current->content;
        if (env_entry && ft_strncmp(env_entry, key, key_len) == 0 
            && env_entry[key_len] == '=')
        {
            return (env_entry + key_len + 1); // Return value after '='
        }
        current = current->next;
    }
    return (NULL); // Variable not found
}

static int count_varlen_env(const char *str, int i)
{
    int start;

    i += 1;
    start = i;
    if (str[i] == '{')
    {
        i++;
        start = i;
        while (str[i] && str[i] != '}')
            i++;
        if (str[i] == '}')
            return (i);
        return (start);
    }
    else
    {
        while (str[i] && str[i] != ' ' && str[i]!= '"' && str[i] != '\'' && str[i] != '\\') //&& (ft_isalnum(str[i]) || str[i] == '_'))
            i++;
        return (i);
    }
}

static char *extract_braced_var(const char *str, int *var_len)
{
	int i;
	int start;

    i = 2; 
    start = i;
	while (str[i] && str[i] != '}')
		i++;
	if (str[i] == '}')
	{
		*var_len = i + 1;
		return (ft_strndup(str + start, i - start));
	}
	*var_len = 1;
	return (ft_strdup("$"));
}

static char *extract_simple_var(const char *str, int *var_len)
{
	int i;
    int start;
    
    i = 1;
    start = i;
	while (str[i] && str[i] != ' ' && str[i] != '"' && str[i] != '\'' && str[i] != '\\')
		i++;
	*var_len = i;
	if (i == 1)
		return (ft_strdup("$"));
	return (ft_strndup(str + start, i - start));
}

static char *extract_var_name(const char *str, int *var_len)
{
	if (str[1] == '{')
		return extract_braced_var(str, var_len);
	else
		return extract_simple_var(str, var_len);
}

// Helper to update quote state based on character
static t_quote_state update_quote_state(const char *str, int i, t_quote_state current_state)
{
    char c;

    c = str[i];
    if (current_state == QUOTE_NONE)
    {
        if (c == '\'')
            return (QUOTE_SINGLE);
        else if (c == '"')
            return (QUOTE_DOUBLE);
    }
    else if (current_state == QUOTE_SINGLE && c == '\'')
        return (QUOTE_NONE);
    else if (current_state == QUOTE_DOUBLE && c == '"')
        return (QUOTE_NONE);
    return (current_state);
}
/* Dépendances supposées existantes :
 * t_quote_state, QUOTE_* , t_list, ft_lstnew, push_lst,
 * handle_escape_count, update_quote_state,
 * extract_var_name, get_env_value, ft_strlen
 */


/* -- helpers ------------------------------------------------------------- */

static int init_ctx_len(t_xpctx *c, const char *str, t_list *env, t_list **exp)
{
    c->s = str;
    c->res = NULL;                /* => mode longueur */
    c->env = env;
    c->exp = exp;
    c->curr = ft_lstnew(NULL);       /* dummy */
    if (!c->curr)
        return (0);
    *c->exp = c->curr;
    c->len = 0;
    c->i = 0;
    c->j = 0;
    c->state = QUOTE_NONE;
    return (1);
}

static int init_ctx_write(t_xpctx *c, const char *str, int expanded_len, t_list **exp)
{
    c->s = str;
    c->res = (char *)malloc(expanded_len + 1); /* => mode écriture */
    if (!c->res)
        return (0);
    c->env = NULL;
    c->exp = exp;
    c->curr = NULL;
    c->len = (size_t)expanded_len;
    c->i = 0;
    c->j = 0;
    c->state = QUOTE_NONE;
    return (1);
}

static int handle_escape_len(t_xpctx *c)
{
    if (c->s[c->i] != '\\')
        return (0);
    if (c->res)
        c->res = handle_escape_write(c->res, c->s, &c->i, &c->j);
    else
        c->len = handle_escape_count(c->s, &c->i, c->len);
    return (!c->s[c->i]); /* 1 si fin de chaîne atteinte par l’escape */
}

static int  handle_quote_len(t_xpctx *c, char ch, t_quote_state new_state)
{
    if (ch != '\'' && ch != '"')
        return (0);
    if (!((c->state == QUOTE_NONE)
        || (c->state == QUOTE_SINGLE && ch == '\'')
        || (c->state == QUOTE_DOUBLE && ch == '"')))
        return (0);
    c->state = new_state;
    c->i++;
    return (1);
}

static int handle_dollar_len(t_xpctx *c)
{
    if (!(c->s[c->i] == '$' && c->s[c->i + 1] && c->state != QUOTE_SINGLE))
        return (0);

    if (c->res == NULL) /* phase longueur */
    {
        char        *name;
        char        *val;
        const char  *store;
        int         vlen;

        name = extract_var_name(c->s + c->i, &vlen);
        if (!name)
            return (1);
        val = get_env_value(c->env, name);
        if (val)
            store = (const char *)val;
        else
            store = "";
        c->len += ft_strlen(store);
        push_lst(&c->curr, (void *)store); /* jamais NULL ("" si absent) */
        c->i += vlen;
        free(name);
    }
    else /* phase écriture */
    {
        size_t l = ft_strlen((const char *)(*c->exp)->content);
        ft_strcpy(&c->res[c->j], (const char *)(*c->exp)->content);
        advance_node(c->exp);
        c->j += (int)l;
        c->i = count_varlen_env(c->s, c->i);
    }
    return (1);
}

static void len_step(t_xpctx *c)
{
    char            ch;
    t_quote_state   new_state;

    if (handle_escape_len(c))
        return ;
    ch = c->s[c->i];
    new_state = update_quote_state(c->s, c->i, c->state);
    if (handle_quote_len(c, ch, new_state))
        return ;
    if (!handle_dollar_len(c))
    {
         if (c->res)
        {
            c->res[c->j] = c->s[c->i];
            c->j++;
        }
        else
            c->len++;
        c->i++;
    }
    c->state = new_state;
}

/* -- API ----------------------------------------------------------------- */

/* Calcule la longueur développée et prépare *exp :
 * *exp pointera sur le premier vrai nœud (après le dummy), le dummy est libéré.
 */
static size_t calculate_expanded_length(const char *str, t_list *env_list, t_list **exp)
{
    t_xpctx    c;
    t_list      *dummy;

    if (!init_ctx_len(&c, str, env_list, exp))
        return (0);
    while (c.s[c.i])
        len_step(&c);
    /* Finaliser la liste : *exp = dummy->next ; free(dummy) */
    dummy = *exp;
    *exp = (*exp)->next;
    free(dummy);
    return (c.len);
}

static char *write_expansion(const char *str, int expanded_len, t_list **exp)
{
    t_xpctx c;

    if (!init_ctx_write(&c, str, expanded_len, exp))
        return (NULL);
    while (c.s[c.i])
        len_step(&c);
    c.res[c.j] = '\0';
    return (c.res);
}

// Expand a single string with proper quote handling
static char *expand_single_string(const char *str, t_list *env_list)
{
    t_list *exp;
    size_t   expanded_len;

    if (!str)
        return (NULL);
    expanded_len = calculate_expanded_length(str, env_list, &exp);
    return (write_expansion(str, (int)expanded_len, &exp));
}


static int count_strings(char **array)
{
    int count;
	
	count = 0;
    if (!array)
        return (0);
    while (array[count])
        count++;
    return (count);
}

static int expand_array_elements(char **input_array, char **expanded_array, t_list *env_list)
{
	int i;
	int j;

    i = 0;
	while (input_array[i])
	{
		expanded_array[i] = expand_single_string(input_array[i], env_list);
		if (!expanded_array[i])
		{
			j = 0;
			while (j < i)
				free(expanded_array[j++]);
			free(expanded_array);
			return 0;
		}
		i++;
	}
	return 1;
}

char **expand_variables(char **input_array, t_list *env_list)
{
	int array_size;
	char **expanded_array;

	if (!input_array)
		return (NULL);
	array_size = count_strings(input_array);
	expanded_array = ft_calloc(array_size + 1, sizeof(char *));
	if (!expanded_array)
		return (NULL);

	if (!expand_array_elements(input_array, expanded_array, env_list))
		return (NULL);

	return (expanded_array);
}
