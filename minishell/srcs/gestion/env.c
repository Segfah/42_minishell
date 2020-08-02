#include "minishell.h"

void    gestion_env(char **envp)
{
	char	**env;
	int		i;

	env = envp;
	i = 0;
	while (env[i])
	{
		ft_printf("%s\n", env[i]);
		i++;
	}
}
