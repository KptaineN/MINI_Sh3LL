/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 22:41:19 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/08 18:13:11 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	add_cmd(t_shell *shell, t_token *token)
{
	t_list	*tmp;

	tmp = malloc(sizeof(t_list));
	if (!tmp)
	{
		perror("Erreur malloc add_cmd");
		return (false);
	}
	tmp->content = (void *)token;
	tmp->next = NULL;
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
	return (true);
}

int	process_cmd_token(t_shell *shell, t_token *tok, t_token **prev)
{
	if (*prev)
		(*prev)->next = tok;
	tok->next = NULL;
	if (!add_cmd(shell, tok))
	{
		free_cmd_list(shell);
		return (1);
	}
	*prev = tok;
	shell->n_cmd++;
	return (0);
}
