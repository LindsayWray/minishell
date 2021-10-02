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
	int			msg;

	msg = 0;
	oldpwd = ft_get_path();
	if (cmd[1] != NULL)
		ft_cd_a(cmd);
	if (cmd[1] == NULL)
		ret = chdir(getenv("HOME"));
	else if (ft_strlen(cmd[1]) == 1 && cmd[1][0] == '-')
		ft_cd_b(&ret, &msg, fd_out);
	else
		ret = chdir(cmd[1]);
	if (ret != 0)
		ft_cd_c(cmd, oldpwd, msg, &ret);
	else
	{
		ft_cd_update_oldpwd(oldpwd);
		ft_cd_update_pwd();
	}
	return (ret);
}
