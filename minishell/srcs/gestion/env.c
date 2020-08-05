#include "minishell.h"

void				gestion_env(t_lists *test)
{
	t_lists			*tmp;

	tmp = test;
	while (tmp != NULL)
	{
		ft_printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
}

