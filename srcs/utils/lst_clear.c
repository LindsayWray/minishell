#include "../../includes/utils.h"

void	lst_clear(t_token **lst)
{
    if (*lst == NULL)
        return ;
	if ((*lst)->next)
		lst_clear(&((*lst)->next));
	free ((*lst)->content);
    free (*lst);
	*lst = NULL;
}

void	cmd_lst_clear(t_cmd_lst **cmd_lst)
{
    if (*cmd_lst == NULL)
        return ;
	if ((*cmd_lst)->next)
		cmd_lst_clear(&((*cmd_lst)->next));
	free ((*cmd_lst)->subcmd.cmd);
    free (*cmd_lst);
	*cmd_lst = NULL;
}