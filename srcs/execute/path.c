#include "../../includes/minishell.h"

void	command_not_found_error(char *command)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
}

char	*get_path(char *command)
{
	char	**paths;
	char	*path;
	int		i;
	struct stat buf;

	if (lstat(command, &buf) == 0)
		return (ft_strdup(command)); //means it already is the full path
	//paths = find_env_paths(envp);
    paths = ft_split(getenv("PATH"), ':');
    i = 0;
	command = ft_strjoin("/", command);
	i = 1;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], command);
		if (lstat(path, &buf) == 0)
		{
			//free (command);
			//free_array(paths);
			return (path);
		}
		free (path);
		i++;
	}
	command_not_found_error(command + 1);
	// free (command);
	// free_array(paths);
	exit (EXIT_FAILURE);
}