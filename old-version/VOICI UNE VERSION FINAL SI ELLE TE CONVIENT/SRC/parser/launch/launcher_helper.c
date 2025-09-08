/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:29:47 by nkiefer           #+#    #+#             */
/*   Updated: 2025/09/08 12:29:48 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Helper 1 : prépare args/handler/tok si (1 seul cmd) et (builtin trouvé).
** Retourne 1 si prêt à exécuter le builtin, sinon 0 (avec frees comme avant).
*/
static int	prepare_args_and_handler(t_shell *sh, char ***out_args,
		int (**out_handler)(t_shell *, char **), t_token **out_tok)
{
	t_list	*curr;
	char	**args;
	int		idx;
	int		(*handler)(t_shell *, char **);

	if (sh->n_cmd != 1)
		return (0);
	curr = sh->cmd_head;
	args = expand_cmd((t_token *)curr->content, sh->env);
	if (!args || !args[0])
		return (free_tab(args), 0);
	idx = is_in_t_arr_str(sh->bcmd, args[0]);
	if (idx == -1)
		return (free_tab(args), 0);
	handler = get_builtin_handler(sh->bcmd, idx);
	if (!handler)
		return (free_tab(args), 0);
	*out_args = args;
	*out_handler = handler;
	*out_tok = (t_token *)curr->content;
	return (1);
}

/* Helper 2 : exécute le builtin avec redirections locales, restaure FDs.
** Toujours retourne 0 (comme ton code) ; met exit_status seulement si redirs OK.
*/
static int	run_builtin_with_redirs(t_shell *sh, t_token *tok,
		int (*handler)(t_shell *, char **), char **args)
{
	t_cmd	tmp;
	int		save_in;
	int		save_out;
	int		ret;

	ft_bzero(&tmp, sizeof(t_cmd));
	tmp.r = tok->r;
	tmp.r_count = tok->r_count;
	save_in = dup(STDIN_FILENO);
	save_out = dup(STDOUT_FILENO);
	ret = apply_redirs_in_child(&tmp, sh);
	if (ret == 0)
		sh->exit_status = handler(sh, args);
	dup2(save_in, STDIN_FILENO);
	dup2(save_out, STDOUT_FILENO);
	close(save_in);
	close(save_out);
	return (0);
}

int	run_single_builtin_if_alone(t_shell *shell)
{
	char	**args;
	int		(*handler)(t_shell *, char **);
	t_token	*tok;

	if (!prepare_args_and_handler(shell, &args, &handler, &tok))
		return (1);
	run_builtin_with_redirs(shell, tok, handler, args);
	free_tab(args);
	return (0);
}
