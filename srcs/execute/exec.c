#include "../../includes/minishell.h"

int	is_builtin(char *cmd)
{
	static char *str[7] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	int i;
	
	i = 0;
	while (i < 7)
	{
		if (ft_streql(cmd, str[i]))
			return (i);
		i++;
	}
	return (-1);
}

// fake functions in order to compile 
void	ft_echo(char **cmd, int fd_out)
{
	(void)cmd;
	write (fd_out, "My echo\n", 8);
}
void	ft_cd(char **cmd, int fd_out)
{
	(void)cmd;
	(void)fd_out;
}
void	ft_pwd(char **cmd, int fd_out)
{
	(void)cmd;
	(void)fd_out;
}
void	ft_export(char **cmd, int fd_out)
{
	(void)cmd;
	(void)fd_out;
}
void	ft_unset(char **cmd, int fd_out)
{
	(void)cmd;
	(void)fd_out;
}
void	ft_env(char **cmd, int fd_out)
{
	(void)cmd;
	(void)fd_out;
}
void	ft_exit(char **cmd, int fd_out)
{
	(void)cmd;
	(void)fd_out;
}

void	run_builtin(char **cmd, int fd_out)
{
	static void (*func[7])(char **, int) = {ft_echo, ft_cd, ft_pwd, ft_export, ft_unset, ft_env, ft_exit};
	int i;

	i = is_builtin(*cmd);
	func[i](cmd, fd_out);
}

void	run_command(char **cmd, char **env)
{
	char	*path;
	
	path = get_path(*cmd);
	if (execve(path, cmd, env) == -1)
	{
		free (path);
		exit (EXIT_FAILURE);
	}
}

int	exec(t_cmd_lst *cmd_lst, char **env)
{
	pid_t	pid;
	int		p[2];
    int     read_pipe;
	int		stat_loc;
	int		*pids;
	int i;

	pids = malloc(lst_size(cmd_lst) * sizeof(pid_t));
    read_pipe = STDIN_FILENO;
	i = 0;
	while (cmd_lst)
	{
		if (pipe(p) == -1)
			perror("pipe error"); // temporary 
		if (is_builtin(*cmd_lst->subcmd.cmd) == -1)
		{
			pid = fork();
			if (pid == -1)
				perror("fork error"); // temporary
			pids[i] = pid;
			if (pid == 0)
        	{
            	if (cmd_lst->next == NULL)
                	p[1] = STDOUT_FILENO;
			set_redirection(&read_pipe, &p[1], cmd_lst->subcmd);
			dup_fd(read_pipe, p[1]);
			run_command(cmd_lst->subcmd.cmd, env);
			}
    	}
		else
		{
			if (cmd_lst->next == NULL)
                p[1] = STDOUT_FILENO;
			set_redirection(&read_pipe, &p[1], cmd_lst->subcmd);
			run_builtin(cmd_lst->subcmd.cmd, p[1]);
			pids[i] = 0; // temporary fix. Needs different solution
		}
		close (p[1]);
		read_pipe = p[0];
		cmd_lst = cmd_lst->next;
		i++;
	}
	int j = 0;
	while (j < i)
	{
		if (pids[j])
		{
			waitpid(pids[j], &stat_loc, 0);
			printf("Exitstatus:  %d\n", WEXITSTATUS(stat_loc));
			// for command not found error, perhaps hardcode error status
		}
		j++;
	}
	free (pids);
	cmd_lst_clear(&cmd_lst);
	return (read_pipe);
}