#include "../../includes/minishell.h"

t_node	*lst_last(t_node *last)
{
	if (last == NULL)
		return (NULL);
	while ((last->next) != NULL)
		last = (last->next);
	return (last);
}