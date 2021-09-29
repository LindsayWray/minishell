#include "../../includes/minishell.h"

t_data  g_data;

static void ft_unset_del(char *cmd)
{
    t_env_lst   *temp;
    t_env_lst   *temp2;
    int         first;

    temp = g_data.env_lst;
    first = 0;
    while (temp)
    {
        if (ft_streql(cmd, temp->key) == 1)
        {
            free(temp->key);
            if (temp->value != NULL)
                free(temp->value);
            temp2 = temp;
            temp2 = temp2->next;
            if (temp->previous != NULL)
                temp->previous->next = temp2;
            else
                first = 1;
            if (temp2 != NULL)
            {
                if (temp2->next != NULL)
                    temp2->previous = temp->previous;
            }
            free(temp);
            if  (first == 1)
                g_data.env_lst = temp2;
            return ;
        }
        temp = temp->next;
    }
    return ;
}

int ft_unset(char **cmd, int fd_out)
{
    int i;

    i = 0;
    while (cmd[i] != NULL)
        i++;
    i--;
    while (i >= 0)
    {
        if (ft_isdigit(cmd[i][0]) == 1 || ft_isalnum_str(cmd[i]) == 0)
        {
            ft_dprintf(fd_out, "unset: `%s': not a valid identifier\n", cmd[i]);
            return (1);
        }
        else
            ft_unset_del(cmd[i]);
        i--;
    }
    return (0);
}