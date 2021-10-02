/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/02 20:43:11 by lwray         #+#    #+#                 */
/*   Updated: 2021/10/02 20:43:12 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	ft_putstr_fd(char *str, int fd)
{
	int	len;

	if (str)
	{
		len = ft_strlen (str);
		write(fd, str, len);
	}
}
