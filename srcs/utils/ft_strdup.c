/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/02 20:43:41 by lwray         #+#    #+#                 */
/*   Updated: 2021/10/02 20:43:42 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

char	*ft_strdup(char *src)
{
	char	*dup;
	int		i;
	int		src_len;

	if (src == NULL)
		return (NULL);
	src_len = ft_strlen(src);
	dup = malloc(src_len + 1);
	if (dup == NULL)
		system_error("Malloc Error");
	i = 0;
	while (src[i] != '\0')
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
