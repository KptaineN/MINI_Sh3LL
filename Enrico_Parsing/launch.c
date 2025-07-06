/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:56:01 by eganassi          #+#    #+#             */
/*   Updated: 2025/07/06 11:45:36 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void malloc_pipes(t_shell * shell)
{
    free(shell->pipes);
    shell->head_p = malloc(sizeof(t_list)*sizeof(shell->n_pipe));
    if (!shell->pipes)
        return;
    shell->head_p->content = (void *)malloc(sizeof(int *)*shell->n_pipe);
    if (!shell->pipes->content)
        return;
}


void launch_process(t_shell *shell)
{
    int idx = 0;
    int tidx;
    t_token * token;
    int (*pipes)[2] = malloc(sizeof(*pipes)* shell->n_cmd);
    if (!pipes)
        return;
    token = shell->tokens;
    
    tidx = shell->smaller; // < 
    if (tidx != -1)
    {
        if (tidx == 0)
            (void) shell;
        else
        {
            if (tidx+1 == shell->n_tokens-1 || token[tidx+1].type == TOKEN_WORD || token[tidx+1].u.all_parts.n_parts != 1)
                return; //problem file not in the args
            shell->fd_in= open(token[tidx+1].u.all_parts.parts, O_RDONLY);
            if (shell->fd_in < 0)
                return; //problem not found
        }
    }

    tidx = shell->bigger; // > create or rewrite 
    if (tidx != -1)
    {
        if (tidx+1 == shell->n_tokens-1 || token[tidx+1].type == TOKEN_WORD || token[tidx+1].u.all_parts.n_parts != 1)
            return; //problem file not in the args
        shell->fd_in= open(token[tidx+1].u.all_parts.parts, O_CREAT | O_RDWR | O_TRUNC, 0644);
        if (shell->fd_in < 0)
            return;  // or handle the error appropriately
    }

    tidx = shell->doc; // << 
    if (shell->append != -1)
    {
        if (shell->smaller != -1 && shell->smaller > shell->append) // if << first <
        {
            if (shell->fd_in < 0)
                return; //problem not found

        }
    }
    
    tidx = shell->append;
    if (shell->doc != -1)
    {

    }

    while(idx<shell->n_cmd)
    {

    }


}




