#include "../includes/minishell.h"

int main()
{
	char *str;
	t_token	*token;
	t_cmd_lst	*cmd_lst;

	while (true)
	{
		str = readline("our minishell prompt: ");
		if (!str)
			exit(EXIT_SUCCESS);	// when ctrl D is typed, the shell needs to exit
		if (*str)
			add_history(str); // an empty line should not be added to the history
		token = lexer(str);
		cmd_lst = parser(token);
		// while(token)
		// {
		// 	printf("TOKEN:  %s, %d\n", token->content, token->type);
		// 	token = token->next;
		// }
		// printf("you typed: %s\n", str);
		free (str);
		while (cmd_lst)
		{
			printf("in_type: %d\n", cmd_lst->subcmd.in_type);
			if (cmd_lst->subcmd.in_type != VOID)
				printf("infile: %s\n", cmd_lst->subcmd.in_file);
			printf("out_type: %d\n", cmd_lst->subcmd.out_type);
			if (cmd_lst->subcmd.out_type != VOID)
				printf("outfile: %s\n", cmd_lst->subcmd.out_file);
			while (*cmd_lst->subcmd.cmd)
			{
				printf("%s, ", *cmd_lst->subcmd.cmd);
				cmd_lst->subcmd.cmd++;
			}
			printf("\n\n");
			cmd_lst = cmd_lst->next;
		}
	}
	return (0);
}