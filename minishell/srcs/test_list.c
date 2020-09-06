#include <stdio.h>

void	ft_lstadd_back1(t_list **alst, t_list *new)
{
	t_list	*tmp;

	tmp = NULL;
	if (new)
	{
		if (!alst || !(*alst))
		{
			*alst = new;
			new->next = NULL;
			return ;
		}
		tmp = *alst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->next = NULL;
	}
}


t_list	*ft_lstnew1(char c)
{
	t_list	*tmp;

	if (!(tmp = malloc(sizeof(t_list))))
		return (NULL);
	if (c)
		tmp->c = c;
	else
		tmp->c = '\0';
	tmp->next = NULL;
	return (tmp);
}


int main()
{
    t_list *list;
    t_list *new;
    char abc[26] = "abcdefighjklmnopqrstuvwxyz";
    int i;

    i = 0;
    list = NULL;
    while(abc[i])
    {
        new = ft_lstnew1(abc[i]);
        ft_lstadd_back1(&list, new);
        i++;
    }
    new = list;
    while(new->next != NULL)
    {
        printf("list = %c\n", new->c);
        new = new->next;
    }
}