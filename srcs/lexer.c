#include "../includes/minishell.h"

t_node	*lexer(char *str)
{
	int i;
	int start;
	t_token	token;
	t_node *token_list;

	token_list = NULL;
	i = 0;
	while (str[i] != '\0')
	{
		start = i;
		while (str[i] != '|' && str[i] != '<' && str[i] != '>' && str[i] != '\0')
		{
			if (str[i] == '"')
			{
				i++;
				while (str[i] != '"' && str[i] != '\0')
				i++;
			}
			if (str[i] == '\'')
			{
				i++;
				while (str[i] != '\'' && str[i] != '\0')
				i++;
			}
			i++;
		}
		
		token.content = ft_substr(str, start, i - start);
		if (!token.content)
			return (NULL);
		if (i != 0 && start != i)
		{
			token.type = COMMAND; 
			lst_add_back(&token_list, lst_new(token));
		}
		if (str[i] == '|')
		{
			token.type = PIPE;
			token.content = NULL;
			lst_add_back(&token_list, lst_new(token));
			i++;
		}
		if (str[i] == '<' || str[i] == '>')
		{
			if (str[i] == '<' && str[i + 1] != '<')
				token.type = INPUT_REDIRECTION;
			if (str[i] == '>' && str[i + 1] != '>')
				token.type = OUTPUT_REDIRECTION;
			i++;
			if (str[i] == '<')
			{
				token.type = HEREDOC;
				i++;
			}
			if (str[i] == '>')
			{
				token.type = APPEND;
				i++;
			}
			while (str[i] == ' ')
				i++;
			start = i;
			while (str[i] != ' ' && str[i] != '\0')
				i++;
			token.content = ft_substr(str, start, i - start);
			if (!token.content)
				return (NULL);
			lst_add_back(&token_list, lst_new(token));
			i++;
		}
	}
	return (token_list);
}