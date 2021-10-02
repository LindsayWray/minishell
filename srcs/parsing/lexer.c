/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/02 18:18:47 by lwray         #+#    #+#                 */
/*   Updated: 2021/10/02 18:18:49 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_data	g_data;

void	new_token(char *content, t_token **token, t_type type)
{
	if ((!content || !*content) && type == WORD)
		return ;
	if (!lst_add_back(token, lst_new(content, type)))
		system_error("Malloc Error");
}

void	handle_redirections(char *str, int *i, t_token **token)
{
	t_type	type;
	int		start;

	if (str[*i] == '<')
		type = INPUT_REDIRECTION;
	if (str[*i] == '<' && str[(*i) + 1] == '<')
		type = HEREDOC;
	if (str[*i] == '>')
		type = OUTPUT_REDIRECTION;
	if (str[*i] == '>' && str[(*i) + 1] == '>')
		type = APPEND;
	(*i)++;
	if (type == HEREDOC || type == APPEND)
		(*i)++;
	while (is_whitespace(str[*i]))
		(*i)++;
	start = *i;
	while (!is_whitespace(str[*i]) && str[*i] != '\0')
		(*i)++;
	new_token(ft_substr(str, start, (*i) - start), token, type);
}

t_token	*lexer(char *str)
{
	int	i;
	int	start;

	g_data.token = NULL;
	i = 0;
	while (str[i] != '\0')
	{
		start = i;
		while (str[i] != '|' && str[i] != '<' && str[i] != '>'
			&& !is_whitespace(str[i]) && str[i] != '\0')
			skip_over_quotes(str, &i);
		if (start != i)
			new_token(ft_substr(str, start, i - start), &g_data.token, WORD);
		if (str[i] == '|')
		{
			if (!lst_add_back(&g_data.token, lst_new(NULL, PIPE)))
				system_error("Malloc Error");
		}
		if (str[i] == '<' || str[i] == '>')
			handle_redirections(str, &i, &g_data.token);
		i++;
	}
	return (g_data.token);
}
