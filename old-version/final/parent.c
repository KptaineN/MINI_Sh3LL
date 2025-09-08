/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:48:41 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/03 11:27:48 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	one_parent(t_sh *sh, t_list *cmd, t_launch *all)
{
    (void)cmd;
    (void)sh;
	close(all->curr_pipe[0]);
	close(all->curr_pipe[1]);	
}

void	multi_parent(t_sh *sh, t_list *cmd, t_launch *all)
{
	(void)cmd;
	(void)sh;
	close(all->prev_pipe[0]);
	close(all->curr_pipe[1]);
	all->prev_pipe[0] = all->curr_pipe[0];
	all->prev_pipe[1] = all->curr_pipe[1];
}

void	end_parent(t_sh *sh, t_list *cmd, t_launch *all)
{
	(void)cmd;
	(void)sh;
	close(all->prev_pipe[0]);
	close(all->curr_pipe[0]);
	close(all->curr_pipe[1]);
}
