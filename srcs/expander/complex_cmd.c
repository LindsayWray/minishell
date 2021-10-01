#include "../../includes/minishell.h"

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
				char *str2 = ft_substr(str, j + 1, (ft_strlen(str) - j));
				cmd = insert_str_in_array(cmd, str1, str2, i);
				break;
			}
			j++;
		}
		i++;
	}
	return (cmd);
}