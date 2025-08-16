/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:35:53 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/16 14:39:11 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtin(const char *cmd)
{
	return (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}

int	ft_env(t_shell *shell, char **argv)
{
	return (builtin_env(shell, argv));
}

int	ft_exit(t_shell *shell, char **argv)
{
	return (builtin_exit(shell, argv));
}

int (*get_builtin_handler(t_arr *bcmd, int idx))(t_shell *, char **)
{
    if (!bcmd || idx < 0 || idx >= bcmd->len)
        return NULL;
    t_dic *dic = (t_dic *)bcmd->arr[idx];
    return dic->value;
}
