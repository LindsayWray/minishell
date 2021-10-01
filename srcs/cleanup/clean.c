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

void	env_lst_clear(t_env_lst **env)
{
    if (*env == NULL)
        return ;
	if ((*env)->next)
		env_lst_clear(&((*env)->next));
	free ((*env)->key);
	free ((*env)->value);
    free (*env);
	*env = NULL;
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
	g_data.cmd_lst = NULL;
}

void	refresh(void)
{
	free_cmdlst();
	free(g_data.pids);
	if (g_data.token)
		lst_clear(&g_data.token);
}

void	clean_all(void)
{
	free_cmdlst();
	free(g_data.pids);
	if (g_data.token)
		lst_clear(&g_data.token);
	env_lst_clear(&g_data.env_lst);
	g_data.env_lst = NULL;
	rl_clear_history();
}