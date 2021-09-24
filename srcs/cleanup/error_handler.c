#include "../../includes/minishell.h"

void	system_error(char *msg)
{
	clean_all();
	perror(msg);
	exit (EXIT_FAILURE);
}