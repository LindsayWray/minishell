#include "../../includes/minishell.h"

t_data	g_data;

void	wait_for_childprocesses(int *pids, int len)
{
	int		stat_loc;
	char	*exit_status;
	int j;

	j = 0;
	while (j < len)
	{
		waitpid(pids[j], &stat_loc, 0);
		if (WIFEXITED(stat_loc))
		{
			exit_status = ft_itoa(WEXITSTATUS(stat_loc));
			export_exists("?", exit_status);
		}
		j++;
	}
	free (pids);
	g_data.pids = NULL;
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
		system_error("Fork Error");
	if (pid == 0)
		exit(exit_status);
	return (pid);
}

pid_t	run_command_in_childprocess(int in_fd, int out_fd, t_cmd_lst *cmd_lst, int p)
{
	pid_t	pid;
	char	*path;

	pid = fork();
	if (pid == -1)
		system_error("Fork Error");
	if (pid == 0)
	{
		if (cmd_lst->next == NULL)
			out_fd = STDOUT_FILENO;
		if (set_redirection(&in_fd, &out_fd, cmd_lst->subcmd))
			exit (EXIT_FAILURE);
		dup_fd(in_fd, out_fd);
		close (p);
		path = get_path(*cmd_lst->subcmd.cmd);
		if (execve(path, cmd_lst->subcmd.cmd, ft_envlst_to_array(g_data.env_lst)) == -1)
		{
			// free env_array
			free (path);
			exit (EXIT_FAILURE);
		}
	}
	return (pid);
}

void	exec(t_cmd_lst *cmd_lst)
{
	int		p[2];
    int     read_pipe;
	int		i;
	
	g_data.pids = malloc(lst_size(cmd_lst) * sizeof(pid_t));
	if (!g_data.pids)
		system_error("Malloc Error");
    read_pipe = STDIN_FILENO;
	i = 0;
	while (cmd_lst->next)
	{
		if (pipe(p) == -1)
			system_error("Pipe Error");
		if (is_builtin(*cmd_lst->subcmd.cmd) != -1)
			g_data.pids[i] = run_builtin(read_pipe, p[1], cmd_lst);
		else
			g_data.pids[i] = run_command_in_childprocess(read_pipe, p[1], cmd_lst, p[0]);
		close (p[1]);
		if (read_pipe != STDIN_FILENO)
			close (read_pipe);
		read_pipe = p[0];
		cmd_lst = cmd_lst->next;
		i++;
	}
	if (is_builtin(*cmd_lst->subcmd.cmd) != -1)
		g_data.pids[i] = run_builtin(read_pipe, STDOUT_FILENO, cmd_lst);
	else
		g_data.pids[i] = run_command_in_childprocess(read_pipe, STDOUT_FILENO, cmd_lst, p[0]);
	if (read_pipe != STDIN_FILENO)
		close (read_pipe);
	i++;
	g_data.pids[i] = 0;
	i++;
	wait_for_childprocesses(g_data.pids, i - 1);
}
