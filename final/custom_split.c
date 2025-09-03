/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 15:25:28 by nkiefer           #+#    #+#             */
/*   Updated: 2025/09/02 12:17:29 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h" 

typedef struct s_scan_ctx
{
	const char	*str;
	t_sh		*sh;
	int			i;
	int			count;
	bool		in_sq;
	bool		in_dq;
	bool		in_word;
}				t_scan_ctx;

int	skip_spaces(const char *s, int pos)
{
	while (s[pos] && s[pos] == ' ')
		pos++;
	return (pos);
}

bool	escape_check(const char *str, int idx)
{
	bool	toggle;

	toggle = true;
	while (idx > 0 && str[--idx] == '\\')
		toggle = !toggle;
	return (toggle);
}

void	toggle_quotes_ctx(t_scan_ctx *s)
{
	if (s->str[s->i] == '\'' && !s->in_dq && escape_check(s->str, s->i))
		s->in_sq = !s->in_sq;
	else if (s->str[s->i] == '"' && !s->in_sq && escape_check(s->str, s->i))
		s->in_dq = !s->in_dq;
}

void	flush_on_space_ctx(t_scan_ctx *s)
{
	if (s->str[s->i] == ' ' && !s->in_sq && !s->in_dq && s->in_word)
	{
		s->count++;
		s->in_word = false;
	}
}

void	handle_oper_or_word_ctx(t_scan_ctx *s)
{
	int		idx_oper;
	int		keylen;
	t_dic	*dic;

	idx_oper = -1;
	keylen = 0;
	idx_oper = is_in_t_arr_dic_str(s->sh->oper, (char *)&s->str[s->i]);
	if (idx_oper != -1 && escape_check(s->str,s->i)) // ADD_ENRICOP
	{
		if (s->in_word)
		{
			s->count++;
			s->in_word = false;
		}
		dic = (t_dic *)s->sh->oper->arr[idx_oper];
		keylen = ft_strlen((char *)dic->key);
		s->count++;
		s->i += keylen - 1;
	}
	else if (!s->in_word)
		s->in_word = true;
}

void	handle_count_char_ctx(t_scan_ctx *s)
{
	toggle_quotes_ctx(s);
	if (!s->in_sq && !s->in_dq)
	{
		flush_on_space_ctx(s);
		if (s->str[s->i] != ' ')
			handle_oper_or_word_ctx(s);
	}
	else if (!s->in_word)
		s->in_word = true;
}

int	count_arg(const char *str, t_sh *sh)
{
	t_scan_ctx	s;
	ft_memset(&s, 0, sizeof(t_scan_ctx));
	s.str = str;
	s.sh = sh;
	while (s.str[s.i])
	{
		char c = s.str[s.i];
		(void)c; // for debug
		 
		handle_count_char_ctx(&s);
		s.i++;
	}
	if (s.in_word)
		s.count++;
	return (s.count);
}


int	operator_len_at(const char *s, int pos, t_sh *sh)
{
	int		idx;
	t_dic	*dic;
	int		len;

	idx = is_in_t_arr_dic_str(sh->oper, (char *)&s[pos]);
	if (idx == -1 || escape_check(s,pos))
		return (0);
	dic = (t_dic *)sh->oper->arr[idx];
	len = ft_strlen((char *)dic->key);
	return (len);
}

void	update_quotes(const char *s, int i, bool *in_sq, bool *in_dq)
{
	if (s[i] == '\'' && !*in_dq && escape_check(s, i))
		*in_sq = !*in_sq;
	else if (s[i] == '"' && !*in_sq && escape_check(s, i))
		*in_dq = !*in_dq;
}

int	scan_token_end(const char *s, int pos, t_sh *sh)
{
	int		i;
	bool	in_sq;
	bool	in_dq;

	i = pos;
	in_sq = false;
	in_dq = false;
	while (s[i])
	{
		update_quotes(s, i, &in_sq, &in_dq);
		if (!in_sq && !in_dq)
		{
			if (s[i] == ' ')
				break ;
			if (operator_len_at(s, i, sh) > 0)
				break ;
		}
		i++;
	}
	return (i);
}

char	*dup_slice(const char *s, int start, int end)
{
	int		len;
	char	*out;

	len = end - start;
	out = malloc(len + 1);
	if (!out)
		return (NULL);
	ft_memcpy(out, s + start, len);
	out[len] = '\0';
	return (out);
}

char	*extract_arg(const char *str, int *start, t_sh *sh)
{
	int		token_start;
	int		token_end;
	int		oplen;
	char	*token;

	token_start = *start;
	token_end = 0;
	oplen = 0;
	token = NULL;
	token_start = skip_spaces(str, token_start);
	if (!str[token_start])
		return (NULL);
	oplen = operator_len_at(str, token_start, sh);
	if (oplen > 0)
	{
		token = dup_slice(str, token_start, token_start + oplen);
		if (!token)
			return (NULL);
		*start = token_start + oplen;
		return (token);
	}
	token_end = scan_token_end(str, token_start, sh);
	*start = token_end;
	token = dup_slice(str, token_start, token_end);
	return (token);
}


int	allocate_t_arr_for_split(char ***out, const char *str, t_sh *sh)
{
	sh->n_parsed = count_arg(str, sh);
	if (sh->n_parsed <= 0)
	{
		return (-1);
	}
	*out = malloc(sizeof(char *) * (sh->n_parsed  + 1));
	if (!*out)
		return (-1);
	return (0);
}

void	free_split_partial(t_arr *res, int upto)
{
	int		i;
	char	**arr;

	if (!res)
		return ;
	arr = (char **)res->arr;
	i = 0;
	while (arr && i < upto)
	{
		free(arr[i]);
		i++;
	}
	free(res->arr);
	free(res);
}

int	fill_tokens(const char *str, t_sh *sh, char **arr)
{
	int		pos;
	int		k;

	pos = 0;
	k = 0;
	while (k<sh->n_parsed)
	{
		arr[k] = extract_arg(str, &pos, sh);
		if (!arr[k])
		{
			free_string_array(arr);
			return (-1);
		}
		k++;
	}
	arr[k] = NULL;
	return (0);
}

char	**custom_split(const char *str, t_sh *sh)
{
	char	**result;
	
	result = NULL; 
	if (allocate_t_arr_for_split(&result, str, sh) < 0)
		return (NULL);
	if (fill_tokens(str, sh, result) < 0)
		return (NULL);
	return (result);
}


