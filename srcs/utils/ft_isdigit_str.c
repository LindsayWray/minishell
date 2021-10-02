/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isdigit_str.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/02 20:42:59 by lwray         #+#    #+#                 */
/*   Updated: 2021/10/02 20:43:00 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

int	ft_isdigit_str(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (-1);
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 1)
			i++;
		else
			return (0);
	}
	return (1);
}
