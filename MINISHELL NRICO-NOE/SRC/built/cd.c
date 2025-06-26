/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:35:57 by eganassi          #+#    #+#             */
/*   Updated: 2025/06/26 07:33:28 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


int builtin_cd(char **args, t_minishell *shell)
{
    (void)shell;
	if (!args[1])
		return (chdir(getenv("HOME")));

	if (chdir(args[1]) != 0)
	{		if (errno == ENOENT)
			fprintf(stderr, "cd: no such file or directory: %s\n", args[1]);
		else if (errno == EACCES)
			fprintf(stderr, "cd: permission denied: %s\n", args[1]);
		else
		perror("cd");
		return (1);
	}
	// Optionnel : mettre à jour PWD dans shell->env
	return (0);
}
