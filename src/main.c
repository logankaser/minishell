/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 14:44:02 by lkaser            #+#    #+#             */
/*   Updated: 2018/10/22 19:42:22 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <libgen.h>
#include <signal.h>
#include "libft.h"
#include "minishell.h"
#include "builtin/builtin.h"

extern char	**environ;

void	init_minishell(t_minishell *ms)
{
	unsigned	i;
	t_envvar	*var;

	ft_map_init(&ms->builtins, 0, 17);
	ft_map_init(&ms->env, 0, 97);
	ft_map_init(&ms->path, 0, 1021);
	i = 0;
	while (environ[i])
	{
		var = malloc(sizeof(t_envvar));
		var->data = ft_strdup(environ[i++]);
		var->value = ft_strchr(var->data, '=');
		*(var->value) = '\0';
		ft_map_set(&ms->env, var->data, var);
		*(var->value) = '=';
		var->value += 1;
	}
	ft_map_set(&ms->builtins, "echo", &b_echo);
	ft_map_set(&ms->builtins, "cd", &b_cd);
	ft_map_set(&ms->builtins, "env", &b_env);
	ft_map_set(&ms->builtins, "path", &b_path);
	ft_map_set(&ms->builtins, "setenv", &b_setenv);
	ft_map_set(&ms->builtins, "unsetenv", &b_unsetenv);
	ft_map_set(&ms->builtins, "exit", &b_exit);
	update_path(ms);
}

/*
** Prompt displays user name then the base directory of PWD,
** Like so: `user.your_dir)`.
*/

static void	prompt(t_minishell *ms)
{
	t_envvar	*var_user;
	char		*user;
	char		pwd[PATH_MAX];
	char		*base;

	getcwd(pwd, PATH_MAX);
	base = basename(pwd);
	var_user = ft_map_get(&ms->env, "USER");
	user = var_user ? var_user->value : ":";
	ft_printf("\033[33m%s\033[0m.%s) ", user, base);
}

void	ignore(int arg)
{
	(void)arg;
	ft_putchar('\n');
}

int	main(void)
{
	char				*line;
	int					ret;
	t_minishell			ms;
	struct sigaction	action;

	action = (struct sigaction){.sa_handler = &ignore, .sa_flags = 0};
	sigemptyset(&action.sa_mask);
	sigaction(SIGINT, &action, NULL);
	getcwd(ms.pwd, PATH_MAX);
	getcwd(ms.old_pwd, PATH_MAX);
	init_minishell(&ms);
	line = NULL;
	ms.running = TRUE;
	while (ms.running)
	{
		prompt(&ms);
		ret = get_next_line(STDIN_FILENO, &line);
		if (ret > 0 && ft_strlen(line) > 0)
			run_commands_semicolon(&ms, line);
		ft_memdel((void**)&line);
	}
	close(STDIN_FILENO);
	get_next_line(STDIN_FILENO, &line);
	return (0);
}
