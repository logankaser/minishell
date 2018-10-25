#include "builtin.h"

int	b_env(int argc, char *argv[], t_minishell *ms)
{
	unsigned	i;
	char		**env_array;
	t_bool		sort;

	sort = argc == 2 && !ft_strcmp(argv[1], "-s");
	if (argc > 2 || (!sort && argc == 2))
	{
		ft_printf("usage: env [-s]\n");
		return (1);
	}
	env_array = map_to_env_array(&ms->env, sort);
	i = 0;
	while (env_array[i])
		ft_printf("%s\n", env_array[i++]);
	free(env_array);
	return (0);
}
