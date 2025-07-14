/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:19:35 by nkiefer           #+#    #+#             */
/*   Updated: 2024/12/01 07:48:37 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

char	*get_next_line(int fd);
char	*ftt_strchr(const char *str, int c);
char	*ftt_strdup(const char *s);
char	*ftt_strjoin(char *s1, char *s2);
char	*ftt_substr(char const *s, unsigned int start, size_t len);
int		ftt_strlen(const char *str);

#endif
