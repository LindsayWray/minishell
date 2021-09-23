#include "../../includes/minishell.h"

void	system_error(char *msg)
{
	clean_all();
	perror(msg);
	exit (EXIT_FAILURE);
}

void	clean_and_exit(void)
{
	clean_all();
	exit(EXIT_FAILURE);
}