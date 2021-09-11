#include "../../includes/minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
	{
		while (*s != '\0')
		{
			write(fd, s, 1);
			s++;
		}
	}
}

void	command_not_found_error(char *command)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
}

char	*get_path(char *command)
{
	char	**paths;
	char	*path;
	int		i;
	struct stat buf;

	if (lstat(command, &buf) == 0)
		return (ft_strdup(command)); //means it already is the full path
	//paths = find_env_paths(envp);
    paths = ft_split(getenv("PATH"), ':');
    i = 0;
	command = ft_strjoin("/", command);
	i = 1;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], command);
		if (stat(path, &buf) == 0)
		{
			//free (command);
			//free_array(paths);
			return (path);
		}
		free (path);
		i++;
	}
	command_not_found_error(command + 1);
	// free (command);
	// free_array(paths);
	exit (EXIT_FAILURE);
}

int	get_output(char *output_file, t_type type)
{
	int		output_fd;

	if (type == APPEND)
		output_fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (output_fd == -1)
		perror("couldn't open output_file");
	return (output_fd);
}

int	get_input(char *input_file)
{
	int		input_fd;

	input_fd = open(input_file, O_RDONLY);
	if (input_fd == -1)
		perror("input file does not exist");
	return (input_fd);
}

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

void	process(int input_fd, int output_fd, t_subcmd subcmd)
{
    if (subcmd.in_type == INPUT_REDIRECTION) //look ino heredoc later
        input_fd = get_input(subcmd.in_file);
    if (subcmd.out_type == OUTPUT_REDIRECTION || subcmd.out_type == APPEND)
        output_fd = get_output(subcmd.out_file, subcmd.out_type);
	if (dup2(output_fd, STDOUT_FILENO) == -1)
		perror("dup error"); // temporary 
	if (output_fd != STDOUT_FILENO)
		close (output_fd);
	if (dup2(input_fd, STDIN_FILENO) == -1)
		perror("dup error"); // temporary
	if (input_fd != STDIN_FILENO)
		close (input_fd);
	run_command(subcmd.cmd);
}

int	exec(t_cmd_lst *cmd_lst)
{
	pid_t	pid;
	int		p[2];
    int     read_pipe;

    read_pipe = STDIN_FILENO;
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
			process(read_pipe, p[1], cmd_lst->subcmd);
        }
		wait(0); // will need to be moved. look into later
		close (p[1]);
		read_pipe = p[0];
		cmd_lst = cmd_lst->next;
	}
	return (read_pipe);
}