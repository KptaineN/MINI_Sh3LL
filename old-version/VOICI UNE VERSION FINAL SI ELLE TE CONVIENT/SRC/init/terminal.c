/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:28:30 by nkiefer           #+#    #+#             */
/*   Updated: 2025/09/08 14:23:39 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	term_init(t_shell *shell)
{
	if (!shell)
		return (false);
	if (tcgetattr(STDIN_FILENO, &shell->term_orig) == -1)
		return (false);
	shell->term_orig.c_lflag |= ECHOCTL;
	shell->term_shell = shell->term_orig;
	shell->term_shell.c_iflag |= ICRNL;
	shell->term_shell.c_oflag |= OPOST | ONLCR;
	shell->term_shell.c_iflag &= ~(INLCR | IGNCR);
	shell->term_shell.c_lflag |= ICANON | ECHO;
	shell->term_shell.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &shell->term_shell);
	shell->term_init = true;
	return (true);
}

void	term_restore(t_shell *shell)
{
	if (!shell || !shell->term_init)
		return ;
	shell->term_orig.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &shell->term_orig);
	shell->term_init = false;
}

void	term_apply(t_shell *shell)
{
	if (!shell || !shell->term_init)
		return ;
	tcsetattr(STDIN_FILENO, TCSANOW, &shell->term_shell);
}
