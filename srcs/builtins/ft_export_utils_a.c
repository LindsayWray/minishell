/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export_utils_a.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: idonado <idonado@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/04 14:34:46 by idonado       #+#    #+#                 */
/*   Updated: 2021/10/06 18:17:31 by idonado       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_data	g_data;

int	export_exists(char *key, char *value)
{
	t_env_lst	*temp;

	temp = g_data.env_lst;
	while (temp)
	{
		if (ft_streql(key, temp->key))
		{
			if (temp->value != NULL)
				free(temp->value);
			if (value != NULL)
				temp->value = ft_strdup(value);
			else
				temp->value = ft_strdup("");
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

int	export_exists_key(char *key)
{
	t_env_lst	*temp;

	temp = g_data.env_lst;
	while (temp)
	{
		if (ft_streql(key, temp->key))
			return (1);
		temp = temp->next;
	}
	return (0);
}

int	ft_export_add(char *key, char *value)
{
	t_env_lst	*new;
	char		*set_key;
	char		*set_value;

	set_value = NULL;
	set_key = ft_strdup(key);
	if (set_key == NULL)
		return (1);
	if (value != NULL)
		set_value = ft_strdup(value);
	new = env_lst_new(set_key, set_value);
	env_lst_add_back(&(g_data.env_lst), new);
	return (0);
}

static void	ft_export_noarg_a(t_env_lst *lst, t_env_lst *temp, int fd_out)
{
	while (lst)
	{
		if (lst->value == NULL)
			ft_dprintf(fd_out, "declare -x %s\n", lst->key);
		else
			ft_dprintf(fd_out, "declare -x %s=\"%s\"\n", lst->key, lst->value);
		temp = lst;
		lst = lst->next;
		free(temp->key);
		if (temp->value != NULL)
			free(temp->value);
		free(temp);
	}
	return ;
}

int	ft_export_noarg(int fd_out)
{
	t_env_lst	*temp;
	t_env_lst	*new;
	t_env_lst	*lst;

	temp = g_data.env_lst;
	lst = NULL;
	while (temp)
	{
		if (temp->value != NULL)
			new = env_lst_new(ft_strdup(temp->key), ft_strdup(temp->value));
		else
			new = env_lst_new(ft_strdup(temp->key), NULL);
		env_lst_add_back(&lst, new);
		temp = temp->next;
	}
	lst = sort_env_lst(lst);
	ft_export_noarg_a(lst, temp, fd_out);
	return (0);
}
