#include "../../includes/minishell.h"

t_data	g_data;// delete this

static int	exit_code_result(void)
{
	int	exit_code;

	if (ft_get_env_var("?") != NULL)
		exit_code = ft_atoi((ft_get_env_var("?"))->value);
	else
		exit_code = 0;
	if (exit_code > 255)
		exit_code = exit_code % 256;
	return (exit_code);
}

int	ft_exit(char **cmd, int fd_out)
{
	if (!cmd[1])
	{
		// Do something with last exit code
		//the exit code if its > 255
		//then its exit code = exit code % 256
		// free everything before exit but free 
		//within exit_code_result because you'll 
		//need the environment linked list
		if (g_data.cmd_lst->next == NULL)
			exit(exit_code_result());
		else
			return (exit_code_result());
	}
	else if (cmd[1])
	{
		if (cmd[2])
		{
			if (ft_isdigit_str(cmd[1]) == 1)
			{
				ft_dprintf(fd_out, "exit\nminishell: exit: too many arguments\n");
				return (1);
			}
			else
			{
				ft_dprintf(fd_out, \
				"exit\nminishell: exit: %s: numeric argument required\n", cmd[1]);
				//free everything before exit
				if (g_data.cmd_lst->next == NULL)
					exit(255);
				else
					return (255);
			}
		}
		if (ft_isdigit_str(cmd[1]) == 0)
		{
			ft_dprintf(fd_out, \
			"exit\nminishell: exit: %s: numeric argument required\n", cmd[1]);
			//free everything before exit
			if (g_data.cmd_lst->next == NULL)
				exit(255);
			else
				return (255);
		}
		else
		{
			//free everything before exit
			if (g_data.cmd_lst->next == NULL)
			{
				if (ft_atoi(cmd[1]) > 255)
					exit(ft_atoi(cmd[1]) % 256);
				exit(ft_atoi(cmd[1]));
			}
			else
			{
				if (ft_atoi(cmd[1]) > 255)
					return (ft_atoi(cmd[1]) % 256);
				return (ft_atoi(cmd[1]));
			}
		}
	}
	return (0);
}
