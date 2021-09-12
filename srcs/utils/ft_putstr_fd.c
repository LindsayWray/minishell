#include "../../includes/utils.h"

void	ft_putstr_fd(char *str, int fd)
{
	int len;
	
	if (str)
	{
		len = ft_strlen (str);
		write(fd, str, len);
	}
}