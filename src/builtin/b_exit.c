/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 20:00:45 by lkaser            #+#    #+#             */
/*   Updated: 2018/10/25 20:00:46 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	free_envvar(void *v)
{
	t_envvar	*env;

	env = v;
	free(env->data);
	free(env);
}

int			b_exit(int argc, char *argv[], t_minishell *ms)
{
	if (argc != 1)
	{
		ft_printf("usage: exit\n");
		return (1);
	}
	(void)argv;
	ft_map_clear(&ms->path, &free);
	ft_map_clear(&ms->env, &free_envvar);
	ft_map_clear(&ms->builtins, NULL);
	free(ms->path.data);
	free(ms->env.data);
	free(ms->builtins.data);
	ms->running = FALSE;
	return (0);
}
