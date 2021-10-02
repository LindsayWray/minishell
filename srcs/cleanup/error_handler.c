/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handler.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/02 18:23:17 by lwray         #+#    #+#                 */
/*   Updated: 2021/10/02 18:23:20 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	system_error(char *msg)
{
	clean_all();
	perror(msg);
	exit (EXIT_FAILURE);
}
