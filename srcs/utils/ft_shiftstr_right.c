#include "../../includes/utils.h"

char    *ft_shiftstr_right(char *str)
{
        char    *new_str;
        char    *temp;
        int             i;

        new_str = malloc(ft_strlen(str));
        temp = ft_strdup(str);
        i = 0;
        while (i < ft_strlen(temp) - 1)
        {
                new_str[i] = temp[i];
                i++;
        }
        new_str[i] = '\0';
        free(temp);
        return (new_str);
}
