
#include <stdlib.h>
#include <string.h>
#include "libft.h"

char *ft_strndup(const char *s, size_t n)
{
    char *dup = malloc(n + 1);
    if (!dup)
        return NULL;
    ft_memcpy(dup, s, n);
    dup[n] = '\0';
    return dup;
}
