/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/02 18:18:55 by lwray         #+#    #+#                 */
/*   Updated: 2021/10/02 18:18:57 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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

void	give_subcmd_content(t_subcmd *subcmd, t_token *token, int *i)
{
	int	fd;

	if (token->type == WORD)
	{
		subcmd->cmd[*i] = ft_strdup(token->content);
		(*i)++;
	}
	if (token->type == INPUT_REDIRECTION || token->type == HEREDOC)
	{
		free (subcmd->in_file);
		subcmd->in_type = token->type;
		subcmd->in_file = ft_strdup(token->content);
	}
	if (token->type == OUTPUT_REDIRECTION || token->type == APPEND)
	{
		if (subcmd->out_file)
		{
			fd = open(subcmd->out_file, O_WRONLY | O_CREAT, 0644);
			close(fd);
			free (subcmd->out_file);
		}
		subcmd->out_type = token->type;
		subcmd->out_file = ft_strdup(token->content);
	}
}

t_cmd_lst	*parse_commands(t_token **token, t_cmd_lst *cmd_lst)
{
	t_subcmd	subcmd;
	int			i;

	i = 0;
	set_default(&subcmd, *token);
	while (*token && (*token)->type != PIPE)
	{
		give_subcmd_content(&subcmd, *token, &i);
		*token = (*token)->next;
	}
	subcmd.cmd[i] = NULL;
	cmd_lst_add_back(&cmd_lst, cmd_lst_new(subcmd));
	return (cmd_lst);
}

t_cmd_lst	*parser(t_token *token_lst)
{
	t_cmd_lst	*cmd_lst;
	t_token		*token;

	token = token_lst;
	cmd_lst = NULL;
	while (token)
	{
		cmd_lst = parse_commands(&token, cmd_lst);
		if (token)
			token = token->next;
	}
	if (syntax_error(token_lst, cmd_lst))
	{
		free_cmdlst(cmd_lst);
		cmd_lst = NULL;
	}
	lst_clear(&token_lst);
	return (cmd_lst);
}
