#include "minishell.h"

char	**map_to_env_array(t_map *env, t_bool sort)
{
	unsigned	i;
	t_list		*link;
	t_envvar	*var;
	t_vector	env_array;

	ft_vector_init(&env_array);
	i = 0;
	while (i < env->capacity)
	{
		if (!(link = env->data[i++]))
			continue ;
		while (link)
		{
			var = link->content;
			ft_vector_push(&env_array, var->data);
			link = link->next;
		}
	}
	if (sort)
		ft_qsort(env_array.data, env_array.length, ft_compare_str_asc);
	ft_vector_push(&env_array, NULL);
	return (char**)env_array.data;
}