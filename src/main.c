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
	int			i;
	t_envvar	*var;

	ft_map_init(&ms->env, 0);
	i = -1;
	while(environ[++i])
	{
		var = malloc(sizeof(t_envvar));
		var->name = ft_strdup(environ[i]);
		var->value = ft_strchr(var->name, '=');
		*(var->value) = '\0';
		var->value += 1;
		ft_map_insert(&ms->env, var->name, var);
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
	ft_printf("%s) ", ((t_envvar*)ft_map_get(&ms.env, "USER"))->value);
	(void)argc;
	while (1)
	{
		ret = get_next_line(0, &line);
		if (!ft_strncmp("exit", line, 4))
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
		ft_printf("%s) ", ((t_envvar*)ft_map_get(&ms.env, "USER"))->value);
		ft_memdel((void**)&line);
	}
	return (0);
}
