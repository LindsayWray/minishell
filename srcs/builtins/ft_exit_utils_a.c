#include "../../includes/minishell.h"

int	ft_exit_negative(int exit_code)
{
	while (exit_code < -256)
		exit_code = exit_code + 256;
	exit_code = 256 + exit_code;
	return (exit_code);
}
