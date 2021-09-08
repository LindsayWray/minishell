#include "../../includes/minishell.h"

void	lst_add_back(t_node **list, t_node *new)
{
	t_node	*last;

	if (*list)
	{
		last = lst_last(*list);
		if (last)
			last->next = new;
	}
	else if (list)
		*list= new;
}