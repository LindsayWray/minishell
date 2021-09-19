#include "../../includes/minishell.h"

//************ fake functions in order to compile 
int	ft_echo(char **cmd, int fd_out)
{
	(void)cmd;
	write (fd_out, "My echo\n", 8);
	return (0);
}

int	ft_exit(char **cmd, int fd_out)
{
	(void)cmd;
	(void)fd_out;
	return (0);
}
//*********** end of fake functions


void	wait_for_childprocesses(int *pids, int len)
{
	int		stat_loc;
	char	*exit_status;
	int j;

	j = 0;
	while (j < len)
	{
		waitpid(pids[j], &stat_loc, 0);
		printf("Exitstatus:  %d      %d\n", WEXITSTATUS(stat_loc), WTERMSIG(stat_loc));
		j++;
	}
	printf("children are dead\n");
	exit_status = ft_itoa(WEXITSTATUS(stat_loc)); // does a %256 on statloc
	export_exists("?", exit_status); // is created in ft_getenv to give it value before first command
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
	static int (*builtin_func[7])(char **, int) = {ft_echo, ft_cd, ft_pwd, ft_export, ft_unset, ft_env, ft_exit};
	int i;
			
	if (cmd_lst->next == NULL)
		out_fd = STDOUT_FILENO;
	if (!set_redirection(&in_fd, &out_fd, cmd_lst->subcmd))
	{
		i = is_builtin(*cmd_lst->subcmd.cmd);
		exit_status = builtin_func[i](cmd_lst->subcmd.cmd, out_fd);
	}
	else
		exit_status = EXIT_FAILURE;
	pid = fork();
	if (pid == -1)
		perror("fork error"); // temporary
	if (pid == 0)
		exit(exit_status);
	return (pid);
}

pid_t	run_command_in_childprocess(int in_fd, int out_fd, t_cmd_lst *cmd_lst, char **env, int p)
{
	pid_t	pid;
	char	*path;

	pid = fork();
	if (pid == -1)
		perror("fork error"); // temporary
	if (pid == 0)
	{
		close (p);
		if (cmd_lst->next == NULL)
			out_fd = STDOUT_FILENO;
		if (set_redirection(&in_fd, &out_fd, cmd_lst->subcmd))
			exit (EXIT_FAILURE);
		dup_fd(in_fd, out_fd);
		path = get_path(*cmd_lst->subcmd.cmd);
		if (execve(path, cmd_lst->subcmd.cmd, env) == -1)
		{
			free (path);
			exit (EXIT_FAILURE);
		}
	}
	close (p);
	//close (in_fd);
	close (out_fd);
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
			perror("pipe error"); // still need to free and exit
		if (is_builtin(*cmd_lst->subcmd.cmd) != -1)
			pids[i] = run_builtin(read_pipe, p[1], cmd_lst);
		else
			pids[i] = run_command_in_childprocess(read_pipe, p[1], cmd_lst, env, p[0]);
		close (p[1]);
		read_pipe = p[0];
		cmd_lst = cmd_lst->next;
		i++;
	}
	wait_for_childprocesses(pids, i);
	cmd_lst_clear(&cmd_lst);
}
