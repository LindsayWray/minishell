#include "../../includes/utils.h"

char	*ft_strdup(char *src)
{
	char	*dup;
	int		i;
	int		src_len;

	src_len = ft_strlen(src);
	dup = malloc(src_len + 1);
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}