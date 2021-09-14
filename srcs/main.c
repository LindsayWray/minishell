#include "../includes/minishell.h"

void	print_cmd_lst(t_cmd_lst *cmd_lst)
{
	while (cmd_lst)
	{
		printf("\n***COMMAND***\n");
		printf("in_type: %d\n", cmd_lst->subcmd.in_type);
		if (cmd_lst->subcmd.in_type != VOID)
			printf("infile: %s\n", cmd_lst->subcmd.in_file);
		printf("out_type: %d\n", cmd_lst->subcmd.out_type);
		if (cmd_lst->subcmd.out_type != VOID)
			printf("outfile: %s\n", cmd_lst->subcmd.out_file);
		int i = 0;
		while (cmd_lst->subcmd.cmd[i])
		{
			printf("%s,", cmd_lst->subcmd.cmd[i]);
			i++;
		}
		cmd_lst = cmd_lst->next;
		printf("\n************\n\n");
	}
}

int main(int argc, char **argv, char **env)
{
	char *str;
	t_token	*token;
	t_cmd_lst	*cmd_lst;
	t_env_lst	*env_lst;

	(void)argv;
	if (argc != 1)
	{
		printf("Minishell should be run without arguments\n"); // send to stderr
		return (EXIT_FAILURE);
	}
	env_lst = ft_getenv(env);
	// if (isatty(STDIN_FILENO))
	// 	printf("\n\033[1m\033[36mWelcome to Isaac's and Lindsay's minishell!\n\033[0m");
	while (true)
	{
		str = readline("=^..^= ");
		if (!str || ft_streql(str, "exit")) // temporary for the tester
			break ;
		if (*str)
			add_history(str); // an empty line should not be added to the history
		token = lexer(str);
		cmd_lst = parser(token);
		free (str);
		//print_cmd_lst(cmd_lst);
		exec(cmd_lst, env);
	}
	//printf("\n\033[1m\033[36mBye, come again!\n\033[0m");
	return (0);
}