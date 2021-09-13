#include "../../includes/minishell.h"

void	run_command(char **cmd)
{
	char	*path;
	
	// if (str_eql(*cmd, "echo")
	// 	ft_echo(cmd);
	// else if (str_eql(*cmd, "cd")
	// 	ft_cd(cmd);
	// else if (str_eql(*cmd, "pwd")
	// 	ft_pwd(cmd);
	// else if (str_eql(*cmd, "export")
	// 	ft_export(cmd);
	// else if (str_eql(*cmd, "unset")
	// 	ft_unset(cmd);
	// else if (str_eql(*cmd, "env")
	// 	ft_env(cmd);
	// else if (str_eql(*cmd, "exit")
	// 	ft_exit(cmd);
	// else
	// {
		path = get_path(*cmd);
		if (execve(path, cmd, NULL) == -1)
		{
			free (path);
			exit (EXIT_FAILURE);
		}
	// }
}

int	exec(t_cmd_lst *cmd_lst)
{
	pid_t	pid;
	int		p[2];
    int     read_pipe;
	int		stat_loc;
	int i;

    read_pipe = STDIN_FILENO;
	i = 0;
	while (cmd_lst)
	{
		if (pipe(p) == -1)
			perror("pipe error"); // temporary 
		pid = fork();
		if (pid == -1)
			perror("fork error"); // temporary
		if (pid == 0)
        {
            if (cmd_lst->next == NULL)
                p[1] = STDOUT_FILENO;
			set_redirection(read_pipe, p[1], cmd_lst->subcmd);
			run_command(cmd_lst->subcmd.cmd);
        }
		close (p[1]);
		read_pipe = p[0];
		cmd_lst = cmd_lst->next;
		i++;
	}
	while (i > 0)
	{
		wait(&stat_loc);
		//printf("Exitstatus:  %d\n", WEXITSTATUS(stat_loc));
		// for command not found error, perhaps hardcode error status
		i--;
	}
	return (read_pipe);
}