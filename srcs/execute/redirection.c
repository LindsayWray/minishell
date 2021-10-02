/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/02 20:32:17 by lwray         #+#    #+#                 */
/*   Updated: 2021/10/02 20:32:18 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_output(char *output_file, t_type type)
{
	int		output_fd;

	if (type == APPEND)
		output_fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (output_fd == -1)
		system_error(output_file);
	return (output_fd);
}

int	get_input(char *input_file)
{
	int		input_fd;

	input_fd = open(input_file, O_RDONLY);
	if (input_fd == -1)
		perror(input_file);
	return (input_fd);
}

int	set_redirection(int *input_fd, int *output_fd, t_subcmd subcmd)
{
	if (subcmd.in_type == INPUT_REDIRECTION)
	{
		*input_fd = get_input(subcmd.in_file);
		if (*input_fd == -1)
			return (EXIT_FAILURE);
	}
	if (subcmd.in_type == HEREDOC)
		*input_fd = read_input_heredoc(subcmd.in_file);
	if (subcmd.out_type == OUTPUT_REDIRECTION || subcmd.out_type == APPEND)
	{
		*output_fd = get_output(subcmd.out_file, subcmd.out_type);
		if (*output_fd == -1)
			return (EXIT_FAILURE);
	}
	if (*subcmd.cmd == NULL)
		exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

void	dup_fd(int input_fd, int output_fd)
{
	if (dup2(output_fd, STDOUT_FILENO) == -1)
		system_error("dup error");
	if (output_fd != STDOUT_FILENO)
		close (output_fd);
	if (dup2(input_fd, STDIN_FILENO) == -1)
		system_error("dup error");
	if (input_fd != STDIN_FILENO)
		close (input_fd);
}
