#include "miniRT.h"

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	if (str)
		while (str[i])
			i++;
	return (i);
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