#include "builtin.h"

int	b_path(int argc, char *argv[], t_minishell *ms)
{
	unsigned	i;
	t_list		*link;
	t_bool		total;

	total = argc == 2 && !ft_strcmp(argv[1], "-t");
	if (argc > 2 || (!total && argc == 2))
	{
		ft_printf("usage: path [-t]\n");
		return (1);
	}
	i = 0;
	while (i < ms->path.capacity)
	{
		if (!(link = ms->path.data[i++]))
			continue ;
		while (link)
		{
			ft_printf("%s\n", link->content);
			link = link->next;
		}
	}
	if (total)
		ft_printf("\n\033[0;1mtotal %u\033[0m\n", ms->path.count);
	return (0);
}
