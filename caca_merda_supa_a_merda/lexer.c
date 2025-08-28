/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 22:20:55 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/26 15:00:07 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/*
	Ici on attribu les sous types
	*array de pointeur de taille n_partie
*/
/*
void attribute_subtoken_type(t_token *token)
{
	const char *subtoken;
	int idx_tail;
	t_subtoken *parts;	
	int n_parts = token->n_parts;
	token.parts = malloc(sizeof(t_subtoken)*n_parts);
	if (!token->u.all_parts.parts)
		return;
	subtoken = token->value;
	parts = token->u.all_parts.parts;
	int i = 0;
	int idx = 0;
	while(subtoken[idx])
	{
		if (subtoken[idx] == '\'' && escape_check(subtoken,idx))
		{	
			idx++;
			parts[i].type = QUOTE_SINGLE;
			idx_tail = find_c_nonescaped(&subtoken[idx],"\'", 1); //make a while for finding the one who dosent escape !!! WorkToDo
		}
		else if (subtoken[idx] == '\"' && escape_check(subtoken,idx))
		{	
			idx++;
			parts[i].type = QUOTE_DOUBLE;
			idx_tail = find_c_nonescaped(&subtoken[idx],"\"", 1);
		}
		else
		{	
			parts[i].type = QUOTE_NONE;
			idx_tail = find_c_nonescaped(&subtoken[idx],"\"\'",2);
		}
		parts[i].len = idx_tail+1;
		parts[i].p = (char *)&subtoken[idx];
		idx +=idx_tail;
		//if (parts[i].type != QUOTE_NONE)
		//	subtoken+=2;
		i++;
	}
}*/

/*
main loop

check if its an operator && checks if its a bcmd checks if its a command
if not continue *

else break (free the command)
continue *, increment n_args 	
loop
*/
static int count_args_cmd(t_shell *shell, int i)
{
	int n_args = 0;
	char **arr = (char **)shell->parsed_args->arr;
	int len = shell->parsed_args->len;
	
	int idx_oper;
	//print_dic(shell->oper);
	while (1)
	{
		if (i==len)
			break;
		if (arr[i] != NULL)
		{
			printf("arg%d %s\n", i, arr[i]);
			idx_oper = is_in_t_arr_dic_str(shell->oper, arr[i]);
			if (idx_oper != -1)
				return n_args;
			n_args++;
		}
		i++;
	}
	return n_args;
}

void subtoken_of_cmd(t_subtoken_conainter *container, char *arg)
{
	t_subtoken *parts;
	char *head = arg;
	int idx_tail;
	int n_parts = container->n_parts;
	container->parts = malloc(sizeof(t_subtoken)*n_parts);
	parts = container->parts;
	if (!parts)
		return;

	int i = 0;
	int idx = 0;
	while(head[idx])
	{
		if (head[idx] == '\'' && escape_check(head,idx))
		{	
			idx++;
			parts[i].type = QUOTE_SINGLE;
			idx_tail = find_c_nonescaped(&head[idx],"\'", 1);
		}
		else if (head[idx] == '\"' && escape_check(head,idx))
		{	
			idx++;
			parts[i].type = QUOTE_DOUBLE;
			idx_tail = find_c_nonescaped(&head[idx],"\"", 1);
		}
		else
		{	
			parts[i].type = QUOTE_NONE;
			idx_tail = find_c_nonescaped(&head[idx],"\"\'",2);
		}
		parts[i].len = idx_tail;
		parts[i].p = (char *)&head[idx];
		//printf("%.*s\n", idx_tail, &head[idx]);
		idx+= idx_tail+(parts[i].type != QUOTE_NONE);
		//if (parts[i].type != QUOTE_NONE)
		//	head+=2;
		i++;
	}
}



int attribute_cmd_subtokens(t_shell *shell, t_token *cmd_token, int idx, int len)
{
	t_subtoken_conainter *arr_container;
	t_arr *arr_arg = shell->parsed_args;
	char *curr_arg;
	int idx_container = 0;
	cmd_token->cmd_args_parts = malloc(sizeof(t_subtoken_conainter *)*len);
	arr_container = cmd_token->cmd_args_parts;
	if (!arr_container)
		return -1;

	while(idx_container<len)
	{
		curr_arg = arr_arg->arr[idx];
		if (curr_arg != NULL)
		{
			arr_container[idx_container].n_parts = count_subtokens(curr_arg);
			subtoken_of_cmd(&arr_container[idx_container++], curr_arg);
		}
		idx++;
	}
	cmd_token->n_parts = len;
	return idx-1;
}


static void add_cmd(t_shell *shell, int last, int curr, int n_redir)
{
	t_list *tmp;
	t_cmd_red *container;
	
	container = malloc(sizeof(t_cmd_red));
	container->redir = (t_arr *)malloc(sizeof(t_arr));
	container->cmd = (t_arr *)malloc(sizeof(t_arr));
	container->redir->len = n_redir;
	container->cmd->len = curr-last-n_redir;
	 
	if (container->cmd->len <= 0)
	{	
		free(container->cmd);
		free(container->redir);
		free(container);
		perror("add_cmd");
	}
 	tmp = malloc(sizeof(t_list));
	if (!tmp)
		perror("malloc add cmd"); // ERROR
	
	if (!shell->cmd_head)
	{	
		shell->cmd_head = tmp;
		shell->cmd_tail = tmp;
	}
	else
	{
		shell->cmd_tail->next = tmp;
		shell->cmd_tail = tmp;
	}
	t_token *token;
	container->redir->arr = malloc(sizeof(t_token)*n_redir);
	container->cmd->arr = malloc(sizeof(t_token)*container->cmd->len);
	int i_cmd = 0;
	int i_redir = 0;
	while(last<curr)
	{
		token = &shell->tokens[last];
		if (token->type == TOKEN_CMD || token->type == TOKEN_BCMD)
			container->cmd->arr[i_cmd++] = token;
		else
			container->redir->arr[i_redir++] = token;
		last++;
	}

	tmp->content = (void *)container;
	tmp->next = NULL;
}

void oper_assign(t_shell *shell, t_token *token, int *idx)
{
	if (!((*idx)+1< shell->parsed_args->len))
		perror("inside oper assign");
	t_subtoken_conainter *arr_container;
	t_arr *arr_arg = shell->parsed_args;
	token->cmd_args_parts = malloc(sizeof(t_subtoken_conainter *)*2);
	arr_container = token->cmd_args_parts;
	if (!arr_container)
		perror("oper_assign malloc");
	token->type = TOKEN_OPER;
	token->n_parts = 2;
	arr_container[0].n_parts = 1;
	subtoken_of_cmd(&arr_container[0], arr_arg->arr[*idx]);
	arr_container[1].n_parts = count_subtokens(arr_arg->arr[(*idx)+1]);
	subtoken_of_cmd(&arr_container[1], arr_arg->arr[(*idx)+1]);
	
	(*idx)++;
}

void attribute_token_type(t_shell *shell)
{
 	int t_arr_index;
    int i = 0;
	int idx_token = 0;
	void **arr = shell->parsed_args->arr;
	t_token *token;
	int last_cmd = 0;
	int redir = 0;

	/*
	COSE DA FARE: 
	add var per last add_cmd che deve diventare add_cmd_red
	fare un error case se due "|" "|" di seguito
	*/

		shell->n_tokens = count_tokens(shell);
	if (shell->n_tokens != 0)
	{
		shell->tokens = malloc(sizeof(t_token)*shell->n_tokens);
		if (!shell->tokens)
			perror("Erreur d'allocation pour les tokens");
	}
	while(idx_token < shell->n_tokens)
	{
		if (arr[i] != NULL)
		{
			token = &shell->tokens[idx_token];
			token->type = TOKEN_WORD;
			token->value = arr[i];
			
			t_arr_index = is_in_t_arr_dic_str(shell->oper, arr[i]);
			if (t_arr_index != -1)
			{	
				
				if (t_arr_index == 4)
				{
					if (last_cmd == i)
						perror("problem on last command attribute token type");
					
					add_cmd(shell, last_cmd, idx_token, redir);
					redir = 0;
					last_cmd = idx_token;	
					shell->n_cmd++;
					idx_token--;
				}
				else
				{	
					oper_assign(shell,token, &i);
					redir++;
				}	
			} 
			else if (token->type == TOKEN_WORD) //BCMD
			{
				t_arr_index = is_in_t_arr_dic_str(shell->bcmd, arr[i]);
				if (t_arr_index != -1)
					token->type = TOKEN_BCMD;
				else
					token->type = TOKEN_CMD;
				i = attribute_cmd_subtokens(shell,token, i, count_args_cmd(shell,i));
			}
			i++;
		}
		idx_token++;
	}
	if (last_cmd != i)
	{
		add_cmd(shell,last_cmd,idx_token,redir);
		shell->n_cmd++;
	}
	shell->cmd_tail = shell->cmd_head;
}
