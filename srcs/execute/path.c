/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/02 20:32:01 by lwray         #+#    #+#                 */
/*   Updated: 2021/10/02 20:32:04 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	command_not_found_error(char *command)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
}

static char	*absolute_path(char *command, struct stat buf)
{
	if (ft_streql(command, ".."))
	{
		command_not_found_error(command);
		free (command);
		exit (COMMAND_NOT_FOUND);
	}
	if (buf.st_mode & S_IFDIR)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: is a directory\n", command);
		exit(IS_A_DIRECTORY);
	}
	return (ft_strdup(command));
}

static void	free_cmd_and_paths(char *command, char **paths)
{
	free (command);
	ft_free_array(paths);
}

char	*get_path(char *command)
{
	char		**paths;
	char		*path;
	int			i;
	struct stat	buf;

	if (lstat(command, &buf) == 0 && ft_strchr(command, '/'))
		return (absolute_path(command, buf));
	paths = ft_split(get_env_value("PATH"), ':');
	command = ft_strjoin("/", command);
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], command);
		if (lstat(path, &buf) == 0)
		{
			free_cmd_and_paths (command, paths);
			return (path);
		}
		free (path);
		i++;
	}
	command_not_found_error(command + 1);
	free_cmd_and_paths (command, paths);
	exit (COMMAND_NOT_FOUND);
}
