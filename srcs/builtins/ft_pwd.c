/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_pwd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: idonado <idonado@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/04 14:34:58 by idonado       #+#    #+#                 */
/*   Updated: 2021/10/04 14:34:59 by idonado       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(char **cmd, int fd_out)
{
	char	*path;

	(void)cmd;
	path = malloc(PATH_MAX);
	getcwd(path, PATH_MAX);
	ft_dprintf(fd_out, "%s\n", path);
	free(path);
	return (0);
}
