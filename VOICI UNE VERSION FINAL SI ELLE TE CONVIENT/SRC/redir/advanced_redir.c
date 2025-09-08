/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkief <nkief@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 02:23:55 by nkiefer           #+#    #+#             */
/*   Updated: 2025/09/06 16:29:26 by nkief            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

char	*expand_filename_if_needed(char *arg, t_shell *sh)
{
	char	*tmp;
	char	*res;
	char	*clean;

	if (!arg)
		return (NULL);
	tmp = replace_exit_code(arg, sh->exit_status);
	res = replace_variables(tmp, sh);
	free(tmp);
	if (!res)
		return (NULL);
	clean = remove_quotes(res);
	free(res);
	return (clean);
}

char	*resolve_path(const char *cmd, t_shell *sh)
{
	(void)sh;
	return ((char *)cmd);
}
