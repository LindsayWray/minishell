#include "../../includes/minishell.h"

int	invalid_io_file_char(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	set_syntax_error(char *msg)
{
	char	*str;

	str = "minishell: syntax error near unexpected token ";
	dprintf(STDERR_FILENO, "%s`%s'\n", str, msg);
	export_exists("?", "2");
	return (EXIT_FAILURE);
}

int	syntax_error(t_token *token_lst, t_cmd_lst *cmd_lst)
{
	t_cmd_lst	*lst;

	lst = cmd_lst;
	while (lst)
	{
		if ((!*lst->subcmd.cmd && lst->subcmd.in_type == VOID
				&& lst->subcmd.out_type == VOID)
			|| lst_last(token_lst)->type == PIPE)
			return (set_syntax_error("|"));
		if ((lst->subcmd.in_type == INPUT_REDIRECTION
				|| lst->subcmd.in_type == HEREDOC) && (!*lst->subcmd.in_file
				|| invalid_io_file_char(*lst->subcmd.in_file)))
		{
			if (invalid_io_file_char(*lst->subcmd.in_file))
				return (set_syntax_error(lst->subcmd.in_file));
			else
				return (set_syntax_error("newline"));
		}
		if ((lst->subcmd.out_type == OUTPUT_REDIRECTION
				|| lst->subcmd.out_type == APPEND) && (!*lst->subcmd.out_file
				|| invalid_io_file_char(*lst->subcmd.out_file)))
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