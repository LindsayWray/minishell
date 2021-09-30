#include "../../includes/utils.h"

static t_env_lst *get_shell_lvl(t_env_lst *temp)
{
    while (temp)
    {
        if (ft_streql(temp->key, "SHLVL") == 1)
            return (temp);
        temp = temp->next;
    }
    return (temp);
}

static void set_shell_lvl(t_env_lst *lst)
{
    t_env_lst   *temp;
    int         level;

    temp = get_shell_lvl(lst);
    if (temp && temp->value)
    {
        level = ft_atoi(temp->value);
		level++;
        free(temp->value);
        temp->value = ft_itoa(level);
    }
}

t_env_lst   *ft_getenv(char **env)
{
	t_env_lst	*env_lst;
	t_env_lst	*env_new;
	char		**temp;
	int			i;

	env_lst = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		temp = ft_split(env[i], '=');
		env_new = env_lst_new(ft_strdup(temp[0]), ft_strdup(temp[1]));
		env_lst_add_back(&env_lst, env_new);
		ft_free_array(temp);
		i++;
	}
	set_shell_lvl(env_lst);
	env_new = env_lst_new(ft_strdup("?"), ft_strdup("0"));
	env_lst_add_back(&env_lst, env_new); // added these lines to set the exit_status on 0 at the beginning
	return (env_lst);
}
