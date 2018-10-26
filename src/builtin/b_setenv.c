/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_setenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 20:01:03 by lkaser            #+#    #+#             */
/*   Updated: 2018/10/25 20:01:04 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	b_setenv(int argc, char *argv[], t_minishell *ms)
{
	t_envvar	*var;

	if (argc != 3)
	{
		ft_printf("usage: setenv <VAR> <VALUE>\n");
		return (1);
	}
	var = ft_map_remove(&ms->env, argv[1]);
	if (!var)
		var = malloc(sizeof(t_envvar));
	else
		free(var->data);
	var->data = ft_memalloc(ft_strlen(argv[1]) + ft_strlen(argv[2]) + 2);
	var->value = var->data + ft_strlen(argv[1]) + 1;
	ft_strcat(var->data, argv[1]);
	ft_strcat(var->data, "=");
	ft_strcat(var->data, argv[2]);
	ft_map_set(&ms->env, argv[1], var);
	if (argc == 3 && !ft_strcmp(argv[1], "PATH"))
	{
		ft_map_clear(&ms->path, free);
		update_path(ms);
	}
	return (0);
}
