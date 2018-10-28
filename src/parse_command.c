/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 19:59:38 by lkaser            #+#    #+#             */
/*   Updated: 2018/10/25 19:59:40 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include "minishell.h"

static int		exec_command(char *path, char *argv[], t_minishell *ms)
{
	pid_t	pid;
	int		status;
	char	**env_array;

	status = 1;
	pid = fork();
	env_array = NULL;
	if (pid == 0)
	{
		lseek(STDIN_FILENO, 0, SEEK_END);
		env_array = map_to_env_array(&ms->env, FALSE);
		status = execve(path, argv, env_array);
		ft_putstr("Failed to execute command\n");
		free(argv);
		exit(1);
	}
	else
		waitpid(pid, 0, 0);
	free(env_array);
	return (status);
}

/*
** Will need to be replace in 21sh with a version that tokenizes
** input, currently it is a hacky mess
** This is how it works:
** `     echo -n  word word 0`
** `00000echo0-n00word0word00`
**       ^>>> ^>  ^>>> ^>>>
**
** `echo   "extract to"   "~/ okay?"`
** `0000000"extract to0000"~/ okay?0`
** Leading `"` is kept by the first pass so that next pass knows
** not to expand it.
*/

static int		split_argv(t_vector *v, char *src, t_minishell *ms)
{
	long		len;
	long		i;
	t_bool		esc;

	len = ft_strlen(src);
	esc = FALSE;
	i = -1;
	while (++i < len)
	{
		if (src[i] == '"')
			esc = !esc;
		if (!esc && ANY4(src[i], ' ', '\t', '\v', '"'))
			src[i] = '\0';
	}
	i = -1;
	while (++i < len && !esc)
		if (src[i])
		{
			ft_vector_push(v, src[i] == '"' ?
				ft_strdup(src + i + 1) : expand(src + i, ms));
			while (src[i])
				++i;
		}
	return (v->length);
}

static t_bool	is_executable(char *path)
{
	struct stat	file_info;

	if (access(path, X_OK))
		return (FALSE);
	stat(path, &file_info);
	if (!S_ISREG(file_info.st_mode))
		return (FALSE);
	return (TRUE);
}

/*
** Status will be used in 21sh.
*/

static void		parse_command(t_minishell *ms, char *command)
{
	t_builtin	fn_ptr;
	char		*path;
	t_vector	argv;
	int			status;

	status = 127;
	ft_vector_init(&argv);
	if (!split_argv(&argv, command, ms))
	{
		ft_vector_del(&argv);
		return ;
	}
	ft_striter_u(argv.data[0], &ft_tolower);
	ft_vector_push(&argv, NULL);
	if (is_executable((char*)argv.data[0]))
		status = exec_command(argv.data[0], (char**)argv.data, ms);
	else if ((fn_ptr = ft_map_get(&ms->builtins, argv.data[0])))
		status = fn_ptr(argv.length - 1, (char**)argv.data, ms);
	else if ((path = ft_map_get(&ms->path, argv.data[0])))
		status = exec_command(path, (char**)argv.data, ms);
	else
		ft_printf("`%s` not found\n", argv.data[0]);
	ft_vector_del(&argv);
}

void			run_commands(t_minishell *ms, char *line)
{
	char		**commands;
	unsigned	i;

	commands = ft_strsplit(line, ';');
	i = 0;
	while (commands[i])
	{
		parse_command(ms, commands[i]);
		free(commands[i++]);
	}
	free(commands);
}
