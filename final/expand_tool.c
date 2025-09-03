#include "minish.h"

static int count_escape(const char* str, int i)
{
    int count = 0;
    while(str[i] && str[i] == '\\')
    {    
        count++;
        i++;
    }    
    return count;
}

int modulo(int i, int mod)
{
    if (i<0)
    {
        while(i<0)
            i+=mod;
    }
    else
    {
        while(i>=mod)
            i-=mod;
    }
    return i;
}

int handle_escape_count(const char* str, int *i,int len)
{

    int s = *i;
    int count = count_escape(str,s);
    int parity;
    (*i)+= count;
    parity = modulo(count,2);
    count /= 2;
    if (str[*i] == '$' || str[*i] == '"' || str[*i] == '\'' ) 
        (*i)+=parity;
    return len+count+parity;
}

char *handle_escape_write(char *dst, const char* src, int *i, int *j)
{
    int s = *i;
    int count = count_escape(src,s);
    int parity;
    (*i)+= count;
    parity = modulo(count,2);
    count /= 2;
    int z = 0;
    while(z++ < count)
        dst[(*j)++] = '\\';
    if (!(src[(*i)] && (src[(*i)] == '$' || src[*i] == '"' || src[*i] == '\'')))
    {
        dst[(*j)++] = '\\';
        return dst;
    }
    if(parity)
        dst[(*j)++] = src[(*i)++];
    return dst;
}