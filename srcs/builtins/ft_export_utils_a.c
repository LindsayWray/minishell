#include "../../includes/minishell.h"

t_data  g_data;

char    *clean_value(char *value)
{
    size_t      val_len;

    val_len = ft_strlen(value);
    if (val_len != 0)
    {
        if ((value[0] == '\'' || value[0] == '"') && \
        (value[val_len - 1] == '\''|| value[val_len - 1] == '"') && \
        (0 != (val_len - 1)))
        {
            value = ft_shiftstr_left(value);
            value = ft_shiftstr_right(value);
        }
    }
    return (value);
}

int export_exists(char *key, char *value)
{
    t_env_lst   *temp;

    temp = g_data.env_lst;
    while (temp)
    {
        if (ft_streql(key, temp->key))
            {
                value = clean_value(value);
                if (value[0] == '\0')
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

    value = clean_value(value);
    set_key = ft_strdup(key);
    if (set_key == NULL)
        return (1);
    set_value = ft_strdup(value);
    if (set_value == NULL)
    {
        free(set_key);
        return (1);
    }
    new = env_lst_new(set_key, set_value);
    env_lst_add_back(&(g_data.env_lst), new);
    return (0);
}