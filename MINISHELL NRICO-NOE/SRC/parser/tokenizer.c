/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 13:54:38 by nkiefer           #+#    #+#             */
/*   Updated: 2025/06/24 15:41:29 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


int	count_tokens(const char *str)//, int *sub_n)
{
	int		count;
	int 	i;
	bool	in_single_quote;
	bool	in_double_quote;
	bool	in_word;
	//t_quote_type current_quote = QUOTE_NONE;
	
	count = 0;
	in_single_quote = false;
	in_double_quote = false;
	in_word = false;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (str[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (str[i] == ' ' && !in_single_quote && !in_double_quote)
		{
			if (in_word)
			{
				in_word = false;
				count++;
			}
		}
		else if (!in_word)
			in_word = true;
		i++;
	}
	if (in_word)
		count++;
	return (count);
}

int count_subtoken(const char *str)
{
	bool in_single_quote;
	bool in_double_quote;
	bool in_no_quote;
	int i = 0;
	int count = 0;

	in_single_quote = 0;
	in_double_quote = 0;
	in_no_quote = 0;
	while(str[i])
	{
		if (str[i] == '\"' && !in_single_quote)
		{
			in_no_quote = false;
			in_double_quote =!in_double_quote;
			if (in_double_quote)
				count++;
		}
		else if (str[i] == '\'' && !in_double_quote)
		{
			in_no_quote = false;
			in_single_quote =!in_single_quote;
			if (in_single_quote)
				count++;
		}
		else if (!in_single_quote && !in_double_quote && !in_no_quote)
		{	
			count++;
			in_no_quote = true;
		}
		i++;
	}
	return count;
}

char *find_c_needle(const char *str, char *needle, int size_needle)
{
	int c;
	
	while (*str)
	{
		c = 0;
		while(c<size_needle)
		{
			if (*str == needle[c])
				return (char *)str;
			c++;
		}
		str++;
	}
	return (char *)str;
}


// Function to extract a single token
char	*extract_token(const char *str, int *start)
{
	bool	in_single_quote;
	bool	in_double_quote;
	int		token_start;
	int		token_end;
	int		token_len;
	char	*token;

	in_single_quote = false;
	in_double_quote = false;
	token_start = *start;
	token_end = *start;
	// Skip leading spaces
	while (str[token_start] && str[token_start] == ' ')
		token_start++;
	if (!str[token_start])
		return (NULL);
	token_end = token_start;
	// Find the end of the token
	while (str[token_end])
	{
		if (str[token_end] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (str[token_end] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (str[token_end] == ' ' && !in_single_quote && !in_double_quote)
			break ;
		token_end++;
	}
	*start = token_end;
	// Allocate and copy the token
	token_len = token_end - token_start;
	token = malloc(token_len + 1);
	if (!token)
		return (NULL);
	strncpy(token, str + token_start, token_len);
	token[token_len] = '\0';
	return (token);
}

t_arr *custom_split(const char *str)
{
    int pos = 0, token_index = 0;
    t_arr *result;

    if (!str)
        return (NULL);
    result = malloc(sizeof(t_arr));
    if (!result)
        return (NULL);
    result->len = count_tokens(str);
    result->arr = malloc(sizeof(char *) * result->len);
    if (!result->arr)
        return (free(result), NULL);
    while (token_index < result->len)
    {
        result->arr[token_index] = extract_token(str, &pos);
        if (!result->arr[token_index])
        {
            while (token_index--)
                free(result->arr[token_index]);
            free(result->arr);
            free(result);
            return (NULL);
        }
        token_index++;
    }
    return (result);
}
