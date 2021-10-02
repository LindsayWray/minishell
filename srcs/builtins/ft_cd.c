#include "../../includes/minishell.h"

t_data	g_data;

static void	ft_cd_change_value(char *path, t_env_lst *temp)
{
	if (temp->value == NULL)
		temp->value = path;
	else
	{
		free(temp->value);
		temp->value = path;
	}
	return ;
}

static void	ft_cd_update_pwd(void)
{
	t_env_lst	*temp;
	char		*path;
	char		*key;

	path = malloc(PATH_MAX);
	getcwd(path, PATH_MAX);
	temp = ft_get_env_var("PWD");
	if (!temp)
	{
		key = ft_strdup("PWD");
		temp = env_lst_new(key, path);
		env_lst_add_back(&(g_data.env_lst), temp);
	}
	else
		ft_cd_change_value(path, temp);
	return ;
}

static void	ft_cd_update_oldpwd(char *oldpwd)
{
	t_env_lst	*temp;
	char		*key;

	temp = ft_get_env_var("OLDPWD");
	if (!temp)
	{
		key = ft_strdup("OLDPWD");
		temp = env_lst_new(key, oldpwd);
		env_lst_add_back(&(g_data.env_lst), temp);
	}
	else
		ft_cd_change_value(oldpwd, temp);
	return ;
}

static char	*ft_get_path(void)
{
	char	*path;

	path = malloc(PATH_MAX);
	getcwd(path, PATH_MAX);
	return (path);
}

int	ft_cd(char **cmd, int fd_out)
{
	int			ret;
	char		*oldpwd;
	char		*temp_str;
	t_env_lst	*temp;
	int			msg;

	msg = 0;
	oldpwd = ft_get_path();
	if (cmd[1] != NULL)
	{
		if (cmd[1][0] == '~')
		{
			cmd[1]++;
			temp_str = ft_strjoin((ft_get_env_var("HOME"))->value, cmd[1]);
			cmd[1]--;
			free(cmd[1]);
			cmd[1] = temp_str;
		}
	}
	if (cmd[1] == NULL)
		ret = chdir(getenv("HOME"));
	else if (ft_strlen(cmd[1]) == 1 && cmd[1][0] == '-')
	{
		temp = ft_get_env_var("OLDPWD");
		if (!temp)
		{
			msg = 1;
			ft_dprintf(fd_out, "cd: OLDPWD not set\n");
			ret = 1;
		}
		else
		{
			if (!(temp->value))
			{
				msg = 1;
				ft_dprintf(fd_out, "cd: OLDPWD not set\n");
				ret = 1;
			}
			else
			{
				ret = chdir(temp->value);
				ft_dprintf(fd_out, "%s\n", temp->value);
			}
		}
	}
	else
		ret = chdir(cmd[1]);
	if (ret != 0)
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
				ret = 1;
			}
		}
		free(oldpwd);
	}
	else
	{
		ft_cd_update_oldpwd(oldpwd);
		ft_cd_update_pwd();
	}
	return (ret);
}
