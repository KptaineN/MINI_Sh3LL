/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_section.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:53:10 by eganassi          #+#    #+#             */
/*   Updated: 2025/07/18 18:00:46 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void ft_free(void **thing)
{
    if (!*thing)
        return;
    free(*thing);
    *thing = NULL;
}
