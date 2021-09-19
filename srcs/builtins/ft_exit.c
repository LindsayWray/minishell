#include "../../includes/minishell.h"

int ft_exit(char **cmd, int fd_out)
{
    if (!cmd[1])
    {
        // Do something with last exit code
        //the exit code if its > 255
        //then its exit code = exit code % 256
        exit(0);
    }
    else if (cmd[2])
    {
        ft_dprintf(fd_out, "exit: too many arguements");
        // free everything before exit
        exit(1);
    }
    else
    {
        // free everything before exit
        exit(ft_atoi(cmd[1]));
    }
    return (0);
}