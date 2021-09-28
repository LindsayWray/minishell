#include "../../includes/minishell.h"

t_data  g_data;

int export_exists(char *key, char *value)
{
    t_env_lst   *temp;

    temp = g_data.env_lst;
    while (temp)
    {
        if (ft_streql(key, temp->key))
            {
                if (value[0] == '\0' && temp->value != NULL)
                    return (1);
                else
                {
                    free(temp->value);
                    temp->value = ft_strdup(value);
                    return (1);
                }
            }
        temp = temp->next;
    }
    return (0);
}

int export_exists_key(char *key)
{
    t_env_lst   *temp;

    temp = g_data.env_lst;
    while (temp)
    {
        if (ft_streql(key, temp->key))
            return (1);
        temp = temp->next;
    }
    return (0);
}

int    ft_export_add(char *key, char *value)
{
    t_env_lst   *new;
    char        *set_key;
    char        *set_value;

    set_key = ft_strdup(key);
    if (set_key == NULL)
        return (1);
    if (value != NULL)
        set_value = ft_strdup(value);
    else
    {
        set_value = malloc(sizeof(NULL));
        set_value = NULL;
    }
    new = env_lst_new(set_key, set_value);
    env_lst_add_back(&(g_data.env_lst), new);
    return (0);
}