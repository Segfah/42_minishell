#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct	s_test
{
	void			*content;
	struct s_test	*next;
}				t_test;

typedef struct	s_tmp
{
	t_test *varenv;
}				t_tmp;

void				print_list(t_test *test)
{
	t_test *tmp;

	tmp = test;
	while (tmp != NULL)
	{
		printf("nodo->content[%s]\n", tmp->content);
		tmp = tmp->next;
	}
}

/*
 ** By: Lmartin (leo el bueno)
 */

void				add_list_back(t_test **head, char *str)
{
	t_test *new;
	t_test *tmp;

	new = malloc(sizeof(t_test));
	new->content = strdup(str);
	new->next = NULL;
	if (!(*head))
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}

}


void				add_list_front(t_test **head, char *str)
{
	t_test *tmp;

	tmp = malloc(sizeof(t_test));
	tmp->content = strdup(str);
	tmp->next = *head;
	*head = tmp;
}



void	free_list(t_test *test)
{
	t_test *tmp;

	while (test != NULL)
	{
		tmp = test->next;
		free(test->content);
		free(test);
		test = tmp;
	}
}

void	save_env(t_test *test, char **envp)
{
	test = NULL;
	int i = 0;
	while (envp[i])
		i++;
	while (i--)
	{
		//add_list_back(&test, envp[i++]);
		add_list_front(&test, envp[i]);
	}
	print_list(test);
	free_list(test);
}

int		main(int ac, char **av, char **envp)
{
	t_tmp tmp;

	save_env(tmp.varenv, envp);
	//	free_env(tmp.varenv);

	while (1)
		;
	(void)ac;
	(void)av;

	//	print_list();
	return (0);
}
