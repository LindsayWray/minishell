/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: idonado <idonado@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/04 14:37:33 by idonado       #+#    #+#                 */
/*   Updated: 2021/10/06 18:37:03 by idonado       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_data	g_data;

void	terminal_settings(void)
{
	struct termios	termios_p;

	tcgetattr(STDIN_FILENO, &termios_p);
	termios_p.c_lflag = termios_p.c_lflag & ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &termios_p);
}

void	prompt_loop(void)
{
	char		*str;
	t_token		*token;
	t_cmd_lst	*cmd_lst;

	while (true)
	{
		str = NULL;
		str = readline("=^..^= ");
		if (!str)
			break ;
		if (*str)
			add_history(str);
		token = lexer(str);
		free (str);
		cmd_lst = parser(token);
		g_data.cmd_lst = cmd_lst;
		if (!cmd_lst)
			continue ;
		expand(cmd_lst);
		exec(cmd_lst);
		free_cmdlst(cmd_lst);
		g_data.cmd_lst = NULL;
	}
	return ;
}

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	if (argc != 1)
	{
		ft_dprintf(STDERR_FILENO, "Minishell should run without arguments\n");
		return (EXIT_FAILURE);
	}
	signal(SIGINT, received_signal);
	signal(SIGQUIT, received_signal);
	g_data.env_lst = ft_getenv(env);
	if (export_exists("?", "0") == 0)
		ft_export_add("?", "0");
	if (isatty(STDIN_FILENO))
		printf("\n%sWelcome to Isaac's and Lindsay's minishell!\n%s",
			BLUE, RESET);
	terminal_settings();
	prompt_loop();
	ft_dprintf(STDERR_FILENO, "exit\n");
	clean_all();
	if (isatty(STDIN_FILENO))
		printf("\n%sBye, come again!\n%s", BLUE, RESET);
	return (0);
}
