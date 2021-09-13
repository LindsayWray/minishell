#include "../includes/minishell.h"

void	new_token(char *str, int i, int start, t_token **token, t_type type)
{
	char *content;

	content = ft_substr(str, start, i - start);
	if (!content)
		lst_clear(token); //add error message
	if (!lst_add_back(token, lst_new(content, type)))
		lst_clear(token); //add error message
}

void	handle_quotes(char * str, int *i)
{
	if (str[*i] == '"')
	{
		(*i)++;
		while (str[*i] != '"' && str[*i] != '\0')
			(*i)++;
	}
	if (str[*i] == '\'')
	{
		(*i)++;
		while (str[*i] != '\'' && str[*i] != '\0')
			(*i)++;
	}
	(*i)++;
}

void	handle_redirections(char *str, int *i, t_token **token)
{
	t_type	type;
	int		start;

	if (str[*i] == '<')
	{
		if (str[(*i) + 1] == '<')
			type = HEREDOC;
		else
			type = INPUT_REDIRECTION;
	}
	if (str[*i] == '>')
	{
		if (str[(*i) + 1] == '>')
			type = APPEND;
		else
			type = OUTPUT_REDIRECTION;
	}
	(*i)++;
	if (type == HEREDOC || type == APPEND)
		(*i)++;
	while (str[*i] == ' ')
		(*i)++;
	start = *i;
	while (str[*i] != ' ' && str[*i] != '\0')
		(*i)++;
	new_token(str, *i, start, token, type);
}

t_token	*lexer(char *str)
{
	int i;
	int start;
	t_token *token;

	token = NULL;
	i = 0;
	while (str[i] != '\0')
	{
		start = i;
		while (str[i] != '|' && str[i] != '<' && str[i] != '>' && str[i] != ' ' && str[i] != '\0')
			handle_quotes(str, &i);
		if (start != i) // this condition prevents empty tokens
			new_token(str, i, start, &token, WORD);
		if (str[i] == '|')
		{
			if (!lst_add_back(&token, lst_new(NULL, PIPE)))
				lst_clear(&token); //add error message
		}
		if (str[i] == '<' || str[i] == '>')
			handle_redirections(str, &i, &token);
		i++;
	}
	return (token);
}