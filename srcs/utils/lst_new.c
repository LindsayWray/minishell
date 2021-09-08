#include "../../includes/minishell.h"

t_node	*lst_new(t_token token)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->token = token;
	node->previous = NULL;
	node->next = NULL;
	return (node);
}