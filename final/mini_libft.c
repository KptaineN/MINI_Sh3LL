/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_libft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 12:46:39 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/02 11:46:21 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"
#include <unistd.h>
// »»-----► Number of lines: 6
size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}
// »»-----► Number of lines: 10
void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}
// »»-----► Number of lines: 13
void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	total_size;

	if (count == 0 || size == 0)
		return (malloc(0));
	if (count > SIZE_MAX / size)
		return (NULL);
	total_size = count * size;
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, total_size);
	return (ptr);
}
// »»-----► Number of lines: 18
char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	len;
	size_t	i;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
// »»-----► Number of lines: 20
char	*ft_strndup(const char *s1, size_t n)
{
	char	*dup;
	size_t	len;
	size_t	i;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	if (len > n)
		len = n;
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len && s1[i])
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
// »»-----► Number of lines: 6
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
// »»-----► Number of lines: 10
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
// »»-----► Number of lines: 10
char	*ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
// »»-----► Number of lines: 1
int	ft_isalnum(int c)
{
	return (('A'<= c && c<='Z') || ('a'<= c && c<='z' )|| ('0'<=c && c<= '9'));
}
// »»-----► Number of lines: 15
char *ft_strncpy(char *dest, const char *src, size_t n)
{
    size_t i;

    i = 0;
    while (i < n && src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    while (i < n)
    {
        dest[i] = '\0';
        i++;
    }
    
    return dest;
}
// »»-----► Number of lines: 10
char *ft_strchr(const char *s, int c)
{
    while (*s != '\0')
    {
        if (*s == (char)c)
            return (char *)s;
        s++;
    }
    if ((char)c == '\0')
        return (char *)s;
    
    return NULL;
}
// »»-----► Number of lines: 15
void	*ft_memcpy(void *dst, const char *src, size_t n)
{
	unsigned char	*tmp_dst;
	unsigned char	*tmp_src;

	if (dst == ((void *)0) && src == (void *)0)
		return (dst);
	tmp_dst = (unsigned char *) dst;
	tmp_src = (unsigned char *) src;
	while (n > 0)
	{
		*tmp_dst = *tmp_src;
		tmp_dst++;
		tmp_src++;
		n--;
	}
	return (dst);
}
// »»-----► Number of lines: 9
void	*ft_memset(void *s, int c, size_t len)
{
	unsigned char	*tmp_ps;

	tmp_ps = ((unsigned char *)s);
	while (len > 0)
	{
		*(tmp_ps++) = ((unsigned char ) c);
		len--;
	}
	return (s);
}
// »»-----► Number of lines: 4
void ft_putstr_fd(char *s, int fd)
{
    if (!s)
        return;
    while (*s)
        write(fd, s++, 1);
}
// »»-----► Number of lines: 1
void	ft_putchar_fd(char c, int fd)
{
    write(fd, &c, 1);
}
// »»-----► Number of lines: 11
static int	ft_numlen(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}
// »»-----► Number of lines: 23
char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	num;

	num = n;
	len = ft_numlen(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (num < 0)
	{
		str[0] = '-';
		num = -num;
	}
	if (num == 0)
		str[0] = '0';
	while (num > 0)
	{
		str[--len] = (num % 10) + '0';
		num /= 10;
	}
	return (str);
}
// »»-----► Number of lines: 18
char *ft_substr(const char *s, unsigned int start, size_t len)
{
    size_t  s_len;
    size_t  i;
    char    *substr;

    if (!s)
        return NULL;
    s_len = ft_strlen(s);
    if (start >= s_len)
        return ft_strdup(""); // Return empty string if start is out of bounds
    if (len > s_len - start)
        len = s_len - start;
    substr = malloc(len + 1);
    if (!substr)
        return NULL;
    for (i = 0; i < len; i++)
        substr[i] = s[start + i];
    substr[len] = '\0';
    return substr;
}
// »»-----► Number of lines: 1
int	ft_isdigit(int c)
{
    return (c >= '0' && c <= '9');
}
// »»-----► Number of lines: 19
int	ft_atoi(const char *str)
{
    int		sign;
    long	result;

    sign = 1;
    result = 0;
    while (*str == ' ' || (*str >= 9 && *str <= 13))
        str++;
    if (*str == '-' || *str == '+')
    {
        if (*str == '-')
            sign = -1;
        str++;
    }
    while (*str && (*str >= '0' && *str <= '9'))
    {
        result = result * 10 + (*str - '0');
        str++;
    }
    return ((int)(result * sign));
}
// »»-----► Number of lines: 1
int	ft_isalpha(int c)
{
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}
// »»-----► Number of lines: 5
void	ft_putendl_fd(const char *s, int fd)
{
    if (!s)
        return;
    while (*s)
        write(fd, s++, 1);
    write(fd, "\n", 1);
}

/***************** ft_itoa_inplace*******************/
// »»-----► Number of lines: 7
int count_digits(long n)
{
    int d = 0;
    while (n > 0)
    {
        n /= 10;
        d++;
    }
    return (d);
}
// »»-----► Number of lines: 7
static void write_digits(char *dst, long n, int digits)
{
    char *ptr = dst + digits - 1;
    while (n > 0)
    {
        *ptr-- = (n % 10) + '0';
        n /= 10;
    }
    dst[digits] = '\0';
}
// »»-----► Number of lines: 20
char *ft_itoa_inplace(char *buf, int n)
{
    char *start = buf;
    long num = n;
    if (!buf)
        return (NULL);
    if (num == 0)
    {
        buf[0] = '0';
        buf[1] = '\0';
        return (start);
    }
    if (num < 0)
    {
        *buf++ = '-';
        num = -num;
    }
    write_digits(buf, num,  count_digits(num));
    return (start);
}
