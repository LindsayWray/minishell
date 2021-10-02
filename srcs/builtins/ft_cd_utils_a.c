#include "../../includes/minishell.h"

void	ft_cd_a(char **cmd)
{
	char	*temp_str;

	if (cmd[1][0] == '~')
	{
		cmd[1]++;
		temp_str = ft_strjoin((ft_get_env_var("HOME"))->value, cmd[1]);
		cmd[1]--;
		free(cmd[1]);
		cmd[1] = temp_str;
	}
	return ;
}

void	ft_cd_b(int *ret, int *msg, int fd_out)
{
	t_env_lst	*temp;

	temp = ft_get_env_var("OLDPWD");
	if (!temp)
	{
		*msg = 1;
		ft_dprintf(fd_out, "cd: OLDPWD not set\n");
		*ret = 1;
	}
	else
	{
		if (!(temp->value))
		{
			*msg = 1;
			ft_dprintf(fd_out, "cd: OLDPWD not set\n");
			*ret = 1;
		}
		else
		{
			*ret = chdir(temp->value);
			ft_dprintf(fd_out, "%s\n", temp->value);
		}
	}
	return ;
}

void	ft_cd_c(char **cmd, char *oldpwd, int msg, int *ret)
{
	if (!msg)
	{
		if (errno == ENOTDIR)
			ft_dprintf(STDERR_FILENO, "cd: %s: Not a directory\n", cmd[1]);
		else if (ft_strlen(cmd[1]) > PATH_MAX)
			ft_dprintf(STDERR_FILENO, \
			"cd: %s: File name too long\n", cmd[1]);
		else if (errno == ENOENT)
		{
			ft_dprintf(STDERR_FILENO, \
			"cd: %s: No such file or directory\n", cmd[1]);
			*ret = 1;
		}
	}
	free(oldpwd);
	return ;
}
