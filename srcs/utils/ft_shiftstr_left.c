#include "../../includes/utils.h"

char    *ft_shiftstr_left(char *str)
{
        char    *new_str;
        char    *temp;
        int             i;
        int             j;

        new_str = malloc(ft_strlen(str));
        temp = ft_strdup(str);
        i = 0;
        j = 1;
        while (temp[j] != '\0')
        {
                new_str[i] = temp[j];
                i++;
                j++;
        }
        new_str[i] = '\0';
        free(temp);
        return (new_str);
}
