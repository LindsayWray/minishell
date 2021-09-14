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
                if (value[0] == '\0')
                    return (1);
                else
                {
                    free(temp->value);
                    printf("hey: %s\n", temp->value);
                    temp->value = ft_strdup(value);
                    printf("hey: %s\n", temp->value);
                    return (1);
                }
            }
        temp = temp->next;
    }
    return (0);
}