/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 22:20:55 by eganassi          #+#    #+#             */
/*   Updated: 2025/07/10 13:35:54 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/*
	Ici on attribu les sous types
	*array de pointeur de taille n_partie
*/
void attribute_subtoken_type(t_token *token)
{
	const char *subtoken;
	int idx_tail;
	t_subtoken *parts;	
	int n_parts = token->u.all_parts.n_parts;
	token->u.all_parts.parts = malloc(sizeof(t_subtoken)*n_parts);
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
}

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
	int curr;
	char *temp;
	char **arr = (char **)shell->parsed_args->arr;
	curr = i+1;


	while (curr<shell->n_tokens && is_in_t_arr_str(shell->oper, arr[curr]) == -1 && is_in_t_arr_str(shell->oper, arr[curr]) == -1)
	{
		temp = find_command_path(arr[curr], shell->env);
		if (temp)
		{
			free(temp);
			return n_args;
		}
		n_args++;
		curr++;
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
			head++;
			parts[i].type = QUOTE_SINGLE;
			idx_tail = find_c_nonescaped(&head[idx],"\'", 1);
		}
		else if (head[idx] == '\"' && escape_check(head,idx))
		{	
			head++;
			parts[i].type = QUOTE_DOUBLE;
			idx_tail = find_c_nonescaped(&head[idx],"\"", 1);
		}
		else
		{	
			parts[i].type = QUOTE_NONE;
			idx_tail = find_c_nonescaped(&head[idx],"\"\'",2);
		}
		parts[i].len = idx_tail+1;
		parts[i].p = (char *)head;
		idx+= idx_tail;
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
	char *temp;
	cmd_token->u.cmd_args_parts = malloc(sizeof(t_subtoken_conainter *)*len);
	arr_container = cmd_token->u.cmd_args_parts;
	if (!arr_container)
		return -1;
	
	idx++;
	while(idx<len)
	{
		curr_arg = arr_arg->arr[idx];
		temp = find_command_path(curr_arg, shell->env);
		if (temp && is_in_t_arr_dic_str(shell->oper,curr_arg) == -1 && is_in_t_arr_str(shell->oper, curr_arg) == -1)
			break;
		
		arr_container[idx_container].n_parts = count_subtokens(curr_arg);
		subtoken_of_cmd(&arr_container[idx_container], curr_arg);

		idx++;
	}
	free(temp);
	return idx;
}

// "<<",">>","&&","||","|","<",">"
//   0    1   2     3  	4   5   6
static void file_access_redirection(t_shell *shell,void **arr, int t_arr_index, int i)
{
	if (i+1 >= shell->n_tokens)
		perror("Argument manquant pour l'opérateur"); // ERROR
	if (t_arr_index == 5)
	{
		if (shell->fd_in != -1) //<5 
		{
			shell->fd_in = open(arr[i+1], O_RDONLY);
			if (!shell->fd_in)
			 	perror("Erreur lors de l'ouverture en lecture"); // ERROR NOT OPENING;
		}
		else
		{
			if (access(arr[i+1], O_RDONLY) < 0)
				perror("ERROR ACCESS"); // ERROR NOT OPENING;
		}
		return;
	}

	if (shell->fd_out != -1) // 1>> 6>  
	{
		if (t_arr_index == 1)
		{
			shell->fd_out = open(arr[i+1] , O_CREAT | O_RDWR | O_APPEND, 0644);
			if (!shell->fd_out)
				perror("Erreur lors de l'ouverture en écriture (append)"); // ERROR SPACE
		}
		else if (t_arr_index == 6)
		{
			shell->fd_out = open(arr[i+1] , O_CREAT | O_RDWR, 0644);
			if (!shell->fd_out)
				perror("Erreur lors de l'ouverture en écriture (troncated)"); // ERROR SPACE
		}
		return;
	}
	if (t_arr_index == 1)
	{
		if (access(arr[i+1] , O_CREAT | O_RDWR | O_APPEND | O_TRUNC) < 0)
			perror("Erreur lors de l'ouverture en écriture (append)"); // ERROR SPACE
	}
	else if (t_arr_index == 6)
	{
		if (access(arr[i+1] , O_CREAT | O_RDWR | O_TRUNC) < 0)
			perror("Erreur lors de l'ouverture en écriture (troncated)"); // ERROR SPACE
	}
}

static void add_cmd(t_shell *shell, t_token *token)
{
	t_list *tmp;
 	tmp = malloc(sizeof(t_list));
	if (!tmp)
			return; // ERROR
	
	
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
	tmp->content = (void *)token;
	tmp->next = NULL;
}


void attribute_token_type(t_shell *shell)
{
 	int t_arr_index;
    int i = 0;
	int idx_token = 0;
	void **arr = shell->parsed_args->arr;
	t_token *token;
	bool c;
	
	shell->n_tokens = count_tokens(shell);
	shell->tokens = malloc(sizeof(t_token)*shell->n_tokens);
	if (!shell->tokens)
		perror("Erreur d'allocation pour les tokens");

	while(i < shell->n_tokens)
	{
		c = 0;
		token = &shell->tokens[idx_token];
		token->type = TOKEN_WORD;
		token->value = arr[i];
		
		//OPERATOR
		t_arr_index = is_in_t_arr_dic_str(shell->oper, arr[i]);
		if (t_arr_index != -1)
		{
			c = 1;
			if (t_arr_index == 1 || t_arr_index == 5 || t_arr_index == 6)
				file_access_redirection(shell,arr,t_arr_index,i);
			else if (t_arr_index == 0) // << doctype
				return; //IMPLEMENT !!!
		
			// Use the corresponding type from the operator_types array
			//token->u.oper_handlers = shell->oper_handlers[];
			token->type = TOKEN_OPER;
			//token->u.cmd_args_parts = shell->oper;
		}
		//BCMD 
		if (c == 0)
		{
			t_arr_index = is_in_t_arr_dic_str(shell->bcmd, arr[i]);
			if (t_arr_index != -1)
			{
				c= 1;
				token->type = TOKEN_BCMD;
				i = attribute_cmd_subtokens(shell,token, i, count_args_cmd(shell,i));
			}
		}
		if (c == 0)
		{
			token->value = find_command_path(token->value, shell->env); //CMD
			if (token->value)
			{
				c = 1;
				token->type = TOKEN_CMD;
				i = attribute_cmd_subtokens(shell,token, i, count_args_cmd(shell,i));
				/*
		_		call args_cmd to get the amount 
				set the all_parts: cmd + args
				*/
			}
			else
				token->value = arr[i];
		}
		//Word token
		if (token->type == TOKEN_WORD)
		{
			token->u.all_parts.n_parts = count_subtokens(token->value);
			attribute_subtoken_type(token);
		}
		if (token->type != TOKEN_OPER)
		{	
			add_cmd(shell,token);
			shell->n_cmd++;
		}
		i++;
		idx_token++;
	}
}
