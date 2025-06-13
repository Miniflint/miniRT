#include "miniRT.h"

unsigned int ft_atoi(char **s)
{
    unsigned int   n;

    n = 0;
    while (**s >= '0' && **s <= '9')
        n = n * 10 + *((*s)++) - '0';
    return (n);
}

double ft_atof(char **s)
{
    int n;
    int dec;
    int neg;

    neg = 1;
    if (**s == '-' || **s == '+')
    {
        if (**s == '-')
            neg = -1;
        (*s)++;
    }
    n = ft_atoi(s);
    if (!(**s) || **s != '.')
        return ((double)n);
    (*s)++;
    dec = ft_atoi(s);
    return ((n + ((double)dec / pow(10, ft_nblen(dec)))) * neg);
}

int ft_iswhitespace(char c)
{
    if (c == ' ' || (c >= 8 && c <= 13))
        return (1);
    return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	char *const	tmp = s1;
	char		*new_str;

	new_str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	if (s1)
		while (*s1)
			new_str[i++] = *(s1++);
	if (s1)
		free(tmp);
	if (s2)
		while (*s2)
			new_str[i++] = *(s2++);
	new_str[i] = 0;
	return (new_str);
}

void    *ft_memset(void *b, int c, size_t len)
{
    unsigned char    *tmp_ptr;
    
    tmp_ptr = (unsigned char *)b;
    while (len > 0)
    {
        *(tmp_ptr++) = (unsigned char)c;
        len--;
    }
    return (b);
}