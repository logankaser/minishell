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

void	scan_dir_for_executables(t_uvector *tmp_str, DIR *dir, 
	char *dir_path, t_map *path)
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
		free(ft_map_remove(path, file->d_name));
		ft_map_set(path, file->d_name, ft_strdup((char*)tmp_str->data));
	}
}

void	update_path(t_minishell *ms)
{
	t_envvar		*var_path;
	char			**path_array;
	unsigned		i;
	DIR				*dir;
	t_uvector		tmp_str;

	ft_uvector_init(&tmp_str, sizeof(char));
	if (!(var_path = ft_map_get(&ms->env, "PATH")))
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
		scan_dir_for_executables(&tmp_str, dir, path_array[i], &ms->path);
		closedir(dir);
		free(path_array[i++]);
	}
	free(path_array);
	free(tmp_str.data);
}


int	b_echo(int argc, char *argv[], t_minishell *ms)
{
	int			i;
	t_bool		flag_n;

	(void)ms;
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

int	b_cd(int argc, char *argv[], t_minishell *ms)
{
	struct stat	dir;
	int			status;
	char		*path;

	(void)ms;
	path = argv[1];
	status = 0;
	if ((status = argc != 2))
		ft_printf("usage: cd <path>\n");
	else if ((status = lstat(path, &dir)))
		ft_printf("cd: no such file or directory: %s\n", path);
	else if ((status = !S_ISDIR(dir.st_mode)))
		ft_printf("cd: not a directory: %s\n", path);
	else if ((status = chdir(path)))
		ft_printf("cd: permission denied: %s\n", path);
	return (status);
}

int	b_env(int argc, char *argv[], t_minishell *ms)
{
	unsigned	i;
	t_list		*link;
	t_envvar	*var;

	(void)argc;
	(void)argv;
	i = 0;
	while (i < ms->env.capacity)
	{
		if (!(link = ms->env.data[i++]))
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

int	b_path(int argc, char *argv[], t_minishell *ms)
{
	unsigned	i;
	t_list		*link;

	(void)argc;
	(void)argv;
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
	return (0);
}

int	b_setenv(int argc, char *argv[], t_minishell *ms)
{
	t_envvar	*var;

	if (argc != 3)
	{
		ft_printf("usage: setenv <VAR> <VALUE>\n");
		return 1;
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

int	b_unsetenv(int argc, char *argv[], t_minishell *ms)
{
	t_envvar	*var;

	if (argc != 2)
	{
		ft_printf("usage: unsetenv <VAR>\n");
		return 1;
	}
	var = ft_map_remove(&ms->env, argv[1]);
	free(var->data);
	free(var);
	if (argc == 2 && !ft_strcmp(argv[1], "PATH"))
		ft_map_clear(&ms->path, free);
	return (0);
}

void	free_envvar(void *v)
{
	t_envvar	*env;

	env = v;
	free(env->data);
	free(env);
}

void	noop(void *v)
{
	(void)v;
}

int	b_exit(int argc, char *argv[], t_minishell *ms)
{
	(void)argc;
	(void)argv;
	ft_map_clear(&ms->path, &free);
	ft_map_clear(&ms->env, &free_envvar);
	ft_map_clear(&ms->builtins, &noop);
	free(ms->path.data);
	free(ms->env.data);
	free(ms->builtins.data);
	ms->running = FALSE;
	return (0);
}

void	init_minishell(t_minishell *ms)
{
	unsigned	i;
	t_envvar	*var;

	ft_map_init(&ms->builtins, 0, 17);
	ft_map_init(&ms->env, 0, 97);
	ft_map_init(&ms->path, 0, 1021);
	i = 0;
	while(environ[i])
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
		ft_printf("Failed to execute command\n");
		exit(1);
	}
	else
		waitpid(pid, 0, 0);
	return status;
}

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
	ft_printf("\033[33m%s\033[0m.%s$ ", user, base);
}

static char* expand(const char *raw, t_minishell *ms)
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
			var = ft_map_get(&ms->env, "HOME");
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
static int split_argv(t_vector *v, char *src, t_minishell *ms)
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
			ft_vector_push(v, expand(src + i, ms));
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
	if (!split_argv(&argv, line, ms))
	{
		ft_vector_del(&argv);
		return ;
	}
	ft_striter_u(argv.data[0], &ft_tolower);
	ft_vector_push(&argv, NULL);
	if (!access((char*)argv.data[0], X_OK))
		status = exec_command(argv.data[0], (char**)argv.data);
	else if ((fn_ptr = ft_map_get(&ms->builtins, argv.data[0])))
		status = fn_ptr(argv.length - 1, (char**)argv.data, ms);
	else if ((path = ft_map_get(&ms->path, argv.data[0])))
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

	ms.last_pwd = NULL;
	init_minishell(&ms);
	line = NULL;
	ms.running = TRUE;
	while (ms.running)
	{
		prompt(&ms);
		ret = get_next_line(STDIN_FILENO, &line);
		if (ret > 0 && ft_strlen(line) > 0)
			parse_command(&ms, line);
		ft_memdel((void**)&line);
	}
	close(STDIN_FILENO);
	get_next_line(STDIN_FILENO, &line);
	return (0);
}
