#include "../main.h"

char	*ft_strdup(const char *s1)
{
	const char	*clone;
	int			len;

	len = ft_strlen(s1);
	clone = malloc(sizeof(char) * (len + 1));
	if (!clone)
		return (NULL);
	ft_memcpy((void *)clone, s1, len + 1);
	return ((char *)clone);
}
