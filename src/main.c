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

#include <unistd.h>
#include "libft.h"
#include "minishell.h"

extern char	**environ;

void	init_minishell(t_minishell *ms)
{
	int		i;
	t_map	env;
	char	*key;

	ft_map_init(&env, 0);
	*ms = (t_minishell){0, 0};
	i = -1;
	while(environ[++i])
	{
		if (!ft_strncmp("USER=", environ[i], 5))
			ms->user = ft_strdup(environ[i] + 5);
		else if (!ft_strncmp("PATH=", environ[i], 5))
			ms->path = ft_strdup(environ[i] + 5);
		key = ft_strsub(environ[i], 0, ft_strchr(environ[i], '=') - environ[i]);
		ft_map_insert(&env, (uint8_t*)key, key);
		ft_printf("%s\n", ft_map_get(&env, (uint8_t*)key));
		//free(key);
	}
}

int	main(int argc, char** argv)
{
	char *line;
	int ret;
	t_minishell ms;
	pid_t pid;

	init_minishell(&ms);
	line = NULL;
	ft_printf("%s) ", ms.user);
	(void)argc;
	while (1)
	{
		ret = get_next_line(0, &line);
		if (!ft_strncmp("path", line, 4))
			ft_printf("PATH=%s\n", ms.path);
		else if (!ft_strncmp("exit", line, 4))
			exit(1);
		else if (!ft_strncmp("fork", line, 4))
		{
			pid = fork();
			if (pid == 0)
			{
				lseek(0, 0, SEEK_END);
				execv("/bin/cat", argv);
				printf("Failed to execute command\n");
			}
			else
				waitpid(pid, 0, 0);
		}
		ft_printf("%s) ", ms.user);
		ft_memdel((void**)&line);
	}
	return (0);
}
