/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 14:44:02 by lkaser            #+#    #+#             */
/*   Updated: 2018/07/20 12:46:35 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

extern char	**environ;

t_map	g_env;
t_map	g_path;

int	b_echo(int argc, char *argv[])
{
	for (int i = 1; i < argc; ++i)
		ft_printf("%s", argv[i]);
	ft_putchar('\n');
	return (0);
}

int	b_cd(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	return (0);
}

int	b_env(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	return (0);
}

int	b_setenv(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	return (0);
}

int	b_unsetenv(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	return (0);
}

int	b_exit(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	return (0);
}

void	init_minishell(t_minishell *ms)
{
	unsigned	i;
	t_envvar	*var;

	ft_map_init(&ms->builtins, 0);
	ft_map_init(&g_env, 0);
	ft_map_init(&g_path, 0);
	i = 0;
	while(environ[i])
	{
		var = malloc(sizeof(t_envvar));
		var->data = ft_strdup(environ[i++]);
		var->value = ft_strchr(var->data, '=');
		*(var->value) = '\0';
		ft_map_insert(&g_env, var->data, var);
		*(var->value) = '=';
		var->value += 1;
	}
	ft_map_insert(&ms->builtins, "echo", &b_echo);
	ft_map_insert(&ms->builtins, "cd", &b_cd);
	ft_map_insert(&ms->builtins, "env", &b_env);
	ft_map_insert(&ms->builtins, "setenv", &b_setenv);
	ft_map_insert(&ms->builtins, "unsetenv", &b_unsetenv);
	ft_map_insert(&ms->builtins, "exit", &b_exit);
	ft_printf("Map count: %u\n", g_env.count);
}

static void	str_lower(char *str)
{
	while(*str)
	{
		*str = ft_tolower(*str);
		++str;
	}
}

static void exec_command(char *path, char *argv[])
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		lseek(STDIN_FILENO, 0, SEEK_END);
		execv(path, argv);
		printf("Failed to execute command\n");
	}
	else
		waitpid(pid, 0, 0);
}

static void	prompt(void)
{
	t_envvar	*var_user;
	char		*user;

	var_user = ft_map_get(&g_env, "USER");
	user = var_user ? var_user->value : ":";
	ft_printf("%s) ", user);
}

static char* expand(const char *raw)
{
	unsigned i;
	t_uvector	out;
	t_envvar	*var;

	ft_uvector_init(&out, 1);
	i = 0;
	while (raw[i])
	{
		if (raw[i] == '~')
		{
			ft_string_appendn(&out, raw, i);
			var = ft_map_get(&g_env, "HOME");
			ft_string_append(&out, var ? var->value : "");
			raw += i + 1;
			i = 0;
		}
		else
			++i;
	}
	ft_string_append(&out, raw);
	// FIXME handle black space case.
	return ((char*)out.data);
}

static void	parse_command(t_minishell *ms, char* line)
{
	t_builtin	fn_ptr;
	char		*path;
	t_vector	argv;

	ft_vector_init(&argv);
	while (*line)
	{
		while (ANY3(*line, '\t', ' ', '\v'))
			++line;
		path = line;
		while (*line && !ANY3(*line, '\t', ' ', '\v'))
			++line;
		if (*line && ANY3(*line, '\t', ' ', '\v'))
			*line++ = '\0';
		ft_vector_push(&argv, expand(path));
	}
	str_lower(argv.data[0]);
	ft_vector_push(&argv, NULL);
	if ((fn_ptr = ft_map_get(&ms->builtins, argv.data[0])))
		fn_ptr(argv.length - 1, (char**)argv.data);
	else if ((path = ft_map_get(&g_path, argv.data[0])))
		exec_command((char*)argv.data[0], (char**)argv.data);
	ft_vector_del(&argv);
}

int	main(void)
{
	char		*line;
	int			ret;
	t_minishell ms;

	init_minishell(&ms);
	line = NULL;
	while (1)
	{
		prompt();
		ret = get_next_line(0, &line);
		if (ret > 0 && ft_strlen(line) > 0)
			parse_command(&ms, line);

		ft_memdel((void**)&line);
	}
	return (0);
}
