#include "../../includes/utils.h"

void	ft_split_free(char **str)
{
	free(str[0]);
	free(str[1]);
	return ;
}
