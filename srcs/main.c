#include "../includes/minishell.h"

int main()
{
	char *str;
	t_node	*token;
	while (true)
	{
		str = readline("our minishell prompt: ");
		if (!str)
			exit(EXIT_SUCCESS);	// when ctrl D is typed, the shell needs to exit
		if (*str)
			add_history(str); // an empty line should not be added to the history
		token = lexer(str);
		while(token)
		{
			printf("TOKEN:  %s, %d\n", token->content, token->type);
			token = token->next;
		}
		printf("you typed: %s\n", str);
		free (str);
	}
	return (0);
}