#include "../../includes/minishell.h"

//************ fake functions in order to compile 
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
//*********** end of fake functions


void	wait_for_childprocesses(int *pids, int len)
{
	int		stat_loc;
	int j;

	j = 0;
	while (j < len)
	{
		waitpid(pids[j], &stat_loc, 0);
			// printf("Exitstatus:  %d\n", WEXITSTATUS(stat_loc));
			// for command not found error, perhaps hardcode error status
		j++;
	}
	free (pids);
}

int	is_builtin(char *cmd)
{
	static char	*str[7] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	int			i;
	
	i = 0;
	while (i < 7)
	{
		if (ft_streql(cmd, str[i]))
			return (i);
		i++;
	}
	return (-1);
}

pid_t	run_builtin(int in_fd, int out_fd, t_cmd_lst *cmd_lst)
{
	pid_t	pid;
	int		exit_status;
	static void (*builtin_func[7])(char **, int) = {ft_echo, ft_cd, ft_pwd, ft_export, ft_unset, ft_env, ft_exit};
	int i;
			
	if (cmd_lst->next == NULL)
		out_fd = STDOUT_FILENO;
	set_redirection(&in_fd, &out_fd, cmd_lst->subcmd);
	i = is_builtin(*cmd_lst->subcmd.cmd);
	exit_status = 0; // will be the return value of the builtin_func
	builtin_func[i](cmd_lst->subcmd.cmd, out_fd);
	pid = fork();
	if (pid == -1)
		perror("fork error"); // temporary
	if (pid == 0)
		exit(exit_status);
	return (pid);
}

pid_t	run_command_in_childprocess(int in_fd, int out_fd, t_cmd_lst *cmd_lst, char **env)
{
	pid_t	pid;
	char	*path;

	pid = fork();
	if (pid == -1)
		perror("fork error"); // temporary
	if (pid == 0)
	{
		if (cmd_lst->next == NULL)
			out_fd = STDOUT_FILENO;
		set_redirection(&in_fd, &out_fd, cmd_lst->subcmd);
		dup_fd(in_fd, out_fd);
		path = get_path(*cmd_lst->subcmd.cmd);
		if (execve(path, cmd_lst->subcmd.cmd, env) == -1)
		{
			free (path);
			exit (EXIT_FAILURE);
		}
	}
	return (pid);
}

void	exec(t_cmd_lst *cmd_lst, char **env)
{
	int		p[2];
    int     read_pipe;
	int		*pids;
	int		i;

	pids = malloc(lst_size(cmd_lst) * sizeof(pid_t));
    read_pipe = STDIN_FILENO;
	i = 0;
	while (cmd_lst)
	{
		if (pipe(p) == -1)
			perror("pipe error"); // temporary 
		if (is_builtin(*cmd_lst->subcmd.cmd) != -1)
			pids[i] = run_builtin(read_pipe, p[1], cmd_lst);
		else
			pids[i] = run_command_in_childprocess(read_pipe, p[1], cmd_lst, env);
		close (p[1]);
		read_pipe = p[0];
		cmd_lst = cmd_lst->next;
		i++;
	}
	wait_for_childprocesses(pids, i);
	cmd_lst_clear(&cmd_lst);
}