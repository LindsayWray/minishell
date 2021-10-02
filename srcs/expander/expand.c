/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/02 18:18:23 by lwray         #+#    #+#                 */
/*   Updated: 2021/10/02 18:18:26 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_data	g_data;

char	*add_string(char *str1, char *str2)
{
	char	*joined_str;

	if (str2)
	{
		joined_str = ft_strjoin(str1, str2);
		free (str1);
		free (str2);
		return (joined_str);
	}
	return (str1);
}

char	*expanding(char *cmd, int i)
{
	char	*value;
	char	*str;
	int		j;

	value = NULL;
	j = i + 1;
	while (ft_isalnum(cmd[j]) || cmd[j] == '_' || cmd[j] == '?')
	{
		j++;
		if (cmd[j - 1] == '?')
			break ;
	}
	str = ft_substr(cmd, i + 1, j - (i + 1));
	value = ft_strdup(get_env_value(str));
	free (str);
	value = add_string(ft_substr(cmd, 0, i), value);
	i = j;
	while (cmd[j] != '\0')
		j++;
	value = add_string(value, ft_substr(cmd, i, j - i));
	free (cmd);
	return (value);
}

char	*locate_env_var(char *cmd, bool double_quotes)
{
	int		i;
	char	*value;

	i = 0;
	if (cmd[i + 1] == '\0')
		return (cmd);
	while (cmd[i] != '$' && cmd[i] != '\0')
	{
		if (cmd[i] == '"')
			double_quotes = !double_quotes;
		if (cmd[i] == '\'' && double_quotes == false)
			skip_over_quotes(cmd, &i);
		else
			i++;
	}
	if (cmd[i] == '$')
	{
		value = expanding(cmd, i);
		return (locate_env_var(value, false));
	}
	return (cmd);
}

void	expand(t_cmd_lst *cmd_lst)
{
	char	*expanded_str;
	int		i;

	while (cmd_lst)
	{
		i = 0;
		while (cmd_lst->subcmd.cmd[i])
		{
			expanded_str = locate_env_var(cmd_lst->subcmd.cmd[i], false);
			if (!ft_streql(expanded_str, cmd_lst->subcmd.cmd[i]))
				cmd_lst->subcmd.cmd[i] = expanded_str;
			i++;
		}
		cmd_lst->subcmd.cmd = complex_cmd(cmd_lst->subcmd.cmd);
		i = 0;
		while (cmd_lst->subcmd.cmd[i])
		{
			cmd_lst->subcmd.cmd[i] = quote_handler(cmd_lst->subcmd.cmd[i]);
			i++;
		}
		cmd_lst = cmd_lst->next;
	}
}
