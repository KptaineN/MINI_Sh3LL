/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:35:07 by nkiefer           #+#    #+#             */
/*   Updated: 2025/09/02 13:50:01 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "echo.h"

int	write_and_free(char *dst, char *s, int *i, int new_i)
{
	size_t	len;

	if (!s)
		return (0);
	len = ft_strlen(s);
	if (dst)
		ft_memcpy(dst, s, len);
	free(s);
	*i = new_i;
	return ((int)len);
}

int	is_valid_key_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	is_echo_n_flag(const char *s)
{
	int	i;

	i = 0;
	if (!s || s[0] != '-')
		return (0);
	i = 1;
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (s[1] != '\0');
}

int	builtin_echo(void *v_sh, void **v_argv)
{
    t_sh *sh;
    char **argv; 
    sh = (t_sh *)v_sh;
    argv = (char **)v_argv;
	int	i;
	int	newline;

	i = 0;
	newline = 0;
	i = 1;
	newline = 1;
	while (argv[i] && is_echo_n_flag(argv[i]))
	{
		newline = 0;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (argv[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	(void)sh;
	return (0);
}
