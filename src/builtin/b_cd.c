/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 20:00:26 by lkaser            #+#    #+#             */
/*   Updated: 2018/10/25 20:00:27 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "builtin.h"

static char	*get_path(int argc, char *argv[], t_minishell *ms)
{
	t_envvar	*var;

	if (argc == 1)
	{
		var = ft_map_get(&ms->env, "HOME");
		return (var ? var->value : "/");
	}
	else if (argc == 2 && !ft_strcmp(argv[1], "-"))
		return (ms->old_pwd);
	else
		return (argv[1]);
}

static void	update_pwd(char *path, t_minishell *ms)
{
	t_envvar	*var;

	var = ft_map_remove(&ms->env, "PWD");
	if (!var)
		var = malloc(sizeof(t_envvar));
	else
		free(var->data);
	var->data = ft_memalloc(4 + ft_strlen(path) + 1);
	var->value = var->data + 4;
	ft_strcat(var->data, "PWD=");
	ft_strcat(var->data, path);
	ft_map_set(&ms->env, "PWD", var);
}

int			b_cd(int argc, char *argv[], t_minishell *ms)
{
	struct stat	dir;
	int			status;
	char		*path;

	path = get_path(argc, argv, ms);
	if ((status = argc > 2))
		ft_printf("usage: `cd <path>` or `cd`\n");
	else if ((status = stat(path, &dir)))
		ft_printf("cd: no such file or directory: %s\n", path);
	else if ((status = !S_ISDIR(dir.st_mode)))
		ft_printf("cd: not a directory: %s\n", path);
	else if ((status = chdir(path)))
		ft_printf("cd: permission denied: %s\n", path);
	if (status)
		return (status);
	ft_strcpy(ms->old_pwd, ms->pwd);
	getcwd(ms->pwd, PATH_MAX);
	update_pwd(path, ms);
	return (0);
}
