/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   looping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:24:09 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/07 18:40:40 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"
// »»-----► Number of lines: 14
static int	process_input(t_sh *sh, char *in)
{
	add_history(in);
	in = expand_single_string(in,sh->env); //old line freed 
	sh->parsed_args = custom_split(sh, in); //old line freed 
	display_string_array(sh->parsed_args);
	if (sh->n_parsed == 0)
		return (free(sh->parsed_args),0);
	sh->cmd = build_cmd(sh, sh->parsed_args);
	display_linked_list_of_string_array(sh->cmd);
	if (ft_strcmp((char *)sh->cmd->arr_content[0], "exit") == 0)
	{	
		free_linked_list_of_array_string(sh->cmd);
		return -1;
	}
	return (0);
}
// »»-----► Number of lines: 22
char check_open_quotes(char *in)
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
typedef struct s_get_line
{
// »»-----► Number of lines: 4
	char *in;
	char *add;
	int l_tmp;
	int l_add;
	char type;
	char *tmp;
	char *last_hdoc;
}	t_get_line;

void update_error_env(t_sh *sh, int nbr)
{
	ft_itoa_inplace(sh->msg_error+2,nbr);
	//printf("\t%s\n",sh->msg_error);
	replace_or_add(&sh->env,"?",sh->msg_error);
}

/*
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

// »»-----► Number of lines: 43
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
	l.type = check_open_quotes(l.in);
	while(l.type != 0)
	{
		l.tmp = l.in;
		l.l_tmp = ft_strlen(l.tmp);
		set_signals_interactive();

		if (l.type == '\'')
			l.add = readline("squote> ");
		else if (l.type == '"')
			l.add = readline("dquote> ");
		else if (l.type == '\\')
		{	
			l.add = readline("> ");
			l.in[l.l_tmp-2] = 0;
		}
		else if (l.type == '|')
			l.add = readline("pipe> ");	
		set_signals_noninteractive();
		if (g_exit_status == 127)
			return (free(l.add),free(l.in),NULL);
		if (!l.add)
			continue;
		l.l_add = ft_strlen(l.add);
		l.in = malloc(sizeof(char)*(l.l_tmp + l.l_add + 2));
		if (!l.in)
			return (free(l.tmp), free(l.add), NULL);
		ft_strcpy(l.in,l.tmp);
		l.in[l.l_tmp] = '\n';
		ft_strcpy(l.in+l.l_tmp+1,l.add);
		l.in[l.l_tmp + l.l_add + 1] = '\0';
		free_setnull((void *)&l.tmp);
		free_setnull((void *)&l.add);
		l.type = check_open_quotes(l.in);
	}
	return (l.in);
}

// »»-----► Number of lines: 18
int	looping(t_sh *sh)
{
	char	*in;

	g_exit_status = 0;
	replace_or_add(&sh->env,"PID","PID=0");
	replace_or_add(&sh->env,"PID","0=bash");
	update_error_env(sh,0);
	while (1)
	{
		in = NULL;
		while(!in)
			in = get_full_line(sh);
		if (!in)
			break ;	
		g_exit_status = process_input(sh, in);
		if (g_exit_status == -1)
			break ;
		//int pipe[2] = {-1,-1};
		//sh->cmd->arr_content = (void **)rebuild_noredir_cmd(sh->oper, (char **)sh->cmd->arr_content, pipe);
		launch_process(sh);
		free_linked_list_of_array_string(sh->cmd);
	}	
	return (0);
}
