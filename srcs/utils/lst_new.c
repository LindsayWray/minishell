#include "../../includes/minishell.h"

t_node	*lst_new(char *content, t_type type)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->content = content;
	node->type = type;
	node->previous = NULL;
	node->next = NULL;
	return (node);
}