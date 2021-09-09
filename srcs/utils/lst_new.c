#include "../../includes/minishell.h"

t_token	*lst_new(char *content, t_type type)
{
	t_token	*node;

	node = (t_token *)malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->content = content;
	node->type = type;
	node->previous = NULL;
	node->next = NULL;
	return (node);
}

t_cmd_lst	*cmd_lst_new(t_subcmd subcmd)
{
	t_cmd_lst	*node;

	node = (t_cmd_lst *)malloc(sizeof(t_cmd_lst));
	if (!node)
		return (NULL);
	node->subcmd = subcmd;
	node->previous = NULL;
	node->next = NULL;
	return (node);
}