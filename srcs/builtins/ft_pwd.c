#include "../../includes/minishell.h"

int	ft_pwd(char **cmd, int fd_out)
{
	char	*path;

	(void)cmd;
	path = malloc(PATH_MAX);
	getcwd(path, PATH_MAX);
	ft_dprintf(fd_out, "%s\n", path);
	free(path);
	return (0);
}
