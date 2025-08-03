/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:07:03 by nkiefer           #+#    #+#             */
/*   Updated: 2025/07/28 14:07:43 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h> // pour size_t

char    *ft_strncpy(char *dest, const char *src, size_t n)
{
    size_t i;

    i = 0;
    while (i < n && src[i] != '\0')
    {
        dest[i] = src[i];  // On copie chaque caractère de src vers dest
        i++;
    }
    // Si src est plus court que n, on remplit le reste de dest avec des '\0'
    while (i < n)
    {
        dest[i] = '\0';
        i++;
    }
    return (dest); // On retourne le pointeur vers la destination
}

