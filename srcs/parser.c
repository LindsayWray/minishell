#include "../includes/minishell.h"

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

t_cmd_lst	*parser(t_token *token)
{
	t_subcmd	subcmd;
	t_cmd_lst	*cmd_lst;
	int			count;
	int i;

	cmd_lst = NULL;
	while (token)
	{
		i = 0;
		count = word_count(token);
		subcmd.cmd = malloc((count + 1) * sizeof(char *));
		// if (!subcmd.cmd)
		// 	call to global to clean up
		subcmd.in_type = VOID;
		subcmd.out_type = VOID;
		while (token && token->type != PIPE)
		{
			if (token->type == WORD)
			{
				subcmd.cmd[i] = token->content;
				i++;
			}
			if (token->type == INPUT_REDIRECTION || token->type == HEREDOC)
			{
				subcmd.in_type = token->type;
				subcmd.in_file = token->content;
			}
			if (token->type == OUTPUT_REDIRECTION || token->type == APPEND)
			{
				subcmd.out_type = token->type;
				subcmd.out_file = token->content;
			}	
			token = token->next;	
		}
		subcmd.cmd[i] = NULL;
		cmd_lst_add_back(&cmd_lst, cmd_lst_new(subcmd));
		if (token)
			token = token->next;
	}
	return (cmd_lst); // put in global instead of return
}