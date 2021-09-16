#include "../../includes/minishell.h"

t_data  g_data;

int ft_env_noarg(int fd_out)
{
    t_env_lst *lst;

    lst = g_data.env_lst;
    while (lst)
    {
        if (ft_cinstr(lst->value, ' ') == 1 && ft_strlen(lst->value) != 0)
            ft_dprintf(fd_out, "%s='%s'\n", lst->key, lst->value);
        else if (ft_strlen(lst->value) != 0)
            ft_dprintf(fd_out, "%s=%s\n", lst->key, lst->value);
        lst = lst->next;
    }
    return (0);
}

int ft_env(char **cmd, int fd_out)
{
    if (cmd[1] == NULL)
        return (ft_env_noarg(fd_out));
    return (0);
}