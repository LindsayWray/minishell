#include "../../includes/utils.h"

static t_env_lst *get_shell_lvl(t_env_lst *temp)
{
    while (temp)
    {
        if (ft_streql(temp->key, "SHLVL") == 1)
            return (temp);
        temp = temp->next;
    }
    return (temp);
}

static void set_shell_lvl(t_env_lst *lst)
{
    t_env_lst   *temp;
    int         level;

    temp = get_shell_lvl(lst);
    if (temp && temp->value)
    {
        level = ft_atoi(temp->value);
		level++;
        free(temp->value);
        temp->value = ft_itoa(level);
    }
}

t_env_lst   *ft_getenv(char **env)
{
    t_env_lst   *env_lst;
    t_env_lst   *env_new;
    char    **temp;
    char    *key;
    char    *value;
    int     i;
    char    **env_copy;

    env_lst = NULL;
    i = 0;
    env_copy = NULL;
    while (env[i] != NULL)
    {
        temp = ft_split(env[i], '=');
        key = ft_strdup(temp[0]);
        if (temp[1] != NULL)
            value = ft_strdup(temp[1]);
        else
        {
            value = malloc(sizeof(NULL));
            value = NULL;
        }
        env_new = env_lst_new(key, value);
        env_lst_add_back(&env_lst, env_new);
        free(temp[0]);
        free(temp[1]);
        i++;
    }
    set_shell_lvl(env_lst);
    env_new = env_lst_new(ft_strdup("?"), ft_strdup("0"));
	env_lst_add_back(&env_lst, env_new); // added these lines to set the exit_status on 0 at the beginning
    return (env_lst);
}
