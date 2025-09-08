/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:35:07 by nkiefer           #+#    #+#             */
/*   Updated: 2025/09/02 13:50:25 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ECHO_H
# define ECHO_H

# include "minish.h"

typedef struct s_rv
{
	const char	*a;
	size_t		i;
	size_t		j;
	bool		sq;
	bool		dq;
	t_sh		*sh;
	char		*out;
}	t_rv;

int		builtin_echo(void *v_sh, void **v_argv);
char	*get_dollar_value(const char *arg, int *pos, t_sh *sh);
char	*replace_variables(const char *arg, t_sh *sh);
int		is_valid_key_char(char c);
int		process_dollar(char *dst, const char *arg, int *i, t_sh *sh);
int		dollar_edge_cases(char *dst, const char *arg, int *i, t_sh *sh);
char	*remove_quotes(const char *arg);
int		is_echo_n_flag(const char *s);
char	*find_env_value(t_list *env, const char *key);
int		write_and_free(char *dst, char *s, int *i, int new_i);
void	toggle_quotes(char c, bool *in_sq, bool *in_dq);

#endif // ECHO_H
