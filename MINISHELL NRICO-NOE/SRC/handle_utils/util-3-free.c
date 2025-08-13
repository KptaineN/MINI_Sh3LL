/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util-3-free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:27:38 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/13 16:19:49 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_t_arr_dic(t_arr *array)
{
	t_dic	*dic;

	if (!array)
		return ;
	if (array->arr)
	{
		for (int i = 0; i < array->len; i++)
		{
			dic = (t_dic *)array->arr[i];
			if (dic)
			{
				if (dic->key)
					free(dic->key);
				free(dic);
			}
		}
		free(array->arr);
	}
	free(array);
}

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	for (i = 0; tab[i]; i++)
		free(tab[i]);
	free(tab);
}

void	free_t_arr(t_arr *array)
{
	if (!array)
		return ;
	if (array->arr)
	{
		for (int i = 0; i < array->len; i++)
			free(array->arr[i]);
		free(array->arr);
	}
	free(array);
}

void	free_list_str(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst->next;
		if (lst->content)
			free(lst->content);
		free(lst);
		lst = tmp;
	}
}

void	free_env(t_list *env)
{
	free_list_str(env);
}

void	free_str_array(char **arr)
{
	if (!arr)
	{
		printf("[DEBUG] free_str_array: arr == NULL\n");
		return ;
	}
	for (int i = 0; arr[i]; i++)
		free(arr[i]);
	free(arr);
}

void	free_cmd_list(t_shell *shell)
{
	t_list	*node;
	t_list	*next;

	node = shell->cmd_head;
	while (node)
	{
		next = node->next;
		free(node);
		node = next;
	}
	shell->cmd_head = NULL;
	shell->cmd_tail = NULL;
	shell->n_cmd = 0;
}

void	free_tokens(t_shell *shell)
{
	int						i;
	t_token					*tok;
	int						j;
	t_subtoken_container	*cont;
	int						k;

	if (!shell || !shell->tokens)
		return ;
	i = 0;
	while (i < shell->n_tokens)
	{
		tok = &shell->tokens[i];
		if (tok->cmd_args_parts)
		{
			j = 0;
			while (j < tok->n_args)
			{
				cont = &tok->cmd_args_parts[j];
				if (cont->parts)
				{
					k = 0;
					while (k < cont->n_parts)
					{
						// Si tu as fait ft_substr ou ft_strdup sur parts[k].p,free-le
						if (cont->parts[k].p)
						{
							 /* printf("[DEBUG] free_tokens 138: freeing part
								%d of token '%s'\n", k, tok->value);
						   printf("[DEBUG] free_tokens: freeing part
								%d of token '%s' (p: %p, val: %.10s)\n",
							     k, tok->value ? tok->value : "(null)",
								cont->parts[k].p, cont->parts[k].p);
							  free(cont->parts[k].p);
							 printf("[DEBUG] free_tokens 140: freed part
								%d of token '%s'\n", k, tok->value);*/
						}
						k++;
					}
					free(cont->parts);
				}
				j++;
			}
			free(tok->cmd_args_parts);
			if (tok->value)
			{
				free(tok->value);
				tok->value = NULL;
			}
		}
		if (tok->r)
		{
			j = 0;
			while (j < tok->r_count)
			{
				free(tok->r[j].arg);
				j++;
			}
			free(tok->r);
			tok->r = NULL;
		}
		i++;
	}
	free(shell->tokens);
	shell->tokens = NULL;
	shell->n_tokens = 0;
}

void	free_subtoken_container(t_subtoken_container *container)
{
	t_subtoken	*sub;

	if (!container)
		return ;
	if (container->parts)
	{
		for (int i = 0; i < container->n_parts; i++)
		{
			sub = &container->parts[i];
			if (sub->p)
				free(sub->p);
		}
		free(container->parts);
	}
	free(container);
}

void	free_parser(t_shell *parser)
{
	if (!parser)
		return ;
	if (parser->parsed_args)
		free_t_arr(parser->parsed_args);
	parser->parsed_args = NULL;
	if (parser->bcmd)
		free_t_arr_dic(parser->bcmd);
	parser->bcmd = NULL;
	if (parser->oper)
		free_t_arr_dic(parser->oper);
	parser->oper = NULL;
	if (parser->env)
		free_list_str(parser->env);
	parser->env = NULL;
}

void	free_minishell(t_shell *shell)
{
	if (!shell)
		return ;
	free_parser(shell);
	if (shell->args)
		free_str_array(shell->args);
	shell->args = NULL;
}

void	child_exit(char **args, char *cmd_path, char **envp, t_list *candidates,
		int code)
{
	if (envp)
		free_str_array(envp);
	if (args)
		free_str_array(args);
	if (cmd_path)
		free(cmd_path);
	if (candidates)
		free_list_str(candidates);
	_exit(code);
}

void	exit_shell(t_shell *shell, int exit_code)
{
	free_minishell(shell);
	rl_clear_history();
	exit(exit_code);
}
