#include "../../includes/minishell.h"

t_token	**lst_add_back(t_token **list, t_token *new)
{
	if (new == NULL)
		return ((void *)NULL);
	t_token	*last;

	if (*list)
	{
		last = lst_last(*list);
		if (last)
		{
			new->previous = last;
			last->next = new;
		}
	}
	else if (list)
		*list= new;
	return (list);
}

void	cmd_lst_add_back(t_cmd_lst **list, t_cmd_lst *new)
{
	t_cmd_lst	*last;

	if (*list)
	{
		last = cmd_lst_last(*list);
		if (last)
		{
			new->previous = last;
			last->next = new;
		}
	}
	else if (list)
		*list= new;
}