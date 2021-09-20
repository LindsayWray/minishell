#include "../../includes/minishell.h"

int	word_count(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == WORD)
			count++;
		token = token->next;
	}
	return (count);
}

t_cmd_lst	*parser(t_token *token_lst)
{
	t_subcmd	subcmd;
	t_cmd_lst	*cmd_lst;
	int			count;
	int i;
	t_token		*token = token_lst;
	cmd_lst = NULL;
	while (token)
	{
		i = 0;
		count = word_count(token);
		subcmd.cmd = malloc((count + 1) * sizeof(char *));
		if (!subcmd.cmd)
			return (NULL);
		subcmd.in_type = VOID;
		subcmd.out_type = VOID;
		while (token && token->type != PIPE)
		{
			if (token->type == WORD)
			{
				subcmd.cmd[i] = ft_strdup(token->content);
				i++;
			}
			if (token->type == INPUT_REDIRECTION || token->type == HEREDOC)
			{
				subcmd.in_type = token->type;
				subcmd.in_file = ft_strdup(token->content);
			}
			if (token->type == OUTPUT_REDIRECTION || token->type == APPEND)
			{
				subcmd.out_type = token->type;
				subcmd.out_file = ft_strdup(token->content);
			}	
			token = token->next;	
		}
		subcmd.cmd[i] = NULL;
		cmd_lst_add_back(&cmd_lst, cmd_lst_new(subcmd));
		if (token)
			token = token->next;
	}
	token = token_lst;
	t_cmd_lst	*lst = cmd_lst;
	while (lst)
	{
		printf("-> %d\n", lst_last(token)->type);
		if ((!*lst->subcmd.cmd && lst->subcmd.in_type == VOID && lst->subcmd.out_type == VOID) || lst_last(token)->type == PIPE)
		{
			dprintf(STDERR_FILENO, "minishell: syntax error near unexpected token `|'\n");
			return (NULL);
		}
		lst = lst->next;
	}
	lst = cmd_lst;
	while (lst)
	{
		if (lst->subcmd.in_type == INPUT_REDIRECTION || lst->subcmd.in_type == HEREDOC || lst->subcmd.out_type == OUTPUT_REDIRECTION || lst->subcmd.out_type == APPEND)
		{
			if (!*lst->subcmd.in_file || !*lst->subcmd.out_file)
			{
				dprintf(STDERR_FILENO, "minishell: syntax error near unexpected token `newline'\n");
				return (NULL);
			}
		}
		lst = lst->next;
	}
	lst_clear(&token);
	return (cmd_lst);
}