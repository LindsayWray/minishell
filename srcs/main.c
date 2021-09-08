#include "../includes/minishell.h"

int main()
{
	char *str;
	t_node	*token_list;
	while (true)
	{
		str = readline("our minishell prompt: ");
		if (!str)
			exit(EXIT_SUCCESS);	// when ctrl D is typed, the shell needs to exit
		if (*str)
			add_history(str); // an empty line should not be added to the history
		token_list = lexer(str);
		while(token_list)
		{
			printf("TOKEN:  %s\n", token_list->token.content);
			token_list = token_list->next;
		}
		printf("you typed: %s\n", str);
		free (str);
	}
	return (0);
}