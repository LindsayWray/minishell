/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_shiftstr_left.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/02 20:43:18 by lwray         #+#    #+#                 */
/*   Updated: 2021/10/02 20:43:19 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

char	*ft_shiftstr_left(char *str)
{
	char	*new_str;
	char	*temp;
	int		i;
	int		j;

	new_str = malloc(ft_strlen(str));
	temp = ft_strdup(str);
	i = 0;
	j = 1;
	while (temp[j] != '\0')
	{
		new_str[i] = temp[j];
		i++;
		j++;
	}
	new_str[i] = '\0';
	free(temp);
	return (new_str);
}
