#include "../../includes/minishell.h"

t_token	*lst_last(t_token *last)
{
	if (last == NULL)
		return (NULL);
	while ((last->next) != NULL)
		last = (last->next);
	return (last);
}

t_cmd_lst	*cmd_lst_last(t_cmd_lst *last)
{
	if (last == NULL)
		return (NULL);
	while ((last->next) != NULL)
		last = (last->next);
	return (last);
}

t_env_lst	*env_lst_last(t_env_lst *last)
{
	if (last == NULL)
		return (NULL);
	while ((last->next) != NULL)
		last = (last->next);
	return (last);
}
