/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unset.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: idonado <idonado@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/04 14:35:02 by idonado       #+#    #+#                 */
/*   Updated: 2021/10/04 14:35:03 by idonado       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_data	g_data;

static void	ft_unset_del_a(t_env_lst *temp, int *first)
{
	t_env_lst	*temp2;

	free(temp->key);
	if (temp->value != NULL)
		free(temp->value);
	temp2 = temp;
	temp2 = temp2->next;
	if (temp->previous != NULL)
		temp->previous->next = temp2;
	else
		*first = 1;
	if (temp2 != NULL)
	{
		if (temp2->next != NULL)
			temp2->previous = temp->previous;
	}
	free(temp);
	if (*first == 1)
		g_data.env_lst = temp2;
}

static void	ft_unset_del(char *cmd)
{
	t_env_lst	*temp;
	int			first;

	temp = g_data.env_lst;
	first = 0;
	while (temp)
	{
		if (ft_streql(cmd, temp->key) == 1)
		{
			ft_unset_del_a(temp, &first);
			return ;
		}
		temp = temp->next;
	}
	return ;
}

int	ft_unset(char **cmd, int fd_out)
{
	int	i;

	(void)fd_out;
	i = 0;
	while (cmd[i] != NULL)
		i++;
	i--;
	while (i >= 0)
	{
		if (ft_isdigit(cmd[i][0]) == 1 || ft_isalnum_str(cmd[i]) == 0)
		{
			ft_dprintf(STDERR_FILENO, \
			"unset: `%s': not a valid identifier\n", cmd[i]);
			return (1);
		}
		else
			ft_unset_del(cmd[i]);
		i--;
	}
	return (0);
}
