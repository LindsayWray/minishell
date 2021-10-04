/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_env.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: idonado <idonado@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/04 14:34:39 by idonado       #+#    #+#                 */
/*   Updated: 2021/10/04 14:34:39 by idonado       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_data	g_data;

int	ft_env_noarg(int fd_out)
{
	t_env_lst	*lst;

	lst = g_data.env_lst;
	while (lst)
	{
		if (lst->value != NULL)
			ft_dprintf(fd_out, "%s=%s\n", lst->key, lst->value);
		lst = lst->next;
	}
	return (0);
}

int	ft_env(char **cmd, int fd_out)
{
	if (cmd[1] == NULL)
		return (ft_env_noarg(fd_out));
	else
		return (2);
	return (0);
}
