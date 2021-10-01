#include "../includes/minishell.h"

t_data	g_data;

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

void	prompt_loop(void)
{
	char	*str;
	t_token	*token;
	t_cmd_lst	*cmd_lst;

	while (true)
	{
		str = readline("=^..^= ");
		if (!str)
			break ;	
		if (*str)
			add_history(str);
		token = lexer(str);
		free (str);
		// t_token *token_list = token;
		// while(token_list)
		// {
		// 	printf("TOKEN:  %s\n", token_list->content);
		// 	token_list = token_list->next;
		// }
		cmd_lst = parser(token);
		//system ("leaks minishell");
		g_data.cmd_lst = cmd_lst;
		if (!cmd_lst)
			continue ;
		// print_cmd_lst(cmd_lst);
		expand(cmd_lst);
		// print_cmd_lst(cmd_lst);
		exec(cmd_lst);
		free_cmdlst();
	}
	return ;
}

int main(int argc, char **argv, char **env)
{
	struct termios termios_p;

	(void)argv;
	if (argc != 1)
	{
		ft_dprintf(STDERR_FILENO, "Minishell should run without arguments\n");
		return (EXIT_FAILURE);
	}
	signal(SIGINT, received_signal);
	signal(SIGQUIT, received_signal); 
	g_data.env_lst = ft_getenv(env);
	// if (isatty(STDIN_FILENO))
	// 	printf("\n\033[1m\033[36mWelcome to Isaac's and Lindsay's minishell!\n\033[0m");
	tcgetattr(STDIN_FILENO, &termios_p);
	termios_p.c_lflag = termios_p.c_lflag & ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &termios_p);
	prompt_loop();
	ft_dprintf(STDERR_FILENO, "exit\n");
	// if (isatty(STDIN_FILENO))
	// 	printf("\n\033[1m\033[36mBye, come again!\n\033[0m");
	clean_all();
	system ("leaks minishell | grep 'leaked bytes'");
	return (0);
}