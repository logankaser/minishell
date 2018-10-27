/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 14:44:02 by lkaser            #+#    #+#             */
/*   Updated: 2018/10/25 19:59:32 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <libgen.h>
#include "libft.h"
#include "minishell.h"
#include "builtin/builtin.h"

#define ENVIRON extern char	**environ

ENVIRON;

volatile		sig_atomic_t g_running = FALSE;

static void		minishell_init_hashmaps(t_minishell *ms)
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
		*(var->value++) = '=';
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

static void		prompt(t_minishell *ms)
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

/*
** Ignore SIGINT / Ctrl + C.
*/

static void		ignore(int arg)
{
	(void)arg;
	write(STDOUT_FILENO, "\n", 1);
}

/*
** Cleanup on SIGTERM.
*/

static void		term(int arg)
{
	(void)arg;
	write(STDOUT_FILENO, "\n", 1);
	g_running = FALSE;
}

/*
** Mainloop runs as long as g_running is TRUE
** g_true `is volatile sig_atomic_t` so that it may
** be safely set from a signal handler.
*/

int				main(void)
{
	char				*line;
	t_minishell			ms;

	set_signal_handler(SIGINT, ignore);
	set_signal_handler(SIGTERM, term);
	minishell_init_hashmaps(&ms);
	getcwd(ms.pwd, PATH_MAX);
	getcwd(ms.old_pwd, PATH_MAX);
	line = NULL;
	g_running = TRUE;
	while (g_running)
	{
		prompt(&ms);
		if (get_next_line(STDIN_FILENO, &line) > 0)
			run_commands_semicolons(&ms, line);
		ft_memdel((void**)&line);
	}
	minishell_cleanup(&ms);
	close(STDIN_FILENO);
	get_next_line(STDIN_FILENO, &line);
	return (0);
}
