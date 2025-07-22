/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 10:43:53 by eganassi          #+#    #+#             */
/*   Updated: 2025/07/20 16:32:12 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char *ft_strdup_count(const char *s, int *count)
{
    size_t len;
    char *dup;

    if (!s || !count) // Check for NULL inputs
        return (NULL);

    len = strlen(s);

    dup = (char *)malloc(len + 1); // Allocate for string + null terminator
    if (!dup)
        return (NULL);
    strncpy(dup,s,len);
    (*count)+=len; // Increment the counter
    return (dup);
}