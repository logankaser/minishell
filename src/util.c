/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 19:59:57 by lkaser            #+#    #+#             */
/*   Updated: 2018/10/25 19:59:59 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <termios.h>
#include "minishell.h"

char			**map_to_env_array(t_map *env, t_bool sort)
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

void			set_signal_handler(int signum, void (*handler)(int))
{
	struct sigaction	action;

	action = (struct sigaction){.sa_handler = handler, .sa_flags = 0};
	sigemptyset(&action.sa_mask);
	sigaction(signum, &action, NULL);
}

static void		free_envvar(void *v)
{
	t_envvar	*env;

	env = v;
	free(env->data);
	free(env);
}

void			minishell_cleanup(t_minishell *ms)
{
	ft_map_clear(&ms->path, &free);
	ft_map_clear(&ms->env, &free_envvar);
	ft_map_clear(&ms->builtins, NULL);
	free(ms->path.data);
	free(ms->env.data);
	free(ms->builtins.data);
	tcsetattr(STDIN_FILENO, TCSANOW, &ms->terminal_settings);
	write(STDOUT_FILENO, "\n", 1);
}

void			set_raw_mode(void)
{
	t_termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHO;
	term.c_lflag &= ~ICANON;
	term.c_cc[VMIN] = 0;
	term.c_cc[VTIME] = 1;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
