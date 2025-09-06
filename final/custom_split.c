/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 15:25:28 by nkiefer           #+#    #+#             */
/*   Updated: 2025/09/05 17:46:34 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h" 

/*
	1 not escaped
	0 escaped
*/
// »»-----► Number of lines: 8
bool escape_check(char *in, int idx)
{
	bool s = 0;
	idx--;
	while(idx && in[idx] == '\\')
	{
		s^=1;
		idx--;
	}
	return s^1;
}
/*
	str = "  hello  cut"
	str-> "hello  cut"
	return "  cut"
	to make (return - str) to have the length
*/
// »»-----► Number of lines: 37
char *set_start_return_end(char **str)
{
	int i = 0;
	bool g = 0;
	bool d_quotes = 0;
	bool s_quotes = 0;
	char *start_found = NULL;
	char *in = *str;

	while(in[i])
	{

		if (in[i] == ' ' && !d_quotes && !s_quotes)
		{	
			g = 0;
			if (start_found)
				break;
		}
		else if (in[i] == '|' && !d_quotes && !s_quotes && escape_check(in,i))
		{
			start_found = &in[i];
			if (i == 0)
				i++;
			break;
		}
		else
		{
			if (in[i] == '"' && !s_quotes && escape_check(in,i))
				d_quotes^=1;
			else if (in[i] == '\'' && !d_quotes && escape_check(in,i))
				s_quotes^=1;
			else if (!g)
				start_found = &in[i];
			g = 1;
		}
		i++;
	}
	*str = start_found;
	return &in[i];
}
// »»-----► Number of lines: 11
int 	ft_splitlen(char *str)
{
	int len = 0;
	char *end;
	while(1)
	{
		end = set_start_return_end(&str);
		if (*end)
			len++;
		else
			return len + ((*str) != 0);
		str = end;
	}
}
// »»-----► Number of lines: 10
char *extract_string(char **in)
{
	char *end;
	int s_len;
	char *result;
	end = set_start_return_end(in);
	s_len = (unsigned int)(end-(*in));
	result =malloc(s_len+1);
	ft_strncpy(result,(const char *)*in, s_len);
	result[s_len] = 0;
	(*in)+=s_len;
	return result; 
}
// »»-----► Number of lines: 18
char **custom_split(char *in)
{
	char **result = NULL;
	char *start = in;
	int len = ft_splitlen(in);
	result = malloc((len+1)*sizeof(char *));
	result[len] = 0;
	int i = 0;
	while(i<len)
	{
		result[i] = extract_string(&in);
		if(!result[i])
		{
			free_string_array(result);
			return NULL;
		}
		i++;
	}
	free(start);
	return result;
}


