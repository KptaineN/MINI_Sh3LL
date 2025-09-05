/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   looping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:24:09 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/05 17:41:55 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	parse_and_prepare(t_sh *sh, char *in)
{
	sh->parsed_args = custom_split(in);
	display_string_array(sh->parsed_args);
	sh->cmd = build_cmd(sh, sh->parsed_args);
}

static int	process_input(t_sh *sh, char *in)
{
	if (!in || *in == '\0')
		return (0);

	add_history(in);
	in = expand_single_string(in,sh->env);
	parse_and_prepare(sh, in);
	display_linked_list_of_string_array(sh->cmd);
	if (ft_strcmp((char *)sh->cmd->arr_content[0], "exit") == 0)
	{	
		free_linked_list_of_array_string(sh->cmd);
		return 1;
	}
	//sh->cmd->arr_content = pid_expansion(sh->cmd->arr_content,sh->env);
	//free_linked_list_of_array_string(sh->cmd);
	launch_process(sh);
	return (2);
}

int check_open_quotes(char *in)
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
	if (single_quote)
		return 1;
	else if (double_quote)
		return 2;
	else
		return 0;
}

char *get_full_line(void)
{
	char *in;
	char *add;
	int l_tmp;
	int l_add;
	int type;
	in = NULL;
	(void) add;
	set_signals_interactive();
	in = readline("ᕕ( ᐛ )ᕗ minish$ ");
	set_signals_noninteractive();
	if (!in)
	{	
		write(1, "exit\n", 5);
		return (NULL);
	}
	type = check_open_quotes(in);
	while(type != 0)
	{
		set_signals_interactive();
		if (type == 1)
			add = readline("squote> ");
		else
			add = readline("dquote> ");
		set_signals_noninteractive();
		if (!add)
		{
			write(1, "exit\n", 5);
			return (free(in),NULL);
		}
		char *tmp = in;
		l_tmp = ft_strlen(tmp);
		l_add = ft_strlen(add);
		in = malloc(sizeof(char)*(l_tmp + l_add + 2));
		if (!in)
			return (free(tmp), free(add), NULL);
		ft_strcpy(in,tmp);
		in[l_tmp] = '\n';
		ft_strcpy(in+l_tmp+1,add);
		in[l_tmp + l_add + 1] = '\0';
		free(tmp);
		free(add);
	}
	return (in);
}

int	looping(t_sh *sh)
{
	char	*in;
	int		retour;

	retour = 0;
	replace_or_add(&sh->env,"?","?=0");
	g_exit_status = 0;
	char *error_message = ft_calloc(20,sizeof(char));
	error_message[0] = '?';
	error_message[1] = '=';
	replace_or_add(&sh->env,"PID","PID=0");
	while (1)
	{
		in = get_full_line();
		if (!in)
			break ;	
		retour = process_input(sh, in);
		ft_itoa_inplace(&error_message[2], g_exit_status);
		replace_or_add(&sh->env,"?",error_message);
		if (retour == 1)
			break ;
	}
	free(error_message);
	return (0);
}
