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
#include <sys/types.h>
#include <dirent.h>
#include <libgen.h>
#include <limits.h>
#include "libft.h"
#include "minishell.h"

extern char	**environ;

t_map	g_env;
t_map	g_path;

int	b_echo(int argc, char *argv[])
{
	int			i;
	t_bool		flag_n;

	flag_n = 0;
	i = 1;
	if (i < argc && argv[i][0] == '-' && argv[i][1] == 'n')
		flag_n = ++i;
	while (i < argc)
		if (i + 1 < argc)
			ft_printf("%s ", argv[i++]);
		else
			ft_printf("%s", argv[i++]);
	if (!flag_n)
		ft_putchar('\n');
	return (0);
}

int	b_cd(int argc, char *argv[])
{
	struct stat dir;

	if (argc != 2)
	{
		printf("usage: cd <path>\n");
		return 1;
	}
	if (lstat(argv[1], &dir))
	{
		printf("cd: no such file or directory: %s\n", argv[1]);
		return 1;
	}
	if (!S_ISDIR(dir.st_mode))
	{
		printf("cd: not a directory: %s\n", argv[1]);
		return 1;
	}
	if (chdir(argv[1]))
	{
		printf("cd: permission denied: %s\n", argv[1]);
		return 1;
	}
	return (0);
}

int	b_env(int argc, char *argv[])
{
	unsigned	i;
	t_list		*link;
	t_envvar	*var;

	(void)argc;
	(void)argv;
	i = 0;
	while (i < g_env.capacity)
	{
		if (!(link = g_env.data[i++]))
			continue ;
		while (link)
		{
			var = link->content;
			ft_printf("%s\n", var->data);
			link = link->next;
		}
	}
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
	exit(0);
	return (0);
}

void	scan_dir_for_executables(t_uvector *tmp_str, DIR *dir, char *dir_path)
{
	struct dirent	*file;
	unsigned		len;

	tmp_str->length = 0;
	ft_string_append(tmp_str, dir_path);
	len = tmp_str->length;
	while ((file = readdir(dir)))
	{
		tmp_str->length = len;
		ft_string_append(tmp_str, "/");
		ft_string_append(tmp_str, file->d_name);
		if (access((char*)tmp_str->data, X_OK))
			continue ;
		ft_map_insert(&g_path, file->d_name, ft_strdup((char*)tmp_str->data));
	}
}

void	update_path(void)
{
	t_envvar		*var_path;
	char			**path_array;
	unsigned		i;
	DIR				*dir;
	t_uvector		tmp_str;

	ft_uvector_init(&tmp_str, sizeof(char));
	if (!(var_path = ft_map_get(&g_env, "PATH")))
		return ;
	path_array = ft_strsplit(var_path->value, ':');
	i = 0;
	while (path_array[i])
	{
		if (!(dir = opendir(path_array[i])))
		{
			free(path_array[i++]);
			continue ;
		}
		scan_dir_for_executables(&tmp_str, dir, path_array[i]);
		closedir(dir);
		free(path_array[i++]);
	}
	free(path_array);
	free(tmp_str.data);
}

void	init_minishell(t_minishell *ms)
{
	unsigned	i;
	t_envvar	*var;

	ft_map_init(&ms->builtins, 0, 17);
	ft_map_init(&g_env, 0, 97);
	ft_map_init(&g_path, 0, 1021);
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
	update_path();
}

static void	str_lower(char *str)
{
	while(*str)
	{
		*str = ft_tolower(*str);
		++str;
	}
}

static int exec_command(char *path, char *argv[])
{
	pid_t	pid;
	int 	status;

	status = 1;
	pid = fork();
	if (pid == 0)
	{
		lseek(STDIN_FILENO, 0, SEEK_END);
		status = execv(path, argv);
		printf("Failed to execute command\n");
		exit(1);
	}
	else
		waitpid(pid, 0, 0);
	return status;
}

static void	prompt(void)
{
	t_envvar	*var_user;
	char		*user;
	char		pwd[PATH_MAX];
	char		*base;

	getcwd(pwd, PATH_MAX);
	base = basename(pwd);
	var_user = ft_map_get(&g_env, "USER");
	user = var_user ? var_user->value : ":";
	ft_printf("\033[33m%s\033[0m.%s$ ", user, base);
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
	return ((char*)out.data);
}

/*
** Will need to be replace in 21sh with a version that tokenizes
** "     echo -n  word word 0"
** "00000echo0-n00word0word00"
**       ^>>> ^>  ^>>> ^>>>
**.
*/
static int split_argv(t_vector *v, char *src)
{
	long		len;
	long		i;
	t_bool		quote;

	len = ft_strlen(src);
	i = -1;
	quote = FALSE;
	while (++i < len)
	{
		if (src[i] == '"')
			quote = !quote;
		if ((!quote && ANY3(src[i], ' ', '\t', '\v')) || src[i] == '"')
			src[i] = '\0';
	}
	i = -1;
	while (++i < len)
		if (src[i])
		{
			ft_vector_push(v, expand(src + i));
			while (src[i])
				++i;
		}
	return (v->length);
}

/*
** Status will be used in 21sh.
*/
static void	parse_command(t_minishell *ms, char* line)
{
	t_builtin	fn_ptr;
	char		*path;
	t_vector	argv;
	int			status;

	status = 127;
	ft_vector_init(&argv);
	if (!split_argv(&argv, line))
	{
		ft_vector_del(&argv);
		return ;
	}
	str_lower(argv.data[0]);
	ft_vector_push(&argv, NULL);
	if (!access((char*)argv.data[0], X_OK))
		status = exec_command(argv.data[0], (char**)argv.data);
	else if ((fn_ptr = ft_map_get(&ms->builtins, argv.data[0])))
		status = fn_ptr(argv.length - 1, (char**)argv.data);
	else if ((path = ft_map_get(&g_path, argv.data[0])))
		status = exec_command(path, (char**)argv.data);
	else
		ft_printf("`%s` not found\n", argv.data[0]);
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
