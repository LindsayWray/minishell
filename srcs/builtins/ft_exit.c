/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exit.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: idonado <idonado@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/04 14:33:13 by idonado       #+#    #+#                 */
/*   Updated: 2021/10/04 14:33:14 by idonado       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_data	g_data;

static int	exit_code_result(void)
{
	int	exit_code;

	if (ft_get_env_var("?") != NULL)
		exit_code = ft_atoi((ft_get_env_var("?"))->value);
	else
		exit_code = 0;
	if (exit_code > 255)
		exit_code = exit_code % 256;
	else if (exit_code < 0)
		exit_code = ft_exit_negative(exit_code);
	clean_all();
	return (exit_code);
}

int	ft_exit_a(char **cmd, int fd_out)
{
	if (ft_isdigit_str(cmd[1]) == 1)
	{
		ft_dprintf(fd_out, "exit\nminishell: exit: too many arguments\n");
		return (1);
	}
	else
	{
		ft_dprintf(fd_out, \
		"exit\nminishell: exit: %s: numeric argument required\n", cmd[1]);
		if (g_data.cmd_lst->next == NULL)
		{
			clean_all();
			exit(255);
		}
		return (255);
	}
}

int	ft_exit_b(char **cmd, int fd_out)
{
	ft_dprintf(fd_out, \
	"exit\nminishell: exit: %s: numeric argument required\n", cmd[1]);
	if (g_data.cmd_lst->next == NULL)
	{
		clean_all();
		exit(255);
	}
	return (255);
}

int	ft_exit_c(char **cmd)
{
	int	exit_code;

	exit_code = ft_atoi(cmd[1]);
	if (g_data.cmd_lst->next == NULL)
	{
		clean_all();
		if (exit_code > 255)
			exit(exit_code % 256);
		else if (exit_code < 0)
			exit_code = ft_exit_negative(exit_code);
		exit(exit_code);
	}
	else
	{
		if (exit_code > 255)
			return (exit_code % 256);
		else if (exit_code < 0)
			exit_code = ft_exit_negative(exit_code);
		return (exit_code);
	}
}

int	ft_exit(char **cmd, int fd_out)
{
	if (!cmd[1])
	{
		if (g_data.cmd_lst->next == NULL)
			exit(exit_code_result());
		return (exit_code_result());
	}
	else if (cmd[1])
	{
		if (cmd[2])
			return (ft_exit_a(cmd, fd_out));
		if (ft_isdigit_str(cmd[1]) == 0)
			return (ft_exit_b(cmd, fd_out));
		else
			return (ft_exit_c(cmd));
	}
	return (0);
}
