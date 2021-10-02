/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/02 18:23:40 by lwray         #+#    #+#                 */
/*   Updated: 2021/10/02 18:23:43 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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

void	free_cmdlst(t_cmd_lst *cmd_lst)
{
	t_cmd_lst	*temp_next;

	while (cmd_lst)
	{
		free (cmd_lst->subcmd.in_file);
		free (cmd_lst->subcmd.out_file);
		ft_free_array(cmd_lst->subcmd.cmd);
		temp_next = cmd_lst->next;
		free (cmd_lst);
		cmd_lst = temp_next;
	}
	cmd_lst = NULL;
}

void	refresh(void)
{
	if (g_data.cmd_lst)
		free_cmdlst(g_data.cmd_lst);
	g_data.cmd_lst = NULL;
	free(g_data.pids);
	if (g_data.token)
		lst_clear(&g_data.token);
}

void	clean_all(void)
{
	if (g_data.cmd_lst)
		free_cmdlst(g_data.cmd_lst);
	g_data.cmd_lst = NULL;
	free(g_data.pids);
	if (g_data.token)
		lst_clear(&g_data.token);
	env_lst_clear(&g_data.env_lst);
	g_data.env_lst = NULL;
	rl_clear_history();
}
