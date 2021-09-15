#include "../../includes/minishell.h"

t_data  g_data;

char *get_value(char *key)
{
    t_env_lst   *temp;

    temp = g_data.env_lst;
    while (temp)
    {
        if (ft_streql(key, temp->key))
        {
            return (ft_strdup(temp->value));
        }
        temp = temp->next;
    }
    return (NULL);
}

char *add_after_string(char *value, char *after_str)
{
    char    *joined_str;

    if (after_str)
    {
        joined_str = ft_strjoin(value, after_str);
        free (after_str);
        free (value);
        return (joined_str);
    }
    return (value);
}

char *add_pre_string(char *pre_str, char *value)
{
    char    *joined_str;

    if (value)
    {
        joined_str = ft_strjoin(pre_str, value);
        free (pre_str);
        free (value);
        return (joined_str);
    }
    return (pre_str);
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
            handle_quotes(cmd, &i);
        //if (cmd[i] == '"')
        i++;
    }
    if (cmd[i] == '$')
    {
        j = i + 1;
        while (ft_isalpha(cmd[j]) || ft_isdigit(cmd[j]) || cmd[j] == '_')
            j++;
        printf("%s\n", ft_substr(cmd, i + 1, j - (i + 1)));
        value = get_value(ft_substr(cmd, i + 1, j - (i + 1)));
        if (i != 0)
            value = add_pre_string(ft_substr(cmd, 0, i), value);
        i = j;
        while (cmd[j] != '\0' && cmd[j] != '$')
            j++;
        if (i != j)
            value = add_after_string(value, ft_substr(cmd, i, j));
        return (value);
    }
    return (NULL);
}

void    expand(t_cmd_lst *cmd_lst)
{
    char *expanded_str;
    int    i;
    
    while (cmd_lst)
    {
        i = 1;
        while (cmd_lst->subcmd.cmd[i])
        {
            expanded_str = locate_env_var(cmd_lst->subcmd.cmd[i]);
            if (expanded_str)
            {
                free (cmd_lst->subcmd.cmd[i]);
                cmd_lst->subcmd.cmd[i] = expanded_str;
            }
            i++;
        }
        cmd_lst = cmd_lst->next;
    }
}