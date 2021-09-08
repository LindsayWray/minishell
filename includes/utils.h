#ifndef UTILS_H
# define UTILS_H

#include <stdlib.h>
#include "types.h"

char	*ft_substr(char const *s, unsigned int start, size_t len);
void	lst_add_back(t_node **list, t_node *new);
t_node	*lst_new(t_token token);
t_node	*lst_last(t_node *last);
int		ft_strlen(char *str);

#endif