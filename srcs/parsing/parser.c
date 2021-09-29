#include "../../includes/minishell.h"

t_data	g_data;

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

void	set_default(t_subcmd *subcmd, t_token *token)
{
	subcmd->cmd = malloc((word_count(token) + 1) * sizeof(char *));
	if (!subcmd->cmd)
		system_error("Malloc Error");
	subcmd->in_type = VOID;
	subcmd->out_type = VOID;
	subcmd->in_file = NULL;
	subcmd->out_file = NULL;
}

int	invalid_io_file_char(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	set_syntax_error(char *msg)
{
	dprintf(STDERR_FILENO, "minishell: syntax error near unexpected token `%s'\n", msg);
	export_exists("?", ft_strdup("2"));
	return (EXIT_FAILURE);
}

int	syntax_error(t_token *token_lst, t_cmd_lst *cmd_lst)
{
	t_cmd_lst	*lst = cmd_lst;

	while (lst)
	{
		if ((!*lst->subcmd.cmd && lst->subcmd.in_type == VOID && lst->subcmd.out_type == VOID) || lst_last(token_lst)->type == PIPE)
			return (set_syntax_error("|"));
		if ((lst->subcmd.in_type == INPUT_REDIRECTION || lst->subcmd.in_type == HEREDOC) && (!*lst->subcmd.in_file || invalid_io_file_char(*lst->subcmd.in_file)))
		{
			if (invalid_io_file_char(*lst->subcmd.in_file))
				return (set_syntax_error(lst->subcmd.in_file));
			else
				return (set_syntax_error("newline"));
		}
		if ((lst->subcmd.out_type == OUTPUT_REDIRECTION || lst->subcmd.out_type == APPEND) && (!*lst->subcmd.out_file || invalid_io_file_char(*lst->subcmd.out_file)))
		{
			if (invalid_io_file_char(*lst->subcmd.out_file))
				return (set_syntax_error(lst->subcmd.out_file));
			else
				return (set_syntax_error("newline"));
		}
		lst = lst->next;
	}
	return (EXIT_SUCCESS);
}

void	give_subcmd_content(t_subcmd *subcmd, t_token *token, int *i)
{
	if (token->type == WORD)
	{
		subcmd->cmd[*i] = ft_strdup(token->content);
		(*i)++;
	}
	if (token->type == INPUT_REDIRECTION || token->type == HEREDOC)
	{
		subcmd->in_type = token->type;
		subcmd->in_file = ft_strdup(token->content);
	}
	if (token->type == OUTPUT_REDIRECTION || token->type == APPEND)
	{
		subcmd->out_type = token->type;
		subcmd->out_file = ft_strdup(token->content);
	}
}

t_cmd_lst	*parser(t_token *token_lst)
{
	t_subcmd	subcmd;
	t_cmd_lst	*cmd_lst;
	int i;
	t_token		*token;

	token = token_lst;
	cmd_lst = NULL;
	while (token)
	{
		i = 0;
		set_default(&subcmd, token);
		while (token && token->type != PIPE)
		{
			give_subcmd_content(&subcmd, token, &i);
			token = token->next;
		}
		subcmd.cmd[i] = NULL;
		cmd_lst_add_back(&cmd_lst, cmd_lst_new(subcmd));
		if (token)
			token = token->next;
	}
	if (syntax_error(token_lst, cmd_lst))
	{
		free_cmdlst();
		cmd_lst = NULL;
	}
	lst_clear(&token);
	g_data.token = NULL;
	return (cmd_lst);
}