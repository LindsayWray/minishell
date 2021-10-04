/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exit_utils_a.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: idonado <idonado@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/04 14:33:17 by idonado       #+#    #+#                 */
/*   Updated: 2021/10/04 14:33:17 by idonado       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exit_negative(int exit_code)
{
	while (exit_code < -256)
		exit_code = exit_code + 256;
	exit_code = 256 + exit_code;
	return (exit_code);
}
