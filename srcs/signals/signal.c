/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/02 18:19:47 by lwray         #+#    #+#                 */
/*   Updated: 2021/10/02 18:19:49 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_data	g_data;

void	signal_from_heredoc(int signal)
{
	if (signal == SIGINT)
		exit (signal);
}

void	signal_from_child(int signal)
{
	if (signal == SIGINT)
		ft_dprintf(STDOUT_FILENO, "\n");
	if (signal == SIGQUIT)
		ft_dprintf(STDOUT_FILENO, "Quit: %d\n", signal);
}

void	received_signal(int signal)
{
	int	i;

	i = 0;
	while (g_data.pids && g_data.pids[i] != 0)
	{
		printf("%d\n", i);
		kill(g_data.pids[i], signal);
		i++;
	}
	if (signal == SIGINT)
	{
		export_exists("?", "1");
		rl_replace_line("", 1);
		ft_dprintf(STDOUT_FILENO, "\n");
	}
	rl_on_new_line();
	rl_redisplay();
	refresh();
}
