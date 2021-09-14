#include "../../includes/utils.h"

int ft_cinstr(const char *str, char c)
{
    int i;

    i = 0;
    if (str == NULL)
        return (-1);
    while (str[i] != '\0')
    {
        if (str[i] == c)
            return (1);
        i++;
    }
    return (0);
}