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
		if (cmd[i + 1] == '\0')
			return (cmd);
		value = expanding(cmd, i);
		return (locate_env_var(value, false));
	}
	return (cmd);
}

char	**replace_array(int count, char **cmd)
{
	char	**new_cmd;
	int		i;
	int		j;

	new_cmd = malloc((count + 1) * sizeof(char *));
	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (*cmd[i])
		{
			new_cmd[j] = cmd[i];
			j++;
		}
		else
			free (cmd[i]);
		i++;
	}
	new_cmd[j] = NULL;
	free(cmd);
	return (new_cmd);
}

char	**remove_empty_strings(char **cmd)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		if (*cmd[i])
			count++;
		i++;
	}
	if (arr_len(cmd) == count)
		return (cmd);
	return (replace_array(count, cmd));
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
			cmd_lst->subcmd.cmd[i] = expanded_str;
			i++;
		}
		cmd_lst->subcmd.cmd = complex_cmd(cmd_lst->subcmd.cmd);
		cmd_lst->subcmd.cmd = remove_empty_strings(cmd_lst->subcmd.cmd);
		i = 0;
		while (cmd_lst->subcmd.cmd[i])
		{
			cmd_lst->subcmd.cmd[i] = quote_handler(cmd_lst->subcmd.cmd[i]);
			i++;
		}
		cmd_lst = cmd_lst->next;
	}
}
