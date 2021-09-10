#include "../../includes/minishell.h"

char	*get_path(char *command)
{
	char	**paths;
	char	*path;
	int		i;

	// if (access(command, X_OK) == 0)
	// 	return (ft_strdup(command)); //means it already is the full path
	//paths = find_env_paths(envp);
    paths = ft_split(getenv("PATH"), ':');
    i = 0;
	command = ft_strjoin("/", command);
	i = 1;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], command);
		if (access(path, X_OK) == 0)
		{
			//free (command);
			//free_array(paths);
			return (path);
		}
		free (path);
		i++;
	}
	// command_not_found_error(command + 1);
	// free (command);
	// free_array(paths);
	exit (EXIT_FAILURE);
}

int	get_output(char *output_file)
{
	int		output_fd;

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

void	process(int input_fd, int output_fd, t_subcmd subcmd)
{
	char	*path;

    if (subcmd.in_type == INPUT_REDIRECTION) //look ino heredoc later
        input_fd = get_input(subcmd.in_file);
    if (subcmd.out_type == OUTPUT_REDIRECTION || subcmd.out_type == APPEND)
        output_fd = get_output(subcmd.out_file);
	if (dup2(output_fd, STDOUT_FILENO) == -1)
		perror("dup error"); // temporary 
	//close (output_fd);
	if (dup2(input_fd, STDIN_FILENO) == -1)
		perror("dup error"); // temporary 
	//close (input_fd);
	path = get_path(*subcmd.cmd);
	if (execve(path, subcmd.cmd, NULL) == -1)
	{

		free (path);
		exit (EXIT_FAILURE);
	}
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