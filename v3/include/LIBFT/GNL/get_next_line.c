/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:16:19 by nkiefer           #+#    #+#             */
/*   Updated: 2024/12/01 07:47:50 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "get_next_line.h"

static char	*read_fd(const int fd, char *line)
{
	int		bread;
	char	*buffer;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (free(buffer), NULL);
	bread = 1;
	while (bread > 0)
	{
		bread = read(fd, buffer, BUFFER_SIZE);
		if (bread < 0)
			return (free(buffer), NULL);
		if (bread == 0)
			break ;
		buffer[bread] = '\0';
		if (!line)
			line = ftt_strdup("");
		line = ftt_strjoin(line, buffer);
		if (ftt_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (line);
}

static char	*get_line(char *nline)
{
	char	*new_line;
	size_t	i;

	i = 0;
	while (nline[i] != '\0' && nline[i] != '\n')
		i++;
	if (nline[i] == '\0' || nline[i + 1] == '\0')
		return (NULL);
	new_line = ftt_substr(nline, i + 1, ftt_strlen(nline) - (i + 1));
	if (!new_line)
		return (NULL);
	nline[i + 1] = '\0';
	return (new_line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*nline;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	nline = read_fd(fd, stash);
	if (!nline)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = get_line(nline);
	if (stash && *stash == '\0')
	{
		free(stash);
		stash = NULL;
	}
	return (nline);
}
