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

t_env_lst	*env_lst_new(char *key, char *value)
{
	t_env_lst	*node;
	char		*set_key;
	char		*set_value;

	node = (t_env_lst *)malloc(sizeof(t_env_lst));
	if (!node)
		return (NULL);
	set_key = ft_strdup(key);
	set_value = ft_strdup(value);
	if (set_key == NULL || set_value == NULL)
	{
		if (set_key != NULL)
			free(set_key);
		if (set_value != NULL)
			free(set_value);
		free(node);
		return (NULL);
	}
	node->key = set_key;
	node->value = set_value;
	node->next = NULL;
	return (node);
}
