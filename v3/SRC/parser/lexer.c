/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 22:20:55 by eganassi          #+#    #+#             */
/*   Updated: 2025/07/28 15:05:35 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	Ici on attribue les sous‐types
	*array de pointeur de taille n_parts

void attribute_subtoken_type(t_token *token)
{
	const char *subtoken;
	int idx_tail;
	t_subtoken *parts;
	int n_parts = token->u.all_parts.n_parts;

	token->u.all_parts.parts = malloc(sizeof(t_subtoken) * n_parts);
	if (!token->u.all_parts.parts)
		return;

	subtoken = token->value;
	parts    = token->all_parts.parts;
	int i = 0;
	int idx = 0;
	while (subtoken[idx])
	{
		if (subtoken[idx] == '\'' && escape_check(subtoken, idx))
		{
			idx++;
			parts[i].type = QUOTE_SINGLE;
			idx_tail     = find_c_nonescaped(&subtoken[idx], "\'", 1);
		}
		else if (subtoken[idx] == '\"' && escape_check(subtoken, idx))
		{
			idx++;
			parts[i].type = QUOTE_DOUBLE;
			idx_tail     = find_c_nonescaped(&subtoken[idx], "\"", 1);
		}
		else
		{
			parts[i].type = QUOTE_NONE;
			idx_tail     = find_c_nonescaped(&subtoken[idx], "\"\'", 2);
		}
		parts[i].len = idx_tail + 1;
		parts[i].p   = (char *)&subtoken[idx];
		idx += idx_tail;
		i++;
	}
}*/
/*
static int count_args_cmd(t_shell *shell, int i)
{
	int n_args = 0;
	int curr;
	char *temp;
	char **arr = (char **)shell->parsed_args->arr;

	curr = i + 1;
	while (curr < shell->n_tokens
	   && is_in_t_arr_str(shell->oper, arr[curr]) == -1
	   && is_in_t_arr_str(shell->oper, arr[curr]) == -1)
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
}*/

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
			idx_oper = is_in_t_arr_str(shell->oper, arr[i]);
			if (idx_oper != -1)
				return n_args;
			n_args++;
		}
		i++;
	}
	return n_args;
}

void subtoken_of_cmd(t_subtoken_container *container, char *arg)
{
	t_subtoken *parts = NULL;
	char *head = arg;
	int idx_tail;
	int n_parts = container->n_parts;

	container->parts = malloc(sizeof(t_subtoken) * n_parts);
	if (!container->parts)
		return;

	//parts = container->parts;
	int i   = 0;
	int idx = 0;
	while (head[idx])
	{
		if (head[idx] == '\'' && escape_check(head, idx))
		{
			head++;
			parts[i].type = QUOTE_SINGLE;
			idx_tail     = find_c_nonescaped(&head[idx], "\'", 1);
		}
		else if (head[idx] == '\"' && escape_check(head, idx))
		{
			head++;
			parts[i].type = QUOTE_DOUBLE;
			idx_tail     = find_c_nonescaped(&head[idx], "\"", 1);
		}
		else
		{
			parts[i].type = QUOTE_NONE;
			idx_tail     = find_c_nonescaped(&head[idx], "\"\'", 2);
		}
		parts[i].len = idx_tail;
		parts[i].p = (char *)&head[idx];
		//printf("%.*s\n", idx_tail, &head[idx]);
		idx+= idx_tail+(parts[i].type != QUOTE_NONE);
		//parts[i].len = idx_tail + 1;
		//parts[i].p   = head;
		//idx += idx_tail;
		i++;
	}
}
/*
int attribute_cmd_subtokens(t_shell *shell, t_token *cmd_token, int idx, int len)
{
	t_arr *arr_arg = shell->parsed_args;
	t_subtoken_container *containers;
	char *curr_arg;
	char *temp;
	int idx_container = 0;

	// allouer len+1 pour le marqueur de fin 
	containers = malloc(sizeof(*containers) * (len + 1));
	if (!containers)
		return -1;
	cmd_token->u.cmd_args_parts = containers;

	idx++;
	while (idx < len)
	{
		curr_arg = arr_arg->arr[idx];
		temp     = find_command_path(curr_arg, shell->env);

		if (temp
		 && is_in_t_arr_dic_str(shell->oper, curr_arg) == -1
		 && is_in_t_arr_str(shell->oper, curr_arg)     == -1)
		{
			free(temp);
			break;
		}

		containers[idx_container].n_parts = count_subtokens(curr_arg);
		subtoken_of_cmd(&containers[idx_container], curr_arg);

		idx_container++;
		idx++;
		free(temp);
	}

	// marqueur de fin 
	containers[idx_container].n_parts = 0;
	containers[idx_container].parts   = NULL;

	return idx;
}*/

void file_access_redirection(t_shell *shell, void **arr, int t_arr_index, int i)
{
	if (i + 1 >= shell->n_tokens)
		perror("Argument manquant pour l'opérateur");

	if (t_arr_index == 5)
	{
		if (shell->fd_in != -1)
		{
			shell->fd_in = open(arr[i + 1], O_RDONLY);
			if (shell->fd_in < 0)
				perror("Erreur lors de l'ouverture en lecture");
		}
		else if (access(arr[i + 1], O_RDONLY) < 0)
		{
			perror("ERROR ACCESS");
		}
		return;
	}

	// sortie 
	if (shell->fd_out != -1)
	{
		if (t_arr_index == 1)
		{
			shell->fd_out = open(arr[i + 1], O_CREAT | O_RDWR | O_APPEND, 0644);
			if (shell->fd_out < 0)
				perror("Erreur lors de l'ouverture en écriture (append)");
		}
		else if (t_arr_index == 6)
		{
			shell->fd_out = open(arr[i + 1], O_CREAT | O_RDWR, 0644);
			if (shell->fd_out < 0)
				perror("Erreur lors de l'ouverture en écriture (trunc)");
		}
		return;
	}

	if (t_arr_index == 1)
	{
		if (access(arr[i + 1], O_CREAT | O_RDWR | O_APPEND | O_TRUNC) < 0)
			perror("Erreur lors de l'ouverture en écriture (append)");
	}
	else if (t_arr_index == 6)
	{
		if (access(arr[i + 1], O_CREAT | O_RDWR | O_TRUNC) < 0)
			perror("Erreur lors de l'ouverture en écriture (trunc)");
	}
}

int attribute_cmd_subtokens(t_shell *shell, t_token *cmd_token, int idx, int len)
{
	t_subtoken_container *arr_containers;
	t_arr *arr_arg = shell->parsed_args;
	char *curr_arg;
	int idx_container = 0;

	// allocate len+1 for the end marker
	cmd_token->cmd_args_parts = malloc(sizeof(t_subtoken_container) * (len + 1));
	arr_containers = cmd_token->cmd_args_parts;
	if (!arr_containers)
		return -1;
	//cmd_token->cmd_args_parts = arr_containers;

	// fill containers[0..len-1]
	while (idx_container < len)
	{
		curr_arg = arr_arg->arr[idx];
		if (curr_arg)
		{
			arr_containers[idx_container].n_parts = count_subtokens(curr_arg);
			subtoken_of_cmd(&arr_containers[idx_container++], curr_arg);
		}
		idx++;
	}

	cmd_token->cmd_args_parts->n_parts = len;
	// end marker
	//containers[idx_container].n_parts = 0;
	//containers[idx_container].parts   = NULL;

	return idx - 1;
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
	tmp->next    = NULL;
}


void attribute_token_type(t_shell *shell)
{
	int t_arr_index;
	int i = 0;
	int idx_token = 0;
	void **arr = shell->parsed_args->arr;
	t_token *token;

	shell->n_tokens = count_tokens(shell, shell->parsed_args, shell->oper);
	if (shell->n_tokens != 0)
	{
		shell->tokens = malloc(sizeof(t_token) * shell->n_tokens);
		if (!shell->tokens)
			perror("Erreur d'allocation pour les tokens");
	}
	while (idx_token < shell->n_tokens)
	{
		if (arr[i] != NULL)
		{
			token = &shell->tokens[idx_token];
			token->type = TOKEN_WORD;
			token->value = arr[i];

			// operator
			t_arr_index = is_in_t_arr_dic_str(shell->oper, arr[i]);
			if (t_arr_index != -1)
				token->type = TOKEN_OPER;

			// builtin or cmd
			if (token->type == TOKEN_WORD)
			{
				t_arr_index = is_in_t_arr_dic_str(shell->bcmd, arr[i]);
				if (t_arr_index != -1)
					token->type = TOKEN_BCMD;
				else
					token->type = TOKEN_CMD;
				i = attribute_cmd_subtokens(shell, token, i, count_args_cmd(shell, i));
			}

			if (token->type != TOKEN_OPER)
			{
				add_cmd(shell, token);
				shell->n_cmd++;
			}
			i++;
			idx_token++;
		}
	}
}

/*void attribute_token_type(t_shell *shell)
{
	int    t_arr_index;
	int    i         = 0;
	int    idx_token = 0;
	void **arr       = shell->parsed_args->arr;
	t_token *token;
	//bool   c;

	shell->n_tokens = count_tokens(shell->parser);
	//shell->tokens   = malloc(sizeof(t_token) * shell->n_tokens);
	if (shell->n_tokens != 0)
	{
		shell->tokens = malloc(sizeof(t_token)*shell->n_tokens);
		if (!shell->tokens)
			perror("Erreur d'allocation pour les tokens");
	}
	while (idx_token < shell->n_tokens) //i < shell->n_tokens
	{
		//c     = false;
		token = &shell->tokens[idx_token];
		//token->idx   = idx_token;
		token->type  = TOKEN_WORD;
		token->value = arr[i];

		// OPERATOR ? 
		t_arr_index = is_in_t_arr_dic_str(shell->oper, arr[i]);
		if (t_arr_index != -1)
		{
			//c         = true;
			token->type = TOKEN_OPER;
			if (t_arr_index == 1 || t_arr_index == 5 || t_arr_index == 6)
				file_access_redirection(shell, arr, t_arr_index, i);
			// else << 
		}

		// BUILTIN ? 
		if (!c)
		{
			t_arr_index = is_in_t_arr_dic_str(shell->bcmd, arr[i]);
			if (t_arr_index != -1)
			{
				c          = true;
				token->type = TOKEN_BCMD;
				i          = attribute_cmd_subtokens(shell, token, i, count_args_cmd(shell, i));
			}
		}

		// CMD ? 
		if (!c)
		{
			token->value = find_command_path(token->value, shell->env);
			if (token->value)
			{
				c          = true;
				token->type = TOKEN_CMD;
				i          = attribute_cmd_subtokens(shell, token, i, count_args_cmd(shell, i));
			}
			else
				token->value = arr[i];
		}

		// WORD
		if (token->type == TOKEN_WORD)
		{
			token->u.all_parts.n_parts = count_subtokens(token->value);
			attribute_subtoken_type(token);
		}

		if (token->type != TOKEN_OPER)
		{
			add_cmd(shell, token);
			shell->n_cmd++;
		}

		i++;
		idx_token++;
	}
}*/
