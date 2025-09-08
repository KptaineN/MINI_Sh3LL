/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 02:23:55 by nkiefer           #+#    #+#             */
/*   Updated: 2025/09/08 18:03:21 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

char	*expand_filename_if_needed(char *arg, t_shell *sh)
{
	char	*tmp;
	char	*clean;

	if (!arg)
		return (NULL);
	tmp = replace_exit_code(arg, sh->exit_status);
	if (!tmp)
		return (NULL);
	clean = remove_quotes(tmp);
	free(tmp);
	return (clean);
}

char	*resolve_path(const char *cmd, t_shell *sh)
{
	(void)sh;
	return ((char *)cmd);
}
