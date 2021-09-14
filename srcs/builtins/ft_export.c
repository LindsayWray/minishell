#include "../../includes/minishell.h"

t_data  g_data;

static int ft_export_noarg(int fd_out)
{
    t_env_lst   *temp;

    temp = g_data.env_lst;
    while (temp)
    {
        ft_dprintf(fd_out, "%s=%s\n", temp->key, temp->value);
        temp = temp->next;
    }
    return (0);
}

static int ft_export_eql(char *cmd, int fd_out)
{
    char **temp;

    if (cmd[0] == '=')
    {
        ft_dprintf(fd_out, "export: not valid in this context\n");
        return (2);
    }
    else
    {
        temp = ft_split(cmd, '=');
        if (ft_isalpha(temp[0][0]) == 0)
        {
            ft_dprintf(fd_out, "export, not an identifier: %s\n", temp[0]);
            ft_split_free(temp);
            return (2);
        }
        else if (ft_isalnum_str(temp[0]) == 0)
        {
            ft_dprintf(fd_out, "export, not valid in this context: %s\n", temp[0]);
            ft_split_free(temp);
            return (2);
        }
        else if (export_exists(temp[0], temp[1]) == 1)
            ft_split_free(temp);
        else
        {
            ft_export_add(temp[0], temp[1]);
			ft_split_free(temp);
        }
    }
    return (0);
}

int    ft_export(char **cmd, int fd_out)
{
    int i;

    (void)fd_out;
    if (cmd[1] == NULL)
        return (ft_export_noarg(fd_out));
    else
    {
        i = 1;
        while (cmd[i])
        {
            if (ft_cinstr(cmd[i], '=') == 1)
                return (ft_export_eql(cmd[i], fd_out));
            i++;
        }
    }
    return (0);
}