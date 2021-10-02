#include "../../includes/minishell.h"

t_data  g_data;

static  t_env_lst   *sort_env_lst(t_env_lst *lst)
{
    t_env_lst   *sort_i;
    t_env_lst   *sort_j;
    char        *temp_key;
    char        *temp_value;

    sort_i = lst;
    while (sort_i)
    {
        sort_j = sort_i->next;
        while (sort_j)
        {
            if (ft_strcmp(sort_i->key, sort_j->key) > 0)
            {
                temp_key = sort_i->key;
                temp_value = sort_i->value;
                sort_i->key = sort_j->key;
                sort_i->value = sort_j->value;
                sort_j->key = temp_key;
                sort_j->value = temp_value;
            }
            sort_j = sort_j->next;
        }
        sort_i = sort_i->next;
    }
    return (lst);
}

static int ft_export_noarg(int fd_out)
{
    t_env_lst   *temp;
    t_env_lst   *new;
    t_env_lst   *lst;

    temp = g_data.env_lst;
    lst = NULL;
    while (temp)
    {
        if (temp->value != NULL)
            new = env_lst_new(ft_strdup(temp->key), ft_strdup(temp->value));
        else
            new = env_lst_new(ft_strdup(temp->key), NULL);
        env_lst_add_back(&lst, new);
        temp = temp->next;
    }
    lst = sort_env_lst(lst);
    while (lst)
    {
        if (lst->value == NULL)
            ft_dprintf(fd_out, "declare -x %s\n", lst->key);
        else
            ft_dprintf(fd_out, "declare -x %s=\"%s\"\n", lst->key, lst->value);
        temp = lst;
        lst = lst->next;
        free(temp->key);
        if (temp->value != NULL)
            free(temp->value);
        free(temp);
    }
    return (0);
}

static int ft_export_eql(char *cmd, int fd_out)
{
    char    **temp;
    int     ret;

	(void)fd_out;
    if (cmd[0] == '=')
    {
        ft_dprintf(STDERR_FILENO, "export: `%s': not a valid identifier\n", cmd);
        return (1);
    }
    else
    {
        temp = ft_split(cmd, '=');
        if (ft_isalpha(temp[0][0]) == 0 && temp[0][0] != '_')
        {
            ft_dprintf(STDERR_FILENO, "export: `%s': not a valid identifier\n", temp[0]);
            ft_free_array(temp);
            return (1);
        }
        else if (ft_isalnum_str(temp[0]) == 0)
        {
            ft_dprintf(STDERR_FILENO, "export: `%s=%s': not a valid identifier\n", temp[0], temp[1]);
            ft_free_array(temp);
            return (1);
        }
        else if (export_exists(temp[0], temp[1]) == 1)
            ft_free_array(temp);
        else
        {
            ret = ft_export_add(temp[0], temp[1]);
			ft_free_array(temp);
            return (ret);
        }
    }
    return (0);
}

static int ft_export_key(char *cmd, int fd_out)
{
	(void)fd_out;
    if (ft_isdigit(cmd[0]) == 1)
    {
        ft_dprintf(STDERR_FILENO, "export: `%s': not a valid identifier\n", cmd);
        return (1);
    }
    else if (ft_isalnum_str(cmd) == 0)
    {
        ft_dprintf(STDERR_FILENO, "export: `%s': not a valid identifier\n", cmd);
        return (1);
    }
    else if (export_exists_key(cmd) == 1)
        return (0);
    else
        return (ft_export_add(cmd, NULL));
    return (0);
}

int    ft_export(char **cmd, int fd_out)
{
    int i;
    int ret;

    (void)fd_out;
    if (cmd[1] == NULL)
        return (ft_export_noarg(fd_out));
    else
    {
        i = 1;
        while (cmd[i])
        {
            if (ft_cinstr(cmd[i], '=') == 1)
                ret = ft_export_eql(cmd[i], fd_out);
            else
                ret = ft_export_key(cmd[i], fd_out);
            if (ret != 0)
                return (ret);
            i++;
        }
    }
    return (0);
}
