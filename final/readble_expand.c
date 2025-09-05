/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readble_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:20:48 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/05 17:43:08 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"
// »»-----► Number of lines: 7
int count_escape(const char* str, int i)
{
    int count = 0;
    while(str[i] && str[i] == '\\')
    {    
        count++;
        i++;
    }    
    return count;
}
// »»-----► Number of lines: 11
int modulo(int i, int mod)
{
    if (i<0)
    {
        while(i<0)
            i+=mod;
    }
    else
    {
        while(i>=mod)
            i-=mod;
    }
    return i;
}
// »»-----► Number of lines: 10
int handle_escape_count(const char* str, int *i,int len)
{

    int s = *i;
    int count = count_escape(str,s);
    int parity;
    (*i)+= count;
    parity = modulo(count,2);
    count /= 2;
    if (str[*i] == '$' || str[*i] == '"' || str[*i] == '\'' ) 
        (*i)+=parity;
    return len+count+parity;
}
// »»-----► Number of lines: 17
char *handle_escape_write(char *dst, const char* src, int *i, int *j)
{
    int s = *i;
    int count = count_escape(src,s);
    int parity;
    (*i)+= count;
    parity = modulo(count,2);
    count /= 2;
    int z = 0;
    while(z++ < count)
        dst[(*j)++] = '\\';
    if (!(src[(*i)] && (src[(*i)] == '$' || src[*i] == '"' || src[*i] == '\'')))
    {
        dst[(*j)++] = '\\';
        return dst;
    }
    if(parity)
        dst[(*j)++] = src[(*i)++];
    return dst;
}
// »»-----► Number of lines: 14
char *get_env_value(t_list *env_list, const char *key)
{
    t_list *current = env_list;
    size_t key_len = ft_strlen(key);
    
    while (current)
    {
        char *env_entry = (char *)current->content;
        if (env_entry && ft_strncmp(env_entry, key, key_len) == 0 
            && env_entry[key_len] == '=')
        {
            return (env_entry + key_len + 1); // Return value after '='
        }
        current = current->next;
    }
    return (NULL);
}
// »»-----► Number of lines: 18
static int count_varlen_env(const char *str, int i)
{
    i += 1; // Skip the '$'
    int start = i;
    if (str[i] == '{')
    {
        i++; // Skip '{'
        start = i;
        while (str[i] && str[i] != '}')
            i++;
        if (str[i] == '}')
            return (i);
        // Malformed ${}, treat as literal
        return (start);
    }
    else
    {
        while (str[i] && str[i] != ' ' && str[i]!= '"' && str[i] != '\'' && str[i] != '\\') //&& (ft_isalnum(str[i]) || str[i] == '_'))
            i++;
        return (i);
    }
}

// Helper function to extract variable name from $VAR or ${VAR}
// »»-----► Number of lines: 33
static char *extract_var_name(const char *str, int *var_len)
{
    int i = 1; // Skip the '$'
    int start = i;
    
    if (str[i] == '{')
    {
        i++; // Skip '{'
        start = i;
        while (str[i] && str[i] != '}')
        {   
            if (str[i] == '{')
            {
                if (count_escape(str,i)%2!=1)
                    break;
            } 
            i++;
        }
        if (str[i] == '}')
        {
            *var_len = i + 1; // Include '}' in total length
            return (ft_strndup(str + start, i - start));
        }
        // Malformed ${}, treat as literal
        *var_len = 1;
        return (ft_strdup("$"));
    }
    else
    {
        while (str[i] && str[i] != ' ' && str[i]!= '"' && str[i] != '\'' && str[i] != '\\') //&& (ft_isalnum(str[i]) || str[i] == '_'))
            i++;
        *var_len = i;
        if (i == 1) // Just '$' with no valid variable name
            return (ft_strdup("$"));
        return (ft_strndup(str + start, i - start));
    }
}

// Helper to update quote state based on character
// »»-----► Number of lines: 14
static t_quote_state update_quote_state(const char *str, int i, t_quote_state current_state)
{
    char c = str[i];
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



// Calculate expanded string length considering quotes
// »»-----► Number of lines: 46
static size_t calculate_expanded_length(const char *str, t_list *env_list, t_list **exp)
{
    size_t len = 0;
    int i = 0;
    t_quote_state state = QUOTE_NONE;
    t_list *curr = ft_lstnew(NULL);
    *exp = curr;

    while (str[i])
    {
        if(str[i] == '\\')
            len = handle_escape_count(str, &i,len);
        char c = str[i];
        t_quote_state new_state = update_quote_state(str, i, state);

        // Handle quotes (they will be removed in final output)
        if ((c == '\'' || c == '"') &&
            ((state == QUOTE_NONE) || 
             (state == QUOTE_SINGLE && c == '\'') ||
             (state == QUOTE_DOUBLE && c == '"')))
        {
            state = new_state;
            i++;
            continue; // Don't count quote characters in length
        }
        
        // Handle variable expansion
        if (c == '$' && str[i + 1] && state != QUOTE_SINGLE)
        {
            int var_len;
            char *var_name = extract_var_name(str + i, &var_len);
            char *value = get_env_value(env_list, var_name);
            if (value)
                len += ft_strlen(value);    
            
            i += var_len;
            free(var_name);
            push_lst(&curr,value);
        }
        else
        {
            len++;
            i++;
        }
        state = new_state;
    }
    curr = *exp;
    *exp = (*exp)->next;
    free(curr);
    return (len);
}
// »»-----► Number of lines: 39
char *write_expansion(const char *str, int expanded_len, t_list **exp)
{
    int j = 0;
    int i = 0;
    t_quote_state state = QUOTE_NONE;
    char *result = malloc(expanded_len+1);

    while (str[i])
    {
        if (str[i] == '\\')
            result= handle_escape_write(result,str,&i,&j); // echo \B and echo "\B"
        if(!str[i])
            break;
        char c = str[i];
        t_quote_state new_state = update_quote_state(str, i, state);
        
        if ((c == '\'' || c == '"') &&
            ((state == QUOTE_NONE) || 
             (state == QUOTE_SINGLE && c == '\'') ||
             (state == QUOTE_DOUBLE && c == '"')))
        {
            state = new_state;
            i++;
            continue; // Don't count quote characters in length
        }
        if (c == '$' && str[i + 1] && state != QUOTE_SINGLE)
        {
            if ((*exp)->content)
            {   
                ft_strcpy(&result[j],(const char *)(*exp)->content);
                j += ft_strlen((const char *)(*exp)->content);
            }
            advance_node(exp);
            i = count_varlen_env(str, i);
        }
        else
            result[j++] = str[i++]; // assign
        state = new_state;
    }
    result[j] = 0;
    return (result);
}

// Expand a single string with proper quote handling
// »»-----► Number of lines: 8
char *expand_single_string(char *str, t_list *env_list)
{
    t_list *exp;
    char *result;
    if (!str)
        return (NULL);
    size_t expanded_len = calculate_expanded_length(str, env_list, &exp);
    result = write_expansion(str,expanded_len,&exp);
    free(str);
    return (result);
}
