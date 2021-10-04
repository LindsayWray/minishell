/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_echo.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: idonado <idonado@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/04 14:34:32 by idonado       #+#    #+#                 */
/*   Updated: 2021/10/04 14:34:33 by idonado       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo_b(int *n_flag, int *i)
{
	*n_flag = 1;
	*i = 2;
	return ;
}

int	ft_echois_n_b(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (i == 0 && cmd[i] == '-')
			i++;
		else if (cmd[i] == 'n')
			i++;
		else
			return (0);
	}
	if (ft_strlen(cmd) < 2)
		return (0);
	return (1);
}

void	ft_echois_n(char **cmd, int *n_flag, int *i)
{
	while (cmd[*i] && ft_echois_n_b(cmd[*i]) == 1)
	{
		*n_flag = 1;
		*i = *i + 1;
	}
	(void)i;
	return ;
}

int	ft_echo(char **cmd, int fd_out)
{
	int	i;
	int	n_flag;

	n_flag = 0;
	if (!cmd[1])
	{
		ft_dprintf(fd_out, "\n");
		return (0);
	}
	i = 1;
	ft_echois_n(cmd, &n_flag, &i);
	while (cmd[i])
	{
		ft_dprintf(fd_out, "%s", cmd[i]);
		i++;
		if (cmd[i])
			ft_dprintf(fd_out, " ");
	}
	if (n_flag == 0)
		ft_dprintf(fd_out, "\n");
	return (0);
}
