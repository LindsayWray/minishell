#include "../../includes/minishell.h"

void	lst_add_back(t_token **list, t_token *new)
{
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

void	env_lst_add_back(t_env_lst **list, t_env_lst *new)
{
	t_env_lst	*last;

	if (*list)
	{
		last = env_lst_last(*list);
		if (last)
			last->next = new;
	}
	else if (list)
		*list= new;
}
