/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_whitespace.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/02 20:44:19 by lwray         #+#    #+#                 */
/*   Updated: 2021/10/02 20:44:20 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

bool	is_whitespace(char c)
{
	if (c == 32 || (c > 8 && c < 14))
		return (true);
	return (false);
}
