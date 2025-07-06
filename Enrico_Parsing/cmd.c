/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 22:41:19 by eganassi          #+#    #+#             */
/*   Updated: 2025/06/29 09:36:25 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

bool is_command(char *str, t_list *env)
{
    char *cmd_path;
    cmd_path = find_command_path(str, env);
	if (cmd_path)
        return 0;
    free(cmd_path);
    return 1;
}
