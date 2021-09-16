#include "../../includes/minishell.h"

t_data  g_data;

static void    ft_oldpwd(char *path, t_env_lst *temp)
{
    if (temp->value == NULL)
        temp->value = path;
    else
    {
        free(temp->value);
        temp->value = path;
    }
    return ;
}

int ft_pwd(char **cmd, int fd_out)
{
    t_env_lst   *temp;
    char        *path;
    char        *key;

    (void)cmd;
    temp = g_data.env_lst;
    path = malloc(PATH_MAX);
    getcwd(path, PATH_MAX);
    ft_dprintf(fd_out, "%s\n", path);
    while (temp)
    {
        if (ft_streql(temp->key, "OLDPWD"))
        {
            ft_oldpwd(path, temp);
            return (0);
        }
        temp = temp->next;
    }
    if (!temp)
    {
        key = ft_strdup("OLDPWD");
        temp = env_lst_new(key, path);
        env_lst_add_back(&(g_data.env_lst), temp);
    }
    return (0);
}