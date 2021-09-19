#include "../../includes/minishell.h"

void    ft_echo_b(int *n_flag, int *i)
{
    *n_flag = 1;
    *i = 2;
    return ;
}

int ft_echo(char **cmd, int fd_out)
{
    int i;
    int n_flag;

    n_flag = 0;
    if (!cmd[1])
    {
        ft_dprintf(fd_out, "\n");
        return (0);
    }
    if (ft_streql(cmd[1], "-n") == 1)
        ft_echo_b(&n_flag, &i);
    else
        i = 1;
    while (cmd[i])
    {
        ft_dprintf(fd_out, "%s", cmd[i]);
        i++;
        if (cmd[i])
            ft_dprintf(fd_out, " ");
    }
    if (n_flag == 0)
        ft_dprintf(fd_out, "\n");
    return (0);
}