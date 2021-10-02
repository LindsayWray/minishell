/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   complex_cmd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/02 18:18:09 by lwray         #+#    #+#                 */
/*   Updated: 2021/10/02 18:18:11 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	arr_len(char **cmd)
{
	int	len;

	len = 0;
	while (cmd[len])
		len++;
	return (len);
}

char	**insert_str_in_array(char **cmd, char *str1, char *str2, int insert)
{
	char	**new_cmd;
	int		len;
	int		i;
	int		j;

	len = arr_len(cmd);
	new_cmd = malloc((len + 2) * sizeof(char *));
	i = 0;
	j = 0;
	while (i != len + 1)
	{
		if (i == insert)
			new_cmd[i] = str1;
		else if (i == insert + 1)
			new_cmd[i] = str2;
		else
			new_cmd[i] = ft_strdup(cmd[j]);
		if (i != insert + 1)
			j++;
		i++;
	}
	new_cmd[i] = NULL;
	ft_free_array(cmd);
	return (new_cmd);
}

static int	divide_str(char ***cmd, char *str, int *j, int i)
{
	char	*str1;
	char	*str2;

	if (str[*j] == '"' || str[*j] == '\'')
	{
		skip_over_quotes(str, j);
		return (0);
	}
	if (str[*j] == ' ')
	{
		str1 = ft_substr(str, 0, *j);
		str2 = ft_substr(str, (*j) + 1, (ft_strlen(str) - (*j)));
		*cmd = insert_str_in_array(*cmd, str1, str2, i);
		return (1);
	}
	return (0);
}

char	**complex_cmd(char **cmd)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (cmd[i])
	{
		str = cmd[i];
		j = 0;
		while (str[j])
		{
			if (divide_str(&cmd, str, &j, i))
				break ;
			j++;
		}
		i++;
	}
	return (cmd);
}
