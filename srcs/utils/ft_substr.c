/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/10 15:38:50 by lwray         #+#    #+#                 */
/*   Updated: 2020/12/11 19:42:14 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

char	*empty_str(void)
{
	char	*substr;

	substr = (char *)malloc(1);
	if (substr == NULL)
		system_error("Malloc Error");
	substr[0] = '\0';
	return (substr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	size_t			i;
	unsigned int	len_s;

	if (!s)
		return (NULL);
	len_s = (unsigned int)ft_strlen((char *)s);
	if (len_s < start)
		return (empty_str());
	if (len < (len_s - start))
		substr = (char *)malloc(len + 1);
	else
		substr = (char *)malloc(len_s - start + 1);
	if (substr == 0)
		system_error("Malloc Error");
	i = 0;
	while ((s[i] != '\0') && (i < len))
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
