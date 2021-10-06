/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   envlst_to_array.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/02 20:35:48 by lwray         #+#    #+#                 */
/*   Updated: 2021/10/06 18:27:54 by idonado       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_data	g_data;

char	**ft_envlst_to_array(t_env_lst *env_lst)
{
	char	**env_array;
	char	*temp_str;
	char	*temp_str_final;
	int		i;

	i = env_lst_size(env_lst) + 1;
	env_array = malloc(sizeof(char *) * i);
	i = 0;
	while (env_lst)
	{
		if (env_lst->value != NULL)
		{
			temp_str = ft_strjoin(env_lst->key, "=");
			temp_str_final = ft_strjoin(temp_str, env_lst->value);
			env_array[i] = temp_str_final;
			free(temp_str);
		}
		else
			env_array[i] = ft_strdup(env_lst->key);
		i++;
		env_lst = env_lst->next;
	}
	env_array[i] = NULL;
	return (env_array);
}
