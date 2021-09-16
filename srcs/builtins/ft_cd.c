#include "../../includes/minishell.h"

t_data  g_data;

void    ft_cd_change_pwd(char *path, t_env_lst *temp)
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

void    ft_cd_updatepwd(void)
{
    t_env_lst   *temp;
    char        *path;
    char        *key;

    temp = g_data.env_lst;
    path = malloc(PATH_MAX);
    getcwd(path, PATH_MAX);
    while (temp)
    {
        if (ft_streql(temp->key, "PWD"))
        {
            ft_cd_change_pwd(path, temp);
            return ;
        }
        temp = temp->next;
    }
    if (!temp)
    {
        key = ft_strdup("PWD");
        temp = env_lst_new(key, path);
        env_lst_add_back(&(g_data.env_lst), temp);
    }
    return ;
}

int ft_cd(char **cmd, int fd_out)
{
    int ret;

    if (cmd[1] == NULL)
        return (0);
    ret = chdir(cmd[1]);
    if (ret != 0)
    {
        if (errno == ENOTDIR)
            ft_dprintf(fd_out, "cd: %s: Not a directory\n", cmd[1]);
        else if (ft_strlen(cmd[1]) > PATH_MAX)
            ft_dprintf(fd_out, "cd: %s: Path is way too long.\n", cmd[1]);
        else
            ft_dprintf(fd_out, "cd: %s: No such file or directory\n", cmd[1]);

    }
    else
        ft_cd_updatepwd();
    return (ret);
}