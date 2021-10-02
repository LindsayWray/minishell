/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalnum_str.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/02 20:42:37 by lwray         #+#    #+#                 */
/*   Updated: 2021/10/02 20:42:38 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}

int	ft_isalnum_str(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (-1);
	while (str[i] != '\0')
	{
		if (ft_isalpha(str[i]) == 1)
			i++;
		else if (ft_isdigit(str[i]) == 1)
			i++;
		else if (str[i] == '_' || (str[i + 1] == '\0' && str[i] == '+'))
			i++;
		else
			return (0);
	}
	return (1);
}
