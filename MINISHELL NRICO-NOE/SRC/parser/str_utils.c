/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 10:43:53 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/29 11:30:14 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup_count(const char *str, int *count)
{
	size_t	len;
	char	*dup;

	if (!str || !count)
		return (NULL);
	len = ft_strlen(str);
	dup = (char *)malloc(len + 1);
	if (!dup)
		return (NULL);
	ft_strncpy(dup, str, len);
	(*count) += len;
	return (dup);
}

void	write_number_into(char *str, long nb)
{
	int		digits;
	long	t;
	int		i;

	digits = 0;
	t = nb;
	while (t > 0)
	{
		digits++;
		t /= 10;
	}
	i = digits - 1;
	while (nb > 0)
	{
		str[i] = (char)((nb % 10) + '0');
		nb /= 10;
		i--;
	}
	str[digits] = '\0';
}

char	*ft_itoa_inplace(char *str, int n)
{
	char	*start;
	long	nb;

	start = str;
	if (!str)
		return (NULL);
	if (n == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return (start);
	}
	nb = (long)n;
	if (nb < 0)
	{
		*str = '-';
		str++;
		nb = -nb;
	}
	write_number_into(str, nb);
	return (start);
}
