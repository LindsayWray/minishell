#include "../../includes/utils.h"
#include <stdio.h>

static char    **swap_strs(size_t one, size_t two, char **env_copy)
{
    char *temp;

    temp = env_copy[one];
    env_copy[one] = env_copy[two];
    env_copy[two] = temp;
    return (env_copy);
}

static char    **sort_env(char **env)
{
    int i;
    char **env_copy;

    //Copying array
    i = 0;
    while (env[i])
        i++;
    env_copy = malloc(sizeof(char *) * i + 1);
    i = 0;
    while (env[i])
    {
        env_copy[i] = ft_strdup(env[i]);
        i++;
    }
    env_copy[i] = NULL;
    // Finished copying array

    // Sorting Array
    int j;
    i = 0;
    while (env_copy[i])
    {
        j = i + 1;
        while (env_copy[j])
        {
            if (ft_strcmp(env_copy[i], env_copy[j]) > 0)
                env_copy = swap_strs(i, j, env_copy);
            j++;
        }
        i++;
    }
    return (env_copy);
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
    env_copy = sort_env(env);
    while (env_copy[i] != NULL)
    {
        temp = ft_split(env_copy[i], '=');
        key = ft_strdup(temp[0]);
        if (temp[1] != NULL)
            value = ft_strdup(temp[1]);
        else
            value = ft_strdup("");
        env_new = env_lst_new(key, value);
        env_lst_add_back(&env_lst, env_new);
        free(temp[0]);
        free(temp[1]);
        free(env_copy[i]);
        i++;
    }
    free(env_copy[i]);
    free(env_copy);
    return (env_lst);
}
