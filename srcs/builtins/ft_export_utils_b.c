#include "../../includes/minishell.h"

static int	ft_export_eql_a(char **temp)
{
	ft_dprintf(STDERR_FILENO, \
	"export: `%s': not a valid identifier\n", temp[0]);
	ft_free_array(temp);
	return (1);
}

static int	ft_export_eql_b(char **temp)
{
	ft_dprintf(STDERR_FILENO, \
	"export: `%s=%s': not a valid identifier\n", temp[0], temp[1]);
	ft_free_array(temp);
	return (1);
}

static int	ft_export_eql_c(char **temp)
{
	int	ret;

	ret = ft_export_add(temp[0], temp[1]);
	ft_free_array(temp);
	return (ret);
}

int	ft_export_eql(char *cmd, int fd_out)
{
	char	**temp;

	(void)fd_out;
	if (cmd[0] == '=')
	{
		ft_dprintf(STDERR_FILENO, "export: `%s': not a valid identifier\n", cmd);
		return (1);
	}
	else
	{
		temp = ft_split(cmd, '=');
		if (ft_isalpha(temp[0][0]) == 0 && temp[0][0] != '_')
			return (ft_export_eql_a(temp));
		else if (ft_isalnum_str(temp[0]) == 0)
			return (ft_export_eql_b(temp));
		else if (export_exists(temp[0], temp[1]) == 1)
			ft_free_array(temp);
		else
			return (ft_export_eql_c(temp));
	}
	return (0);
}
