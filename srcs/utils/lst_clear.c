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