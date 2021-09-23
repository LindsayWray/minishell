#include "../../includes/minishell.h"

t_data	g_data;

void	lst_clear(t_token **lst)
{
    if (*lst == NULL)
        return ;
	if ((*lst)->next)
		lst_clear(&((*lst)->next));
	free ((*lst)->content);
    free (*lst);
	*lst = NULL;
	g_data.token = NULL;
}

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

void	clean_all(void)
{
	free_cmdlst();
	free(g_data.pids);
	lst_clear(&g_data.token);
	//free env;
}