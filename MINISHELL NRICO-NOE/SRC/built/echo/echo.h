/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:35:07 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/13 15:36:40 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ECHO_H
# define ECHO_H

# include "../../../include/minishell.h"

int		builtin_echo(t_shell *shell, char **argv);
char	*get_dollar_value(const char *arg, int *pos, t_shell *sh);
char	*replace_variables(const char *arg, t_shell *sh);
int		is_valid_key_char(char c);

#endif