/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_env_var.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/02 20:36:00 by lwray         #+#    #+#                 */
/*   Updated: 2021/10/02 20:36:02 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

t_data	g_data;

t_env_lst	*ft_get_env_var(char *key)
{
	t_env_lst	*temp;

	temp = g_data.env_lst;
	while (temp)
	{
		if (ft_streql(temp->key, key))
			return (temp);
		temp = temp->next;
	}
	return (temp);
}

char	*get_env_value(char *key)
{
	t_env_lst	*temp;

	temp = g_data.env_lst;
	while (temp)
	{
		if (ft_streql(key, temp->key))
			return (temp->value);
		temp = temp->next;
	}
	return ("");
}
