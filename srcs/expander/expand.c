#include "../../includes/minishell.h"

t_data  g_data;

char *add_string(char *str1, char *str2)
{
    char    *joined_str;

    if (str2)
    {
        joined_str = ft_strjoin(str1, str2);
        free (str2);
        free (str1);
        return (joined_str);
    }
    return (str1);
}

char *locate_env_var(char *cmd)
{
    int i;
    int j;
    char    *value;

    i = 0;
    while (cmd[i] != '$' && cmd[i] != '\0')
    {
        if (cmd[i] == '\'')
            skip_over_quotes(cmd, &i);
		else
			i++;
    }
    if (cmd[i] == '$')
    {
        j = i + 1;
        while (ft_isalpha(cmd[j]) || ft_isdigit(cmd[j]) || cmd[j] == '_' || cmd[j] == '?')
            j++;
        value = ft_strdup(get_env_value(ft_substr(cmd, i + 1, j - (i + 1))));
		value = add_string(ft_substr(cmd, 0, i), value);
        i = j;
        while (cmd[j] != '\0')
            j++;
        value = add_string(value, ft_substr(cmd, i, j - i));
		free (cmd);
        return (locate_env_var(value));
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
			expanded_str = locate_env_var(cmd_lst->subcmd.cmd[i]);
			if (!ft_streql(expanded_str, cmd_lst->subcmd.cmd[i]))
				cmd_lst->subcmd.cmd[i] = expanded_str;
			cmd_lst->subcmd.cmd[i] = quote_handler(cmd_lst->subcmd.cmd[i]);
			i++;
		}
		cmd_lst = cmd_lst->next;
		}
}