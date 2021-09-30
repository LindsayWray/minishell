#include "../../includes/utils.h"

char	*ft_strdup(char *src)
{
	char	*dup;
	int		i;
	int		src_len;

	if (src == NULL)
		return (NULL);
	src_len = ft_strlen(src);
	dup = malloc(src_len + 1);
	if (dup == NULL)
		system_error("Malloc Error");
	i = 0;
	while (src[i] != '\0')
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}