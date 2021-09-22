#include "../../includes/minishell.h"

t_data	g_data;

void	free_cmdlst(void)
{
	t_cmd_lst	*temp_next;
	
	while (g_data.cmd_lst)
	{
		free (g_data.cmd_lst->subcmd.in_file);
		free (g_data.cmd_lst->subcmd.out_file);
		ft_free_array(g_data.cmd_lst->subcmd.cmd);
		temp_next = g_data.cmd_lst->next;
		free (g_data.cmd_lst);
		g_data.cmd_lst = temp_next;
	}
}