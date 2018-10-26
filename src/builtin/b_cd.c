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

int	b_cd(int argc, char *argv[], t_minishell *ms)
{
	struct stat	dir;
	int			status;
	char		*path;
	t_envvar	*var;

	if (argc == 1)
	{
		var = ft_map_get(&ms->env, "HOME");
		path = var ? var->value : "/";
	}
	else if (argc == 2 && !ft_strcmp(argv[1], "-"))
		path = ms->old_pwd;
	else
		path = argv[1];
	if ((status = argc > 2))
		ft_printf("usage: `cd <path>` or `cd`\n");
	else if ((status = lstat(path, &dir)))
		ft_printf("cd: no such file or directory: %s\n", path);
	else if ((status = !S_ISDIR(dir.st_mode)))
		ft_printf("cd: not a directory: %s\n", path);
	else if ((status = chdir(path)))
		ft_printf("cd: permission denied: %s\n", path);
	ft_strcpy(ms->old_pwd, ms->pwd);
	getcwd(ms->pwd, PATH_MAX);
	return (status);
}
