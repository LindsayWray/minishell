#include "../../includes/utils.h"

t_env_lst   *ft_getenv(char **env)
{
    t_env_lst   *env_lst;
    t_env_lst   *env_new;
    char    **temp;
    char    *key;
    char    *value;
    int     i;

    env_lst = NULL;
    i = 0;
    while (env[i] != NULL)
    {
        temp = ft_split(env[i], '=');
        key = ft_strdup(temp[0]);
        value = ft_strdup(temp[1]);
        env_new = env_lst_new(key, value);
        env_lst_add_back(&env_lst, env_new);
        free(temp[0]);
        free(temp[1]);
        i++;
    }
    return (env_lst);
}
