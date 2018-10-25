#include "builtin.h"

int	b_unsetenv(int argc, char *argv[], t_minishell *ms)
{
	t_envvar	*var;

	if (argc != 2)
	{
		ft_printf("usage: unsetenv <VAR>\n");
		return (1);
	}
	var = ft_map_remove(&ms->env, argv[1]);
	free(var->data);
	free(var);
	if (argc == 2 && !ft_strcmp(argv[1], "PATH"))
		ft_map_clear(&ms->path, free);
	return (0);
}
