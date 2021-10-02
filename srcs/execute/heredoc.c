/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/02 20:31:53 by lwray         #+#    #+#                 */
/*   Updated: 2021/10/02 20:31:55 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	interactive_heredoc(int input_fd, char *delimiter)
{
	char	*line;

	signal(SIGINT, signal_from_heredoc);
	while (true)
	{
		line = readline("> ");
		if (line == NULL || ft_streql(line, delimiter))
		{
			free (line);
			exit(EXIT_SUCCESS);
		}
		ft_dprintf(input_fd, "%s\n", line);
		free (line);
	}
}

int	read_input_heredoc(char *delimiter)
{
	int		input_fd;
	pid_t	pid;

	input_fd = open(HEREDOC_FILE, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (input_fd == -1)
		system_error("input file does not exist");
	pid = fork();
	if (pid == -1)
		system_error("Fork Error");
	if (pid == 0)
		interactive_heredoc(input_fd, delimiter);
	signal(SIGINT, signal_from_child);
	wait (0);
	close (input_fd);
	input_fd = get_input(HEREDOC_FILE);
	unlink (HEREDOC_FILE);
	return (input_fd);
}
