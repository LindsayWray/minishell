/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wait.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/02 20:32:28 by lwray         #+#    #+#                 */
/*   Updated: 2021/10/02 20:32:30 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_data	g_data;

void	wait_for_childprocesses(int *pids, int len)
{
	int		stat_loc;
	char	*exit_status;
	int		j;

	j = 0;
	signal(SIGINT, signal_from_child);
	signal(SIGQUIT, signal_from_child);
	while (j < len)
	{
		waitpid(pids[j], &stat_loc, 0);
		if (WIFEXITED(stat_loc))
			exit_status = ft_itoa(WEXITSTATUS(stat_loc));
		if (WIFSIGNALED(stat_loc))
			exit_status = ft_itoa(128 + WTERMSIG(stat_loc));
		if (WIFSIGNALED(stat_loc) && WTERMSIG(stat_loc) == SIGSEGV)
			ft_dprintf(STDERR_FILENO, "Segmentation fault: %d\n", SIGSEGV);
		export_exists("?", exit_status);
		free (exit_status);
		j++;
	}
	signal(SIGINT, received_signal);
	signal(SIGQUIT, received_signal);
	free (pids);
	g_data.pids = NULL;
}
