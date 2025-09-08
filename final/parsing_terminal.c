/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_terminal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:43:50 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/08 12:32:57 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"
// »»-----► Number of lines: 15
static char *ft_strjoin_consume(char **dst, char **add, char connector)
{
	char *tmp = *dst;
	bool bc = (connector!=0);
	int l_add = ft_strlen(*add);
	int l_tmp = ft_strlen(tmp);
	*dst = malloc(sizeof(char)*(l_tmp + l_add + 1+bc));
	if (!*dst)
		return (free(tmp), free_setnull((void **)add), NULL);
	ft_strcpy(*dst,tmp);
	if (bc)
		(*dst)[l_tmp] = connector;
	ft_strcpy((*dst)+l_tmp + bc,*add);
	(*dst)[l_tmp + l_add + bc] = '\0';
	free_setnull((void **)add);
	free(tmp);
	return *dst;
}
// »»-----► Number of lines: 22
static char check_if_open(char *in)
{
	bool single_quote = false;
	bool double_quote = false;
	int i = 0;
	while(in[i])
	{
		if (in[i] == '\'' && escape_check(in,i) && !double_quote)
			single_quote = !single_quote;
		else if (in[i] == '"' && escape_check(in,i) && !single_quote)
			double_quote = !double_quote;
		i++;
	}
	i--;
	if (single_quote)
		return '\'';
	else if (double_quote)
		return '"';
	else if (in[i] == '\\' && escape_check(in,i))
		return '\\';
	else if (in[i] == '|' && escape_check(in,i))
		return '\\';	
	else
		return 0;
}
// »»-----► Number of lines: 2
static void update_error_env(t_sh *sh, int nbr)
{
	ft_itoa_inplace(sh->msg_error,nbr);
	replace_or_add(&sh->env,"?",sh->msg_error);
}
// »»-----► Number of lines: 35
char *get_full_line(t_sh *sh)
{
	t_get_line l;
	ft_bzero(&l, sizeof(t_get_line));
	set_signals_interactive();
	l.in = readline("ᕕ( ᐛ )ᕗ minish$ ");
	set_signals_noninteractive();
	update_error_env(sh,g_exit_status);
	if (!l.in[0])
		return (free(l.in), NULL);
	l.type = check_if_open(l.in);
	while(l.type != 0)
	{
		set_signals_interactive();
		if (l.type == '\'')
			l.add = readline("squote> ");
		else if (l.type == '"')
			l.add = readline("dquote> ");
		else if (l.type == '\\')
		{	
			l.add = readline("> ");
			l.in[ft_strlen(l.in)-1] = 0;
			l.type = 0;
		}
		else if (l.type == '|')
			l.add = readline("pipe> ");	
		set_signals_noninteractive();
		if (g_exit_status == 127)
			return (free(l.add),free(l.in),NULL);
		if (!l.add)
			continue;	
		if (l.type != 0)
			l.type = '\n';
		ft_strjoin_consume(&l.in, &l.add, l.type);
		l.type = check_if_open(l.in);
	}
	return (l.in);
}

/*
// »»-----► Number of lines: 27
bool find_apply_heredoc(t_get_line *l)
{
	char *explore;
	t_list *here;
	t_list *curr;
	int idx;
	while (1)
	{
		if (!l->last_hdoc)
			l->last_hdoc = ft_strchr(l->in, '<');
		if (!l->last_hdoc)
			break;	
		while(1)
		{
			idx = l->last_hdoc-l->in;
		
			if (l->last_hdoc[1] == '<' && escape_check(l->last_hdoc,idx))
				
			else if (idx != 0 && *(l->last_hdoc-1) == '<' && escape_check(l->last_hdoc-1,idx))

			explore = ft_strchr(l->last_hdoc, '<');
			if (!explore)
				break;
			l->last_hdoc = explore;
		}
	
	}
	return l->last_hdoc;
}*/