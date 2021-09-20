#include "../../includes/utils.h"

t_data  g_data;

t_env_lst	*ft_get_env_var(char *key)
{
	t_env_lst	*temp;

	temp = g_data.env_lst;
	while (temp)
	{
		if (ft_streql(temp->key, key))
			return (temp);
		temp = temp->next;
	}
	return (temp);
}