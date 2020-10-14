int	main(int ac, char **av)
{
	char **tab_env;
	int	f;

	f =execve(av[1], av, tab_env);

	printf("%d\n",f);
	return (0);
}
