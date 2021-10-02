#include "../../includes/minishell.h"

t_data	g_data;

t_env_lst	*sort_env_lst(t_env_lst *lst)
{
	t_env_lst	*sort_i;
	t_env_lst	*sort_j;
	char		*temp_key;
	char		*temp_value;

	sort_i = lst;
	while (sort_i)
	{
		sort_j = sort_i->next;
		while (sort_j)
		{
			if (ft_strcmp(sort_i->key, sort_j->key) > 0)
			{
				temp_key = sort_i->key;
				temp_value = sort_i->value;
				sort_i->key = sort_j->key;
				sort_i->value = sort_j->value;
				sort_j->key = temp_key;
				sort_j->value = temp_value;
			}
			sort_j = sort_j->next;
		}
		sort_i = sort_i->next;
	}
	return (lst);
}

static int	ft_export_key(char *cmd, int fd_out)
{
	(void)fd_out;
	if (ft_isdigit(cmd[0]) == 1)
	{
		ft_dprintf(STDERR_FILENO, "export: `%s': not a valid identifier\n", cmd);
		return (1);
	}
	else if (ft_isalnum_str(cmd) == 0)
	{
		ft_dprintf(STDERR_FILENO, "export: `%s': not a valid identifier\n", cmd);
		return (1);
	}
	else if (export_exists_key(cmd) == 1)
		return (0);
	else
		return (ft_export_add(cmd, NULL));
	return (0);
}

int	ft_export(char **cmd, int fd_out)
{
	int	i;
	int	ret;

	(void)fd_out;
	if (cmd[1] == NULL)
		return (ft_export_noarg(fd_out));
	else
	{
		i = 1;
		while (cmd[i])
		{
			if (ft_cinstr(cmd[i], '=') == 1)
				ret = ft_export_eql(cmd[i], fd_out);
			else
				ret = ft_export_key(cmd[i], fd_out);
			if (ret != 0)
				return (ret);
			i++;
		}
	}
	return (0);
}
