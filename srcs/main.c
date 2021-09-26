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

void	print_env(t_env_lst *env_lst)
{
	printf("*********ENV LIST *********\n");
	while (env_lst)
	{
		printf("%s=%s\n", env_lst->key, env_lst->value);
		env_lst = env_lst->next;
	}
	printf("***************************\n");
	return ;
}

void	received_signal(int signal)
{
	int	i;

	i = 0;
	while (g_data.pids && g_data.pids[i] != 0)
	{
		printf("%d\n", i);
		kill(g_data.pids[i], signal);
		i++;
	}
	if (signal == SIGINT)
	{
		rl_replace_line("", 1);
		ft_dprintf(STDOUT_FILENO, "\n");
	}
	rl_on_new_line();
	rl_redisplay();
	//printf("received signal: %d\n", signal); // for testing
	clean_all(); //not the environment
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
			add_history(str); // an empty line should not be added to the history
		token = lexer(str);
		free (str);
		cmd_lst = parser(token);
		g_data.cmd_lst = cmd_lst;
		if (!cmd_lst)
			continue ;
		//print_cmd_lst(cmd_lst);
		expand(cmd_lst);
		//print_cmd_lst(cmd_lst);
		exec(cmd_lst);
		free_cmdlst();
	}
	return ;
}

int main(int argc, char **argv, char **env)
{
	(void)argv;
	if (argc != 1)
	{
		printf("Minishell should be run without arguments\n"); // send to stderr
		return (EXIT_FAILURE);
	}
	signal(SIGINT, received_signal);
	signal(SIGQUIT, received_signal); 
	g_data.env_lst = ft_getenv(env);
	// if (isatty(STDIN_FILENO))
	// 	printf("\n\033[1m\033[36mWelcome to Isaac's and Lindsay's minishell!\n\033[0m");
	prompt_loop();
	//print_env(g_data.env_lst);
	//printf("\n\033[1m\033[36mBye, come again!\n\033[0m");
	//system ("leaks minishell");
	return (0);
}