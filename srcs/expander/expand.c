#include "../../includes/minishell.h"

t_data  g_data;

char *add_string(char *str1, char *str2)
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

char *expanding(char *cmd, int i)
{
	char	*value;
	char	*str;
	int j;
	
	value = NULL;
	j = i + 1;
	if (cmd[j] == '\0')
		printf("testing"); //value = ft_strdup("$");
	else
	{
		while (ft_isalpha(cmd[j]) || ft_isdigit(cmd[j]) || cmd[j] == '_' || cmd[j] == '?')
			j++;
		str = ft_substr(cmd, i + 1, j - (i + 1));
		value = ft_strdup(get_env_value(str));
		free (str);
	}
	value = add_string(ft_substr(cmd, 0, i), value);
	i = j;
	while (cmd[j] != '\0')
		j++;
	value = add_string(value, ft_substr(cmd, i, j - i));
	free (cmd);
	return (value);
}

char *locate_env_var(char *cmd, bool double_quotes)
{
    int i;
    char    *value;

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

char **insert_str_in_array(char **cmd, char *str1, char *str2, int insert)
{
	char **new_cmd;
	int count;
	int i;

	count = 0;
	while (cmd[count])
		count++;
	new_cmd = malloc((count + 2) * sizeof(char *));
	i = 0;
	int j = 0;
	while (i != count + 1)
	{
		if (i == insert)
		{
			new_cmd[i] = str1;
			j++;
		}
		else if (i == insert + 1)
			new_cmd[i] = str2;
		else
		{
			new_cmd[i] = ft_strdup(cmd[j]);
			j++;
		}
		//printf("str: %s\n", new_cmd[i]);
		i++;
	}
	new_cmd[i] = NULL;
	ft_free_array(cmd);
	return (new_cmd);
}

char **complex_cmd(char **cmd)
{
	char *str;
	int i;
	int j;

	i = 0;
	while (cmd[i])
	{
		str = cmd[i];
		j = 0;
		while (str[j])
		{
			if (str[j] == '"' || str[j] == '\'')
			{
				skip_over_quotes(str, &j);
				continue;
			}
			if (str[j] == ' ')
			{
				char *str1 = ft_substr(str, 0, j);
				//printf("str1: %s\n", str1);
				char *str2 = ft_substr(str, j + 1, (ft_strlen(str) - j));
				//printf("str2: %s\n", str2);
				cmd = insert_str_in_array(cmd, str1, str2, i);
				break;
			}
			j++;
		}
		i++;
	}
	return (cmd);
}

void    expand(t_cmd_lst *cmd_lst)
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